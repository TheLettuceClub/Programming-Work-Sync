// matvw2.cpp : implementation of the CPlanView class
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//

#include "stdafx.h"
#include "resource.h"
#include "matpiece.h"
#include "matdoc.h"
#include "planview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlanView

IMPLEMENT_DYNCREATE(CPlanView, CScrollView)

BEGIN_MESSAGE_MAP(CPlanView, CScrollView)
    //{{AFX_MSG_MAP(CPlanView)
        ON_WM_PAINT()
        ON_WM_LBUTTONDBLCLK()
        ON_WM_LBUTTONDOWN()
        ON_WM_LBUTTONUP()
        ON_WM_MOUSEMOVE()
        ON_WM_KEYDOWN()
        ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
        ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
    //}}AFX_MSG_MAP

    // Standard Print commands
        // REVIEW: later CODEWIZ will allow you to edit these in {{ }}
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlanView construction/destruction

CPlanView::CPlanView()
{
    m_pPiece = NULL;
    m_bCaptured = FALSE;
    m_pMemDC = new CDC;
}

CPlanView::~CPlanView()
{
    CBitmap* pBitmap = (CBitmap*) (m_pMemDC->
        SelectObject(CBitmap::FromHandle(m_hOldBitmap)));
    delete pBitmap; // must deselect before deletion
    delete m_pMemDC;
}

/////////////////////////////////////////////////////////////////////////////
// CPlanView drawing

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnDraw(CDC* pDC)
{
    CPiece* pPiece;
    DrawBackground(pDC);

    CMatplanDoc* pDoc = GetDocument();
    // draw all the pieces that are in the update region
    int nCount =pDoc-> m_pieceArray.GetUpperBound();
    for (int i = 0; i <= nCount; i++) {
        pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
        pPiece->Draw(pDC, m_yChar);
    }
}

