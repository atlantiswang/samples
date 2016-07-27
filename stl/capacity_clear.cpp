/*
 *  vector 容器内存的释放
 *  容器的size与capacity反映的是内容的大小和容量的大小。有些容器在erase.clear后虽然size为0，但实际还是占有一定空间的内存
 *  就可以通过capacity看到.造成内存的浪费。这时候就可以通过swap方法来完全释放，让capacity也变成0
 *  note: 不是所有的容器clear都不会释放，使用时要看清容器类型
 */

#include <stdio.h>
#include <vector>

using std::vector;

int main()
{
	vector<int> temp;
	for (int i = 0 ; i < 10; i++)
	{
		temp.push_back(i);
	}
	printf("capacity:%d|size:%d\n", temp.capacity(), temp.size());
#if 1
	//temp.clear();
	temp.erase(temp.begin());
#else
	vector<int>().swap(temp);
#endif
	printf("capacity:%d|size:%d\n", temp.capacity(), temp.size());
	
}