#define _WINSOCK_DEPRECATED_NO_WARNINGS

//ͷ�ļ�
#include "winsock2.h"  
#include <iostream>  
#pragma comment(lib, "ws2_32.lib")  
using namespace std;
// BOOL RecvLine(SOCKET s, char* buf); //��ȡһ������  
//������

int receive_eamil()
{
	const int BUF_SIZE = 64;
	WSADATA wsd; //WSADATA����  
	SOCKET sHost; //�������׽���  
	SOCKADDR_IN servAddr; //��������ַ  
	char bufSend[BUF_SIZE]; //�������ݻ�����  
	char bufRecv[BUF_SIZE];
	int retVal; //����ֵ  
	int iii = 0;	// ����
				//��ʼ���׽��ֶ�̬��  
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		cout << "WSAStartup failed!" << endl;
		return -1;
	}
	//�����׽���  
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		cout << "socket failed!" << endl;
		WSACleanup();//�ͷ��׽�����Դ  
		return  -1;
	}
	//���÷�������ַ  
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("123.126.97.1");
	servAddr.sin_port = htons((short)25);
	int nServAddlen = sizeof(servAddr);
	//���ӷ�����  
	retVal = connect(sHost, (LPSOCKADDR)&servAddr, sizeof(servAddr));
	if (SOCKET_ERROR == retVal)
	{
		cout << "connect failed!" << endl;
		closesocket(sHost); //�ر��׽���  
		WSACleanup(); //�ͷ��׽�����Դ  
		return -1;
	}
	cout << "���������ӳɹ�" << endl;
	while (true)
	{
		//���������������  
		ZeroMemory(bufSend, BUF_SIZE);
		cout << " ���������������:  ";
		cin.getline(bufSend, BUF_SIZE - 1);
		// string buf_temp;
		// cin >> buf_temp;
		// strcpy_s(buf, buf_temp.c_str());
		retVal = send(sHost, bufSend, strlen(bufSend), 0);
		if (SOCKET_ERROR == retVal)
		{
			cout << "send failed!" << endl;
			closesocket(sHost); //�ر��׽���  
			WSACleanup(); //�ͷ��׽�����Դ  
			return -1;
		}
		// RecvLine(sHost, bufRecv);  
		ZeroMemory(bufRecv, BUF_SIZE);
		recv(sHost, bufRecv, BUF_SIZE, 0); // ���շ������˵����ݣ� ֻ����5���ַ�  
		cout << endl << "�ӷ������������ݣ�" << bufRecv;
		cout << "\n";
	}
	//�˳�  
	closesocket(sHost); //�ر��׽���  
	WSACleanup(); //�ͷ��׽�����Դ  
	return 0;
}