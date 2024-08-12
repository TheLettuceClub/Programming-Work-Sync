// ex24avw.cpp : implementation of the CEx24aView class
//

#include "stdafx.h"
#include "ex24a.h"

#include "ex24aset.h"
#include "ex24adoc.h"
#include "ex24avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24aView

IMPLEMENT_DYNCREATE(CEx24aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx24aView, CScrollView)
    //{{AFX_MSG_MAP(CEx24aView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24aView construction/destruction

CEx24aView::CEx24aView()
{
    // TODO: add construction code here
}

CEx24aView::~CEx24aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx24aView drawing

void CEx24aView::OnDraw(CDC* pDC)
{
    int  y = 0;
    char temp[21];
    
    if (m_pSet->IsBOF()) {
      return;
    }
    m_pSet->MoveFirst();   // fails if recordset is empty
    while (!m_pSet->IsEOF()) {
        wsprintf(temp, "%ld", m_pSet->m_StudentID);
        pDC->TextOut(0, y, temp);
        pDC->TextOut(500, y, m_pSet->m_Name);
        wsprintf(temp, "%d", m_pSet->m_GradYear);
        pDC->TextOut(2500, y, temp);
        m_pSet->MoveNext();
        y -= 200;  // 0.2 inch down
    }
}

void CEx24aView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();
    CSize sizeTotal;

    sizeTotal.cx = 8000;
    sizeTotal.cy = 10500;
    SetScrollSizes(MM_HIENGLISH, sizeTotal);
    
    m_pSet = &GetDocument()->m_ex24aSet;
    // remember that docs/views are reused in SDI apps!
    if (m_pSet->IsOpen()) {
      m_pSet->Close();
    }
    m_pSet->Open();
}

/////////////////////////////////////////////////////////////////////////////
// CEx24aView printing

BOOL CEx24aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CEx24aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx24aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx24aView diagnostics

#ifdef _DEBUG
void CEx24aView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx24aView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx24aDoc* CEx24aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx24aDoc)));
    return (CEx24aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24aView message handlers
