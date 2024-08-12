// ex14a.h : main header file for the EX14A application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx14aApp:
// See ex14a.cpp for the implementation of this class
//

class CEx14aApp : public CWinApp
{
public:
	CEx14aApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx14aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
