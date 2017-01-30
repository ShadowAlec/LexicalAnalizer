#pragma once
#define TOKEN_UNKNOWN				0
#define TOKEN_NOUN					1
#define TOKEN_VERB					2
#define TOKEN_DETERMINER			4
#define TOKEN_ADJECTIVE				8	
#define TOKEN_INTEGER				16
#define	TOKEN_FLOAT					32
#define TOKEN_SEPARATOR				64
#define TOKEN_QUESTIONMARK			128
#define TOKEN_OTHERSYMBOL			256
#define TOKEN_EOS					512

class TokenW
{
public:
	TokenW();
	~TokenW();
	__int32 type;
	wstring text;
	int line;
};

