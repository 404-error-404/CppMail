#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>  
#include <string>  
#include <WinSock2.h> //����ƽ̨ Windows 
using namespace std;
#pragma comment(lib, "ws2_32.lib") /*����ws2_32.lib��̬���ӿ�*/  

int receive_eamil()
{
    char buff[500]; //recv�������صĽ�� 
    string message;

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    //WSAStarup����WSA(Windows SocKNDs Asynchronous��Windows�׽����첽)���������� 
    int err = WSAStartup(wVersionRequested, &wsaData);
    cout << "WSAStartup:" << err << endl;
    SOCKET sockClient; //�ͻ��˵��׽���  
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //����socket����  

    HOSTENT* pHostent;
    pHostent = gethostbyname("smtp.126.com"); //�õ��й�����������Ϣ 
    SOCKADDR_IN addrServer; //����˵�ַ 
    addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //�õ�smtp�������������ֽ����ip��ַ   
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(25); //���Ӷ˿�25  
    //int connect (SOCKET s , const struct sockaddr FAR *name , int namelen ); //����ԭ�� 
    err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //���������������  
    cout << "connect:" << err << endl;
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "connect:" << buff << endl;
    /*
    ��¼�ʼ�������
    */
    message = "ehlo 126.com\r\n";
    send(sockClient, message.c_str(), message.length(), 0); //����ehlo���� 
    buff[recv(sockClient, buff, 500, 0)] = '\0';   //���շ���ֵ 
    cout << "helo:" << buff << endl;     //�������ֵ 

    message = "auth login \r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "auth login:" << buff << endl;
    /*
    ����base64���ܵ��û���������
    */
    message = "xxxx\r\n"; //base64 ������û��� 
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "usrname:" << buff << endl;

    message = "xxxx\r\n";//base64 ��������� 
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "password:" << buff << endl;
    /*
    ʹ�� MAIL ����ָ��������
    ʹ�� RCPT ����ָ�������ߣ������ظ�ʹ��RCPTָ�����������
    */
    message = "MAIL FROM:<xxxx@126.com> \r\nRCPT TO:<xxxx@126.com> \r\n";
    send(sockClient, message.c_str(), message.length(), 0);

    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "mail from: " << buff << endl;
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "rcpt to: " << buff << endl;
    /*
    ʹ�� DATA ������߷�����Ҫ�����ʼ�����
    */
    message = "DATA\r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "data: " << buff << endl;
    message = "From: Bob@example.com\r\n"\
        "To: Alice@example.com\r\n"\
        "Cc: theboss@example.com\r\n"\
        "subject: subject\r\n\r\n"\
        "Hello Alice\r\n"\
        "This is a test message with 4 header fields and 4 lines in the message body\r\n"\
        "your friend\r\n"\
        "Bob\r\n.\r\n"; //ע��subject�ؼ���������֮��Ҫ��һ������ 
        send(sockClient, message.c_str(), message.length(), 0);
    message = "QUIT\r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "QUIT:" << buff << endl;
    system("pause");
    return 0;
}
