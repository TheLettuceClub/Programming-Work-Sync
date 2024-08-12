// ex18avw.cpp : implementation of the CHexView class
//

#include "stdafx.h"
#include "resource.h"

#include "poemdoc.h"
#include "hexvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHexView

IMPLEMENT_DYNCREATE(CHexView, CScrollView)

BEGIN_MESSAGE_MAP(CHexView, CScrollView)
    //{{AFX_MSG_MAP(CHexView)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHexView construction/destruction

CHexView::CHexView()
{
    // TODO: add construction code here
}

CHexView::~CHexView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CHexView drawing

void CHexView::OnDraw(CDC* pDC)
{
    // hex dump of document strings
    int        i, j, k, l, nHeight;
    long       n;
    char       temp[10];
    CString    outputLine;
    TEXTMETRIC tm;
    CFont      font;

    CPoemDoc* pDoc = GetDocument();
    font.CreateFont(-160, 80, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pOldFont = (CFont*) pDC->SelectObject(&font);
    pDC->GetTextMetrics(&tm);
    nHeight = tm.tmHeight + tm.tmExternalLeading;

    j = pDoc->m_stringArray.GetSize();
    for(i = 0; i < j; i++) {
        wsprintf(temp, "%02x   ", i);
        outputLine = temp;
        l = pDoc->m_stringArray[i].GetLength();
        for(k = 0; k < l; k++) {
            n = pDoc->m_stringArray[i][k] & 0x00ff;
            wsprintf(temp, "%02lx ", n);
            outputLine += temp;
        }
        pDC->TextOut(720, -i * nHeight - 720, outputLine);
    }
    pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// CHexView printing

BOOL CHexView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

void CHexView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CHexView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}


void CHexView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetMapMode(MM_TWIPS);
    OnDraw(pDC);
}


/////////////////////////////////////////////////////////////////////////////
// CHexView diagnostics

#ifdef _DEBUG
void CHexView::AssertValid() const
{
    CScrollView::AssertValid();
}

void CHexView::Dump(CDumpContext& dc) const
{
    CScrollView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHexView message handlers


int CHexView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CScrollView::OnCreate(lpCreateStruct) == -1)
        return -1;

    CSize totalSize = CSize(11520, 15120); // 8" x 10.5"
    CSize pageSize = CSize(totalSize.cx / 2, totalSize.cy / 2); // for page scroll
    CSize lineSize = CSize(totalSize.cx / 100, totalSize.cy / 100); // line scroll
    SetScrollSizes(MM_HIENGLISH, totalSize, pageSize, lineSize); // CScrollView function

    return 0;
}
