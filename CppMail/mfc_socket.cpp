#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

// ��ʼ����ز���
void initialization();
// ����������IPv4��ַ���޷������򷵻�-1�������ɹ��򷵻�0
int get_ip_byname(string name, string &ipv4);
// ������Ϣ
int send_messenger(SOCKET& socket_name, string &mes);
// ������Ϣ
int recv_messenger(SOCKET& socket_name);

int mfc_socket() {

	string ipv4;
	if (get_ip_byname("smtp.qq.com", ipv4) != 0) {
		return -1;
	}

	// ���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	// ���巢�ͻ������ͽ��ܻ�����
	char send_buf[100] = "helo lele";
	char recv_buf[100] = "";
	// ���������׽��֣����������׽���
	SOCKET s_server;
	// ����˵�ַ
	SOCKADDR_IN server_addr;
	initialization();
	// ���״̬��Ϣ
	server_addr.sin_family = AF_INET;	// ����AF_INET ��ʾADDRESS FAMILY ��ַ��
										// PF_INET ��ʾPROTOCOL FAMILY Э����
										// windows�»���Ҳ���ⲻ�����ϲ��
	// 123.126.96.4 smtp.126.com
	// 58.251.106.181 smtp.qq.com
	char ipaddr[16] = "";
	strcpy_s(ipaddr, ipv4.c_str());
	inet_pton(AF_INET, ipaddr, &server_addr.sin_addr.S_un.S_addr);
	server_addr.sin_port = htons(25);
	// �����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "����������ʧ��" << endl;
		WSACleanup();
	}
	else {
		cout << "���������ӳɹ�";
		recv_len = recv(s_server, recv_buf, 1000, 0);
		if (recv_len < 0) {
			cout << "��������ʧ��" << endl;
		}
		cout << "�������Ϣ��" << recv_buf << endl;
	}
	string send_str = "";
	












	cout << "�뷢����Ϣ��";
	// send_buf[100] = "helo lele";
	// cin.getline(send_buf, 100);
	strcpy_s(send_buf, "helo lele\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "auth login\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "MTc5MTc4MTY0NEBxcS5jb20=\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "dmRwb2Vuc2JhdXZhYmJjaA==\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "mail from: <1791781644@qq.com>\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "rcpt to: <1791781644@qq.com>\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;

	strcpy_s(send_buf, "data\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}

	strcpy_s(send_buf, "subject: ����\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}

	strcpy_s(send_buf, "from: 1791781644@qq.com\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}

	strcpy_s(send_buf, "to: 1791781644@qq.com\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}

	strcpy_s(send_buf, "����\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;

	}
	strcpy_s(send_buf, "����\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;

	}
	strcpy_s(send_buf, "����\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;

	}
	strcpy_s(send_buf, "����\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;

	}

	strcpy_s(send_buf, ".\r\n");
	send_len = send(s_server, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		cout << "����ʧ��" << endl;
		
	}
	recv_len = recv(s_server, recv_buf, 1000, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		
	}
	cout << "�������Ϣ��" << recv_buf << endl;


	/*recv_len = recv(s_server, recv_buf, 100, 0);
	if (recv_len < 0) {
		cout << "��������ʧ��" << endl;
		break;
	}
	cout << "�������Ϣ��" << recv_buf << endl;*/













	// �ر��׽���
	closesocket(s_server);
	// �ͷ�dll��Դ
	WSACleanup();
	return 0;
}

void initialization() {
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
	}
	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else {
		cout << "�׽��ֿ�汾��ȷ��" << endl;
	}
	//������˵�ַ��Ϣ
}

// ����������IPv4��ַ���޷������򷵻�-1�������ɹ��򷵻�0
// ��������΢��ٷ��ĵ�������΢�Ķ�
// https://docs.microsoft.com/zh-cn/windows/win32/api/ws2tcpip/nf-ws2tcpip-getaddrinfo
int get_ip_byname(string name, string & ipv4) {
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
	dwRetval = getaddrinfo("smtp.qq.com", NULL, &hints, &result);
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
		ipv4 = ipstr;
	}

	freeaddrinfo(result);
	WSACleanup();
	return 0;
}

// ������Ϣ
int send_messenger(SOCKET& socket_name, string &mes) {
	char send_buf[500];
	strcpy_s(send_buf, mes.c_str());
	int send_len = send(socket_name, send_buf, strlen(send_buf), 0);
	if (send_len < 0) {
		// cout << "����ʧ��" << endl;
		return -1;

	}
	return 0;
}
// ������Ϣ
int recv_messenger(SOCKET& socket_name) {
	char recv_buf[500];		// ���ڴ�Ž��ܵ���Ϣ
	int recv_len = recv(socket_name, recv_buf, 500, 0);
	if (recv_len < 0) {
		// cout << "��������ʧ��" << endl;
		return -1;

	}
	return 0;
}