// ex11avw.cpp : implementation of the CEx11aView class
//

#include "stdafx.h"
#include "ex11a.h"

#include "ex11adoc.h"
#include "ex11avw.h"
#include "ex11adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11aView

IMPLEMENT_DYNCREATE(CEx11aView, CView)

BEGIN_MESSAGE_MAP(CEx11aView, CView)
	//{{AFX_MSG_MAP(CEx11aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11aView construction/destruction

CEx11aView::CEx11aView()
{
	// TODO: add construction code here
}

CEx11aView::~CEx11aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView drawing

void CEx11aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView printing

BOOL CEx11aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx11aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx11aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}




/////////////////////////////////////////////////////////////////////////////
// CEx11aView diagnostics

#ifdef _DEBUG
void CEx11aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx11aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx11aDoc* CEx11aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11aDoc)));
	return (CEx11aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11aView message handlers

void CEx11aView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CEx11aDialog dlg;

    if (dlg.DoModal() == IDOK) {
      TRACE("Result = %d\n", dlg.m_nButton);
    }
}
