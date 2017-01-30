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
