#vs bat
@echo off

rem set environment

call "d:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat" > log.txt

rem solution

rem devenv d:\test\solution\solution.sln /rebuild "release|win32"


rem project, sometimes the project will build solution also,so use msbuild is better

devenv "d:\test\solution\mfc\mfc.vcxproj" /build "debug|win32" >> log.txt && type log.txt

rem use msbuild e.g.

<font color=#FF7F50>msbuild d:\test\solution\console2\console2.vcxproj /t:rebuild /p:Configuration=Release /p:Platform=x64</font>

msbuild d:\test\solution\mfc\mfc.sln /t:rebuild /p:Configuration=Release /p:Platform=x64

makensis "d:\work\haiguanpingce\xxx.nsi"

pause

#git command

## -u只操作加入版本库文件，如果.gitignore写的足够好，就不用此参数了

git add . -u

## git对大小写敏感

git config core.ignorecase false
