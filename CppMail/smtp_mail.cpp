#include "smtp_mail.h"
#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

smtp_mail::smtp_mail() {
	// ���ؽ��˵��
	this->smtp_result = {
		{0, "�ʼ����ͳɹ�"},
		{-1, "����������IPv4��ַ������˶��������߼����������"},
		{-2, "���ݷ��ͳ���"},
		{-3, "���ݽ��ճ���"},
		{-4, "����������ʧ�ܣ���˶Զ˿ںŻ��߼����������"},
		{-5, "�˺Ż����������˶�"},
		{-6, "�����˸�ʽ����"},
		{-7, "�ʼ�����ʧ�ܣ������ʼ�����"},
		{-8, "�Ͽ�����ʱ���ִ����ʼ����ͳɹ�"}
	};
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	WSAStartup(w_req, &wsadata);		// ��ʼ���׽��֣�����int������ֵΪ0���ʼ��ʧ�ܣ�Ϊ����ֵ��ɹ��������ﲻ�����
	//���汾�ţ������ﲻ�����
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		// cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else {
		// cout << "�׽��ֿ�汾��ȷ��" << endl;
	}

	// ���״̬��Ϣ
	server_addr.sin_family = AF_INET;	// ����AF_INET ��ʾADDRESS FAMILY ��ַ��
										// PF_INET ��ʾPROTOCOL FAMILY Э����
										// windows�»���Ҳ���ⲻ�����ϲ��
	// �����׽���
	this->smtp_server = socket(AF_INET, SOCK_STREAM, 0);
}

smtp_mail::~smtp_mail() {
	WSACleanup();						// �����˳�
}

