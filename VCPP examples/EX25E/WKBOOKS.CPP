// Machine generated IDispatch driver class(es) created with ClassWizard.

#include "stdafx.h"
#include "wkbooks.h"


/////////////////////////////////////////////////////////////////////////////
// Workbooks properties

//********************************
short Workbooks::GetCount()
{
	short result;
	GetProperty(0x76, VT_I2, (void*)&result);
	return result;
}

void Workbooks::SetCount(const VARIANT& propVal)
{
	SetProperty(0x76, VT_VARIANT, &propVal);
}

VARIANT Workbooks::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void Workbooks::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT Workbooks::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void Workbooks::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Workbooks operations

VARIANT Workbooks::_NewEnum()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Workbooks::Add(const VARIANT& Template)
{
	TRACE("Entering Workbooks::Add(Template)\n");
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Template);
	return result;
}
//*****************************************
LPDISPATCH Workbooks::Add()
{
	// don't know what LPDISPATCH points to
	TRACE("Entering Workbooks::Add()\n");
	LPDISPATCH result;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
//*****************************************

VARIANT Workbooks::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

//***************************
void Workbooks::Close()
{
	TRACE("Entering  Workbooks::Close\n");
	InvokeHelper(0x115, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT Workbooks::Item(const VARIANT& Index)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Workbooks::Open(const VARIANT& Filename, const VARIANT& UpdateLinks, const VARIANT& ReadOnly, const VARIANT& Format, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& IgnoreReadOnlyRecommended, const VARIANT& Origin, 
		const VARIANT& Delimiter, const VARIANT& Editable, const VARIANT& Notify, const VARIANT& Converter)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2aa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename, &UpdateLinks, &ReadOnly, &Format, &Password, &WriteResPassword, &IgnoreReadOnlyRecommended, &Origin, &Delimiter, &Editable, &Notify, &Converter);
	return result;
}

VARIANT Workbooks::OpenText(const VARIANT& Filename, const VARIANT& Origin, const VARIANT& StartRow, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, 
		const VARIANT& Comma, const VARIANT& Space, const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo)
{
	VARIANT result;
	static BYTE BASED_CODE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2ab, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename, &Origin, &StartRow, &DataType, &TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo);
	return result;
}
