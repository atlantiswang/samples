/*
stl 不同的容器在不同的方式删除元素时，没有统一的写法，
需要总结一下

*/

int main()
{
	//1 把容器中所有值为X的对象都去掉。
	//如果是一个连接内存容器(vector\deque\string)。最好的方法是earse-remove惯用法
	vector<int> c;
	c.erase(remove(c.begin(), c.end(), 3), c.end());
	//这方法也适合于List,但list的成员函数remove更高效。
	//如果是标准关联窗口，解决的方法是调用erase();


	//2. 修改一下问题，不是删除每个特定值的物体，而是判断式badvalue(x)
	//对于序列容器，（vector string deque list）,我们要做的是使用remove_if
	//对于标准关联容器，使用如下方法
	for (;;)
	{
		if (badValue(*i))
			c.erase(i++);
		else
			++i;
	}

	//3 再次修改为需要将数据打印，关联容器好说，但序列容器（vector/string/ deque）就要修改为循环方式了
	//对一list 既可以用这种，也可以用上面的方法
	for (;;)
	{
		if (badValue(*i))
		{
			//Log
			//为什么这里不同？因为序列容器删除元素，不仅当前iterator失效，后面的所有
			//iterator都会失效。但返回值会返回一个我们需要的iterator。故采用这种方式
			i = c.erase(i);
		}
		else ++i;
	}

	/*
	为什么remove要与erase配合使用，是因为remove并不会真正删除元素，而是使用挤压的方式remove掉
	也就是说remove后容器的大小不会变。
	*/
}