#ifndef TEST_COLON_IN_C_LANGUAGE_H
#define TEST_COLON_IN_C_LANGUAGE_H

typedef struct
{
	int i : 30;
	int j : 3;
	int k : 3;
	int h : 3;
}colon_str;

typedef union
{
	colon_str c_tr;
	char c;
}colon_un;

extern int test_colon_in_c_language();

#endif // !TEST_COLON_IN_C_LANGUAGE_H


