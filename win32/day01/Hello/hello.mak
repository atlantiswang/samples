HELLO:CLEAN
	CL.EXE /C Hello.c
	RC.EXE Hello.rc
	LINK.EXE Hello.obj Hello.res user32.lib

CLEAN:
	del*.obj
	del*.res
	del*.exe