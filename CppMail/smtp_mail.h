#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class smtp_mail {
private:
    char ipv4_addr[16];         // IPv4��ַ
    int send_messenger(SOCKET& socket_name, char* mes);         // ������Ϣ
    int recv_messenger(SOCKET& socket_name, char* mes);         // ������Ϣ
public:
    string account = "";        // �˺�
    string password = "";       // ����
    string site = "";           // �����Ӧ����ַ
    string data = "";           // �����ʼ�������
    int post = 25;              // ���ʼ�Ĭ�϶˿�
    int send_mail();            // �����ʼ�
};