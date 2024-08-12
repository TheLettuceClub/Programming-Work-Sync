// cvariant.h -- just to get started
#ifndef _CVARIANT
#define _CVARIANT
class CVariant : public tagVARIANT
{
public:
	CVariant();
	CVariant(const CVariant FAR& rv);
	CVariant(const tagVARIANT FAR& rv);
	CVariant(const char*);
	CVariant(int nYr, int nMo, int nDa, int nHr, int nMn, int nSc);
	CVariant(double); // works for DATE
	CVariant(short);
	CVariant(long);
	~CVariant();
	void GetYMD(int& nYr, int& nMo, int& nDa) const;
	void GetHMS(int& nHr, int& nMn, int& nSc) const;
	BOOL ChangeType(VARTYPE vtDest, tagVARIANT FAR& vDest);
	const CVariant& operator=(const CVariant FAR& rv);
	const CVariant& operator=(const tagVARIANT FAR& rv);
};
#endif
