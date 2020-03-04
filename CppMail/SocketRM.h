#pragma once
#include <string>
#include <WinSock2.h>
class SocketRM
{
public:
	void getHostAddr();
	void ConnectServer();
	//void loginServer();
	//void SayHELLO();
	//void SayAUTH();
	//void GetList();
	void GetUIDL();
	void GetEmailInfo();
	//void GetFromInfo();
	//void GetSubjectInfo();
	//void GetDATE();
private:
	SOCKET ServMail;
	SOCKADDR_IN ServAddr;
	WSADATA wsd;
	hostent* ptr;			//通过地址获取完整的服务器地址
	in_addr addr;			//将地址转成以.相隔的IP地址，然后通过inet_addr函数转为unsigned long型
	char buf[2048];			//接收登录信息从Server传回来的数据
	char recvbuf[20000];		//从SOCKET缓存区复制的本地缓存变量
	std::string User;		//用户名....POP协议登录信息；
	std::string Psd;		//密码
	std::string FromStr;		//解码输入字符串
	std::string OutStr;		//解码输出字符串
	std::string bufStr;		//缓存所下载的邮件信息
	std::string Order;		//POP命令
};

