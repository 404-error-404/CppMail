#include "smtp_mail.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

smtp_mail::smtp_mail() {
	this->smtp_result = {
		{-1, "域名解析到IPv4地址错误，请核对域名或者检查网络连接"},
		{-2, "数据发送出错"},
		{-3, "数据接收出错"},
		{-4, "服务器连接失败，请核对端口号或者检查网络连接"}
	};
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	WSAStartup(w_req, &wsadata);		// 初始化套接字，返回int，返回值为0则初始化失败，为其他值则成功，但这里不做检测
	//检测版本号，但这里不做检测
	/*if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}*/

	// 填充状态信息
	server_addr.sin_family = AF_INET;	// 这里AF_INET 表示ADDRESS FAMILY 地址族
										// PF_INET 表示PROTOCOL FAMILY 协议族
										// windows下混用也问题不大（网上查的
}

smtp_mail::~smtp_mail() {
	WSACleanup();						// 清理退出
}

// base64编码
// 代码来自网络，有极轻微改动
// https://blog.harrynull.tech/post/base64
string smtp_mail::base64_decode(string src) {
	// base64编码解码字符串
	const char base64_char[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string ret = "";
	int len = src.length();
	ret.reserve(len * 4 / 3);               // base64编码长度大概是原来的4/3
	for (int i = 0; i < len; i += 3) {   // 每三个byte处理一次
		char first = src[i];
		char second = i + 1 < len ? src[i + 1] : 0;
		char third = i + 2 < len ? src[i + 2] : 0;

		ret += base64_char[(first >> 2) & 0b111111]; // 1st high 6 bits
		ret += base64_char[(first & 0b11) << 4 | ((second >> 4) & 0b1111)]; // 1st low 2 bits + 2nd high 4 bits
		if (i + 1 >= len) { ret += "=="; break; }
		ret += base64_char[(second & 0b1111) << 2 | ((third >> 6) & 0b11)]; // 2nd low 4 bits + 3rd high 2 bits
		if (i + 2 >= len) { ret += "="; break; }
		ret += base64_char[third & 0b111111]; // 3rd low 6 bits
	}
	return ret;
}

/* base64解码一并附上
解码
然后再来实现解码函数。解码函数基本上就是编码的逆向过程。

首先先定义一个base64_char_convert函数用来将base64字符转换成原始byte。以下是一个最简单的实现。出于效率考虑还可以把这个函数实现成查表。

struct InvalidBase64 {};

char base64_char_convert(char c) {
	for (size_t i = 0; i < sizeof(base64_char); ++i)
		if (base64_char[i] == c) return i;
	throw InvalidBase64(); // Invalid base64 character
}
然后再实现真正的解码函数：

vector<char> base64_decode(const string& src) {
	vector<char> ret;
	ret.reserve(src.length() * 3 / 4);
	for (size_t i = 0; i < src.length(); i += 4) {
		char b1 = base64_char_convert(src[i]);
		char b2 = base64_char_convert(src[i + 1]);

		ret.push_back((b1 << 2) | ((b2 >> 4 & 0b11))); // 1st 6bits, 2nd high 2bits

		if (src[i + 2] == '=') break;
		char b3 = base64_char_convert(src[i + 2]);
		ret.push_back(((b2 & 0b1111) << 4) | ((b3 >> 2) & 0b1111)); // 2nd low 4bits, 3rd high 4bits

		if (src[i + 3] == '=') break;
		char b4 = base64_char_convert(src[i + 3]);
		ret.push_back(((b3 & 0b11) << 6) | b4); // 3rd low 2bits, 4th 6bits
	}
	return ret;
}
*/


// 发送消息
int smtp_mail::send_messenger(SOCKET& socket_name, string mes) {
	int send_len = send(socket_name, mes.c_str(), mes.length(), 0);
	if (send_len < 0) {
		// cout << "发送失败" << endl;
		return -2;
	}
	return 0;
}

// 接受消息
int smtp_mail::recv_messenger(SOCKET& socket_name) {
	char recv_buf[500];		// 用于存放接受的消息
	int recv_len = recv(socket_name, recv_buf, 500, 0);
	if (recv_len < 0 || &recv_buf[recv_len - 8] != "250 OK\r\n") {
		// cout << "接受数据失败" << endl;
		return -3;
	}
	return 0;
}

// 从域名解析到ipv4地址
// 解析域名到IPv4地址，无法解析则返回-1，解析成功则返回0
// 代码来自微软官方文档，有轻微改动
// https://docs.microsoft.com/zh-cn/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
int smtp_mail::get_ip_byname(string name) {
	//-----------------------------------------
	// Declare and initialize variables
	WSADATA wsaData;

	int iResult;
	char ipstr[16];		// 存放ipv4地址
	DWORD dwRetval;

	struct addrinfo* result = NULL;
	struct addrinfo hints;
	struct sockaddr_in* addr;

	// 下边是官方原来的ipv4和v6写法
	//	struct sockaddr_in* sockaddr_ipv4;
	//  struct sockaddr_in6 *sockaddr_ipv6;




	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		// printf("WSAStartup failed: %d\n", iResult);
		return -1;
	}

	//--------------------------------
	// Setup the hints address info structure
	// which is passed to the getaddrinfo() function
	// 初始化相关参数
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// 获取域名对应的ip地址
	dwRetval = getaddrinfo(name.c_str(), NULL, &hints, &result);
	if (dwRetval != 0) {
		// printf("getaddrinfo failed with error: %d\n", dwRetval);
		WSACleanup();
		return -1;
	}
	else {
		addr = (struct sockaddr_in*) result->ai_addr; //获取当前 address  

		sprintf_s(ipstr, "%d.%d.%d.%d",
			addr->sin_addr.S_un.S_un_b.s_b1,
			addr->sin_addr.S_un.S_un_b.s_b2,
			addr->sin_addr.S_un.S_un_b.s_b3,
			addr->sin_addr.S_un.S_un_b.s_b4
			);
		// 成功获取ipv4地址
		strcpy_s(this->ipv4_addr, ipstr);
	}

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}

