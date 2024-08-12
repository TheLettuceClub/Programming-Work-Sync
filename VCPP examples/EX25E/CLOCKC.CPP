// clockc.cpp

#include "stdafx.h"
#include "clockc.h"


/////////////////////////////////////////////////////////////////////////////
// CClockControl properties

CVariant CClockControl::GetFigure(short i)
{
    CVariant result;
    static BYTE BASED_CODE parms[] =
        VTS_I2;
    InvokeHelper(DID_FIGURE, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result,
        parms, i);
    return result;
}

void CClockControl::SetFigure(short i, const VARIANT& propVal)
{
    static BYTE BASED_CODE parms[] =
          VTS_I2 VTS_VARIANT;
    InvokeHelper(DID_FIGURE, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL,
        parms, i, &propVal);
}

CVariant CClockControl::GetTime()
{
    CVariant result;
    GetProperty(DID_TIME, VT_VARIANT, (void*)&result);
    return result;
}

void CClockControl::SetTime(const VARIANT& propVal)
{
    SetProperty(DID_TIME, VT_VARIANT, &propVal);
}

void CClockControl::ShowWin()
{
    TRACE("Entering CClockControl::ShowWin\n");
    InvokeHelper(DID_SHOW, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CClockControl::RefreshWin()
{
    TRACE("Entering CClockControl::RefreshWin\n");
    InvokeHelper(DID_REFRESH, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH CClockControl::CreateAlarm(const VARIANT& vTime)
{
    TRACE("Entering CClockControl::CreateAlarm -- time = %f\n",
           vTime.dblVal);
    LPDISPATCH result;
    static     BYTE BASED_CODE parms[] = VTS_VARIANT;
    InvokeHelper(DID_CREATEALARM, DISPATCH_METHOD, VT_DISPATCH,
                (void*)&result, parms, &vTime);
    TRACE("Leaving CClockControl::CreateAlarm\n");
    return result;
}
