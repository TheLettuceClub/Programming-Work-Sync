// alarmc.cpp

#include "stdafx.h"
#include "alarmc.h"

CVariant CAlarmControl::GetTime()
{
	CVariant result;
	GetProperty(DID_TIME, VT_VARIANT, (void*)&result);
	return result;
}

void CAlarmControl::SetTime(const VARIANT& propVal)
{
	SetProperty(DID_TIME, VT_VARIANT, &propVal);
}

