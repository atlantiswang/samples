

#include "stdio.h"
#include "../dllclass/dllclass.h"
#pragma comment(lib,"../lib/dllclass.lib")
int main()
{
	CMath math;
	int sum = math.Add(5,2);
	int sub = math.Sub(5,2);
	printf("sum=%d,sub=%d\n",sum,sub);
	return 0;
}
