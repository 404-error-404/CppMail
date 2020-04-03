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
    SOCKET smtp_server = socket(AF_INET, SOCK_STREAM, 0);       // socket连接
    SOCKADDR_IN server_addr;                                    // 服务端地址
    char ipv4_addr[16] = "";                                    // IPv4地址

    int send_messenger(SOCKET& socket_name, string mes);        // 发送消息
    int recv_messenger(SOCKET& socket_name);                    // 接受消息
    int get_ip_byname(string name);                             // 从域名解析到ipv4地址
    string base64_decode(string str);                           // base64编码
public:
    smtp_mail();                                                // 构造函数
    ~smtp_mail();                                               // 析构函数   
    string account = "";                                        // 账号
    string password = "";                                       // 密码
    string site = "";                                           // 服务对应的网址
    string subject = "";                                        // 主题
    string data = "";                                           // 发送邮件的内容
    string receiver = "";                                       // 接收方
    int port = 25;                                              // 发邮件默认端口
    int send_mail();                                            // 发送邮件
    map<int, string> smtp_result;                               // 存储各个返回值对应的错误信息
};