// Win32 Headers
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>

// OpenGl realated header files
#include<gl/GL.h>
#include<gl/GLU.h>

//custome header files
#include "OGL.h"
#include "Scene1.h"
#include "POINTS.h"
#include "utility.h"

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

// openGl related libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
//#define DEV_MODE 
//#define NO_SOUND

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// global variable declarations
BOOL gbFullScreen = FALSE;
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

// varaibles related to file I/O
char gszLogFileName[] = "Log.txt";
FILE *gpFile = NULL;

// Active window related variables
BOOL gbActiveWindow = FALSE;

// Exit key press related
BOOL gbEscapKeyIsPressed = FALSE;
BOOL gbRotateBoy = FALSE;
BOOL gbMoonDisplay = FALSE;
BOOL gbShowHouse = TRUE;
BOOL gbShowModel = FALSE;
BOOL gbShowGirl = FALSE;
BOOL showCTree = TRUE;
BOOL showCoTree = FALSE;
BOOL gbShowWater = FALSE;
BOOL rendering_scene1 = TRUE;
BOOL complete_scene1 = FALSE;
BOOL rendering_scene2 = FALSE;
BOOL moving_cam_completed_scene2 = FALSE;

// Opengl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Texture related global variables
GLuint texture_night_bg;
GLuint texture_moon;
GLuint texture_eye;
GLuint texture_mouth;
GLuint texture_head;
GLuint texture_hair;
GLuint texture_shirt;
GLuint texture_face;
GLuint texture_full_boy;
GLuint texture_girl_shirt;
GLuint texture_girl_leg;
GLuint texture_girl_left_hand;
GLuint texture_colured_tree;
GLuint texture_coco_tree;
GLuint texture_water;
GLuint texture_ground;
GLuint texture_inner_wall;
GLuint texture_eye_closing;
GLuint texture_wall_stone;

GLUquadric *quadric = NULL;

// camera related variabls
GLfloat cameraZ = 5.0f;

// Light related variables 
GLfloat moonLinghtAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat moonLightDifuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat moonLightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat moonLightPoistion[] = {-1.0f, -1.0f, -1.0f, 1.0f};

GLfloat waterLightAmbient[] = { 0.05f, 0.05f, 0.1f, 1.0f };
GLfloat waterLightDefuse[] = { 0.2f, 0.2f, 0.3f, 1.0f };
GLfloat waterLightAmbientSpecular[] = { 0.8f, 0.8f, 1.0f, 1.0f };
GLfloat watermatSpecular[] = { 0.8f, 0.8f, 1.0f, 1.0f };
GLfloat waterLightPosition[] = { 0.0f, 10.0f, 10.0f, 1.0f };
GLfloat matEmission[] = { 0.0f, 0.0f, 0.05f, 1.0f };
GLfloat watermatShininess[] = { 100.0f };

BOOL bLight = FALSE;

// points related variable
point_t point_vertices[800];

// Roatate boy model
GLfloat boyAngle = 0.0f;
GLfloat points[45][45][3];
int wiggle_count = 0; 
int animateEyeCnt = 0;
GLfloat hold;    
GLfloat xrot=0.0f;
GLfloat yrot=0.0f;
GLfloat zrot=0.0f;
GLfloat xLook = 5.0f;
GLfloat yLook = 4.05f;
GLfloat zLook = -13.4f;
GLfloat xLookAt = 5.0f;
GLfloat yLookAt = 4.0f;
GLfloat zLookAt = -14.0f;
GLfloat location[16];
GLfloat girl_walk_z = -3.0f;
GLfloat girl_walk_y = -1.1f;
BOOL startMovingLooAt = FALSE;
BOOL animateEye = TRUE;
BOOL rotate_left = TRUE;
int rotate_leg = 0;
BOOL renderScene3 = FALSE;
int wait_camera = 0;
GLfloat handAnimation = 0.0f;
BOOL animateLeft = FALSE;


