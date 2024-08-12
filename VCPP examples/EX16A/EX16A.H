// ex16a.h : main header file for the EX16A application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx16aApp:
// See ex16a.cpp for the implementation of this class
//

class CEx16aApp : public CWinApp
{
public:
	CEx16aApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CEx16aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
