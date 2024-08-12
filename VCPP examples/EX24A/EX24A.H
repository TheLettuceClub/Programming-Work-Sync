// ex24a.h : main header file for the EX24A application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24aApp:
// See ex24a.cpp for the implementation of this class
//

class CEx24aApp : public CWinApp
{
public:
	CEx24aApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx24aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