// EntryPoint Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	// Function declarations
	int initialize(void);
	void resize(int, int);
	void update(void);
	void uninitialize(void);
	void display(void);
	void toggleFullScreen(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR06");
	BOOL bDone = FALSE;

	// code
	// Create log file
	gpFile = fopen(gszLogFileName, "w");
	
	if(gpFile == NULL)
	{
		MessageBox(NULL, "Failed to open log file", "Error", MB_OK);
		exit(0);
	}

	fprintf(gpFile, "Program started successfully...\n");
	fprintf(gpFile, "Initializing class...\n");
	// Window class initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	fprintf(gpFile, "Initialization completed...\n");
	// Registration of window class
	RegisterClassEx(&wndclass);
	fprintf(gpFile, "Registration completed...\n");

	// Create Window
	fprintf(gpFile, "Creating window...\n");
	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName, 
		TEXT("Narendra Suresh Ingale"), 
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		WIN_WIDTH, 
		WIN_HEIGHT, 
		NULL, 
		NULL, 
		hInstance, 
		NULL);

	ghwnd = hwnd;

	// Show window
	ShowWindow(hwnd, iCmdShow);

	// Paint the background of the window
	UpdateWindow(hwnd);

	
	// initalize window
	int result = initialize();

	if(result != 0)
	{
		fprintf(gpFile, "Intializaton failed...\n");
		DestroyWindow(hwnd);
		hwnd = NULL;
	}
	else
	{
		fprintf(gpFile, "Initialization completed successfully...\n");
	}

	// Set this window as forground and active window
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	toggleFullScreen();
	#ifndef NO_SOUND
		PlaySound(TEXT("audio\\chandoba_audio.wav"), NULL, SND_FILENAME |SND_ASYNC );
	#endif

	// Game Loop
	while(bDone == FALSE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}
		}
		else
		{
			if(gbActiveWindow == TRUE)
			{
				if(gbEscapKeyIsPressed == TRUE)
				{
					bDone = TRUE;
				}
				// Render
				display();

				// Update
				update();
			}
		}
	}

	uninitialize();

	return((int)msg.wParam);
}

// callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize();
	// variable declarations

	// code
	switch (iMsg)
	{
	
	case WM_CREATE:
		fprintf(gpFile, "Received message WM_CREATE...\n");
		fprintf(gpFile, "Intialization of wpPrev....\n");
		ZeroMemory((void*)&wpPrev, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT);
		fprintf(gpFile, "wpPrev initializaton completed....\n");
		break;
	case WM_SETFOCUS:
		gbActiveWindow = TRUE;
		break;
	case WM_KILLFOCUS:
		gbActiveWindow = FALSE;
		break;
	case WM_ERASEBKGND:
		return(0);
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_ESCAPE: 
				gbEscapKeyIsPressed = TRUE;
				break;
			case VK_UP:
				yLookAt = yLookAt + 0.01f;
				fprintf(gpFile, "yLookAt = %f\n", yLookAt);
				break;
			case VK_DOWN:
				yLookAt = yLookAt - 0.01f;
				fprintf(gpFile, "yLookAt = %f\n", yLookAt);
				break;
			case VK_LEFT:
				xLookAt = xLookAt - 0.01f;
				fprintf(gpFile, "xLookAt = %f\n", xLookAt);
				break;
			case VK_RIGHT:
				xLookAt = xLookAt + 0.01f;
				fprintf(gpFile, "xLookAt = %f\n", xLookAt);
				break;
			case VK_OEM_PLUS:
				zLookAt = zLookAt + 0.01f;
				fprintf(gpFile, "zLookAt = %f\n", zLookAt);
				break;
			case VK_OEM_MINUS:
				zLookAt = zLookAt - 0.01f;
				fprintf(gpFile, "zLookAt = %f\n", zLookAt);
				break;
			default:
				break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
			case 'f':
			case 'F':
				if(gbFullScreen == FALSE)
				{
					toggleFullScreen();	
					gbFullScreen = TRUE;
				}
				else
				{
					toggleFullScreen();
					gbFullScreen = FALSE;
				}
				break;
			case 'g':
			case 'G':
				if(gbShowGirl == FALSE)
				{
					gbShowGirl = TRUE;
				}
				else
				{
					gbShowGirl = FALSE;
				}
				break;
			case 's':
			case 'S':
				if(gbShowModel == FALSE)
				{
					gbShowModel = TRUE;
				}
				else
				{
					gbShowModel = FALSE;
				}
				break;
			case 'h':
			case 'H':
				if(gbShowHouse == FALSE)
				{
					gbShowHouse = TRUE;
				}
				else
					gbShowHouse = FALSE;
				break;
			case 'm':
			case 'M':
				if(gbMoonDisplay == FALSE)
				{
					gbMoonDisplay = TRUE;
				}
				else
					gbMoonDisplay = FALSE;
				break;
			case 'R':
			case 'r':
				if(gbRotateBoy == FALSE)
				{
					gbRotateBoy = TRUE;
				}
				else
					gbRotateBoy = FALSE;
				break;
			case 't':
			case 'T':
				if(showCTree == FALSE)
				{
					showCTree = TRUE;
				}
				else
					showCTree = FALSE;
				break;
			case 'u':
			case 'U':
				if(showCoTree == FALSE)
				{
					showCoTree = TRUE;
				}
				else
					showCoTree = FALSE;
				break;
			case 'w':
				if(gbShowWater == FALSE)
					gbShowWater = TRUE;
				else
					gbShowWater = FALSE;
				break;
			case 'x':
					xLook = xLook + 0.01;
					fprintf(gpFile, "xLook = %f\n", xLook);
				break;
			case 'X':
					xLook = xLook - 0.01;
					fprintf(gpFile, "xLook = %f\n", xLook);
				break;
			case 'y':
					yLook = yLook + 0.01;
					fprintf(gpFile, "yLook = %f\n", yLook);
				break;
			case 'Y':
					yLook = yLook - 0.01;
					fprintf(gpFile, "yLook = %f\n", yLook);
				break;
			case 'z':
					zLook = zLook + 0.01;
					fprintf(gpFile, "zLook = %f\n", zLook);
				break;
			case 'Z':
					zLook = zLook - 0.01;
					fprintf(gpFile, "zLook = %f\n", zLook);
				break;
			default:
				break;
		}
		break;
	case WM_CLOSE:
		uninitialize();
	case WM_DESTROY: 
		PostQuitMessage(0);
		break;
	default: 
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void toggleFullScreen(void)
{
	// Variable declarations
	MONITORINFO mi;
	
	// code
	dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

	if(dwStyle & WS_OVERLAPPEDWINDOW)
	{
		
		ZeroMemory((void*) &mi, sizeof(MONITORINFO));
		mi.cbSize = sizeof(MONITORINFO);
		if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
		{
			SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
			SetWindowPos(ghwnd, 
				HWND_TOP, 
				mi.rcMonitor.left, 
				mi.rcMonitor.top, 
				mi.rcMonitor.right - mi.rcMonitor.left, 
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOZORDER | SWP_FRAMECHANGED);
			
		}
		ShowCursor(FALSE);
	}
	else
	{

		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}


}

