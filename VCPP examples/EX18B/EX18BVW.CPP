// ex18bvw.cpp : implementation of the CEx18bView class
//

#include "stdafx.h"
#include "ex18b.h"

#include "ex18bdoc.h"
#include "ex18bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx18bView

IMPLEMENT_DYNCREATE(CEx18bView, CView)

BEGIN_MESSAGE_MAP(CEx18bView, CView)
    //{{AFX_MSG_MAP(CEx18bView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx18bView construction/destruction

CEx18bView::CEx18bView()
{
    // TODO: add construction code here
}

CEx18bView::~CEx18bView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx18bView drawing

void CEx18bView::OnDraw(CDC* pDC)
{
    int i, j;

    CEx18bDoc* pDoc = GetDocument();
    j = pDoc->m_nEllipseQty;
    for (i = 0; i < j; i++) {
      pDC->Ellipse(pDoc->m_ellipseArray[i]);
    }
}

void CEx18bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetMapMode(MM_LOENGLISH);
}

void CEx18bView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    int        i, nStart, nEnd, nHeight;
    char       temp[133];
    CPoint     point(720, -1440);
    CFont      font;
    TEXTMETRIC tm;

    pDC->SetMapMode(MM_TWIPS);
    CEx18bDoc* pDoc = GetDocument();
    m_nPage = pInfo->m_nCurPage; // for PrintPageFooter's benefit
    TRACE("page = %d\n", m_nPage);
    nStart = (m_nPage - 1) * CEx18bDoc::nLinesPerPage;
    nEnd = nStart + CEx18bDoc::nLinesPerPage;
    TRACE("Start = %d, End = %d\n", nStart, nEnd);
    // 14-point fixed-pitch font
    font.CreateFont(-280, 0, 0, 0, 400, FALSE, FALSE,
                    0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_MODERN, "Courier New");
                    // Courier New is a TrueType font
    CFont* pOldFont = (CFont*) (pDC->SelectObject(&font));
    PrintPageHeader(pDC);
    pDC->GetTextMetrics(&tm);
    nHeight = tm.tmHeight + tm.tmExternalLeading;
    for (i = nStart; i < nEnd; i++) {
      if (i >= pDoc->m_nEllipseQty)
        break;
      wsprintf(temp, "%6d %6d %6d %6d %6d", i + 1,
               pDoc->m_ellipseArray[i].left,
               pDoc->m_ellipseArray[i].top,
               pDoc->m_ellipseArray[i].right,
               pDoc->m_ellipseArray[i].bottom);
      point.y -= nHeight;
      pDC->TextOut(point.x, point.y, temp);
    }
    PrintPageFooter(pDC);
    pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CEx18bView printing

BOOL CEx18bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CEx18bDoc* pDoc = GetDocument();
	pInfo->SetMaxPage(pDoc->m_nEllipseQty / CEx18bDoc::nLinesPerPage + 1);
	return DoPreparePrinting(pInfo);
}

void CEx18bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx18bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}

void CEx18bView::PrintPageHeader(CDC* pDC)
{
    char temp[133];

    CPoint point(0, 0);
    pDC->TextOut(point.x, point.y, "Bubble Report");
    point += CSize(720, -720);
    wsprintf(temp, "%6.6s %6.6s %6.6s %6.6s %6.6s",
            (LPCSTR) "Index", (LPCSTR) "Left", (LPCSTR) "Top",
            (LPCSTR) "Right", (LPCSTR) "Bottom");
    pDC->TextOut(point.x, point.y, temp);
}

void CEx18bView::PrintPageFooter(CDC* pDC)
{
    char temp[133];

    CPoint point(0, -14400); // 10" down
    CEx18bDoc* pDoc = GetDocument();
    wsprintf(temp, "Document %s",(LPCSTR) pDoc->GetTitle());
    pDC->TextOut(point.x, point.y, temp);
    wsprintf(temp, "Page %d", m_nPage);
    CSize size = pDC->GetTextExtent(temp, strlen(temp));
    point.x += 11520 - size.cx;
    pDC->TextOut(point.x, point.y, temp); // right-justified
}

/////////////////////////////////////////////////////////////////////////////
// CEx18bView diagnostics

#ifdef _DEBUG
void CEx18bView::AssertValid() const
{
    CView::AssertValid();
}

void CEx18bView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx18bDoc* CEx18bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx18bDoc)));
    return (CEx18bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx18bView message handlers
