#pragma once  //______________________________________ NaturalLanguageProcessing.h  
#include "Resource.h"
#include "LexicalAnalizer.h"
#include "TokenW.h"
class NaturalLanguageProcessing : public Win::Dialog
{
public:
	NaturalLanguageProcessing()
	{
		item = 0;
	}
	~NaturalLanguageProcessing()
	{
	}
private:
	int item;
	LexicalAnalizer lexicalAnalizer;
protected:
	//______ Wintempla GUI manager section begin: DO NOT EDIT AFTER THIS LINE
	Win::Textbox tbx1;
	Win::ListView lvResponse;
	Win::Button btSubmit;
	Win::Button bt2;
protected:
	Win::Gdi::Font fontArial014A;
	void GetDialogTemplate(DLGTEMPLATE& dlgTemplate)
	{
		dlgTemplate.cx = Sys::Convert::PixelToDlgUnitX(1027);
		dlgTemplate.cy = Sys::Convert::PixelToDlgUnitY(356);
		dlgTemplate.style = WS_CAPTION | WS_POPUP | WS_SYSMENU | WS_VISIBLE | DS_CENTER | DS_MODALFRAME;
	}
	//_________________________________________________
	void InitializeGui()
	{
		this->Text = L"NaturalLanguageProcessing";
		tbx1.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_HSCROLL | WS_TABSTOP | WS_VISIBLE | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN | ES_LEFT | ES_WINNORMALCASE, 21, 28, 427, 320, hWnd, 1000);
		lvResponse.Create(WS_EX_CLIENTEDGE, NULL, WS_CHILD | WS_TABSTOP | WS_VISIBLE | LVS_REPORT, 475, 25, 448, 324, hWnd, 1001);
		btSubmit.Create(NULL, L"Submit", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 947, 23, 73, 28, hWnd, 1002);
		bt2.Create(NULL, L"Token", WS_CHILD | WS_TABSTOP | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, 948, 61, 72, 28, hWnd, 1003);
		lvResponse.SetExtStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		fontArial014A.Create(L"Arial", 14, false, false, false, false);
		tbx1.Font = fontArial014A;
		lvResponse.Font = fontArial014A;
		btSubmit.Font = fontArial014A;
		bt2.Font = fontArial014A;
	}
	//_________________________________________________
	void tbx1_Change(Win::Event& e);
	void btSubmit_Click(Win::Event& e);
	void bt2_Click(Win::Event& e);
	void Window_Open(Win::Event& e);
	//_________________________________________________
	bool EventHandler(Win::Event& e)
	{
		if (tbx1.IsEvent(e, EN_CHANGE)) {tbx1_Change(e); return true;}
		if (btSubmit.IsEvent(e, BN_CLICKED)) {btSubmit_Click(e); return true;}
		if (bt2.IsEvent(e, BN_CLICKED)) {bt2_Click(e); return true;}
		return false;
	}
};
