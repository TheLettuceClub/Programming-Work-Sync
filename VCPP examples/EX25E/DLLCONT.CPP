// dllcont.cpp

#include "stdafx.h"
#include "dllcont.h"


/////////////////////////////////////////////////////////////////////////////
// CDLLControl properties

CVariant CDLLControl::GetTextData()
{
    CVariant result;
    GetProperty(DID_TEXTDATA, VT_VARIANT, (void*)&result);
    return result;
}

void CDLLControl::SetTextData(const VARIANT& propVal)
{
    SetProperty(DID_TEXTDATA, VT_VARIANT, &propVal);
}

long CDLLControl::GetLongData()
{
    long result;
    GetProperty(DID_LONGDATA, VT_I4, (void*)&result);
    return result;
}

void CDLLControl::SetLongData(long propVal)
{
    SetProperty(DID_LONGDATA, VT_I4, propVal);
}

BOOL CDLLControl::DisplayDialog()
{
    BOOL result;
    InvokeHelper(DID_DISPDIALOG, DISPATCH_METHOD, VT_BOOL,
                  (void*)&result, NULL);
    return result;
}
