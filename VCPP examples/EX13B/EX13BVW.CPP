// ex13bvw.cpp : implementation of the CEx13bView class
//

#include "stdafx.h"
#include "ex13b.h"

#include "ex13bdoc.h"
#include "ex13bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13bView

IMPLEMENT_DYNCREATE(CEx13bView, CView)

BEGIN_MESSAGE_MAP(CEx13bView, CView)
    //{{AFX_MSG_MAP(CEx13bView)
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13bView construction/destruction

CEx13bView::CEx13bView()
{
    // TODO: add construction code here
}

CEx13bView::~CEx13bView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx13bView drawing

void CEx13bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Watch the status bar while you move the mouse.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx13bView diagnostics

#ifdef _DEBUG
void CEx13bView::AssertValid() const
{
    CView::AssertValid();
}

void CEx13bView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx13bDoc* CEx13bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx13bDoc)));
    return (CEx13bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13bView message handlers

void CEx13bView::OnMouseMove(UINT nFlags, CPoint point)
{
    char text[100];

    CStatusBar* pStatus = (CStatusBar*)
        AfxGetApp()->m_pMainWnd->GetDescendantWindow(ID_MY_STATUS_BAR);
    if (pStatus) {
      wsprintf(text, "x = %d", point.x);
      pStatus->SetPaneText(0, text); // first pane
      wsprintf(text, "y = %d", point.y);
      pStatus->SetPaneText(1, text); // second pane
    }
}
