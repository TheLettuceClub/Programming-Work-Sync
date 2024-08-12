// ex11cvw.cpp : implementation of the CEx11cView class
//

#include "stdafx.h"
#include "ex11c.h"

#include "ex11cdoc.h"
#include "ex11cvw.h"
#include "ex11cdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11cView

IMPLEMENT_DYNCREATE(CEx11cView, CView)

BEGIN_MESSAGE_MAP(CEx11cView, CView)
    //{{AFX_MSG_MAP(CEx11cView)
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11cView construction/destruction

CEx11cView::CEx11cView()
{
    // TODO: add construction code here
}

CEx11cView::~CEx11cView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx11cView drawing

void CEx11cView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0, "Press the left mouse button here.");
}



/////////////////////////////////////////////////////////////////////////////
// CEx11cView diagnostics

#ifdef _DEBUG
void CEx11cView::AssertValid() const
{
    CView::AssertValid();
}

void CEx11cView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx11cDoc* CEx11cView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11cDoc)));
    return (CEx11cDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11cView message handlers

int CEx11cView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CVBControl* pCntr = &((CEx11cApp*) AfxGetApp())->m_cntr;
    pCntr->Create("CNTR.VBX;Counter;", WS_VISIBLE | WS_CHILD | WS_BORDER, 
                  CRect(50, 175, 180, 208), this, 1);
    pCntr->SetNumProperty("DigitsLeft", 3);
    pCntr->SetNumProperty("DigitsRight", 2);
    pCntr->SetFloatProperty("Value", 123.45);

    return 0;
}

void CEx11cView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx11cDialog dlg;

    dlg.DoModal();
}
