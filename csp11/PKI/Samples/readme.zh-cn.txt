======================================================
    目录 & 说明
======================================================

PKCS11     基于PKCS#11接口的示例程序
CryptoAPI  基于CryptoAPI接口的示例程序
CNG        基于CNG接口的示例程序


注：除Microsoft Visual C++外，你需要另外安装
Microsoft Platform SDK，并把SDK安装目录中的
include目录和lib目录分别放置在VC开发环境选项
（对于VC6来说，是菜单中Tools->Options...弹出的
对话框中的Directories页）中的目录（include）
和库（lib）中VC++的路径之前才能够正确编译链接运
行。

CNG示例不能使用VC6编译，最好使用VS2008以上的版本。