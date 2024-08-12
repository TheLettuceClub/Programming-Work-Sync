// ex25dvw.cpp : implementation of the CEx25dView class
//

#include "stdafx.h"
#include "ex25d.h"

#include "ex25ddoc.h"
#include "ex25dvw.h"
#include "alarm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25dView

IMPLEMENT_DYNCREATE(CEx25dView, CView)

BEGIN_MESSAGE_MAP(CEx25dView, CView)
    //{{AFX_MSG_MAP(CEx25dView)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25dView construction/destruction

CEx25dView::CEx25dView()
{
    TRACE("Entering CEx25dView ctor\n");
}

CEx25dView::~CEx25dView()
{
    TRACE("Entering CEx25dView dtor\n");
}

/////////////////////////////////////////////////////////////////////////////
// CEx25dView drawing

void CEx25dView::OnDraw(CDC* pDC)
{
    CEx25dDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    CRect rectClient;
    CPen pen0(PS_SOLID, 0, 0);
    CPen pen1(PS_SOLID, 20, 0);
    CPen pen2(PS_SOLID, 30, 0);
    int i, j, n, m, nS, nM, nH;
    CSize sz;
    pDC->SetMapMode(MM_ISOTROPIC);
    GetClientRect(rectClient);
    pDC->SetWindowExt(2400, 2400);
    pDC->SetViewportExt(rectClient.right, -rectClient.bottom);
    pDC->SetViewportOrg(rectClient.right / 2, rectClient.bottom / 2);
    pDC->SelectObject(&m_font);
    pDC->SelectObject(&pen0);
    for (i = 0; i < 60; i++) { // second/minute ticks
        pDC->MoveTo(nX[i], nY[i]);
        pDC->LineTo(nX[i] * 9 / 10, nY[i] * 9 / 10);
    }
    pDC->SelectObject(&pen1);
    for (i = 0; i < 12; i++) { // hour ticks
        j = i * 5;
        pDC->MoveTo(nX[j], nY[j]);
        pDC->LineTo(nX[j] * 8 / 10, nY[j] * 8 / 10);
    }
    for (i = 0; i < 4; i++) { // figures
        j = i * 15;
        sz = pDC->GetTextExtent(pDoc->m_figure[i], pDoc->m_figure[i].GetLength());
        n  = nX[j] * 10 / 9 - sz.cx / 2;
        m  = nY[j] * 10 / 9 + sz.cy / 2;
        pDC->TextOut(n, m, pDoc->m_figure[i]);
    }

    // draw the clock hands
    pDoc->m_time.GetHMS(nH, nM, nS);
    pDC->SelectObject(&pen0);
    i = nS;
    pDC->MoveTo(0, 0);
    pDC->LineTo(nX[i], nY[i]); // seconds
    
    pDC->SelectObject(&pen1);
    i = nM;
    pDC->MoveTo(0, 0);
    pDC->LineTo(nX[i] * 8 / 10, nY[i] * 8 / 10); // minutes

    pDC->SelectObject(&pen2);
    i = nH * 5;
    i = (i % 60) + nM / 12;
    pDC->MoveTo(0, 0);
    pDC->LineTo(nX[i] * 6 / 10, nY[i] * 6 / 10); // hours

    pDC->SelectStockObject(BLACK_PEN);
    CAlarm* pAlarm;
    if ((pAlarm = pDoc->m_pAlarm) != NULL) {
        pAlarm->m_time.GetHMS(nH, nM, nS);
        i = nH * 5;
        i = (i % 60) + nM / 12;
        pDC->TextOut(nX[i] * 8 / 10, nY[i] * 8 / 10, "A"); // alarm
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx25dView diagnostics

#ifdef _DEBUG
void CEx25dView::AssertValid() const
{
    CView::AssertValid();
}

void CEx25dView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx25dDoc* CEx25dView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx25dDoc)));
    return (CEx25dDoc*)m_pDocument;
}
#endif //_DEBUG
// computer-generated x-y coordinates for 60 points around a circle

const int CEx25dView::nX[] = {
    0, 105, 208, 309, 407, 500, 588, 669, 743, 809, 866, 914, 
    951, 978, 995, 1000, 995, 978, 951, 914, 866, 809, 743, 669, 
    588, 500, 407, 309, 208, 105, 0, -104, -207, -308, -406, -499, 
    -587, -668, -742, -808, -865, -913, -950, -977, -994, -999, -994, -977, 
    -950, -913, -865, -808, -742, -668, -587, -499, -406, -308, -207, -104 }; 
const int CEx25dView::nY[] = {
    999, 994, 978, 951, 913, 866, 809, 743, 669, 587, 499, 406, 
    309, 207, 104, 0, -104, -207, -309, -406, -499, -587, -669, -743, 
    -809, -866, -913, -951, -978, -994, -999, -994, -978, -951, -913, -866, 
    -809, -743, -669, -587, -500, -406, -309, -207, -104, 0, 104, 207, 
    309, 406, 499, 587, 669, 743, 809, 866, 913, 951, 978, 994 }; 


/////////////////////////////////////////////////////////////////////////////
// CEx25dView message handlers

int CEx25dView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    m_font.CreateFont(150, 0, 0, 0, 400, FALSE, FALSE,
                    0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS,
                    "Arial");                   
    return 0;
}
