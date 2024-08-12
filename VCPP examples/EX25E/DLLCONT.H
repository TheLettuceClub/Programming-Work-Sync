// dllcont.h

/////////////////////////////////////////////////////////////////////////////
// CDLLControl wrapper class
#include "cvariant.h"

class CDLLControl : public COleDispatchDriver
{
// Attributes
public:
	enum { DID_ZERO, DID_LONGDATA, DID_TEXTDATA, DID_DISPDIALOG };
	CVariant GetTextData();
	void SetTextData(const VARIANT& propVal);
	long GetLongData();
	void SetLongData(long propVal);
	BOOL DisplayDialog();

// Operations
public:
	void ShowWin();
	void RefreshWin();
};

