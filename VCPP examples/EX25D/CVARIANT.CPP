// cvariant.cpp
#include "stdafx.h"
#include "cvariant.h"
#include <math.h>

CVariant::CVariant()
{
	::VariantInit(this);   // VT_EMPTY
}

CVariant::CVariant(const CVariant FAR& rv)
{
	::VariantInit(this);   // VT_EMPTY
	::VariantCopyInd(this, (CVariant FAR*) &rv);	
}

CVariant::CVariant(const tagVARIANT FAR& rv)
{
	::VariantInit(this);   // VT_EMPTY
	::VariantCopyInd(this, (CVariant FAR*) &rv);	
}

CVariant::CVariant(const char* pchArg)
{
	::VariantInit(this);
	vt = VT_BSTR;
	bstrVal = SysAllocString(pchArg);
}

CVariant::CVariant(int nYr, int nMo, int nDa, int nHr, int nMn, int nSc)
{
	unsigned short wDOSDate, wDOSTime;
	if((nYr == 0) && (nMo == 0) && (nDa == 0)) {
		nYr = 1980; nMo = 1; nDa = 1;
	}
	wDOSDate = ((nYr - 1980) << 9) + (nMo << 5) + nDa;
	wDOSTime = (nHr << 11) + (nMn << 5) + (nSc / 2);
	::VariantInit(this);
	vt = VT_DATE;
	// dates before 1/1/1980 can't be converted to DOSDate
	VERIFY(DosDateTimeToVariantTime(wDOSDate, wDOSTime, &dblVal));
}

CVariant::CVariant(double dArg)
{
	::VariantInit(this);
	vt = VT_R8;
	dblVal = dArg;
}

CVariant::CVariant(short iArg)
{
	::VariantInit(this);
	vt = VT_I2;
	iVal = iArg;
}
	
CVariant::CVariant(long lArg)
{
	::VariantInit(this);
	vt = VT_I4;
	lVal = lArg;
}

CVariant::~CVariant()
{
	::VariantClear(this);
}

void CVariant::GetYMD(int& nYr, int& nMo, int& nDa) const
{
	unsigned short wDOSDate, wDOSTime;
	if(vt == VT_DATE || vt == VT_R8) {
		// dates < 29221.0 (1/1/1980) invalid for conversion to DOS date/time
		VERIFY(VariantTimeToDosDateTime(dblVal, &wDOSDate, &wDOSTime));
		nDa = wDOSDate & 0x1F;
		nMo = ((wDOSDate >> 5) & 0x0F);
		nYr = ((wDOSDate >> 9) & 0x7F) + 1980;
	}
	else {
		TRACE("CVariant::GetYMD: vt = %d\n", vt);
	}
}

void CVariant::GetHMS(int& nHr, int& nMn, int& nSc) const
{
	//  Excel passes VARIANTs as R8 as well as DATE -- when?
	
	unsigned short wDOSDate, wDOSTime;
	double dTime;
	if(vt == VT_DATE || vt == VT_R8) {
		if((dTime = dblVal) < 29221.0) {     // 1/1/1980
			dTime = 29221.0 + (dTime - floor(dTime));   // 1/1/1980
		}   // dates < 29221.0 invalid for conversion to DOS date/time
		VERIFY(VariantTimeToDosDateTime(dTime, &wDOSDate, &wDOSTime));
		nSc = (wDOSTime & 0x1F) * 2;
		nMn = ((wDOSTime >> 5) & 0x3F);
		nHr = ((wDOSTime >> 11) & 0x1F);
	}
	else {
		TRACE("CVariant::GetHMS: vt = %d\n", vt);
	}
}

BOOL CVariant::ChangeType(VARTYPE vtDest, tagVARIANT FAR& vDest)
{
	if(::VariantChangeType(&vDest, this, 0, vtDest) == S_OK)
		return TRUE;
	else
		return FALSE;
}

const CVariant& CVariant::operator=(const tagVARIANT FAR& rv)
{
	::VariantCopyInd(this, (CVariant FAR*) &rv);	// releases destination first
	return *this;
}

const CVariant& CVariant::operator=(const CVariant FAR& rv)
{
	::VariantCopyInd(this, (CVariant FAR*) &rv);	// releases destination first
	return *this;
}