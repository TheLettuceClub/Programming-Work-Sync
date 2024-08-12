// matplan.h : main header file for the MATPLAN application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMatplanApp:
// See matplan.cpp for the implementation of this class
//

class CMatplanApp : public CWinApp
{
public:
	CMultiDocTemplate* m_pTemplate1;
	CMultiDocTemplate* m_pTemplate2;
public:
	CMatplanApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	//{{AFX_MSG(CMatplanApp)
		afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
