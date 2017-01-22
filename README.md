# vs
* vs bat
 @echo off  
 rem set environment  
 %comspec% /k ""d:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"" x86 > log.txt  
 rem solution  
 rem devenv d:\test\solution\solution.sln /rebuild "release|win32"  
 rem project, sometimes the project will build solution also,so use msbuild is better  
 devenv "d:\test\solution\mfc\mfc.vcxproj" /build "debug|win32" >> log.txt && type log.txt  
 rem use msbuild e.g.  
 msbuild d:\test\solution\console2\console2.vcxproj /t:rebuild /p:Configuration=Release /p:Platform=x64  
 msbuild d:\test\solution\mfc\mfc.sln /t:rebuild /p:Configuration=Release /p:Platform=x64  
 makensis "d:\work\haiguanpingce\xxx.nsi"  
 pause  

* vs debug  
  remote debug:  
  Remote Command: path  
  Working Directory: path without programm name  
  Remote Server Name: computer name or IP  
  when a thread is debug, others also run slowly.  

* vs  shortcutkey  
  函数提示：ctrl+shift+space  
  找到对应的.h/.cpp文件：Alt + O  
  
* makefile  
  Build Command Line: nmake
  Rebuild Command Line: 
  Clean Command Line:
  Output:


# qt
添加qt依赖库： windeployqt xxx.exe  
qt下载： www.qt.io/download-open-source/

# git

git的分支不是用来做定制的。而是用来帮助协同工作的。版本定制请在代码中使用宏开关。这样才能更高效地利用git且减少工作量。
* git add
 git add -a 暂存 所有文件（增加，修改，删除）  
 git add -u 暂存修改和删除的文件  
 git add . 不包括已删除的文件  

* git对大小写敏感
 git config core.ignorecase false  

* git修改commit
 git使用amend选项提供了最后一次commit的反悔。但是对于历史提交呢，就必须使用rebase了。  
 git rebase -i HEAD~3 //修改当前版本的倒数第三次状态。如果修改哪个就把哪行的pick改成edit,然后退出。git log查看最后一次提交变成修改的那个，再git commit --amend来对commit进行修改。  
 修改完了之后，要回来，使用git rebase --continue  
 git rebase -i HEAD^^^合并最后三次提交，将pick改为s,修改git commit内容为一个，OK  
 ![](https://github.com/atlantiswang/picture/blob/master/rebase.png)  

* git下载远程分支
 git checkout --track origin/develop | git checkout -b develop origin/develop  
 git merge --no-ff branchname//this is a good habit  
 
# linux
mingw:（Minimalist GNU for Windows）是windows下的Linux环境，在bash中进入windows目录下，输入: /盘符

# boost
 boost库命令规则：libboost_atomic-vc100-mt-sgd-1_57  
 libboost:是否为静态库 bjam（b2）编译选项：link=static/shared  
 atomic:库的名字  --with-atomic  
 vc100:使用的编译器版本  --toolset=msvc-10.0  
 mt:线程类型 threading=multi  
 s: runtime类型 runtime-link=static  
 gd: debug or release debug/release  

# coded format BOM(FEFF)
UCS中有一个叫做"zero width no-break space"的编码：FEFF，此编码在UCS中是不存在的字符，我们使用它在开关来表明  
UCS的字节序，故FEFF是大端，FFFE是小端（微软一般就用小端）。而UTF-8没有字节，但也使用了BOM来表示此为UTF-8编码。  
FEFF的UTF-8编码为1110 1111（EF）1011 1011（BB） 1011 1111（BF）
即EFBBBF。

# windows
set 查看所有的环境变量  
set PATH=%PATH%;D:/test; 追加PATH项的值 
windows句柄： 
DuplicateHandle()  
driver & server programm

| #             | drvier        | server|
| ------------- | ------------- | ----- |
| 创建服务/驱动 | sc create xxx binPath= "xxx" | ----- |
| 启动服务/驱动 | sc start xxx  | ...   |
| 关闭服务/驱动 | sc stop  xxx  | ...   |
| 删除服务/驱动 | sc delete xxx | ...   |

# json

| type          | style         | note  |
| ------------- | ------------- | ----- |
| object        | {"key":value} | 值 可以做开头 |
| array         | [value1,value2]| 值 可以做开头 | 
| num           | 1 or 1.1      | 值  |
| string        | "string"      | 键、值 |
| logic value   | true or false | 值 |
| null          | null          | 值 |