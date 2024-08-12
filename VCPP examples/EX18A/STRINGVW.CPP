// stringvw.cpp : implementation of the CStringView class
//

#include "stdafx.h"
#include "ex18a.h"

#include "poemdoc.h"
#include "stringvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringView

IMPLEMENT_DYNCREATE(CStringView, CScrollView)

BEGIN_MESSAGE_MAP(CStringView, CScrollView)
    //{{AFX_MSG_MAP(CStringView)
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringView construction/destruction

CStringView::CStringView()
{
    SetScrollSizes(MM_TEXT, CSize(0, 0));
}

CStringView::~CStringView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CStringView drawing

void CStringView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
    if (pDC->IsPrinting()) {
        pDC->SetMapMode(MM_TWIPS);
    }
    else {
        CScrollView::OnPrepareDC(pDC, pInfo);
        pDC->SetMapMode(MM_ANISOTROPIC);
        pDC->SetWindowExt(1440, 1440);
        pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
                           -pDC->GetDeviceCaps(LOGPIXELSY));
    }
}

void CStringView::SetScrollInfo()
{
    CClientDC dc(NULL);
    OnPrepareDC(&dc);
    CSize totalSize = CSize(11520, 15120);      // 8" x 10.5"
    dc.LPtoDP(&totalSize);
    CSize pageSize = CSize(totalSize.cx / 2,
                           totalSize.cy / 2);   // page scroll
    CSize lineSize = CSize(totalSize.cx / 100,
                           totalSize.cy / 100); // line scroll
    SetScrollSizes(MM_TEXT, totalSize, pageSize, lineSize);
}

void CStringView::OnDraw(CDC* pDC)
{
    int        i, j, nHeight;
    char       temp[10];
    CFont      font;
    TEXTMETRIC tm;

    CPoemDoc* pDoc = GetDocument();
    // draw a border 8 x 10.5
    pDC->Rectangle(CRect(0, 0, 11505, -15105));
    // draw horizontal and vertical rulers
    for (i = 0; i <= 8; i++) {
      wsprintf(temp, "%02d", i);
      pDC->TextOut(i * 1440, 0, temp);
    }
    for (i = 0; i <= 10; i++) {
      wsprintf(temp, "%02d", i);
      pDC->TextOut(0, -i * 1440, temp);
    }
    // print the poem 0.5 inch down and over
    // use Roman 10-point font
    font.CreateFont(-200, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                    DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
                    "Times New Roman");
    CFont* pOldFont = (CFont*) pDC->SelectObject(&font);
    pDC->GetTextMetrics(&tm);
    nHeight = tm.tmHeight + tm.tmExternalLeading;
    TRACE("font height = %d, internal leading = %d\n",
          nHeight, tm.tmInternalLeading);
    j = pDoc->m_stringArray.GetSize();
    for (i = 0; i < j; i++) {
      pDC->TextOut(720, -i * nHeight - 720, pDoc->m_stringArray[i]);
    }
    pDC->SelectObject(pOldFont);
}

void CStringView::OnInitialUpdate()
{
    SetScrollInfo();
    CScrollView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CStringView printing

BOOL CStringView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CStringView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CStringView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStringView diagnostics

#ifdef _DEBUG
void CStringView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CStringView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

CPoemDoc* CStringView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoemDoc)));
    return (CPoemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStringView message handlers

void CStringView::OnSize(UINT nType, int cx, int cy)
{
    SetScrollInfo();
    CScrollView::OnSize(nType, cx, cy);
}
