#include "stdafx.h"
#include "LexicalAnalizer.h"


LexicalAnalizer::LexicalAnalizer()
{
	windex = 0;
	lineNumber = 1;
	END_OF_TEXT = false;
	readDataBaseFile(DETERMINER_FILEPATH, determiner);
	readDataBaseFile(ADJECTIVE_FILEPATH, adjective);
	readDataBaseFile(VERB_FILEPATH, verb);
	readDataBaseFile(NOUN_FILEPATH, noun);
	readDataBaseFile(NAMES_FILEPATH, names);
}


LexicalAnalizer::~LexicalAnalizer()
{
}

bool LexicalAnalizer::removeCapitals()
{
	for (int i = 0; i < (int)text.size(); i++)
	{
		if (text[i] >= 'A' && text[i] <= 'Z')
			workingText[i] += CAPITAL_TO_LOWER_CASE_CONST;
	}
	return false;
}

bool LexicalAnalizer::getToken(TokenW& outputToken)
{
	outputToken.text.clear();
	outputToken.type = TOKEN_UNKNOWN;
	
	wchar_t c;

	// check if the sentence is over.

	//Eating the white spaces.
	while (workingText[windex] == ' ' || workingText[windex] == '\t' || workingText[windex] == '\r' && windex<text_length) windex++;
	
	c = workingText[windex];
	//Checking if there is an end of line.
	if (c == '\n')
	{
		lineNumber++;
		c = workingText[++windex];
	}
	if (windex >= text_length)
	{
		outputToken.type = TOKEN_END_OF_TEXT;
		outputToken.text = L"";
		if (END_OF_TEXT == false)
		{
			END_OF_TEXT = true;
			return true;
		}
		else
			return false;
	}
	outputToken.line = lineNumber;

	if (c == '.')
	{
		outputToken.type = TOKEN_EOS;
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == ',')
	{
		outputToken.type = TOKEN_SEPARATOR;
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == '?')
	{
		outputToken.type = TOKEN_QUESTIONMARK;
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == '!')
	{
		outputToken.type = TOKEN_EXCLAMATION;
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (isDigit(c))
	{
		if (processNumberSequence(c, outputToken) == true) {
			outputToken.line = lineNumber;
			return true;
		}
	}
	else
	{
		if (processCharSequence(c, outputToken) == true) {
			outputToken.line = lineNumber;
			return true;
		}
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
	removeCapitals();
	if (workingText != L"")
		return true;
	return false;
}

//Gets the word without other tokens at the end.

bool LexicalAnalizer::getTokens(vector<TokenW>& output)
{
	lineNumber = 1;
	TokenW token;
	do {
		getToken(token);
		output.push_back(token);
	} while (token.type != TOKEN_END_OF_TEXT);
	if (output.size() != 0)
		return true;
	else
		return false;
}

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
	if (findWord(outputToken) == true && outputToken.text!= L"")
		return true;
	else
		return false;
}

bool LexicalAnalizer::processNumberSequence(wchar_t c, TokenW & outputToken)
{
	while (isDigit(c)) {
		outputToken.text += c;
		c = workingText[++windex];
	}
	if (c == '.')
	{
		if (isDigit(workingText[windex + 1]))
		{
			outputToken.text += c;
			c = workingText[++windex];
			while (isDigit(c))
			{
				outputToken.text += c;
				c = workingText[++windex];
			}
			outputToken.type = TOKEN_FLOAT;
		}
		else
		{
			outputToken.type = TOKEN_INTEGER;
		}
	}
	else
		outputToken.type = TOKEN_INTEGER;


	if (outputToken.type != TOKEN_UNKNOWN)
		return true;
	else
		return false;
}

bool LexicalAnalizer::isDigit(wchar_t c)
{
	bool value = false;
	switch (c)
	{
	case '0':
		value = true;
		break;
	case '1':
		value = true;
		break;
	case '2':
		value = true;
		break;
	case '3':
		value = true;
		break;
	case '4':
		value = true;
		break;
	case '5':
		value = true;
		break;
	case '6':
		value = true;
		break;
	case '7':
		value = true;
		break;
	case '8':
		value = true;
		break;
	case '9':
		value = true;
		break;
	default:
		value = false;
		break;
	}
	return value;
}

bool LexicalAnalizer::findWord(TokenW& token)
{
	token.type = TOKEN_UNKNOWN;

	if (adjective.find(token.text) != adjective.end())
		token.type |= TOKEN_ADJECTIVE;
	if (verb.find(token.text) != verb.end())
		token.type |= TOKEN_VERB;
	if (noun.find(token.text) != noun.end() )//|| names.find(token.text) != names.end())
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