int initialize(void)
{
	// Function declarations
	void printOpenGlInfo();
	void resize(int, int);

	// varialbe declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFromatIndex = 0;

	// code
	ZeroMemory((void *)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	// get DC
	ghdc = GetDC(ghwnd);

	if(ghdc == NULL)
	{
		fprintf(gpFile, "Get DC function failed\n");
		return(-1);
	}


	// Get matching pixel format index using HDS and PFD
	iPixelFromatIndex = ChoosePixelFormat(ghdc, &pfd);
	if(iPixelFromatIndex == 0)
	{
		fprintf(gpFile, "ChoosePixelFormat failed...\n");
		return(-2);
	}

	// set the pixel format of found index 
	if(SetPixelFormat(ghdc, iPixelFromatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "SetPixelFormat function failed.. \n");
		return(-3);
	}

	// Create rendering contexet using HDC, PFD and chosen pixelformatindex
	ghrc = wglCreateContext(ghdc);
	if(ghrc == NULL)
	{
		fprintf(gpFile, "wglCreateContext function failed...\n");
		return(-4);
	}

	// Make this rendering context as current context
	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent function failed...\n");
		return(-5);
	}

	// print openGl info
	printOpenGlInfo();

	// Depth related function calls
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// from here onwords opengl code starts
	// tell opengl to choose the colour to clear the screen
	glClearColor(0.02f, 0.02f, 0.08f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// LoadTexture

	/*if(loadGLTexture(&texture_moon, MAKEINTRESOURCE(IDBITMAP_MOON)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for moon texture\n");
		return(-7);
	}*/

	/*if(loadGLTexture(&texture_eye, MAKEINTRESOURCE(IDBITMAP_EYE)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for eye texture\n");
		return(-7);
	}*/

	if(loadGLTexture(&texture_mouth, MAKEINTRESOURCE(IDBITMAP_MOUTH)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for mouth texture\n");
		return(-7);
	}

	if(loadGLTexture(&texture_hair, MAKEINTRESOURCE(IDBITMAP_HAIR)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for hair texuter\n");
		return(-7);
	}

	if(loadGLTexture(&texture_shirt, MAKEINTRESOURCE(IDBITMAP_SHIRT)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for hair texuter\n");
		return(-7);
	}

	if(loadGLTexture(&texture_face, MAKEINTRESOURCE(IDBITMAP_FACE)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for hair texuter\n");
		return(-7);
	}

	// Loading Images to create texture
	stbi_set_flip_vertically_on_load(TRUE);

	if(loadPNGTexture(&texture_full_boy, "texture-images\\girl_face1.png") == FALSE)
	{
		fprintf(gpFile, "PNG structure loading fialed for girl face");
		return(-8);

	}

	if(loadPNGTexture(&texture_girl_shirt, "texture-images\\girl_shirt.png") == FALSE)
	{
		fprintf(gpFile, "PNG structure loading fialed for girl face");
		return(-8);

	}


	if(loadPNGTexture(&texture_girl_leg, "texture-images\\legs.png") == FALSE)
	{
		fprintf(gpFile, "Legs texture image failed ");
		return(-8);

	}

	if(loadPNGTexture(&texture_girl_left_hand, "texture-images\\hand_left.png") == FALSE)
	{
		fprintf(gpFile, "hand texture image failed ");
		return(-8);

	}
	
	if(loadPNGTexture(&texture_eye, "texture-images\\eye-new.png") == FALSE)
	{
		fprintf(gpFile, "eye texture image failed ");
		return(-8);

	}

	if(loadPNGTexture(&texture_colured_tree, "texture-images\\colour-tree.png") == FALSE)
	{
		fprintf(gpFile, "Colured tree");
		return(-9);
	}

	if(loadPNGTexture(&texture_coco_tree, "texture-images\\coco-tree.png") == FALSE)
	{
		fprintf(gpFile, "Failed to lead coco tree");
		return(-9);
	}

	if(loadPNGTexture(&texture_water, "texture-images\\water.png") == FALSE)
	{
		fprintf(gpFile, "Failed to load water texture");
		return(-9);
	}

	if(loadPNGTexture(&texture_moon, "texture-images\\moon-png.png") == FALSE)
	{
		fprintf(gpFile, "Failed to load moon texture");
		return(-10);
	}

	if(loadPNGTexture(&texture_ground, "texture-images\\ground.png") == FALSE)
	{
		fprintf(gpFile, "Failed to ground");
		return(-10);
	}
	if(loadPNGTexture(&texture_inner_wall, "texture-images\\inner-wall.PNG") == FALSE)
	{
		fprintf(gpFile, "Failed load inner wall");
		return(-10);
	}
	
	if(loadPNGTexture(&texture_eye_closing, "texture-images\\girl_face_closing.png") == FALSE)
	{
		fprintf(gpFile, "Failed load inner wall");
		return(-10);
	}

	if(loadPNGTexture(&texture_wall_stone, "texture-images\\stone-wall.png") == FALSE)
	{
		fprintf(gpFile, "Failed load inner wall");
		return(-10);
	}
	// enable texturing
	glEnable(GL_TEXTURE_2D);

	// Initialize quadric
	quadric = gluNewQuadric();

	for(int i = 0; i<800; i++)	
	{
		point_vertices[i].x = getRandomCoord(-3.0f, 3.0f);
		point_vertices[i].y = getRandomCoord(1.0f, 2.0f);
		point_vertices[i].z = getRandomCoord(-8.0f, -3.0f);
		float color = getRandomCoord(05, 0.1);
		point_vertices[i].c.red = color;
		point_vertices[i].c.blue = color;
		point_vertices[i].c.red = color;
		float size = getRandomCoord(1.0f, 3.0f);
		point_vertices[i].size = size;
	}

	for(int x = 0; x < 44; x++)
	{
		for(int y=0; y<45; y++)
		{
			points[x][y][0] = (float)((x/5.0)-5.0f);
			points[x][y][1] = (float)((y/5.0)-4.5f);
			points[x][y][2] = (float)(sin((((x/5.0f)*40.0f)/360.0f)*3.141592654*2.0f))*0.2;
		}
	}

	//warm up resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	return(0);
}

void printOpenGlInfo()
{
	fprintf(gpFile, "========= OpenGL information =============\n");
	fprintf(gpFile, "OpneGl Vendor  : %s\n",glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGlRendorer : %s\n",glGetString(GL_RENDERER));
	fprintf(gpFile, "OpneGl Version : %s\n",glGetString(GL_VERSION));
	fprintf(gpFile, "==========================================\n");
}

BOOL loadGLTexture(GLuint* texture, TCHAR ImageResourceID[])
{
	// variable declarations
	HBITMAP hBitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;

	// code 
	// load the bitmap as image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL),  ImageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION );
	if(hBitmap)
	{
		fprintf(gpFile, "bitmap image laoded\n");
		bResult = TRUE;

		// Get btimap structre from the laoded bitmap image
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		fprintf(gpFile, "Get Object successful\n");

		// generate opengl texture objct
		glGenTextures(1, texture);
		fprintf(gpFile, "Texture has been generated\n");

		// generate opengl texture object
		glBindTexture(GL_TEXTURE_2D, *texture);

		// unpack the image in memorey for faster loading
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		// tell opengl engine to mipmapping and hot compy pixel
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		glBindTexture(GL_TEXTURE_2D, 0);
		DeleteObject(hBitmap);
		hBitmap = NULL;
		fprintf(gpFile, "Texture has been loaded\n");
	}
	fprintf(gpFile, "Before return bResult = %d\n", bResult);
	return bResult;
}

BOOL loadPNGTexture(GLuint* texture, const char *path) {

	// Local Variable Declarations
	int width = 0, height = 0, bitDepth = 0;

	// Code
	unsigned char* texData = stbi_load(path, &width, &height, &bitDepth, STBI_rgb_alpha);
	if (!texData) {

		fprintf(gpFile, "Failed to load image!\n");
		return FALSE;
	}
	
	glGenTextures(1, texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glBindTexture(GL_TEXTURE_2D, *texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (bitDepth == 3) 
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)texData);
	}
	else if (bitDepth == 4) 
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)texData);
	}
	else 
	{

		fprintf(gpFile, "Texture initialize image invalid!\n");
		return FALSE;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

	texData = NULL;

	return TRUE;
}

void resize(int width, int height)
{
	// code
	
	// if height by accident to less than zero then set height to 1
	if(height <= 0)
	{
		height = 1;
	}

	// set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// Set projection mode
	glMatrixMode(GL_PROJECTION);

	// Set to IdentityMetrics
	glLoadIdentity();

	// do prespective projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat) height, 0.1f, 100.0f);
	// fovy
	// aspect ratio
	// near
	// far

}

void display(void)
{
	// code
	
	// clear open gl buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Set metrics to model view mode
	glMatrixMode(GL_MODELVIEW);

	// set identity metrics
	glLoadIdentity();
		
    glTranslatef(0.0f, 0.0f, -8.0f);

	#ifndef DEV_MODE
	gluLookAt(xLook, yLook, zLook, 
			xLookAt, yLookAt, zLookAt, 
			0.0f, 1.0f, 0.0f);
	
	if(moving_cam_completed_scene2 == FALSE)
	{
	

		glPushMatrix();
		if(gbShowModel == TRUE)
		{
			if(gbRotateBoy == TRUE)
				glRotatef(90, 0.0f, 1.0f, 0.0f);
		 	drawBoyModel();

		}

		if(gbShowGirl == TRUE)
		{
			glPushMatrix();
			glScalef(0.4f, 0.2, 0.4f);
			glTranslatef(-8.5f, -4.0f, 0.0f);
			drawGirl(TRUE);
			glPopMatrix();
		}

		if(showCTree == TRUE)
		{
			glPushMatrix();
				drawScene1();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(4.0f, 0.5f, 0.0f);
				glScalef(4.0, 6.0f, 0.0f);
				drawColoredTree();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-5.0f, 0.5f, 0.0f);
				glScalef(4.0, 6.0f, 0.0f);
				drawCocoTree();
			glPopMatrix();

		}

		if(gbShowWater == TRUE)
		{
			glPushMatrix();
				drawWater();
			glPopMatrix();
		}

		if(gbMoonDisplay == TRUE)
		{
			glPushMatrix();
			drawScene1();
			glPopMatrix();
		}

		if(gbShowHouse == TRUE)
		{
			glPushMatrix();
				glTranslatef(0.0f, -2.0f, 0.0f);
				glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
				glScalef(8.0f, 2.0f, 1.0f);
				drawGround();
			glPopMatrix();
			glPushMatrix();
				glScalef(0.5f, 0.5f, 1.0f);
				// glRotatef(-180, 0.0f, 1.0f, 0.0f);
				glTranslatef(0.0f, -2.4f, 0.0f);
				drawHouse();
			glPopMatrix();
		}
		glPopMatrix();
	}

	if(moving_cam_completed_scene2 && rendering_scene2 == TRUE)
	{
		glLoadIdentity();
		glEnable(GL_BLEND);
		drawScene2();
	}
	if(renderScene3 == TRUE)
	{
	#endif
 		drawScene3();
	#ifndef DEV_MODE
	}
	#endif
	// swap the buffers
	SwapBuffers(ghdc);

}

void update(void)
{
	int x, y;
	// code
	if(cameraZ >= 0)
	{
		cameraZ = cameraZ - 0.01;
	}

	boyAngle = boyAngle + 0.5;

	xrot = xrot + 0.003f;
	yrot = yrot + 0.002f;
	zrot = zrot + 0.004f;

	if(animateEye == TRUE)
	{
		animateEyeCnt++;
		if(animateEyeCnt > 100)
		{
			animateEye = FALSE;
			animateEyeCnt = 0;
		}
	}
	else
	{
		animateEyeCnt++;
		if(animateEyeCnt > 10)
		{
			animateEye = TRUE;
			animateEyeCnt = 0;
		}
	}

	if(rotate_left == TRUE)
	{
		
		rotate_leg++;
		if(rotate_leg > 100)
		{
			rotate_left = FALSE;
			rotate_leg = 0;
		}
	}
	else
	{

		rotate_leg++;
		if(rotate_leg > 100)
		{
			rotate_left = TRUE;
			rotate_leg = 0;
		}
	}

	
	if(wiggle_count == 2)
	{
		for(y = 0; y<45; y++)
		{
			hold = points[0][y][2];
			for( x=0; x<44; x++)
			{
				points[x][y][2] = points[x+1][y][2];

			}
			points[44][y][2]=hold;

		}
		wiggle_count = 0;
	}
	wiggle_count++;

	if(rendering_scene1 == TRUE)
	{
		if(zLook<=-1.0f)
			zLook = zLook + 0.02;
		else if (yLook>= 0.5f)
			yLook = yLook - 0.02;
		else if ( xLook >=0.0f)
		{
			xLook = xLook - 0.02;
			fprintf(gpFile, "values fo xLook %f\n", xLook);
		}
		else 
		{

			fprintf(gpFile, "camera rolling finished until tree x = %f, y = %f, z= %f\n", xLook, yLook, zLook);
			rendering_scene1 = FALSE;
			startMovingLooAt = TRUE;
		}
	}

	if(startMovingLooAt == TRUE)
	{
			zLook = 0.0f;
			yLook = 0.0f;
			xLook = 0.0f;

		BOOL final_reset_require = TRUE; 
		if(zLookAt<=-1.0f)
		{
			final_reset_require = FALSE;
			zLookAt = zLookAt + 0.05;
		}
		
		if (yLookAt>= 0.0f)
		{

			yLookAt = yLookAt - 0.05;
			final_reset_require = FALSE;
		}

		if ( xLookAt >=0.0f)
		{
			xLookAt = xLookAt - 0.05;
			final_reset_require = FALSE;
			fprintf(gpFile, "values fo xLook %f\n", xLook);
		}

		if(final_reset_require == TRUE)
		{
			xLookAt = 0.0f;
			yLookAt = 0.0f;
			zLookAt = -1.0f;
			startMovingLooAt = FALSE;
			rendering_scene1 = FALSE;
			rendering_scene2 = FALSE;
			complete_scene1 = TRUE;
			fprintf(gpFile, "final reset done... zLook =  %f", zLook);
		}
	}

	// Camera still for certain second
	if(complete_scene1 == TRUE && rendering_scene2 == FALSE)
	{
		if(wait_camera <= 1000)
		{
			wait_camera++;
			fprintf(gpFile, "Camera is on wait ...\n");
		}
		else
		{
			fprintf(gpFile, "Camera started moving ");
			rendering_scene2 = TRUE;
		}

	}
	//else
	//	rendering_scene2 = TRUE;
	
	if(rendering_scene2 == TRUE && complete_scene1 == TRUE)
	{
		// starting camera to move inside house
		zLookAt = -6.0f;
		if(zLook >= -5.7f && moving_cam_completed_scene2 == FALSE)
		{
			zLook = zLook - 0.01;
			if(zLook <= 1.0f)
				yLookAt = 0.035;

		}
		else 
		{
			moving_cam_completed_scene2 = TRUE;
			xLook = 0.0f;
			yLook = 0.0f;
			zLook = 0.0f;
			xLookAt = 0.0f;
			yLookAt = 0.0f;
			zLookAt = -1.0f;

			fprintf(gpFile, "Camera reset completed inside house\n");


			fprintf(gpFile, "completed camera movement for scene 2...\n");

			if(girl_walk_z <= 9.0f)
			{

				girl_walk_z = girl_walk_z + 0.01f;
				fprintf(gpFile, "Girl walk is in progress\n");
			}
			else 
			{
				fprintf(gpFile, "Girl walk complted...\n");

				renderScene3 = TRUE;
				rendering_scene2 = FALSE;
				xLook = 0.0f;
				yLook = 0.0f;
				zLook = 0.0f;
				xLookAt = 0.0f;
				yLookAt = 0.0f;
				zLookAt = -1.0f;

			}
		}


	}
}

void uninitialize(void)
{
	// function declarations
	void toggleFullScreen(void);

	// code
	// if user is exiting in full screen then restore full screen back to normal
	if(gbFullScreen == TRUE)
	{
		toggleFullScreen();
		gbFullScreen = FALSE;
	}

	// make HDC as current context by releasing rendering context as current context
	if(wglGetCurrentContext()==ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// delete the rendering context
	if(ghrc)
	{	
		wglDeleteContext(ghrc);
		ghrc = NULL;

	}

	// release the dc
	if(ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
	}

	// Destroy window
	if(ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// close the file
	if(gpFile)
	{
		fprintf(gpFile, "Program terminated successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}

}

void keyboard(unsigned cha)
{

}