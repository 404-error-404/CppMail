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
	hostent* ptr;			//ͨ����ַ��ȡ�����ķ�������ַ
	in_addr addr;			//����ַת����.�����IP��ַ��Ȼ��ͨ��inet_addr����תΪunsigned long��
	char buf[2048];			//���յ�¼��Ϣ��Server������������
	char recvbuf[20000];		//��SOCKET���������Ƶı��ػ������
	std::string User;		//�û���....POPЭ���¼��Ϣ��
	std::string Psd;		//����
	std::string FromStr;		//���������ַ���
	std::string OutStr;		//��������ַ���
	std::string bufStr;		//���������ص��ʼ���Ϣ
	std::string Order;		//POP����
};

