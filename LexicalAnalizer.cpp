#include "stdafx.h"
#include "LexicalAnalizer.h"


LexicalAnalizer::LexicalAnalizer()
{
	windex = 0;
	lineNumber = 0;
	readDataBaseFile(DETERMINER_FILEPATH, determiner);
	readDataBaseFile(ADJECTIVE_FILEPATH, adjective);
	readDataBaseFile(VERB_FILEPATH, verb);
	readDataBaseFile(NOUN_FILEPATH, noun);
}


LexicalAnalizer::~LexicalAnalizer()
{
}

bool LexicalAnalizer::getToken(TokenW& outputToken)
{
	outputToken.text.clear();
	outputToken.type = TOKEN_UNKNOWN;
	wchar_t c;

	// check if the sentence is over.

	if (windex >= text_length)
	{
		outputToken.type = TOKEN_EOS;
		outputToken.text = L"";
		return false;
	}
	//Eating the white spaces.
	while (workingText[windex] == ' ' || workingText[windex] == '\t' || workingText[windex] == '\r') windex++;
	
	c = workingText[windex];
	//Checking if there is an end of line.

	if (c == '\n')
	{
		lineNumber++;
		windex++;
		c = workingText[windex];
	}

	if (c == '.')
	{
		outputToken.type = TOKEN_EOS;
		outputToken.text = c;
		windex++;
		return true;
	}
	else if (c == ',')
	{
		outputToken.type = TOKEN_SEPARATOR;
		outputToken.text = c;
		windex++;
		return true;
	}
	else if (c == '?')
	{
		outputToken.type = TOKEN_QUESTIONMARK;
		outputToken.text = c;
		windex++;
		return true;
	}
	else
	{
		if(processCharSequence(c,outputToken) == true)
		return true;
	}
	return false;

}

bool LexicalAnalizer::setText(wstring newText)
{
	text.clear();
	workingText.clear();
	text = newText;
	workingText = text;
	windex = 0;
	text_length = workingText.length();
	if (workingText != L"")
		return true;
	return false;
}

//Gets the word without signs at the end.

bool LexicalAnalizer::readDataBaseFile(const wstring filename, set<wstring>& database)
{
	database.clear();
	wstring text;
	if (Sys::FileAssistant::TextLoad(filename, text) == false) return false;
	wstring palabra;

	const int len = (int)text.size();
	wchar_t letra;
	for (int i = 1; i <= len; i++)
	{
		letra = text[i];
		if (letra == '\r') continue;
		if (letra == '\n')
		{
			if (palabra != L"") {
				database.insert(palabra);
				palabra.clear();
			}
		}
		else
		{
			palabra += letra;
		}
	}

	return false;
}

bool LexicalAnalizer::processCharSequence(wchar_t c, TokenW & outputToken)
{
	while (c != ' ' &&
		c != '\t' &&
		c != '.' &&
		c != '\r' &&
		c != '\n' &&
		c != '\0' &&
		c != ',' &&
		c != '?' &&
		c != '!' &&
		c != ';')
		{
			outputToken.text += c;
			c = workingText[++windex];
		}
	if (findWord(outputToken) == true)
		return true;
	else
		return false;
}

bool LexicalAnalizer::findWord(TokenW& token)
{
	token.type = TOKEN_UNKNOWN;

	if (adjective.find(token.text) != adjective.end())
		token.type |= TOKEN_ADJECTIVE;
	if (verb.find(token.text) != verb.end())
		token.type |= TOKEN_VERB;
	if (noun.find(token.text) != noun.end())
		token.type |= TOKEN_NOUN;
	if (determiner.find(token.text) != determiner.end())
		token.type |= TOKEN_DETERMINER;

	if (token.type == TOKEN_UNKNOWN)
		return false;
	else
		return true;

}

bool LexicalAnalizer::isTheToken(TokenW input_token, int type)
{
	if (input_token.type & type != TOKEN_UNKNOWN)
		return true;
	else
		return false;
}



