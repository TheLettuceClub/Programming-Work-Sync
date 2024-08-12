// ex26a.cpp : DLL main program
//

#include "stdafx.h"

#include <afxdllx.h>

extern AFX_EXTENSION_MODULE NEAR extensionDLL = {NULL, NULL};

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	// do not allocate memory or use TRACE, ASSERT, or MessageBox
	AfxInitExtensionModule(extensionDLL, hInstance);
	return 1; // OK
}

// following initialization function is called from client app
extern "C" extern void WINAPI InitEx26aDLL()
{
	new CDynLinkLibrary(extensionDLL);
}