// 发送邮件
int smtp_mail::send_mail() {
	int result;		// 标记结果
	string end_with = "\r\n";
	// 获取IPv4地址
	result = this->get_ip_byname(this->site);
	if (result != 0) {
		return result;
	}
	// 将IPv4地址写入server_addr
	inet_pton(AF_INET, this->ipv4_addr, &this->server_addr.sin_addr.S_un.S_addr);
	// 设置端口号，默认smtp端口号为25
	this->server_addr.sin_port = htons(this->port);
	this->server_addr.sin_port = htons(25);



	// 开始连接服务器
	if (connect(smtp_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		// cout << "服务器连接失败" << endl;
		WSACleanup();
		return -4;
	}
	result = this->recv_messenger(this->smtp_server);
	if (result != 0) {
		return result;
	}
	// 准备
	result = this->send_messenger(this->smtp_server, "helo smtp_client" + end_with);
	if (result != 0) {
		return result;
	}
	// 请求登录
	result = this->send_messenger(this->smtp_server, "auth login" + end_with);
	if (result != 0) {
		return result;
	}
	// 输入账号
	result = this->send_messenger(this->smtp_server, this->base64_decode(this->account) + end_with);
	if (result != 0) {
		return result;
	}
	// 输入密码
	result = this->send_messenger(this->smtp_server, this->base64_decode(this->password) + end_with);
	if (result != 0) {
		return result;
	}
	// 发信人
	result = this->send_messenger(this->smtp_server, "mail from: <" + this->account + ">" + end_with);
	if (result != 0) {
		return result;
	}
	// 收信人
	// 发信人
	result = this->send_messenger(this->smtp_server, "mail to: <" + this->receiver + ">" + end_with);

	if (result != 0) {
		return result;
	}

	return 0;
}