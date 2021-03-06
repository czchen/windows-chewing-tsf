#include "ChewingConfig.h"

using namespace Chewing;

#define DEF_FONT_SIZE           16

const char* Config::selKeys[]={
	"1234567890",
	"asdfghjkl;",
	"asdfzxcv89",
	"asdfjkl789",
	"aoeuhtn789",
    "1234qweras",
	NULL
};

Config::Config(void) {
	// Configuration
	keyboardLayout = 0;
	candPerRow = 4;
	defaultEnglish = false;
	defaultFullSpace = false;
	spaceAsSelection = false;
	enableShift = true;
	shiftCapital = false;
	enableSimp = false;
	addPhraseForward = true;
	hideStatusWnd = false;
	fixCompWnd = false;
	colorCandWnd = true;
	coloredCompCursor = false;
	advanceAfterSelection = true;
	fontSize = DEF_FONT_SIZE;
	selKeyType = 0;
	// selAreaLen = 50;
	candPerPage = 9;
	cursorCandList = 1;
	enableCapsLock = 0;
	shiftFullShape = 1;
	phraseMark = 1;
	escCleanAllBuf = 0;
	shiftSymbol = 0;
	ctrlSymbol = 0;
	checkNewVersion = true;	// Enable update notifier
}

Config::~Config(void) {
}


void Config::load() {
/*
	#define KB_TYPE_NUM 9
	#define KB_DEFAULT 0
	#define KB_HSU 1
	#define KB_IBM 2
	#define KB_GIN_YIEH 3
	#define KB_ET 4
	#define KB_ET26 5
	#define KB_DVORAK 6
	#define KB_DVORAK_HSU 7
	#define KB_HANYU_PINYING 8
*/
	HKEY hk = NULL;
	if(ERROR_SUCCESS == ::RegOpenKeyW(HKEY_CURRENT_USER, L"Software\\ChewingTextService", &hk)) {
		DWORD size = sizeof(DWORD);
		DWORD type = REG_DWORD;
		::RegQueryValueEx(hk, L"KeyboardLayout", 0, &type, (LPBYTE)&keyboardLayout, &size);		
		::RegQueryValueEx(hk, L"CandPerRow", 0, &type, (LPBYTE)&candPerRow, &size);
		::RegQueryValueEx(hk, L"DefaultEnglish", 0, &type, (LPBYTE)&defaultEnglish, &size);
		::RegQueryValueEx(hk, L"DefaultFullSpace", 0, &type, (LPBYTE)&defaultFullSpace, &size);
		::RegQueryValueEx(hk, L"SpaceAsSelection", 0, &type, (LPBYTE)&spaceAsSelection, &size);
		::RegQueryValueEx(hk, L"EnableShift", 0, &type, (LPBYTE)&enableShift, &size);
		::RegQueryValueEx(hk, L"ShiftCapital", 0, &type, (LPBYTE)&shiftCapital, &size);
		::RegQueryValueEx(hk, L"EnableSimp", 0, &type, (LPBYTE)&enableSimp, &size);
		::RegQueryValueEx(hk, L"AddPhraseForward", 0, &type, (LPBYTE)&addPhraseForward, &size);
		::RegQueryValueEx(hk, L"FixCompWnd", 0, &type, (LPBYTE)&fixCompWnd, &size);
		::RegQueryValueEx(hk, L"HideStatusWnd", 0, &type, (LPBYTE)&hideStatusWnd, &size);
		::RegQueryValueEx(hk, L"ColorCandWnd", 0, &type, (LPBYTE)&colorCandWnd, &size);
		::RegQueryValueEx(hk, L"ColorCompCursor", 0, &type, (LPBYTE)&coloredCompCursor, &size);
		::RegQueryValueEx(hk, L"AdvanceAfterSelection", 0, &type, (LPBYTE)&advanceAfterSelection, &size);
        ::RegQueryValueEx(hk, L"DefFontSize", 0, &type, (LPBYTE)&fontSize, &size);
		::RegQueryValueEx(hk, L"SelKeyType", 0, &type, (LPBYTE)&selKeyType, &size);
		//::RegQueryValueEx(hk, L"SelAreaLen", 0, &type, (LPBYTE)&selAreaLen, &size);
		::RegQueryValueEx(hk, L"SelAreaLen", 0, &type, (LPBYTE)&candPerPage, &size);
		::RegQueryValueEx(hk, L"CursorCandList", 0, &type, (LPBYTE)&cursorCandList, &size);
		::RegQueryValueEx(hk, L"EnableCapsLock", 0, &type, (LPBYTE)&enableCapsLock, &size);
		::RegQueryValueEx(hk, L"ShiftFullShape", 0, &type, (LPBYTE)&shiftFullShape, &size);
		::RegQueryValueEx(hk, L"PhraseMark", 0, &type, (LPBYTE)&phraseMark, &size);
		::RegQueryValueEx(hk, L"EscCleanAllBuf", 0, &type, (LPBYTE)&escCleanAllBuf, &size);
		::RegQueryValueEx(hk, L"ShiftSymbol", 0, &type, (LPBYTE)&shiftSymbol, &size);
		::RegQueryValueEx(hk, L"CtrlSymbol", 0, &type, (LPBYTE)&ctrlSymbol, &size);

		::RegQueryValueEx(hk, L"CheckNewVersion", 0, &type, (LPBYTE)&checkNewVersion, &size);
		::RegCloseKey(hk);
	}

	if(selKeyType > ((sizeof(selKeys)/sizeof(char*))-1))
		selKeyType = 0;

	//if(selAreaLen > 55 || selAreaLen < 40)
	//	selAreaLen = 40;
#if 0
	if(chewing)
		chewing->SelKey((char*)selKeys[selKeyType]);
    if (chewing!=NULL)
        chewing->SetAdvanceAfterSelection((AdvanceAfterSelection!=0)?true: false);
    if (FontSize>64 || FontSize<4)
        FontSize = DEF_FONT_SIZE;
#endif
}


