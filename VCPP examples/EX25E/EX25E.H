// ex25e.h : main header file for the EX25E application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25eApp:
// See ex25e.cpp for the implementation of this class
//

class CEx25eApp : public CWinApp
{
public:
	CEx25eApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	//{{AFX_MSG(CEx25eApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
