#pragma once
#include <string>
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class smtp_mail {
private:
    char ipv4_addr[16];         // IPv4地址
    int send_messenger(SOCKET& socket_name, char* mes);         // 发送消息
    int recv_messenger(SOCKET& socket_name, char* mes);         // 接受消息
public:
    string account = "";        // 账号
    string password = "";       // 密码
    string site = "";           // 服务对应的网址
    string data = "";           // 发送邮件的内容
    int post = 25;              // 发邮件默认端口
    int send_mail();            // 发送邮件
};