/////////////////////////////////////////////////////////////////////////////
BOOL CPlanView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    ShowOverlap();
    Invalidate(TRUE); // forces total redraw
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnInitialUpdate()
{
    TEXTMETRIC tm;

    CSize totalSize = CSize(800, 800);
    CSize lineSize = CSize(totalSize.cx / 100, totalSize.cy / 100);
    CSize pageSize = CSize(totalSize.cx / 4, totalSize.cy / 4);
    SetScrollSizes(MM_LOENGLISH, totalSize, pageSize, lineSize);

    if (m_pMemDC->GetSafeHdc() == NULL) {
        CClientDC dc(this);
        dc.GetTextMetrics(&tm);
        m_xChar = tm.tmAveCharWidth;
        m_yChar = tm.tmHeight + tm.tmExternalLeading;
    
        OnPrepareDC(&dc);
        CRect rectMax(CPoint(0, 0), totalSize);
        dc.LPtoDP(rectMax);
        
        m_pMemDC->CreateCompatibleDC(&dc);
        CBitmap* pBitmap = new CBitmap;
        pBitmap->CreateCompatibleBitmap(&dc, rectMax.right,
                                        -rectMax.bottom);
        CBitmap* pOldBitmap = (CBitmap*) (m_pMemDC->SelectObject(pBitmap));
    // this temp returned pointer doesn't remain valid past IDLE processing
    //  therefore we must save the handle instead
        m_hOldBitmap = (HBITMAP) pOldBitmap->m_hObject;
        m_pMemDC->SetMapMode(MM_LOENGLISH);
    }
    CScrollView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnPaint()
{
    CRect updateRect;

    CPaintDC dc(this);
    OnPrepareDC(&dc);
    dc.GetClipBox(updateRect); // updateRect is already
                               //  in logical coordinates
    m_pMemDC->SelectClipRgn(NULL);
    m_pMemDC->IntersectClipRect(updateRect);
    m_pMemDC->PatBlt(updateRect.left, updateRect.top,
                     updateRect.Width(), updateRect.Height(),
                     WHITENESS);
    OnDraw(m_pMemDC);
    dc.BitBlt(updateRect.left, updateRect.top,
              updateRect.Width(), updateRect.Height(), m_pMemDC,
              updateRect.left, updateRect.top, SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CRect   rect;
    CPiece* pPiece;

    m_pPiece = NULL; // no piece selected
    CClientDC dc(this);
    OnPrepareDC(&dc);
    CMatplanDoc* pDoc = GetDocument();
    for (int i = pDoc->m_pieceArray.GetUpperBound(); i >= 0; i--) {
        pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
        pPiece->GetRect(rect);
        dc.LPtoDP(&rect);
        // PtInRect works only for device coordinates
        if (rect.PtInRect(point)) {
            SetCapture();
            m_bCaptured = TRUE;
            m_pPiece = pPiece;
            dc.DPtoLP(&point);
            m_mousePoint = point;
            ::SetCursor(::LoadCursor(NULL, IDC_CROSS));
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnMouseMove(UINT nFlags, CPoint point)
{
    CSize offset;
    CRect clientRect, priorRect, newRect, invalidRect;

    if (m_bCaptured) {
        // let's work in device coords for scrolling
        CPoint scrollPos = GetDeviceScrollPosition();
       // scrolls in response to mouse movement outside client area
        GetClientRect(&clientRect);
        if (point.y > clientRect.bottom) {
            scrollPos.y += point.y - clientRect.bottom;
            SafeScrollTo(scrollPos);
        }
        if (point.y < 0) {
            scrollPos.y += point.y;
            SafeScrollTo(scrollPos);
        }
        if (point.x > clientRect.right) {
            scrollPos.x += point.x - clientRect.right;
            SafeScrollTo(scrollPos);
        }
        if (point.x < 0) {
            scrollPos.x += point.x;
            SafeScrollTo(scrollPos);
        }

        CClientDC dc(this);
        OnPrepareDC(&dc);
        dc.DPtoLP(&point);
        offset = point - m_mousePoint;
        m_mousePoint = point;
        m_pPiece->GetRect(priorRect);
        dc.LPtoDP(&priorRect);
        m_pPiece->m_x += offset.cx;
        m_pPiece->m_y += offset.cy;
        m_pPiece->GetRect(newRect);
        dc.LPtoDP(&newRect);
        invalidRect.UnionRect(priorRect, newRect);
#ifdef _WIN32       
        invalidRect.InflateRect(1, 1);
#endif
        InvalidateRect(&invalidRect, FALSE);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnLButtonUp(UINT nFlags, CPoint point)
{
    CMatplanDoc* pDoc = GetDocument();
    if (m_bCaptured) {
        // if piece is outside view, move it back in now
        long length = (LONG) (m_pPiece->m_length / .24);
        long width = (LONG) (m_pPiece->m_width / .24);
        if ((m_pPiece->m_x <= 0)) {
            m_pPiece->m_x = 0;
        }
        if (m_pPiece->m_x + length > m_totalLog.cx) {
            m_pPiece->m_x = m_totalLog.cx - length;
        }
        if ((m_pPiece->m_y >= 0)) {
            m_pPiece->m_y = 0;
        }
        if (m_pPiece->m_y - width < -m_totalLog.cx) {
            m_pPiece->m_y = -m_totalLog.cy + width;
        }
        ReleaseCapture();
        m_bCaptured = FALSE;
        ShowOverlap();
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(this); // except this
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    CRect selectedRect, otherRect, priorRect, newRect, invalidRect;
    CPiece* pPiece;
    int i, nCount;

    // adjust selected piece to boundaries
    if (m_pPiece != NULL) {
        CClientDC dc(this);
        OnPrepareDC(&dc);
        CMatplanDoc* pDoc = GetDocument();
        m_pPiece->GetRect(priorRect);
        dc.LPtoDP(&priorRect);

        // move to left sheet boundary
        if (m_pPiece->m_x < m_totalLog.cx / 2) {
            m_pPiece->m_x = 0;
        }
        else {
            m_pPiece->m_x = m_totalLog.cx / 2;
        }

        // if inside another piece, move to right boundary
        m_pPiece->GetRect(selectedRect);
        dc.LPtoDP(&selectedRect);
        nCount =  pDoc->m_pieceArray.GetUpperBound();
        for (i = nCount; i >= 0; i--) {
            pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
            if (pPiece == m_pPiece) continue;
            pPiece->GetRect(otherRect);
            dc.LPtoDP(&otherRect);
            if (otherRect.PtInRect(selectedRect.TopLeft())) {
                m_pPiece->m_x += (LONG) (pPiece->m_length / .24);
                break;
            }
        }

        // move to top of sheet
        for (i = 1; i < 4; i++) {
            if (m_pPiece->m_y > -m_totalLog.cy * i / 4) {
                m_pPiece->m_y = -m_totalLog.cy * (i - 1) / 4;
                break;
            }
        }
        if (i == 4) {
            m_pPiece->m_y = -m_totalLog.cy * 3 / 4;
        }

        // if inside another piece, move to bottom boundary
        m_pPiece->GetRect(selectedRect);
        dc.LPtoDP(&selectedRect);
        for (i = nCount; i >= 0; i--) {
            pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
            if (pPiece == m_pPiece) continue;
            pPiece->GetRect(otherRect);
            dc.LPtoDP(&otherRect);
            if (otherRect.PtInRect(selectedRect.TopLeft())) {
                m_pPiece->m_y -= (LONG) (pPiece->m_width / .24);
                break;
            }
        }
        pPiece->GetRect(newRect);
        dc.LPtoDP(&newRect);
        invalidRect.UnionRect(priorRect, newRect);
        InvalidateRect(&invalidRect, FALSE);
        ShowOverlap();
        pDoc->SetModifiedFlag();
        pDoc->UpdateAllViews(this); // except this
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

/////////////////////////////////////////////////////////////////////////////
LRESULT CPlanView::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
    if (lParam == 0) {
        lParam = HID_BASE_RESOURCE + IDR_PLANVIEW;
    }
    // context already determined above -- we don't modify it
    AfxGetApp()->WinHelp(lParam);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CPlanView::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
    TRACE("Mouse position = (%d, %d)\n",
         (int) HIWORD(lParam), (int) LOWORD(lParam));
    return HID_BASE_RESOURCE + IDR_PLANVIEW;
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::DrawBackground(CDC* pDC)
{
    int i, x, y;
    // draw the grid lines, including a top line under the toolbar
    pDC->SelectStockObject(BLACK_PEN);
    for (i = 0; i < 2; i++) {
        pDC->MoveTo(m_totalLog.cx * i / 2, 0);
        pDC->LineTo(m_totalLog.cx * i / 2, -m_totalLog.cy); // vertical
    }
    // rightmost vert line must be 1 unit less than 8" boundary
    pDC->MoveTo(m_totalLog.cx - 1, 0);
    pDC->LineTo(m_totalLog.cx - 1, -m_totalLog.cy); // vertical
    for (i = 0; i < 5; i++) {
        pDC->MoveTo(0, -m_totalLog.cy * i / 4);
        pDC->LineTo(m_totalLog.cx,-m_totalLog.cy * i / 4); // horizontal
    }
    // print the sheet numbers
    char temp[15];
    for (i = 0; i <= 7; i++) {
        x = (i % 2) * 400 + 2;
        y = -(i / 2) * 200 - 2;
        wsprintf(temp, "sheet %d", i + 1);
        pDC->TextOut(x, y, temp);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::ShowOverlap()
{ // calcuates pieces overlapping other pieces or sheet boundaries
    CRect dummyRect, selectedRect, otherRect;
    CPiece* pSelectedPiece;
    CPiece* pOtherPiece;
    int i, j;

    CClientDC dc(this);
    OnPrepareDC(&dc);
    CMatplanDoc* pDoc = GetDocument();
    int nCount = pDoc->m_pieceArray.GetUpperBound();
    for (i = nCount; i >= 0; i--) {
        pSelectedPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
        pSelectedPiece->m_bOverlap = FALSE;
        pSelectedPiece->GetRect(selectedRect);
        dc.LPtoDP(&selectedRect);
        for (j = nCount; j >= 0; j--) {
            pOtherPiece = (CPiece*) pDoc->m_pieceArray.GetAt(j);
            if (pSelectedPiece == pOtherPiece) continue;
            pOtherPiece->GetRect(otherRect);
            dc.LPtoDP(&otherRect);
            if (dummyRect.IntersectRect(selectedRect, otherRect)) {
                pSelectedPiece->m_bOverlap = TRUE;
                break;
            }
        // recalculate sheet numbers based on top-left coordinates
        pSelectedPiece->m_sheet = (-pSelectedPiece->m_y / 200) * 2
                + (pSelectedPiece->m_x / 400) + 1;
        }
    }
    Invalidate(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
void CPlanView::SafeScrollTo(CPoint posDev)
{   // executes scroll only if viewport is within window bounds
    CRect clientRect;

    GetClientRect(&clientRect);
    clientRect += posDev;
    if (clientRect.top < 0) {
        posDev.y = 0;          
    }
    if (clientRect.bottom > m_totalDev.cy) {
        posDev.y = m_totalDev.cy;
    }
    if (clientRect.left < 0) {
        posDev.x = 0;
    }
    if (clientRect.right > m_totalDev.cx) {
        posDev.x = m_totalDev.cx;
    }
    ScrollToDevicePosition(posDev);
}

/////////////////////////////////////////////////////////////////////////////
// CPlanView diagnostics

#ifdef _DEBUG
void CPlanView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CPlanView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

#endif //_DEBUG
