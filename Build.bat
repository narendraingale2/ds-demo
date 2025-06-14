cl.exe /c /EHsc OGL.c Model.c Scene1.c Shape.c Texture.c Utility.c 
rc.exe OGL.rc
link.exe OGL.obj Model.obj Scene1.obj Shape.obj Texture.obj Utility.obj OGL.res user32.lib gdi32.lib /SUBSYSTEM:WINDOWS
