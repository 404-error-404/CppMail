#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "SocketRM.h"
#include <iostream>


//建立SOCKET
void SocketRM::ConnectServer()
{
	if ((ServMail = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
	{
		std::cout << "ServMail ERROR..." << std::endl;
		WSACleanup();
		closesocket(ServMail);
	}

	getHostAddr();

	ServAddr.sin_family = AF_INET;
	ServAddr.sin_port = htons(110);
	ServAddr.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	int len = sizeof(SOCKADDR_IN);
	int ret;

	if ((ret = connect(ServMail, (LPSOCKADDR)&ServAddr, len)) == INVALID_SOCKET)
	{
		std::cout << "Connect Error..." << std::endl;
		closesocket(ServMail);
		WSACleanup();
	}
	else
	{
		ZeroMemory(buf, 2048);
		recv(ServMail, buf, 2048, 0);
		std::cout << "Connect Success..." << std::endl;
		std::cout << "Server:" << buf << std::endl;

	}
};

// 将域名转换为ip
void SocketRM::getHostAddr()
{
	//ptr是一个hostent类型的指针，目的就是通过gethostbyhome()函数获取目标
	//为pop.126.com的hostent的结构指针。
	ptr = gethostbyname("smtp.126.com");
	if (ptr == nullptr)
		std::cout << "GetHostByName Error..." << std::endl;
	//pop.126.com是一个不可用的地址，要将它转换成unsigned long形的变量
	//传递到servAddr.sin_Addr.s_addr中。
	memcpy(&addr, ptr->h_addr_list[0], sizeof(in_addr));

};

//发送命令
void SocketRM::GetUIDL()
{
	send(ServMail, "uidl\r\n", strlen("uidl\r\n"), 0);
	recv(ServMail, (LPSTR)recvbuf, sizeof(recvbuf), 0);
	//std::cout<<"Serve:"<<recvbuf;
	memset(recvbuf, 0, 20000);
	//std::cout<<"Serve:"<<std::endl;
};

//得到邮件头信息
void SocketRM::GetEmailInfo()
{
	//查看"某"个邮件的前1行
	std::cout << "Which Email do you want?";
	std::string Choice;
	std::cin >> Choice;
	Order = "top " + Choice + " 1\r\n";
	send(ServMail, Order.c_str(), strlen(Order.c_str()), 0);

	recv(ServMail, (LPSTR)recvbuf, sizeof(recvbuf), 0);
	//std::cout<<"Serve:"<<recvbuf;
	memset(recvbuf, 0, 20000);
	//std::cout<<"Serve:"<<std::endl;
	while (true)
	{
		//之所以要收取两次SOCKET的缓存区，是POP3中的retr命令
		//该命令会先从服务器中下载一个邮件信息——大小
		//然后会在下载邮件原文，所以要从服务器上下载两次，也就是要两次存入SOCKET缓存区
		//那么就需要recv()函数进行2次COPY.
		int val = recv(ServMail, (LPSTR)recvbuf, sizeof(recvbuf), 0);
		std::cout << recvbuf;
		bufStr += recvbuf;
		memset(recvbuf, 0, 20000);
		//对于从服务器收到的邮件原文的数据：
		//对于最后的结尾，有：
		//recvbuf[val]=='\0',recvbuf[val-1]=='\n',recvbuf[val-2]=='\r',标志符
		if (recvbuf[val] == '\0')
			break;

	}
	bufStr = bufStr.c_str();

};