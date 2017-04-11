1. 下载sqlite
	源码，动态库，工具
2. 编译sqlite
* 生成动态库
	将下载的sqlite.dll\sqlite.def放入文件夹中，打开 vs的命令行，输入LIB /DEF:sqlite3.def /machine:IX86
	就可以生.lib导入库，头文件可以从源码中获取
* 生成静态库
	将源码中的头文件与sqlite3.c文件导入VS dll工程，编译
	
3. 测试用例
// test1.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdlib.h>
#include "sqlite3.h"
int _tmain(int argc, _TCHAR* argv[])
{
    int rc;
    int i, nrows, ncols, tr;
    char *errmsg = NULL;
    char **results;
    
    sqlite3 *db = NULL;
    rc = sqlite3_open("demodb", &db);
    if (rc)
    {
        fprintf(stderr, "can't open db!\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    else
    {
        printf("db open successfully!\n");
    }
    sqlite3_get_table(db,"select * from clients;",&results,&nrows,&ncols,&errmsg);
    printf("DB has %d rows and %d cols\n\n",nrows,ncols);
    tr=(nrows+1)*ncols;
    for(i=0;i<tr;++i) //输出查询结果
    {
        printf("results[%d]= %s/n",i,results[i]); //此处可以自己定义输出格式，
    }
    sqlite3_free_table(results); //free 
    sqlite3_close(db);
    int a;
    scanf("%d",&a);//没有此行代码，运行窗口出现后会马山消失。
    return 0;
}