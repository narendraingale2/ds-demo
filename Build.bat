cl.exe /c /EHsc OGL.c Model.c Scene1.c Shape.c Texture.c Utility.c boy.c
rc.exe OGL.rc
link.exe OGL.obj Model.obj Scene1.obj Shape.obj Texture.obj Utility.obj boy.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
