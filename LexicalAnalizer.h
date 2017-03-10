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

#define UNKNOWN_STRING				L"TOKEN_UNKNOWN"
#define NOUN_STRING					L"TOKEN_NOUN"
#define VERB_STRING					L"TOKEN_VERB"
#define DETERMINER_STRING			L"TOKEN_DETERMINER"
#define ADJECTIVE_STRING			L"TOKEN_ADJECTIVE"
#define INTEGER_STRING				L"TOKEN_INTEGER"
#define FLOAT_STRING				L"TOKEN_FLOAT"
#define SEPARATOR_STRING			L"TOKEN_SEPARATOR"
#define QUESTIONMARK_STRING			L"TOKEN_QUESTIONMARK"
#define OTHERSYMBOL_STRING			L"TOKEN_OTHER_SYMBOL"
#define EXCLAMATION_STRING			L"TOKEN_EXCLAMATION"
#define EOS_STRING					L"TOKEN_EOS"
#define END_OF_TEXT_STRING			L"TOKEN_END_OF_TEXT"

#define CAPITAL_TO_LOWER_CASE_CONST 0x20

#define ADJECTIVE_FILEPATH					L"dictionary/adjectives/adjectives.txt"
#define NOUN_FILEPATH						L"dictionary/nouns/nouns.txt"
#define DETERMINER_FILEPATH					L"dictionary/determiners/determiners.txt"
#define VERB_FILEPATH						L"dictionary/verbs/verbs.txt"
#define NAMES_FILEPATH						L"dictionary/nouns/names.txt"

class LexicalAnalizer
{
public:
	LexicalAnalizer();
	~LexicalAnalizer();
	bool setText(wstring Text);
	int text_length;
	bool getTokens(vector<TokenW>& output);

private:
	wstring::iterator windex2;
	wstring text;
	wstring workingText;
	bool findWord(TokenW& token);
	bool isBlank(const wchar_t& c);
	set<wstring> adjective;
	set<wstring> noun;
	set<wstring> verb;
	set<wstring> determiner;
	set<wstring> names;
	bool findDeterminer(TokenW& token);
	bool findVerb(TokenW& token);
	bool findAdjective(TokenW& token);
	bool findNoun(TokenW& token);
	bool removeCapitals();
	bool getToken(TokenW& token);
	bool getToken2(TokenW& token);
	bool otherValidSymbol(const wchar_t& c);
	bool isALetter(const wchar_t& c);
	bool readDataBaseFile(const wstring filename, set<wstring>& database);
	bool processCharSequence(wchar_t c, TokenW &outputToken);
	bool processCharSequence2(TokenW& outputToken);
	bool processNumberSequence(wchar_t c, TokenW &outputToken);
	bool processNumberSequence2(TokenW &outputToken);
	bool isDigit(wchar_t c);
	bool isTheToken(TokenW input_token, int type);
	wchar_t getNextDigit();
	vector<TokenW> tokens;
	int lineNumber;
	int windex;
};

