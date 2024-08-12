// ex18b.h : main header file for the EX18B application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx18bApp:
// See ex18b.cpp for the implementation of this class
//

class CEx18bApp : public CWinApp
{
public:
	CEx18bApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx18bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
