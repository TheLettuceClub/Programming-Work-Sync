// ex11c.h : main header file for the EX11C application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx11cApp:
// See ex11c.cpp for the implementation of this class
//

class CEx11cApp : public CWinApp
{
public:
    CVBControl m_cntr;
public:
	CEx11cApp();

// Overrides
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);

// Implementation

	//{{AFX_MSG(CEx11cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// VB-Event extern declarations

//{{AFX_VBX_REGISTER()
//}}AFX_VBX_REGISTER

/////////////////////////////////////////////////////////////////////////////
