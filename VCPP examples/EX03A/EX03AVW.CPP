// ex03avw.cpp : implementation of the CEx03aView class
//

#include "stdafx.h"
#include "ex03a.h"

#include "ex03adoc.h"
#include "ex03avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx03aView

IMPLEMENT_DYNCREATE(CEx03aView, CView)

BEGIN_MESSAGE_MAP(CEx03aView, CView)
	//{{AFX_MSG_MAP(CEx03aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx03aView construction/destruction

CEx03aView::CEx03aView()
{
	// TODO: add construction code here
}

CEx03aView::~CEx03aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx03aView drawing

void CEx03aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Hello, world!");  // prints in default font &
	                                      //  size, top-left corner
	pDC->SelectStockObject(GRAY_BRUSH);   // selects a brush for the
	                                      //  circle interior
	pDC->Ellipse(CRect(0, 20, 100, 120)); // draws a gray circle 100
	                                      //  units in diameter
}



/////////////////////////////////////////////////////////////////////////////
// CEx03aView diagnostics

#ifdef _DEBUG
void CEx03aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx03aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx03aDoc* CEx03aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx03aDoc)));
	return (CEx03aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx03aView message handlers
