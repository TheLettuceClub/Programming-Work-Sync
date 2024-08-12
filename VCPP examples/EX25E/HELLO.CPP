// Machine generated IDispatch driver class(es) created with ClassWizard.

#include "stdafx.h"
#include "hello.h"


/////////////////////////////////////////////////////////////////////////////
// _DHello properties

/////////////////////////////////////////////////////////////////////////////
// _DHello operations

void _DHello::SetHelloMessage(const char* p0)
{
	static BYTE BASED_CODE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 p0);
}

CString _DHello::GetHelloMessage()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _DHello::SayHello()
{
	CString result;
	InvokeHelper(0x60010046, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}
