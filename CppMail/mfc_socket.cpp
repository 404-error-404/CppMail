#include <winsock.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

void initialization();


int mfc_socket() {
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
	server_addr.sin_addr.S_un.S_addr = inet_addr("58.251.106.181");
	server_addr.sin_port = htons(25);
	// �����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "����������ʧ��" << endl;
		WSACleanup();
	}
	else {
		cout << "���������ӳɹ�";
	}
	string send_str = "";
	while (true) {
		cout << "�뷢����Ϣ��";
		// send_buf[100] = "helo lele";
		bv     cin.getline(send_str);
		send_len = send(s_server, send_buf, 100, 0);
		if (send_len < 0) {
			cout << "����ʧ��" << endl;
			break;
		}
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "��������ʧ��" << endl;
			break;
		}
		cout << "�������Ϣ��" << recv_buf << endl;
	}
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