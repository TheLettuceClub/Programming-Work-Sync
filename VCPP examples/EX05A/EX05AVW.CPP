// ex05avw.cpp : implementation of the CEx05aView class
//

#include "stdafx.h"
#include "ex05a.h"

#include "ex05adoc.h"
#include "ex05avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05aView

IMPLEMENT_DYNCREATE(CEx05aView, CView)

BEGIN_MESSAGE_MAP(CEx05aView, CView)
    //{{AFX_MSG_MAP(CEx05aView)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05aView construction/destruction

CEx05aView::CEx05aView()
{
    // TODO: add construction code here
}

CEx05aView::~CEx05aView()
{
}


void CEx05aView::OnPrepareDC(CDC *pDC, CPrintInfo* pInfo /* = NULL */)
{                                                               
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(1440, 1440);
    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
                       -pDC->GetDeviceCaps(LOGPIXELSY));
}


void CEx05aView::ShowFont(CDC *pDC, int& nPos, int nPoints)
{                                                        
    TEXTMETRIC tm;
    CFont      testFont;
    char       text[100];
    CSize      tExtent;

    testFont.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pOldFont = (CFont*) pDC->SelectObject(&testFont);
    pDC->GetTextMetrics(&tm);
    TRACE("points = %d, tmHeight = %d, tmInternalLeading = %d,"
          " tmExternalLeading = %d\n", nPoints, tm.tmHeight,
          tm.tmInternalLeading, tm.tmExternalLeading);
    wsprintf(text, "This is %d-point Arial", nPoints);
    tExtent = pDC->GetTextExtent(text, strlen(text));
    TRACE("string width = %d, string height = %d\n", tExtent.cx,
           tExtent.cy);
    pDC->TextOut(0, nPos, text);
    pDC->SelectObject(pOldFont);
    nPos -= tm.tmHeight + tm.tmExternalLeading;
}


/////////////////////////////////////////////////////////////////////////////
// CEx05aView drawing

void CEx05aView::OnDraw(CDC* pDC)
{
    int nPosition = 0;
    
    for (int i = 6; i <= 24; i += 2) {
      ShowFont(pDC, nPosition, i);
    }
}
     

/////////////////////////////////////////////////////////////////////////////
// CEx05aView printing

BOOL CEx05aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default preparation
    return DoPreparePrinting(pInfo);
}

void CEx05aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add extra initialization before printing
}

void CEx05aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
    // TODO: add cleanup after printing
}




/////////////////////////////////////////////////////////////////////////////
// CEx05aView diagnostics

#ifdef _DEBUG
void CEx05aView::AssertValid() const
{
    CView::AssertValid();
}

void CEx05aView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx05aDoc* CEx05aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05aDoc)));
    return (CEx05aDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05aView message handlers
