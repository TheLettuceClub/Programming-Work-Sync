// marketc.cpp  controller program for CMarket server

#include "stdafx.h"
#include "marketc.h"

short CMarketControl::GetIndustrialsAverage(const VARIANT& vTime)
{
    TRACE("Entering CMarketControl::GetIndustrialsAverage\n");
    short  result;
    static BYTE BASED_CODE parms[] = VTS_VARIANT;
    InvokeHelper(DID_GETAVERAGE, DISPATCH_METHOD, VT_I2,
                (void*)&result, parms, &vTime);
    return result;
}
