// ex05cvw.cpp : implementation of the CEx05cView class
//

#include "stdafx.h"
#include "ex05c.h"

#include "ex05cdoc.h"
#include "ex05cvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05cView

IMPLEMENT_DYNCREATE(CEx05cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx05cView, CScrollView)
    //{{AFX_MSG_MAP(CEx05cView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05cView construction/destruction

CEx05cView::CEx05cView() : m_ellipseRect(0, 0, 100, -100)
{
    m_bCaptured = FALSE;
}

CEx05cView::~CEx05cView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx05cView drawing

void CEx05cView::OnDraw(CDC* pDC)
{
    CBrush hatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
    CPoint tempPoint(0, 0); // logical 0,0
    
    hatchBrush.UnrealizeObject();
    pDC->LPtoDP(&tempPoint);             // In device coordinates,
    pDC->SetBrushOrg(tempPoint);         //  align the brush with
                                         //  the window origin.
    pDC->SelectObject(&hatchBrush);
    pDC->Ellipse(m_ellipseRect);
    pDC->SelectStockObject(BLACK_BRUSH); // deselect hatchBrush
}

void CEx05cView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize totalSize = CSize(800 * 2, 800 * 2); // 8 inch by 8 inch
    CSize pageSize = CSize(totalSize.cx / 2, totalSize.cy / 2);
    CSize lineSize = CSize(totalSize.cx / 100, totalSize.cy / 100);
    SetScrollSizes(MM_LOENGLISH, totalSize, pageSize, lineSize);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05cView diagnostics

#ifdef _DEBUG
void CEx05cView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx05cView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx05cDoc* CEx05cView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05cDoc)));
    return (CEx05cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05cView message handlers

void CEx05cView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect ellipseRect;
    CRgn  circle;
    
    ellipseRect = m_ellipseRect;
    CClientDC dc(this);
    OnPrepareDC(&dc);
    dc.LPtoDP(ellipseRect);
    circle.CreateEllipticRgnIndirect(ellipseRect);
    if (circle.PtInRegion(point)) {
      // capturing the mouse ensures subsequent LButtonUp message
      SetCapture();
      m_bCaptured = TRUE;
      dc.DPtoLP(&point);
      m_mousePos = point;
      // new mouse cursor is active while mouse is captured
      ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
    }
}

void CEx05cView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
      ReleaseCapture();
      m_bCaptured = FALSE;
    }
}

void CEx05cView::OnMouseMove(UINT nFlags, CPoint point)
{
    CSize  offset;
    CPoint mousePos;
    CRect  ellipseRect, newRect, invalidRect, clientRect, tempRect;
    
    CClientDC dc(this);
    OnPrepareDC(&dc);
    GetClientRect(clientRect);
    if (m_bCaptured) {
      ellipseRect = m_ellipseRect;
      mousePos = m_mousePos;
      dc.LPtoDP(ellipseRect);
      dc.LPtoDP(&mousePos);  
      offset = point - mousePos;
      newRect = ellipseRect + (CPoint(0, 0) + offset);
      tempRect.UnionRect(ellipseRect, newRect);
      invalidRect.IntersectRect(tempRect, clientRect);
      InvalidateRect(invalidRect, TRUE);
      dc.DPtoLP(&point);
      dc.DPtoLP(newRect);
      m_mousePos = point;
      m_ellipseRect = newRect;
    }
}
