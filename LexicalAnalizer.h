#pragma once
#include "TokenW.h"

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

#define ADJECTIVE_FILEPATH	L"dictionary/adjective.txt"
#define NOUN_FILEPATH		L"dictionary/noun.txt"
#define DETERMINER_FILEPATH	L"dictionary/determiner.txt"
#define VERB_FILEPATH		L"dictionary/verb.txt"

class LexicalAnalizer
{
public:
	LexicalAnalizer();
	~LexicalAnalizer();
	bool getToken(TokenW& token);
	bool setText(wstring Text);
	wstring text;
	wstring workingText;
	int text_length;

	//private:
	set<wstring> adjective;
	set<wstring> noun;
	set<wstring> verb;
	set<wstring> determiner;

	bool findWord(TokenW& token);

private:
	bool readDataBaseFile(const wstring filename, set<wstring>& database);
	bool processCharSequence(wchar_t c, TokenW &outputToken);
	
	bool isTheToken(TokenW input_token, int type);
	int lineNumber;
	int windex;
};

