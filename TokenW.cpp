#include "stdafx.h"
#include "TokenW.h"


TokenW::TokenW()
{
	type = TOKEN_UNKNOWN;
	text.clear();
	line = -1;
	types.clear();
}


TokenW::~TokenW()
{
}

wstring TokenW::getStringType()
{

	wstring output = L"";
	if ((int)types.size() < 1)
		return output;
	if ((int)types.size() == 1)
	{
		output += types[0];
	}
	else
		for (std::vector<wstring>::iterator i = types.begin(); i != types.end(); i++)
		{
			output += *i;
			if(i != types.end())
				output += L", ";
		}

	return output;
}
