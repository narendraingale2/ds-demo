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

// openGl related libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

// Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

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

// Opengl related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Texture related global variables
GLuint texture_night_bg;
GLuint texture_moon;

GLUquadric *quadric = NULL;

// camera related variabls
GLfloat cameraZ = 5.0f;

// points related variable
point_t point_vertices[800];

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

	// LoadTexture
	if(loadGLTexture(&texture_night_bg, MAKEINTRESOURCE(IDBITMAP_NIGHT_BG)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for lightbg\n");
		return(-6);
	}

	if(loadGLTexture(&texture_moon, MAKEINTRESOURCE(IDBITMAP_MOON)) == FALSE)
	{
		fprintf(gpFile, "loadtexture has been failed for moon texture\n");
		return(-7);
	}

	glEnable(GL_TEXTURE_2D);
	// Initialize quadric
	quadric = gluNewQuadric();
	// enable texturing

	for(int i = 0; i<800; i++)	
	{
		point_vertices[i].x = getRandomCoord(-3.0f, 3.0f);
		point_vertices[i].y = getRandomCoord(-2.0f, 2.0f);
		point_vertices[i].z = getRandomCoord(-8.0f, -3.0f);
		float color = getRandomCoord(05, 0.1);
		point_vertices[i].c.red = color;
		point_vertices[i].c.blue = color;
		point_vertices[i].c.red = color;
		float size = getRandomCoord(1.0f, 3.0f);
		point_vertices[i].size = size;
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

    glTranslatef(0.0f, 0.0f, -3.0f);
	
	drawScene1();

	// swap the buffers
	SwapBuffers(ghdc);

}

void update(void)
{
	// code
	if(cameraZ >= 0)
	{
		cameraZ = cameraZ - 0.01;
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