// base64����
// �����������磬�м���΢�Ķ�
// https://blog.harrynull.tech/post/base64
string smtp_mail::base64_decode(string src) {
	// base64��������ַ���
	const char base64_char[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string ret = "";
	int len = src.length();
	ret.reserve(len * 4 / 3);               // base64���볤�ȴ����ԭ����4/3
	for (int i = 0; i < len; i += 3) {   // ÿ����byte����һ��
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

/* base64����һ������
����
Ȼ������ʵ�ֽ��뺯�������뺯�������Ͼ��Ǳ����������̡�

�����ȶ���һ��base64_char_convert����������base64�ַ�ת����ԭʼbyte��������һ����򵥵�ʵ�֡�����Ч�ʿ��ǻ����԰��������ʵ�ֳɲ��

struct InvalidBase64 {};

char base64_char_convert(char c) {
	for (size_t i = 0; i < sizeof(base64_char); ++i)
		if (base64_char[i] == c) return i;
	throw InvalidBase64(); // Invalid base64 character
}
Ȼ����ʵ�������Ľ��뺯����

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


// ������Ϣ
int smtp_mail::send_messenger(SOCKET& socket_name, string mes) {
	int send_len = send(socket_name, mes.c_str(), mes.length(), 0);
	if (send_len < 0) {
		// cout << "����ʧ��" << endl;
		return -2;
	}
	return 0;
}

// ������Ϣ
int smtp_mail::recv_messenger(SOCKET& socket_name) {
	char recv_buf[500] = "";		// ���ڴ�Ž��ܵ���Ϣ
	int recv_len = recv(socket_name, recv_buf, 1000, 0);
	// ��һ���ַ�Ϊ2��3����ȷ��������Ҫ��"250 OK\r\n"�ж�
	if (recv_buf[0] != '2' && recv_buf[0] != '3' && (recv_len < 0 || &recv_buf[recv_len - 8] != "250 OK\r\n")) {
		// cout << "��������ʧ��" << endl;
		return -3;
	}
	return 0;
}

// ������������ipv4��ַ
// ����������IPv4��ַ���޷������򷵻�-1�������ɹ��򷵻�0
// ��������΢��ٷ��ĵ�������΢�Ķ�
// https://docs.microsoft.com/zh-cn/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
int smtp_mail::get_ip_byname(string name) {
	//-----------------------------------------
	// Declare and initialize variables
	WSADATA wsaData;

	int iResult;
	char ipstr[16];		// ���ipv4��ַ
	DWORD dwRetval;

	struct addrinfo* result = NULL;
	struct addrinfo hints;
	struct sockaddr_in* addr;

	// �±��ǹٷ�ԭ����ipv4��v6д��
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
	// ��ʼ����ز���
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// ��ȡ������Ӧ��ip��ַ
	dwRetval = getaddrinfo(name.c_str(), NULL, &hints, &result);
	if (dwRetval != 0) {
		// printf("getaddrinfo failed with error: %d\n", dwRetval);
		WSACleanup();
		return -1;
	}
	else {
		addr = (struct sockaddr_in*) result->ai_addr; //��ȡ��ǰ address  

		sprintf_s(ipstr, "%d.%d.%d.%d",
			addr->sin_addr.S_un.S_un_b.s_b1,
			addr->sin_addr.S_un.S_un_b.s_b2,
			addr->sin_addr.S_un.S_un_b.s_b3,
			addr->sin_addr.S_un.S_un_b.s_b4
			);
		// �ɹ���ȡipv4��ַ
		strcpy_s(this->ipv4_addr, ipstr);
	}

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}

// �����ʼ�
int smtp_mail::send_mail() {
	int result;		// ��ǽ��
	string end_with = "\r\n";
	// ��ȡIPv4��ַ
	result = this->get_ip_byname(this->site);
	if (result != 0) {
		return result;
	}
	// ��IPv4��ַд��server_addr
	inet_pton(AF_INET, this->ipv4_addr, &this->server_addr.sin_addr.S_un.S_addr);
	// ���ö˿ںţ�Ĭ��smtp�˿ں�Ϊ25
	this->server_addr.sin_port = htons(this->port);
	this->server_addr.sin_port = htons(25);



	// ��ʼ���ӷ�����
	if (connect(this->smtp_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		// cout << "����������ʧ��" << endl;
		WSACleanup();
		return -4;
	}
	result = this->recv_messenger(this->smtp_server);
	if (result != 0) {
		return result;
	}

	// ׼��
	result = this->send_messenger(this->smtp_server, "helo smtp_client" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -4;			// ���ݽ��ճ���
	}

	// �����¼
	result = this->send_messenger(this->smtp_server, "auth login" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -4;			// ���ݽ��ճ���
	}

	// �����˺�
	result = this->send_messenger(this->smtp_server, this->base64_decode(this->account) + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -4;			// ���ݽ��ճ���
	}

	// ��������
	result = this->send_messenger(this->smtp_server, this->base64_decode(this->password) + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -5;			// �˺Ż����������˶�
	}

	// ������
	result = this->send_messenger(this->smtp_server, "mail from: <" + this->account + ">" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -5;			// �˺Ż����������˶�
	}

	// ������
	result = this->send_messenger(this->smtp_server, "rcpt to: <" + this->receiver + ">" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -6;			// �����˸�ʽ����
	}

	// ����������
	result = this->send_messenger(this->smtp_server, "data" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}

	// subject
	result = this->send_messenger(this->smtp_server, "subject: " + this->subject + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}

	// from
	result = this->send_messenger(this->smtp_server, "from: " + this->account + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}

	// to
	result = this->send_messenger(this->smtp_server, "to: " + this->receiver + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}

	// ��Ϣ����
	result = this->send_messenger(this->smtp_server, this->data + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}

	// ��������
	result = this->send_messenger(this->smtp_server, "." + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -7;			// �ʼ�����ʧ�ܣ������ʼ�����
	}

	// �����˳�
	result = this->send_messenger(this->smtp_server, "quit" + end_with);
	if (result != 0) {
		return result;		// ���ݷ��ͳ���
	}
	result = this->recv_messenger(this->smtp_server);		// ������Ϣ
	if (result != 0) {
		return -8;			// �Ͽ�����ʱ���ִ����ʼ����ͳɹ�
	}

	return 0;
}