- 无论是TCP还是UDP，阻塞函数在使用非阻塞的设置后。都会立即返回-1.我们可以使用
WSAGetLastError也获取其状态。  
- 在WSAGetLastError()获取到WSAEWOULDBLOCK时，还可以使用select()进一步操作.  
其中select操作时要根据不同的阻塞函数选择不同的参数。而且设置超时的时间一定要有微  
秒的值（要不会产生意想不到的结果）。

           fd_set rfds;
           struct timeval tv;
           int retval;
 
           /* Watch stdin (fd 0) to see when it has input. */
           FD_ZERO(&rfds);
           FD_SET(0, &rfds);
 
           /* Wait up to five seconds. */
           tv.tv_sec = 5;
           tv.tv_usec = 0;
 
           /*注意这里的二三四参数，不同的阻塞函数对应不同的*/
           retval = select(1, &rfds, NULL, NULL, &tv);
           /* Don’t rely on the value of tv now! */
 
           if (retval == -1)
               perror("select()");
           else if (retval)
               printf("Data is available now.\n");
               /* FD_ISSET(0, &rfds) will be true. */
           else
               printf("No data within five seconds.\n");