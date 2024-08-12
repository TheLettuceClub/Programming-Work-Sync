// ex08a.h : main header file for the EX08A application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx08aApp:
// See ex08a.cpp for the implementation of this class
//

class CEx08aApp : public CWinApp
{
public:
	CEx08aApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx08aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
	extern UINT NEAR VBN_SELCHANGE;
//}}AFX_VBX_REGISTER

/////////////////////////////////////////////////////////////////////////////
