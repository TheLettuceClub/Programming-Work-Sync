// ex17bvw.cpp : implementation of the CEx17bView class
//

#include "stdafx.h"
#include "ex17b.h"

#include "ex17bdoc.h"
#include "ex17bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx17bView

IMPLEMENT_DYNCREATE(CEx17bView, CView)

BEGIN_MESSAGE_MAP(CEx17bView, CView)
	//{{AFX_MSG_MAP(CEx17bView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx17bView construction/destruction

CEx17bView::CEx17bView()
{
	// TODO: add construction code here
}

CEx17bView::~CEx17bView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx17bView drawing

void CEx17bView::OnDraw(CDC* pDC)
{
	CEx17bDoc* pDoc = GetDocument();

	// TODO: add draw code here
}



/////////////////////////////////////////////////////////////////////////////
// CEx17bView diagnostics

#ifdef _DEBUG
void CEx17bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx17bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx17bDoc* CEx17bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx17bDoc)));
	return (CEx17bDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx17bView message handlers
