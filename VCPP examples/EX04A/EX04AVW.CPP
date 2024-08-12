// ex04avw.cpp : implementation of the CEx04aView class
//

#include "stdafx.h"
#include "ex04a.h"

#include "ex04adoc.h"
#include "ex04avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04aView

IMPLEMENT_DYNCREATE(CEx04aView, CView)

BEGIN_MESSAGE_MAP(CEx04aView, CView)
    //{{AFX_MSG_MAP(CEx04aView)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04aView construction/destruction

CEx04aView::CEx04aView() : m_ellipseRect(0, 0, 200, 200)
{
    // TODO: add construction code here
}

CEx04aView::~CEx04aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx04aView drawing

void CEx04aView::OnDraw(CDC* pDC)
{
    pDC->SelectStockObject(GRAY_BRUSH);
    pDC->Ellipse(m_ellipseRect);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04aView diagnostics

#ifdef _DEBUG
void CEx04aView::AssertValid() const
{
    CView::AssertValid();
}

void CEx04aView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx04aDoc* CEx04aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04aDoc)));
    return (CEx04aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04aView message handlers

void CEx04aView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_ellipseRect == CRect(0, 0, 200, 200)) {
	  m_ellipseRect = CRect(0, 0, 100, 100); // little circle
	}
	else {
	  m_ellipseRect = CRect(0, 0, 200, 200); // big circle
	}
	InvalidateRect(CRect(0, 0, 200, 200));
}
