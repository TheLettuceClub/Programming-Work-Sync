// ex25d.h : main header file for the EX25D application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25dApp:
// See ex25d.cpp for the implementation of this class
//

class CEx25dApp : public CWinApp
{
public:
	CEx25dApp();

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CEx25dApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
