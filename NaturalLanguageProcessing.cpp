#include "stdafx.h"  //________________________________________ NaturalLanguageProcessing.cpp
#include "NaturalLanguageProcessing.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR cmdLine, int cmdShow) {
	NaturalLanguageProcessing app;
	return app.BeginDialog(IDI_NaturalLanguageProcessing, hInstance);
}

void NaturalLanguageProcessing::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvResponse
	lvResponse.Cols.Add(0, LVCFMT_LEFT, 100, L"Text");
	lvResponse.Cols.Add(1, LVCFMT_RIGHT, 200, L"Type");
	item = 0;
}

void NaturalLanguageProcessing::btSubmit_Click(Win::Event& e)
{
	lexicalAnalizer.setText(tbx1.Text);
}

void NaturalLanguageProcessing::bt2_Click(Win::Event& e)
{
	TokenW token;
	wstring text;
	text.clear();

	if (lexicalAnalizer.getToken(token) == true)
	{
		lvResponse.Items.Add(item,token.text);
		lvResponse.Items[item][1].Text = Sys::Convert::ToString(token.type);
		item++;
	}



}

