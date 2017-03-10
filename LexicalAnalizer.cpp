#include "stdafx.h"
#include "LexicalAnalizer.h"


LexicalAnalizer::LexicalAnalizer()
{
	windex = 0;
	lineNumber = 1;
	readDataBaseFile(DETERMINER_FILEPATH, determiner);
	readDataBaseFile(ADJECTIVE_FILEPATH, adjective);
	readDataBaseFile(VERB_FILEPATH, verb);
	readDataBaseFile(NOUN_FILEPATH, noun);
	readDataBaseFile(NAMES_FILEPATH, names);
	
}


LexicalAnalizer::~LexicalAnalizer()
{
}

//											Removes the capital letters from the working string.

bool LexicalAnalizer::removeCapitals()
{
	for (wstring::iterator i = workingText.begin(); i != workingText.end();i++)
	{
		if (*i >= 'A' && *i <= 'Z')
			*i += CAPITAL_TO_LOWER_CASE_CONST;
	}
	return false;
}


bool LexicalAnalizer::isBlank(const wchar_t& c)
{
	switch (c)
	{
		
	case 9:		//		character tabulation
	case 10:	//		line feed
	case 11:	//		line tabulation
	case 12:	//		form feed
	case 13:	//		carriage return
	case 32:	//		space
	case 133:	//		No break space.
	case 5760:	//		ogham space mark
	case 8192:	//		en quad
	case 8193:	//		em quad
	case 8194:	//		en space
	case 8195:	//		em space
	case 8196:	//		three-per-em space
	case 8197:	//		four-per-em space
	case 8198:	//		six-per-em space
	case 8199:	//		figure space
	case 8200:	//		punctuation space
	case 8201:	//		thin space
	case 8202:	//		hair space
	case 8232:	//		line separator
	case 8233:	//		paragraph separator
	case 8239:	//		narrow no-break space
	case 8287:	//		medium mathematical space
	case 12288:	//		ideographic space
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool LexicalAnalizer::otherValidSymbol(const wchar_t& c)
{
	if (!isALetter(c))
	{
		if ((c <= '!' && c >= '.') || 
			(c <= ':' && c >= '@') ||
			(c <= '{' && c >= '~') ||
			(c <= '{' && c >= '~') ) return true;
	}
	return false;
}

bool LexicalAnalizer::isALetter(const wchar_t& c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
	return false;
}

//											Gets the word without other tokens at the end.

bool LexicalAnalizer::getToken(TokenW& outputToken)
{
	static bool END_OF_TEXT = false;
	outputToken.text.clear();
	outputToken.types.clear();
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
		outputToken.types.push_back(END_OF_TEXT_STRING);
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
		outputToken.types.push_back(EOS_STRING);
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == ',')
	{
		outputToken.type = TOKEN_SEPARATOR;
		outputToken.types.push_back(SEPARATOR_STRING);
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == '?')
	{
		outputToken.type = TOKEN_QUESTIONMARK;
		outputToken.types.push_back(QUESTIONMARK_STRING);
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == '!')
	{
		outputToken.type = TOKEN_EXCLAMATION;
		outputToken.types.push_back(EXCLAMATION_STRING);
		outputToken.text = c;
		outputToken.line = lineNumber;
		windex++;
		return true;
	}
	else if (c == '-')
	{
		if (isDigit(workingText[windex + 1]))
		{
			outputToken.text += workingText[windex++];
			if(processNumberSequence(workingText[windex], outputToken))
			return true;
		}
		else
		{
			outputToken.type = TOKEN_SEPARATOR;
			outputToken.types.push_back(SEPARATOR_STRING);
			outputToken.text = c;
			outputToken.line = lineNumber;
			windex++;
			return true;
		}
		
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
bool LexicalAnalizer::getToken2(TokenW& outputToken)
{
	static bool END_OF_TEXT_2 = false;

	outputToken.text.clear();
	outputToken.types.clear();
	outputToken.type = TOKEN_UNKNOWN;

	//removing blank spaces
	if(windex2 != workingText.end())
	while (isBlank(*windex2) && windex2 != workingText.end())
	{
		if (*windex2 == '\n')
			lineNumber++;
		windex2++;
	}
	// Cheking if the text is over.
	if (windex2 == workingText.end())
	{
		outputToken.type = TOKEN_END_OF_TEXT;
		outputToken.types.push_back(END_OF_TEXT_STRING);
		outputToken.text = L"";
		if (!END_OF_TEXT_2)
		{
			END_OF_TEXT_2 = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	//checking jump line and setting it to the output.
	if (*windex2 == '\n')
	{
		lineNumber++;
		windex2++;
	}
	outputToken.line = lineNumber;

	// If it's a letter, process the character sequence.
	if (isALetter(*windex2))
	{
		processCharSequence2(outputToken);
		return true;
	}
	else if (isDigit(*windex2))
	{
		processNumberSequence2(outputToken);
	}
	else if (otherValidSymbol(*windex2))
	{
		return true;
	}

	return false;

}

//													Sets the text to be analized.

bool LexicalAnalizer::setText(wstring newText)
{
	text.clear();
	workingText.clear();
	text = newText;
	workingText = text;
	windex = 0;
	text_length = workingText.length();
	removeCapitals();
	windex2 = workingText.begin();
	if (workingText != L"")
		return true;
	return false;
}


//																from the text set extracts the tokens.
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

											//				

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

bool LexicalAnalizer::processCharSequence2(TokenW & outputToken)
{
	while (windex2 != workingText.end() && !isBlank(*windex2) && !otherValidSymbol(*windex2) && *windex2 != '\n' && *windex2 != '\r')
	{
		outputToken.text += *windex2;
		windex2++;
	}
	if (findWord(outputToken) && outputToken.text != L"")
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
			outputToken.types.push_back(FLOAT_STRING);
		}
		else
		{
			outputToken.type = TOKEN_INTEGER;
			outputToken.types.push_back(INTEGER_STRING);
		}
	}
	else
	{
		outputToken.types.push_back(INTEGER_STRING);
		outputToken.type = TOKEN_INTEGER;
	}

	if (outputToken.type != TOKEN_UNKNOWN)
		return true;
	else
		return false;
}

bool LexicalAnalizer::processNumberSequence2(TokenW & outputToken)
{
	while (isDigit(*windex2) && windex2 != workingText.end())
	{
		outputToken.text += *windex2;
	}
	if (getNextDigit() == '.')
	{
		if (isDigit(getNextDigit()))
		{
			outputToken.text += *windex2++;		//	Agrega el punto al texto.
			while (isDigit(*windex2) && windex2 != workingText.end())
			{
				outputToken.text += *windex2;
			}
			outputToken.type = TOKEN_FLOAT;
			outputToken.types.push_back(FLOAT_STRING);
		}
		else
		{
			outputToken.type = TOKEN_INTEGER;
			outputToken.types.push_back(INTEGER_STRING);
		}
	}
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
	if (findDeterminer(token) || findVerb(token) || findAdjective(token) || findNoun(token))
		return true;
	else
	{
		token.types.clear();
		token.types.push_back(UNKNOWN_STRING);
		return false;
	}
}



bool LexicalAnalizer::isTheToken(TokenW input_token, int type)
{
	if (input_token.type & type != TOKEN_UNKNOWN)
		return true;
	else
		return false;
}

wchar_t LexicalAnalizer::getNextDigit()
{
	windex2++;
	wchar_t c;
	if (windex2 != workingText.end())
	{
		c = *windex2;
		windex--;
		return c;
	}
	else
	{
		windex--;
		return L'\0';
	}
}

bool LexicalAnalizer::findDeterminer(TokenW& token) {

	if (determiner.find(token.text) != determiner.end())
	{
		token.types.push_back(DETERMINER_STRING);
		token.type |= TOKEN_DETERMINER;
		return true;
	}
	return false;

}
bool LexicalAnalizer::findVerb(TokenW& token) {

	if (verb.find(token.text) != verb.end())
	{
		token.types.push_back(VERB_STRING);
		token.type |= TOKEN_VERB;
		return true;
	}
	return false;

}
bool LexicalAnalizer::findAdjective(TokenW& token) {

	if (adjective.find(token.text) != adjective.end())
	{
		token.types.push_back(ADJECTIVE_STRING);
		token.type |= TOKEN_ADJECTIVE;
		return true;
	}
	return false;

}
bool LexicalAnalizer::findNoun(TokenW& token) {
	if (noun.find(token.text) != noun.end() || names.find(token.text) != names.end())
	{
		token.types.push_back(NOUN_STRING);
		token.type |= TOKEN_NOUN;
		return true;
	}
	return false;
}