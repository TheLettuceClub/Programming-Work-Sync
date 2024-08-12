// ex10bvw.cpp : implementation of the CEx10bView class
//

#include "stdafx.h"
#include "ex10b.h"

#include "ex10bdoc.h"
#include "ex10bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10bView

IMPLEMENT_DYNCREATE(CEx10bView, CScrollView)

BEGIN_MESSAGE_MAP(CEx10bView, CScrollView)
    //{{AFX_MSG_MAP(CEx10bView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10bView construction/destruction

CEx10bView::CEx10bView() : m_ellipseRect(0, 0, 100, -100) // constructor
{
    m_bCaptured = FALSE;
    m_pMemDC    = new CDC;
    m_pBitmap   = new CBitmap;
}

CEx10bView::~CEx10bView() // destructor
{                                      
    delete m_pBitmap;     // already deselected
    delete m_pMemDC;
}

/////////////////////////////////////////////////////////////////////////////
// CEx10bView drawing

void CEx10bView::OnDraw(CDC* pDC)
{
    pDC->SelectStockObject(BLACK_BRUSH);
    pDC->Rectangle(100, -100, 200, -200);
    pDC->SelectStockObject(GRAY_BRUSH);
    pDC->Ellipse(m_ellipseRect);
}

void CEx10bView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    // sets the scrolling parameters as in EX05C
    CSize totalSize = CSize(800 * 2, 800 * 2);
    CSize pageSize  = CSize(totalSize.cx / 2, totalSize.cy / 2);
    CSize lineSize  = CSize(totalSize.cx / 100, totalSize.cy / 100);
    SetScrollSizes(MM_LOENGLISH, totalSize, pageSize, lineSize);

    // creates the memory device context and the bitmap 
    if (m_pMemDC->GetSafeHdc() == NULL) {
      CClientDC dc(this);
      OnPrepareDC(&dc);
      CRect rectMax(0, 0, totalSize.cx, -totalSize.cy);
      dc.LPtoDP(rectMax);
      m_pMemDC->CreateCompatibleDC(&dc);
      // makes the bitmap the same size as the display window
      m_pBitmap->CreateCompatibleBitmap(&dc, rectMax.right,
                                        rectMax.bottom);
      m_pMemDC->SetMapMode(MM_LOENGLISH);
    }
    CScrollView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CEx10bView diagnostics

#ifdef _DEBUG
void CEx10bView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx10bView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx10bDoc* CEx10bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10bDoc)));
    return (CEx10bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10bView message handlers

void CEx10bView::OnLButtonDown(UINT nFlags, CPoint point)
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

void CEx10bView::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
      ReleaseCapture();
      m_bCaptured = FALSE;
    }
}

void CEx10bView::OnMouseMove(UINT nFlags, CPoint point)
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
      InvalidateRect(invalidRect, FALSE);
      dc.DPtoLP(&point);
      dc.DPtoLP(newRect);
      m_mousePos = point;
      m_ellipseRect = newRect;
    }
}

void CEx10bView::OnPaint()
{
    CRect updateRect;

    CPaintDC dc(this);
    OnPrepareDC(&dc);
    dc.GetClipBox(&updateRect);
    CBitmap* pOldBitmap = (CBitmap*) (m_pMemDC->SelectObject(m_pBitmap));
    
    m_pMemDC->SelectClipRgn(NULL);
    m_pMemDC->IntersectClipRect(&updateRect);
    CBrush backgroundBrush((COLORREF) ::GetSysColor(COLOR_WINDOW));
    CBrush* pOldBrush = m_pMemDC->SelectObject(&backgroundBrush);
    m_pMemDC->PatBlt(updateRect.left, updateRect.top,
                     updateRect.Width(), updateRect.Height(), PATCOPY);
    OnDraw(m_pMemDC);
    dc.BitBlt(updateRect.left, updateRect.top,
              updateRect.Width(), updateRect.Height(), m_pMemDC,
              updateRect.left, updateRect.top, SRCCOPY);
    m_pMemDC->SelectObject(pOldBitmap);
    m_pMemDC->SelectObject(pOldBrush);
}
