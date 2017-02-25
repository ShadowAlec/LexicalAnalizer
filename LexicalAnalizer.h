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
#define TOKEN_EXCLAMATION			512
#define TOKEN_EOS					1024
#define TOKEN_END_OF_TEXT			2048

#define CAPITAL_TO_LOWER_CASE_CONST 0x20

#define ADJECTIVE_FILEPATH					L"dictionary/adjective.txt"
#define NOUN_FILEPATH						L"dictionary/noun.txt"
#define DETERMINER_FILEPATH					L"dictionary/determiner.txt"
#define VERB_FILEPATH						L"dictionary/verb.txt"
#define NAMES_FILEPATH						L"dictionary/nouns/names.txt"

class LexicalAnalizer
{
public:
	LexicalAnalizer();
	~LexicalAnalizer();
	bool setText(wstring Text);
	wstring text;
	wstring workingText;
	int text_length;

	//private:
	set<wstring> adjective;
	set<wstring> noun;
	set<wstring> verb;
	set<wstring> determiner;
	set<wstring> names;
	bool findWord(TokenW& token);
	bool getTokens(vector<TokenW>& output);

private:
	bool removeCapitals();
	bool getToken(TokenW& token);
	bool END_OF_TEXT;
	bool readDataBaseFile(const wstring filename, set<wstring>& database);
	bool processCharSequence(wchar_t c, TokenW &outputToken);
	bool processNumberSequence(wchar_t c, TokenW &outputToken);
	bool isDigit(wchar_t c);
	bool isTheToken(TokenW input_token, int type);
	vector<TokenW> tokens;
	int lineNumber;
	int windex;
};

