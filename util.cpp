/*
 * 使用goto语句进行错误判断
 * 这种方式适用于退出时需要进行清理工作,如果没有需要进行清理的内容，就可以直接使用return false结束
 * 初始化为true; 如果有错误就设置为false
 */


bool fun()
{
	//p初始化为true
	bool nRet = true;
	if(!fun1())
	{
		nRet = false;
		goto err;
	}
	if(!fun2())
	{
		nRet = false;
		goto err;
	}
err:
	return nRet;
	//清理工作
}