// test.h - 包含所有函数的声明
#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif


// 测试用函数，直接返回1
extern "C" MATHLIBRARY_API int test();

extern "C" MATHLIBRARY_API class MyClass
{
public:
	MyClass();
	~MyClass();
	int int_test();

private:

};

