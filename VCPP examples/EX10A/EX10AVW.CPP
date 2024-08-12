// ex10avw.cpp : implementation of the CEx10aView class
//

#include "stdafx.h"
#include "ex10a.h"

#include "ex10adoc.h"
#include "ex10avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10aView

IMPLEMENT_DYNCREATE(CEx10aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx10aView, CScrollView)
    //{{AFX_MSG_MAP(CEx10aView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10aView construction/destruction

CEx10aView::CEx10aView()
{
    m_pDisplayMemDC = new CDC;
}

CEx10aView::~CEx10aView()
{
    // clean up the memory display context and the bitmap
	delete m_pDisplayMemDC->SelectObject(CBitmap::FromHandle
	                                    (m_hOldDisplayBitmap));
	delete m_pDisplayMemDC;
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView drawing

void CEx10aView::OnDraw(CDC* pDC)
{
    pDC->StretchBlt(100, -100, m_nDWidth, m_nDHeight,
                    m_pDisplayMemDC, 0, 0, m_nSWidth,
                    m_nSHeight, SRCCOPY);
}

void CEx10aView::OnInitialUpdate()
{
    CScrollView::OnInitialUpdate();
    CSize totalSize(800, 1050); // 8" x 10"
    CSize lineSize = CSize(totalSize.cx / 100, totalSize.cy / 100);
    SetScrollSizes(MM_LOENGLISH, totalSize, totalSize, lineSize);

    BITMAP bm; // Windows BITMAP data structure (see Win 3.1 help)
    if (m_pDisplayMemDC->GetSafeHdc() == NULL) {
      CClientDC dc(this);  
      OnPrepareDC(&dc); // necessary
      CBitmap* pBitmap = new CBitmap;
      pBitmap->LoadBitmap(IDB_APPEXIT);
      m_pDisplayMemDC->CreateCompatibleDC(&dc);
      CBitmap* pOldBitmap = (CBitmap*)
                            (m_pDisplayMemDC->SelectObject(pBitmap));
      m_hOldDisplayBitmap = (HBITMAP) pOldBitmap->GetSafeHandle();

      pBitmap->GetObject(sizeof(bm), &bm);
      m_nSWidth = bm.bmWidth;
      m_nSHeight = bm.bmHeight;
      CRect rect(0, 0, m_nSWidth, m_nSHeight); // size of the bitmap
      dc.DPtoLP(&rect);
      m_nDWidth = rect.Width() * 4;
      m_nDHeight = rect.Height() * 4; // display bitmap dimensions
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView printing

BOOL CEx10aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CEx10aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx10aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx10aView diagnostics

#ifdef _DEBUG
void CEx10aView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CEx10aView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CEx10aDoc* CEx10aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10aDoc)));
    return (CEx10aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10aView message handlers
