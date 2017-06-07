
COMMathps.dll: dlldata.obj COMMath_p.obj COMMath_i.obj
	link /dll /out:COMMathps.dll /def:COMMathps.def /entry:DllMain dlldata.obj COMMath_p.obj COMMath_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del COMMathps.dll
	@del COMMathps.lib
	@del COMMathps.exp
	@del dlldata.obj
	@del COMMath_p.obj
	@del COMMath_i.obj