void Config::save() {
	HKEY hk = NULL;
	if(ERROR_SUCCESS == ::RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\ChewingTextService", 0, 
			NULL, 0, KEY_ALL_ACCESS , NULL, &hk, NULL)) {
		::RegSetValueEx(hk, L"KeyboardLayout", 0, REG_DWORD, (LPBYTE)&keyboardLayout, sizeof(DWORD));
		::RegSetValueEx(hk, L"CandPerRow", 0, REG_DWORD, (LPBYTE)&candPerRow, sizeof(DWORD));
		::RegSetValueEx(hk, L"DefaultEnglish", 0, REG_DWORD, (LPBYTE)&defaultEnglish, sizeof(DWORD));
		::RegSetValueEx(hk, L"DefaultFullSpace", 0, REG_DWORD, (LPBYTE)&defaultFullSpace, sizeof(DWORD));
		::RegSetValueEx(hk, L"SpaceAsSelection", 0, REG_DWORD, (LPBYTE)&spaceAsSelection, sizeof(DWORD));
		::RegSetValueEx(hk, L"EnableShift", 0, REG_DWORD, (LPBYTE)&enableShift, sizeof(DWORD));
		::RegSetValueEx(hk, L"ShiftCapital", 0, REG_DWORD, (LPBYTE)&shiftCapital, sizeof(DWORD));
		::RegSetValueEx(hk, L"EnableSimp", 0, REG_DWORD, (LPBYTE)&enableSimp, sizeof(DWORD));
		::RegSetValueEx(hk, L"AddPhraseForward", 0, REG_DWORD, (LPBYTE)&addPhraseForward, sizeof(DWORD));
		::RegSetValueEx(hk, L"FixCompWnd", 0, REG_DWORD, (LPBYTE)&fixCompWnd, sizeof(DWORD));
		::RegSetValueEx(hk, L"HideStatusWnd", 0, REG_DWORD, (LPBYTE)&hideStatusWnd, sizeof(DWORD));
		::RegSetValueEx(hk, L"ColorCandWnd", 0, REG_DWORD, (LPBYTE)&colorCandWnd, sizeof(DWORD));
		::RegSetValueEx(hk, L"ColorCompCursor", 0, REG_DWORD, (LPBYTE)&coloredCompCursor, sizeof(DWORD));
		::RegSetValueEx(hk, L"AdvanceAfterSelection", 0, REG_DWORD, (LPBYTE)&advanceAfterSelection, sizeof(DWORD));
		::RegSetValueEx(hk, L"DefFontSize", 0, REG_DWORD, (LPBYTE)&fontSize, sizeof(DWORD));
		::RegSetValueEx(hk, L"SelKeyType", 0, REG_DWORD, (LPBYTE)&selKeyType, sizeof(DWORD));
		//::RegSetValueEx(hk, L"SelAreaLen", 0, REG_DWORD, (LPBYTE)&selAreaLen, sizeof(DWORD));
		::RegSetValueEx(hk, L"SelAreaLen", 0, REG_DWORD, (LPBYTE)&candPerPage, sizeof(DWORD));
		::RegSetValueEx(hk, L"CursorCandList", 0, REG_DWORD, (LPBYTE)&cursorCandList, sizeof(DWORD));
		::RegSetValueEx(hk, L"EnableCapsLock", 0, REG_DWORD, (LPBYTE)&enableCapsLock, sizeof(DWORD));
		::RegSetValueEx(hk, L"ShiftFullShape", 0, REG_DWORD, (LPBYTE)&shiftFullShape, sizeof(DWORD));
		::RegSetValueEx(hk, L"PhraseMark", 0, REG_DWORD, (LPBYTE)&phraseMark, sizeof(DWORD));
		::RegSetValueEx(hk, L"EscCleanAllBuf", 0, REG_DWORD, (LPBYTE)&escCleanAllBuf, sizeof(DWORD));
		::RegSetValueEx(hk, L"ShiftSymbol", 0, REG_DWORD, (LPBYTE)&shiftSymbol, sizeof(DWORD));
		::RegSetValueEx(hk, L"CtrlSymbol", 0, REG_DWORD, (LPBYTE)&ctrlSymbol, sizeof(DWORD));

		::RegSetValueEx(hk, L"CheckNewVersion", 0, REG_DWORD, (LPBYTE)&checkNewVersion, sizeof(DWORD));
		::RegCloseKey(hk);
	}
}
