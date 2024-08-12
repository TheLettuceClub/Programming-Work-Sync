// ex04cvw.cpp : implementation of the CEx04cView class
//

#include "stdafx.h"
#include "ex04c.h"

#include "ex04cdoc.h"
#include "ex04cvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04cView

IMPLEMENT_DYNCREATE(CEx04cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx04cView, CScrollView)
    //{{AFX_MSG_MAP(CEx04cView)
    ON_WM_KEYDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04cView construction/destruction

CEx04cView::CEx04cView()
{
    // TODO: add construction code here
}

CEx04cView::~CEx04cView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx04cView drawing

void CEx04cView::OnDraw(CDC* pDC)
{
    int x = ::GetSystemMetrics(SM_CXSCREEN);
    int y = ::GetSystemMetrics(SM_CYSCREEN);

    pDC->SelectStockObject(GRAY_BRUSH); // selects a brush for
                                        //  the circle interior
    // draw a circle centered in the scrolling window
    pDC->Ellipse(CRect(x - 300, y - 300, x + 300, y + 300));
}

void CEx04cView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();

    CSize totalSize = CSize(::GetSystemMetrics(SM_CXSCREEN) * 2,
                            ::GetSystemMetrics(SM_CYSCREEN) * 2);    
    CSize pageSize = CSize(totalSize.cx / 2,
                           totalSize.cy / 2);
    CSize lineSize = CSize(totalSize.cx / 100,
                           totalSize.cy / 100);
    SetScrollSizes(MM_TEXT, totalSize,
                   pageSize, lineSize);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04cView diagnostics

#ifdef _DEBUG
void CEx04cView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx04cView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx04cDoc* CEx04cView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04cDoc)));
    return (CEx04cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04cView message handlers

void CEx04cView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar) {
    case VK_HOME:
      OnVScroll(SB_TOP, 0, NULL);
      OnHScroll(SB_LEFT, 0, NULL);
      break;
    case VK_END:
      OnVScroll(SB_BOTTOM, 0, NULL);
      OnHScroll(SB_RIGHT, 0, NULL);
      break;
    case VK_UP:
      OnVScroll(SB_LINEUP, 0, NULL);
      break;
    case VK_DOWN:
      OnVScroll(SB_LINEDOWN, 0, NULL);
      break;
    case VK_PRIOR:
      OnVScroll(SB_PAGEUP, 0, NULL);
      break;
    case VK_NEXT:
      OnVScroll(SB_PAGEDOWN, 0, NULL);
      break;
    case VK_LEFT:
      OnHScroll(SB_LINELEFT, 0, NULL);
      break;
    case VK_RIGHT:
      OnHScroll(SB_LINERIGHT, 0, NULL);
      break;
    default:
      break;
    }
}
