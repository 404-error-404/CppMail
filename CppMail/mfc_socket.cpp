#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

// 初始化相关操作
void initialization();
// 解析域名到IPv4地址，无法解析则返回-1，解析成功则返回0
int get_ip_byname(string name, string &ipv4);
// 发送消息
int send_messenger(SOCKET& socket_name, string &mes);
// 接受消息
int recv_messenger(SOCKET& socket_name);

int mfc_socket() {

	string ipv4;
	if (get_ip_byname("smtp.qq.com", ipv4) != 0) {
		return -1;
	}

	// 定义长度变量
	int send_len = 0;
	int recv_len = 0;
	// 定义发送缓冲区和接受缓冲区
	char send_buf[100] = "helo lele";
	char recv_buf[100] = "";
	// 定义服务端套接字，接受请求套接字
	SOCKET s_server;
	// 服务端地址
	SOCKADDR_IN server_addr;
	initialization();
	// 填充状态信息
	server_addr.sin_family = AF_INET;	// 这里AF_INET 表示ADDRESS FAMILY 地址族
										// PF_INET 表示PROTOCOL FAMILY 协议族
										// windows下混用也问题不大（网上查的
	// 123.126.96.4 smtp.126.com
	// 58.251.106.181 smtp.qq.com
	char ipaddr[16] = "";
	strcpy_s(ipaddr, ipv4.c_str());
	inet_pton(AF_INET, ipaddr, &server_addr.sin_addr.S_un.S_addr);
	server_addr.sin_port = htons(25);
	// 创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败" << endl;
		WSACleanup();
	}
	else {
		cout << "服务器连接成功";
		recv_len = recv(s_server, recv_buf, 1000, 0);
		if (recv_len < 0) {
			cout << "接受数据失败" << endl;
		}
		cout << "服务端消息：" << recv_buf << endl;
	}
	string send_str = "";
	












	cout << "请发送信息：";
	// send_buf[100] = "helo lele";
	// cin.getline(send_buf, 100);
	strcpy_s(send_buf, "helo lele\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "auth login\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "MTc5MTc4MTY0NEBxcS5jb20=\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "dmRwb2Vuc2JhdXZhYmJjaA==\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "mail from: <1791781644@qq.com>\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "rcpt to: <1791781644@qq.com>\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;

	strcpy_s(send_buf, "data\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}

	strcpy_s(send_buf, "subject: 测试\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}

	strcpy_s(send_buf, "from: 1791781644@qq.com\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}

	strcpy_s(send_buf, "to: 1791781644@qq.com\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}

	strcpy_s(send_buf, "测试\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;

	}
	strcpy_s(send_buf, "测试\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;

	}
	strcpy_s(send_buf, "测试\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;

	}
	strcpy_s(send_buf, "测试\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;

	}

	strcpy_s(send_buf, ".\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "发送失败" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		
	}
	cout << "服务端消息：" << recv_buf << endl;


	/*recv_len = recv(s_server, recv_buf, 100, 0);
	if (recv_len < 0) {
		cout << "接受数据失败" << endl;
		break;
	}
	cout << "服务端消息：" << recv_buf << endl;*/













	// 关闭套接字
	closesocket(s_server);
	// 释放dll资源
	WSACleanup();
	return 0;
}

void initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

// 解析域名到IPv4地址，无法解析则返回-1，解析成功则返回0
// 代码来自微软官方文档，有轻微改动
// https://docs.microsoft.com/zh-cn/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
int get_ip_byname(string name, string & ipv4) {
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
	dwRetval = getaddrinfo("smtp.qq.com", NULL, &hints, &result);
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
		ipv4 = ipstr;
	}

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}

// 发送消息
int send_messenger(SOCKET& socket_name, string &mes) {
	char send_buf[500];
	strcpy_s(send_buf, mes.c_str());
	int send_len = send(socket_name, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		// cout << "发送失败" << endl;
		return -1;

	}
	return 0;
}
// 接受消息
int recv_messenger(SOCKET& socket_name) {
	char recv_buf[500];		// 用于存放接受的消息
	int recv_len = recv(socket_name, recv_buf, 500, 0);
	if (recv_len < 0) {
		// cout << "接受数据失败" << endl;
		return -1;

	}
	return 0;
}