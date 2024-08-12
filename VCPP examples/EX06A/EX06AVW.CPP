// ex06avw.cpp : implementation of the CEx06aView class
//

#include "stdafx.h"
#include "ex06a.h"

#include "ex06adoc.h"
#include "ex06avw.h"
#include "ex06adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06aView

IMPLEMENT_DYNCREATE(CEx06aView, CView)

BEGIN_MESSAGE_MAP(CEx06aView, CView)
    //{{AFX_MSG_MAP(CEx06aView)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06aView construction/destruction

CEx06aView::CEx06aView()
{
    // TODO: add construction code here
}

CEx06aView::~CEx06aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx06aView drawing

void CEx06aView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0, "Press the left mouse button here.");
}



/////////////////////////////////////////////////////////////////////////////
// CEx06aView diagnostics

#ifdef _DEBUG
void CEx06aView::AssertValid() const
{
    CView::AssertValid();
}

void CEx06aView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx06aDoc* CEx06aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06aDoc)));
    return (CEx06aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx06aView message handlers

void CEx06aView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx06aDialog dlg;
    dlg.m_name     = "Shakespeare, Will";
    dlg.m_lSsn     = 307806636;
    dlg.m_nCat     = 1;  // 0 = hourly, 1 = salary
    dlg.m_bio      = "This person is not a well-motivated tech writer";
    dlg.m_bInsLife = TRUE;
    dlg.m_bInsDis  = FALSE;
    dlg.m_bInsMed  = TRUE;
    dlg.m_dept     = "Documentation";
    dlg.m_skill    = "Writer";
    dlg.m_lang     = "English";
    dlg.m_educ     = "College";
    dlg.m_nLoyal   = dlg.m_nRely = 50;
    int ret = dlg.DoModal();
    TRACE("DoModal return = %d\n", ret);
    TRACE("name = %s, ssn = %ld, nCat = %d\n",
         (const char* ) dlg.m_name, dlg.m_lSsn, dlg.m_nCat);
    TRACE("dept = %s, skill = %s, lang = %s, educ = %s\n",
         (const char* ) dlg.m_dept, (const char* ) dlg.m_skill,
         (const char* ) dlg.m_lang, (const char* ) dlg.m_educ);
    TRACE("life = %d, dis = %d, med = %d, bio = %s\n",
         dlg.m_bInsLife, dlg.m_bInsDis, dlg.m_bInsMed,
         (const char* ) dlg.m_bio);
    TRACE(" loyalty = %d, reliability = %d\n",
         dlg.m_nLoyal, dlg.m_nRely);
}
