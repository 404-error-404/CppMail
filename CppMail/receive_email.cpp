#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>  
#include <string>  
#include <WinSock2.h> //适用平台 Windows 
using namespace std;
#pragma comment(lib, "ws2_32.lib") /*链接ws2_32.lib动态链接库*/  

int receive_eamil()
{
    char buff[500]; //recv函数返回的结果 
    string message;

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 1);
    //WSAStarup，即WSA(Windows SocKNDs Asynchronous，Windows套接字异步)的启动命令 
    int err = WSAStartup(wVersionRequested, &wsaData);
    cout << "WSAStartup:" << err << endl;
    SOCKET sockClient; //客户端的套接字  
    sockClient = socket(AF_INET, SOCK_STREAM, 0); //建立socket对象  

    HOSTENT* pHostent;
    pHostent = gethostbyname("smtp.126.com"); //得到有关于域名的信息 
    SOCKADDR_IN addrServer; //服务端地址 
    addrServer.sin_addr.S_un.S_addr = *((DWORD*)pHostent->h_addr_list[0]); //得到smtp服务器的网络字节序的ip地址   
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(25); //连接端口25  
    //int connect (SOCKET s , const struct sockaddr FAR *name , int namelen ); //函数原型 
    err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //向服务器发送请求  
    cout << "connect:" << err << endl;
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "connect:" << buff << endl;
    /*
    登录邮件服务器
    */
    message = "ehlo 126.com\r\n";
    send(sockClient, message.c_str(), message.length(), 0); //发送ehlo命令 
    buff[recv(sockClient, buff, 500, 0)] = '\0';   //接收返回值 
    cout << "helo:" << buff << endl;     //输出返回值 

    message = "auth login \r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "auth login:" << buff << endl;
    /*
    发送base64加密的用户名、密码
    */
    message = "xxxx\r\n"; //base64 编码的用户名 
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "usrname:" << buff << endl;

    message = "xxxx\r\n";//base64 编码的密码 
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "password:" << buff << endl;
    /*
    使用 MAIL 命令指定发送者
    使用 RCPT 命令指定接收者，可以重复使用RCPT指定多个接收者
    */
    message = "MAIL FROM:<xxxx@126.com> \r\nRCPT TO:<xxxx@126.com> \r\n";
    send(sockClient, message.c_str(), message.length(), 0);

    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "mail from: " << buff << endl;
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "rcpt to: " << buff << endl;
    /*
    使用 DATA 命令告诉服务器要发送邮件内容
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
        "Bob\r\n.\r\n"; //注意subject关键字与正文之间要有一个空行 
        send(sockClient, message.c_str(), message.length(), 0);
    message = "QUIT\r\n";
    send(sockClient, message.c_str(), message.length(), 0);
    buff[recv(sockClient, buff, 500, 0)] = '\0';
    cout << "QUIT:" << buff << endl;
    system("pause");
    return 0;
}
