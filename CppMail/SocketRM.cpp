#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "SocketRM.h"
#include <iostream>


//����SOCKET
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

// ������ת��Ϊip
void SocketRM::getHostAddr()
{
	//ptr��һ��hostent���͵�ָ�룬Ŀ�ľ���ͨ��gethostbyhome()������ȡĿ��
	//Ϊpop.126.com��hostent�Ľṹָ�롣
	ptr = gethostbyname("smtp.126.com");
	if (ptr == nullptr)
		std::cout << "GetHostByName Error..." << std::endl;
	//pop.126.com��һ�������õĵ�ַ��Ҫ����ת����unsigned long�εı���
	//���ݵ�servAddr.sin_Addr.s_addr�С�
	memcpy(&addr, ptr->h_addr_list[0], sizeof(in_addr));

};

//��������
void SocketRM::GetUIDL()
{
	send(ServMail, "uidl\r\n", strlen("uidl\r\n"), 0);
	recv(ServMail, (LPSTR)recvbuf, sizeof(recvbuf), 0);
	//std::cout<<"Serve:"<<recvbuf;
	memset(recvbuf, 0, 20000);
	//std::cout<<"Serve:"<<std::endl;
};

//�õ��ʼ�ͷ��Ϣ
void SocketRM::GetEmailInfo()
{
	//�鿴"ĳ"���ʼ���ǰ1��
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
		//֮����Ҫ��ȡ����SOCKET�Ļ���������POP3�е�retr����
		//��������ȴӷ�����������һ���ʼ���Ϣ������С
		//Ȼ����������ʼ�ԭ�ģ�����Ҫ�ӷ��������������Σ�Ҳ����Ҫ���δ���SOCKET������
		//��ô����Ҫrecv()��������2��COPY.
		int val = recv(ServMail, (LPSTR)recvbuf, sizeof(recvbuf), 0);
		std::cout << recvbuf;
		bufStr += recvbuf;
		memset(recvbuf, 0, 20000);
		//���ڴӷ������յ����ʼ�ԭ�ĵ����ݣ�
		//�������Ľ�β���У�
		//recvbuf[val]=='\0',recvbuf[val-1]=='\n',recvbuf[val-2]=='\r',��־��
		if (recvbuf[val] == '\0')
			break;

	}
	bufStr = bufStr.c_str();

};