// ex17a.h : main header file for the EX17A application
//

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx17aApp:
// See ex17a.cpp for the implementation of this class
//

class CEx17aApp : public CWinApp
{
public:
    CEx17aApp();

// Overrides
    virtual BOOL InitInstance();
    // open named file
    virtual CDocument* OpenDocumentFile(LPCSTR lpszFileName);
    virtual BOOL OnDDECommand(char* pszCommand);

// Implementation

    //{{AFX_MSG(CEx17aApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
