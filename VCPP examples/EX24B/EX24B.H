// ex24b.h : main header file for the EX24C application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx24bApp:
// See ex24b.cpp for the implementation of this class
//

class CEx24bApp : public CWinApp
{
public:
	BOOL m_bFileExit;
public:
	CEx24bApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// Implementation

	//{{AFX_MSG(CEx24bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
