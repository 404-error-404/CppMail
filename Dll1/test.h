// test.h - �������к���������
#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


// �����ú�����ֱ�ӷ���1
extern "C" MATHLIBRARY_API int test();

extern "C" MATHLIBRARY_API class MyClass
{
public:
	MyClass();
	~MyClass();
	int int_test();

private:

};

