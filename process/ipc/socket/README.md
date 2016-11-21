###### 对于可读文件描述符集以下四种情况会导致置位:
- socket接收缓冲区中的数据量大于或等于当前缓冲区的低水位线.此时对于read操作不会被阻塞并且返回一个正值(读取的字节数).低水位线可以通过SO_RCVLOWAT选项设定，对于Tcp和Udp来说其默认值为1.
- socket连接的读端被关闭，如shutdown(socket, SHUT_RD)或者close(socket).对应底层此时会接到一个FIN包,read不会被阻塞但会返回0.代表读到socket末端.
- socket是一个监听socket并且有新连接等待.此时accept操作不会被阻塞.
- 发生socket错误.此时read操作会返回SOCKET_ERROR(-1).可以通过errno来获取具体错误信息.

###### 对于可写文件描述符集以下四种情况会导致置位:
- socket发送缓冲区中的可用缓冲大小大于或等于发送缓冲区中的低水位线并且满足以下条件之一
	- socket已连接
	- socket本身不要求连接，典型如Udp
	低水位线可以通过SO_SNDLOWAT选项设置.对于Tcp和Udp来说一般为2048.
- socket连接的写端被关闭，如shutdown(socket, SHUT_WR)或者close(socket).在一个已经被关闭写端的句柄上写数据会得到SIGPIPE的信号(errno).
- 一个非阻塞的connect操作连接成功 或者 connect操作失败.
- 发生socket错误.此时write操作会返回SOCKET_ERROR(-1).可以通过errno来获取具体错误信息.

###### 对于异常文件描述符集只有一种情况(针对带外数据):
- 当收到带外数据(out-of-band)时或者socket的带外数据标志未被清除.