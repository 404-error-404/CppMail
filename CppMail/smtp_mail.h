#pragma once
#include <map>
#include <string>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class smtp_mail {
private:
    SOCKET smtp_server = socket(AF_INET, SOCK_STREAM, 0);       // socket����
    SOCKADDR_IN server_addr;                                    // ����˵�ַ
    char ipv4_addr[16] = "";                                    // IPv4��ַ

    int send_messenger(SOCKET& socket_name, string mes);        // ������Ϣ
    int recv_messenger(SOCKET& socket_name);                    // ������Ϣ
    int get_ip_byname(string name);                             // ������������ipv4��ַ
    string base64_decode(string str);                           // base64����
public:
    smtp_mail();                                                // ���캯��
    ~smtp_mail();                                               // ��������   
    string account = "";                                        // �˺�
    string password = "";                                       // ����
    string site = "";                                           // �����Ӧ����ַ
    string subject = "";                                        // ����
    string data = "";                                           // �����ʼ�������
    string receiver = "";                                       // ���շ�
    int port = 25;                                              // ���ʼ�Ĭ�϶˿�
    int send_mail();                                            // �����ʼ�
    map<int, string> smtp_result;                               // �洢��������ֵ��Ӧ�Ĵ�����Ϣ
};