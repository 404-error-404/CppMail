#include "pch.h"
#include "test.h"
#include "smtp_mail.h"
#include <iostream>
using namespace std;

/*
LPSTR account, �˺�
LPSTR password, ���룬QQ������Ҫ��QQ������Ȩ��
LPSTR site, ��ַ
LPSTR receiver, ������
LPSTR subject, ����,smtp.qq.com��
LPSTR mail_data, �ʼ�����
int port, �˿ںţ�Ĭ����25��SMTP����Ĭ�϶˿ںţ�

��C#�е��õ�ʱ��Ҫ��������

[System.Runtime.InteropServices.DllImport(@"K:\C++ Project\CppMail\Debug\Dll1.dll", EntryPoint = "send_mail", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = false)]
public static extern int send_mail(
        [MarshalAs(UnmanagedType.LPStr)] string account,    // �˺�
        [MarshalAs(UnmanagedType.LPStr)] string password,   // ���룬QQ������Ҫ��QQ������Ȩ��
        [MarshalAs(UnmanagedType.LPStr)] string site,       // ��ַ,smtp.qq.com��
        [MarshalAs(UnmanagedType.LPStr)] string receiver,   // ������
        [MarshalAs(UnmanagedType.LPStr)] string subject,    // ����
        [MarshalAs(UnmanagedType.LPStr)] string mail_data,  // �ʼ�����
        int port = 25                                       // �˿ںţ�Ĭ����25��SMTP����Ĭ�϶˿ںţ�
    );


���еĲ��������ǣ�


@"K:\C++ Project\CppMail\Debug\Dll1.dll",       ָ��dllλ��
EntryPoint = "send_mail",                       ָ���������
CharSet = CharSet.Ansi,                         �ַ������µ�һ�����⣬д���±ߵ�ע����ߡ�
CallingConvention = CallingConvention.Cdecl,    ������һ��ᱨ��  ������ PInvoke ǩ���ĵ���Լ���Ͳ�������йܵ�Ŀ��ǩ���Ƿ�ƥ�䡱
ExactSpelling = false                           ���ϳ��ģ���֪����ɶ��

*/
int send_mail(LPSTR account, LPSTR password, LPSTR site, LPSTR receiver, LPSTR subject, LPSTR mail_data, int port) {
    smtp_mail mailclient;
    mailclient.account = account;
    mailclient.password = password;
    mailclient.receiver = receiver;
    mailclient.site = site;
    mailclient.subject = subject;
    mailclient.data = mail_data;
    mailclient.port = port;
    return mailclient.send_mail();
}


// ��¼һ�£������ַ�������Ļ����±ߵķ���
// ��Ҳ�и����⣬��������ڴ������ĵ�ʱ��ᵼ�����Ĳ��ֳ��ȼ��룬���� �����ԡ������ܵ���ֻ�� ���⡱�������ǲ��ԡ��������ǡ���������as���ԡ���������as��
// ��ʱ����֪��Ϊɶ������ûʱ��ȥ���ˣ��²��������ַ���Ӣ���ַ���ռλ����
/*
int send_mail2(LPSTR account[][2], LPSTR site, LPSTR mail[][3], int port) {

    smtp_mail mailclient;
    mailclient.account = (*account)[0];
    mailclient.password = (*account)[1];
    mailclient.receiver = (*mail)[0];
    mailclient.site = site;
    mailclient.subject = (*mail)[1];
    mailclient.data = (*mail)[2];
    mailclient.port = port;
    return mailclient.send_mail();
}
*/