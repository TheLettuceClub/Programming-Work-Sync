// ex04bvw.cpp : implementation of the CEx04bView class
//

#include "stdafx.h"
#include "ex04b.h"

#include "ex04bdoc.h"
#include "ex04bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04bView

IMPLEMENT_DYNCREATE(CEx04bView, CView)

BEGIN_MESSAGE_MAP(CEx04bView, CView)
    //{{AFX_MSG_MAP(CEx04bView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04bView construction/destruction

CEx04bView::CEx04bView() : m_ellipseRect(0, 0, 100, 100) // constructor
{
    m_bCaptured = FALSE;
}

CEx04bView::~CEx04bView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx04bView drawing

void CEx04bView::OnDraw(CDC* pDC)
{
    pDC->SelectStockObject(GRAY_BRUSH);
    pDC->Ellipse(m_ellipseRect);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04bView diagnostics

#ifdef _DEBUG
void CEx04bView::AssertValid() const
{
    CView::AssertValid();
}

void CEx04bView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx04bDoc* CEx04bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04bDoc)));
    return (CEx04bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04bView message handlers

void CEx04bView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect rect;
    CRgn  circle;
    
    TRACE("entering CEx04bView::OnLButtonDown - point = %d, %d\n",
           point.x, point.y);
    circle.CreateEllipticRgnIndirect(m_ellipseRect);
    if (circle.PtInRegion(point)) {
      // capturing mouse ensures subsequent LButtonUp message
      SetCapture();
      m_bCaptured = TRUE;
      m_mousePos = point;
      // "cross" mouse cursor is active while mouse is captured
      ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
    }
}

void CEx04bView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
      ReleaseCapture();
      m_bCaptured = FALSE;
    }
}

void CEx04bView::OnMouseMove(UINT nFlags, CPoint point)
{
    CSize offset;
    CRect tempRect, newRect, invalidRect, clientRect;
    
    if (m_bCaptured) {
      GetClientRect(clientRect);
      // dont move the circle outside the client window
      if (clientRect.PtInRect(point)) {
        offset = point - m_mousePos;
        newRect = m_ellipseRect + (CPoint(0, 0) + offset);
        tempRect.UnionRect(m_ellipseRect, newRect);
        invalidRect.IntersectRect(tempRect, clientRect);
        InvalidateRect(invalidRect, TRUE);
        m_mousePos = point;
        m_ellipseRect = newRect;
      }
    }
}
