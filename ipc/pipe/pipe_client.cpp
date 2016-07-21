#include <stdio.h>  
#include <windows.h>  

#define PIPE_NAME "\\\\.\\pipe\\wh"  

HANDLE g_hPipe = INVALID_HANDLE_VALUE;  

int main()  
{  
	char buffer[1024];  
	DWORD ReadNum;  

	printf("test client.\n");  

	g_hPipe = CreateFile(PIPE_NAME, GENERIC_READ | GENERIC_WRITE,   
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	if (g_hPipe == INVALID_HANDLE_VALUE)  
	{  
		printf("Connect pipe failed!\n");  
		goto out;  
	}  
	printf("Connected.\n");  

	while(1)  
	{  
		if(ReadFile(g_hPipe, buffer, sizeof(buffer), &ReadNum, NULL) == FALSE)  
		{  
			break;  
		}  
		buffer[ReadNum] = 0;  
		printf("%s\n", buffer);  
	}  
out:  
	printf("Close pipe.\n");  
	CloseHandle(g_hPipe);  
	system("pause");  
	return 0;  
}  