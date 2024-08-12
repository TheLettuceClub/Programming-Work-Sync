// ex25b.h : main header file for the EX25B application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25bApp:
// See ex25b.cpp for the implementation of this class
//

class CEx25bApp : public CWinApp
{
public:
	CEx25bApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	//{{AFX_MSG(CEx25bApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
