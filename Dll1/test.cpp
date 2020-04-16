#include "pch.h"
#include "test.h"
#include "smtp_mail.h"
#include <iostream>
using namespace std;

/*
LPSTR account, 账号
LPSTR password, 密码，QQ邮箱需要是QQ邮箱授权码
LPSTR site, 网址
LPSTR receiver, 接受者
LPSTR subject, 主题,smtp.qq.com等
LPSTR mail_data, 邮件内容
int port, 端口号，默认是25（SMTP服务默认端口号）

在C#中调用的时候：要这样声明

[System.Runtime.InteropServices.DllImport(@"K:\C++ Project\CppMail\Debug\Dll1.dll", EntryPoint = "send_mail", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, ExactSpelling = false)]
public static extern int send_mail(
        [MarshalAs(UnmanagedType.LPStr)] string account,    // 账号
        [MarshalAs(UnmanagedType.LPStr)] string password,   // 密码，QQ邮箱需要是QQ邮箱授权码
        [MarshalAs(UnmanagedType.LPStr)] string site,       // 网址,smtp.qq.com等
        [MarshalAs(UnmanagedType.LPStr)] string receiver,   // 接受者
        [MarshalAs(UnmanagedType.LPStr)] string subject,    // 主题
        [MarshalAs(UnmanagedType.LPStr)] string mail_data,  // 邮件内容
        int port = 25                                       // 端口号，默认是25（SMTP服务默认端口号）
    );


其中的参数意义是：


@"K:\C++ Project\CppMail\Debug\Dll1.dll",       指明dll位置
EntryPoint = "send_mail",                       指明函数入口
CharSet = CharSet.Ansi,                         字符集【猜到一个问题，写在下边的注释里边】
CallingConvention = CallingConvention.Cdecl,    不加这一句会报错  “请检查 PInvoke 签名的调用约定和参数与非托管的目标签名是否匹配”
ExactSpelling = false                           网上抄的，不知道有啥用

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


// 记录一下，传递字符串数组的话用下边的方法
// 但也有个问题，这个方法在传输中文的时候会导致中文部分长度减半，比如 “测试”，接受到的只有 “测”；“这是测试”→“这是”；“这是as测试”→“这是as”
// 暂时还不知道为啥，但是没时间去查了，猜测是中文字符和英文字符的占位问题
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