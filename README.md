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

## git修改commit

git使用amend选项提供了最后一次commit的反悔。但是对于历史提交呢，就必须使用rebase了。

git rebase -i HEAD~3 //修改当前版本的倒数第三次状态。
如果修改哪个就把哪行的pick改成edit,然后退出。git log查看最后一次提交变成修改的那个，再git commit --amend来对commit进行修改。修改完了之后，要回来，使用git rebase --continue

git rebase -i HEAD^^^合并最后三次提交，将pick改为s,修改git commit内容为一个，OK
