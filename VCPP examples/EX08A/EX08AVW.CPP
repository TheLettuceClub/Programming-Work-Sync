// ex08avw.cpp : implementation of the CEx08aView class
//

#include "stdafx.h"
#include "ex08a.h"

#include "ex08adoc.h"
#include "ex08adlg.h"
#include "ex08avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08aView

IMPLEMENT_DYNCREATE(CEx08aView, CView)

BEGIN_MESSAGE_MAP(CEx08aView, CView)
    //{{AFX_MSG_MAP(CEx08aView)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08aView construction/destruction

CEx08aView::CEx08aView()
{
    // TODO: add construction code here
}

CEx08aView::~CEx08aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx08aView drawing

void CEx08aView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0, "Press the left mouse button here.");
}



/////////////////////////////////////////////////////////////////////////////
// CEx08aView diagnostics

#ifdef _DEBUG
void CEx08aView::AssertValid() const
{
    CView::AssertValid();
}

void CEx08aView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx08aDoc* CEx08aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08aDoc)));
    return (CEx08aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08aView message handlers

void CEx08aView::OnLButtonDown(UINT nFlags, CPoint point)
{
    int          i, j;
    CEx08aDialog dlg;          // constructs the dialog
    
    for (i = 1; i < 8; i++) {  // fills the data array with test data
      for (j= 1; j < 11; j++) {
        dlg.m_dArray[i][j] = i + j;
      }
    }
    
    dlg.DoModal();             // starts the dialog
    
    for (j = 1; j < 11; j++) { // prints the modified array
      for (i = 1; i < 8;  i++) {
        TRACE("%8.2f ", dlg.m_dArray[i][j]);
      }
      TRACE("\n");
    }
}
