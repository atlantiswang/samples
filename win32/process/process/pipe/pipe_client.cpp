#include <stdio.h>  
#include <windows.h>  

#define PIPE_NAME "\\\\.\\pipe\\wh"  

HANDLE g_hPipe = INVALID_HANDLE_VALUE;  

int main()  
{  
	char buffer[1024];  
	DWORD WriteNum;  

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
		scanf("%s", buffer);
		if(WriteFile(g_hPipe, "hello", strlen(buffer), &WriteNum, NULL) == FALSE)  
		{  
			break;  
		}
	}  
out:  
	printf("Close pipe.\n"); 
	DisconnectNamePipe(g_hPipe);
	CloseHandle(g_hPipe);  
	system("pause");  
	return 0;  
}  