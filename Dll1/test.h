// test.h - �������к���������
#pragma once
#include <iostream>
#include <wtypes.h>
using namespace std;

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


// �����ʼ�����
extern "C" MATHLIBRARY_API int send_mail(LPSTR account, LPSTR password, LPSTR site, LPSTR receiver, LPSTR subject, LPSTR mail_data, int port=25);
