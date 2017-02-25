#include "stdafx.h"
#include "TokenW.h"


TokenW::TokenW()
{
	type = TOKEN_UNKNOWN;
	text.clear();
	line = -1;
}


TokenW::~TokenW()
{
}

wstring TokenW::getStringType()
{
	wstring output = L"";
	
	if (type & TOKEN_NOUN)
		output += L"TOKEN_NOUN ";
	if (type & TOKEN_VERB)
		output += L"TOKEN_VERB ";
	if (type & TOKEN_DETERMINER)
		output += L"TOKEN_DETERMINER ";
	if (type & TOKEN_ADJECTIVE)
		output += L"TOKEN_ADJECTIVE ";
	if (type & TOKEN_INTEGER)
		output += L"TOKEN_INTEGER ";
	if (type & TOKEN_FLOAT)
		output += L"TOKEN_FLOAT ";
	if (type & TOKEN_SEPARATOR)
		output += L"TOKEN_SEPARATOR ";
	if (type & TOKEN_QUESTIONMARK)
		output += L"TOKEN_QUESTIONMARK ";
	if (type & TOKEN_OTHERSYMBOL)
		output += L"TOKEN_OTHERSYMBOL ";
	if (type & TOKEN_EXCLAMATION)
		output += L"TOKEN_EXCLAMATION ";
	if (type & TOKEN_EOS)
		output += L"TOKEN_EOS ";
	if (type & TOKEN_END_OF_TEXT)
		output += L"TOKEN_END_OF_TEXT ";
	if (!(type | TOKEN_UNKNOWN))
		output = L"TOKEN_UNKNOWN";

	return output;
}
