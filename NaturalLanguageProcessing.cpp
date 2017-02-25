#include "stdafx.h"  //________________________________________ NaturalLanguageProcessing.cpp
#include "NaturalLanguageProcessing.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR cmdLine, int cmdShow) {
	NaturalLanguageProcessing app;
	return app.BeginDialog(IDI_NaturalLanguageProcessing, hInstance);
}

void NaturalLanguageProcessing::Window_Open(Win::Event& e)
{
	//________________________________________________________ lvResponse
	lvResponse.Cols.Add(0, LVCFMT_LEFT, 40, L"Line");
	lvResponse.Cols.Add(1, LVCFMT_RIGHT, 70, L"Text");
	lvResponse.Cols.Add(2, LVCFMT_RIGHT, 300, L"Type");
	item = 0;
}

void NaturalLanguageProcessing::tbx1_Change(Win::Event& e)
{
	if (tbx1.Text != L"")
	{
		lexicalAnalizer.setText(tbx1.Text);
		vector<TokenW> tokens;
		wstring text;
		text.clear();
		lvResponse.Items.DeleteAll();
		item = 0;
		if (lexicalAnalizer.getTokens(tokens) == true)
		{
			for (int i = 0; i < (int)tokens.size(); i++) {
				lvResponse.Items.Add(item, Sys::Convert::ToString(tokens[i].line));
				lvResponse.Items[item][1].Text = tokens[i].text;
				lvResponse.Items[item][2].Text = tokens[i].getStringType();
				item++;
			}
		}
	}
}

