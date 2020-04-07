// test.h - 包含所有函数的声明
#pragma once
#include <iostream>
#include <wtypes.h>
using namespace std;

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


// 发送邮件函数
extern "C" MATHLIBRARY_API int send_mail(LPSTR account, LPSTR password, LPSTR site, LPSTR receiver, LPSTR subject, LPSTR mail_data, int port=25);
