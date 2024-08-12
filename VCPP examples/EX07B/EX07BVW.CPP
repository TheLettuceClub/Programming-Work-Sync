// ex07bvw.cpp : implementation of the CEx07bView class
//

#include "stdafx.h"
#include "ex07b.h"

#include "ex07bdoc.h"
#include "ex07bvw.h"
#include "ex07bdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07bView

IMPLEMENT_DYNCREATE(CEx07bView, CView)

BEGIN_MESSAGE_MAP(CEx07bView, CView)
    //{{AFX_MSG_MAP(CEx07bView)
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07bView construction/destruction

CEx07bView::CEx07bView()
{
    // TODO: add construction code here
}

CEx07bView::~CEx07bView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx07bView drawing

void CEx07bView::OnDraw(CDC* pDC)
{
    pDC->TextOut(0, 0, "Press the left mouse button here.");
}



/////////////////////////////////////////////////////////////////////////////
// CEx07bView diagnostics

#ifdef _DEBUG
void CEx07bView::AssertValid() const
{
    CView::AssertValid();
}

void CEx07bView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx07bDoc* CEx07bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx07bDoc)));
    return (CEx07bDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx07bView message handlers

void CEx07bView::OnLButtonDown(UINT nFlags, CPoint point)
{
    CEx07bDialog dlg;

    if (dlg.DoModal() != IDCANCEL) {
      CString filename = dlg.GetPathName(); // CFileDialog function
      if (dlg.m_bDeleteFlag) {
        char text[200];
        wsprintf (text, "Are you sure you want to delete %s?",
                 (LPCSTR) filename);
        if (AfxMessageBox(text, MB_YESNO) == IDYES) {
            CFile::Remove(filename);
        }
      }
      else {
        TRACE("Open file %s\n", (const char*) filename);
      }
    }
}
