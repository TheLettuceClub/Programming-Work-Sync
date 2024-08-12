// ex19c.h : main header file for the EX19C application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx19cApp:
// See ex19c.cpp for the implementation of this class
//

class CEx19cApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pTemplate1;
	CMultiDocTemplate* m_pTemplate2;
	int ExitInstance();
public:
	CEx19cApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx19cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
