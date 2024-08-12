// ex25ddoc.cpp : implementation of the CEx25dDoc class
//

#include "stdafx.h"
#include "ex25d.h"
#include "mainfrm.h"
#include "about.h"

#include "ex25ddoc.h"
#include "alarm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc

IMPLEMENT_DYNCREATE(CEx25dDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25dDoc, CDocument)
	//{{AFX_MSG_MAP(CEx25dDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CEx25dDoc, CDocument)
	// An MFC C++ controller has to be aware of this exact map sequence.
	// If the server map changes, then the controller must be recompiled.
	// ClassWizard sometimes changes the sequence here-- be careful!
	DISP_PROPERTY(CEx25dDoc, "Time", m_time, VT_VARIANT)
	//{{AFX_DISPATCH_MAP(CEx25dDoc)
	DISP_FUNCTION(CEx25dDoc, "RefreshWin", Refresh, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CEx25dDoc, "ShowWin", ShowWin, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CEx25dDoc, "CreateAlarm", CreateAlarm, VT_DISPATCH, VTS_VARIANT)
	//}}AFX_DISPATCH_MAP
	DISP_PROPERTY_PARAM(CEx25dDoc, "Figure", GetFigure, SetFigure,
			VT_VARIANT, VTS_I2)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc construction/destruction

CEx25dDoc::CEx25dDoc() : m_time(0, 0, 0, 5, 10, 15)
{
	TRACE("Entering CEx25dDoc ctor\n");
	m_figure[0] = "N"; m_figure[1] = "S";
	m_figure[2] = "E"; m_figure[3] = "W";
	m_pAlarm = NULL;
	
	EnableAutomation();
	AfxOleLockApp();
}

CEx25dDoc::~CEx25dDoc()
{
	TRACE("Entering CEx25dDoc dtor\n");
	AfxOleUnlockApp();
}

void CEx25dDoc::OnFinalRelease()     // debug purposes only
{
	TRACE("Entering CEx25dDoc::OnFinalRelease\n");
	CDocument::OnFinalRelease();
}

BOOL CEx25dDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc diagnostics

#ifdef _DEBUG
void CEx25dDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx25dDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25dDoc commands

void CEx25dDoc::Refresh()
{
	TRACE("Entering CEx25dDoc::Refresh\n");
	UpdateAllViews(NULL);  // invalidates the one-and-only view
	AfxGetApp()->m_pMainWnd->BringWindowToTop();
}

CVariant CEx25dDoc::GetFigure(short n)
{
	TRACE("Entering CEx25dDoc::GetFigure -- n = %d m_figure[n] = %s\n", n, m_figure[n]);
	return CVariant(m_figure[n]);
}

void CEx25dDoc::SetFigure(short n, const VARIANT FAR& vNew)
{
	TRACE("Entering CEx25dDoc::SetFigure -- n = %d, vt = %d\n", n, vNew.vt);
	CVariant vTemp;
	if(((CVariant*) &vNew)->ChangeType(VT_BSTR, vTemp)) {
		m_figure[n] = vTemp.bstrVal;
	}
}

void CEx25dDoc::ShowWin()
{
	TRACE("Entering CEx25dDoc::ShowWin\n");
	CRect rectWindow;
	CWnd* pFrm = AfxGetApp()->m_pMainWnd;
	pFrm->GetWindowRect(rectWindow);
	WINDOWPLACEMENT wndpl;
	wndpl.length = sizeof(WINDOWPLACEMENT);
	wndpl.showCmd = SW_SHOWNORMAL;
	wndpl.rcNormalPosition.left = rectWindow.left;
	wndpl.rcNormalPosition.top = rectWindow.top;
	wndpl.rcNormalPosition.right = rectWindow.left + 150;
	wndpl.rcNormalPosition.bottom = rectWindow.top + 150;
	pFrm->SetWindowPlacement(&wndpl);
	pFrm->ShowWindow(AfxGetApp()->m_nCmdShow);
	pFrm->UpdateWindow();
	pFrm->BringWindowToTop();
}

LPDISPATCH CEx25dDoc::CreateAlarm(const VARIANT FAR& time)
{
	TRACE("Entering CEx25dDoc::CreateAlarm\n");
//	((CEx25dApp*) AfxGetApp())->OnAppAbout();  // dangerous!
	// OLE 2 deletes any prior CAlarm object
	m_pAlarm = new CAlarm(time);
	return m_pAlarm->GetIDispatch(FALSE);   // no AddRef here
}
