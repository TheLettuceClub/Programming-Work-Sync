// ex18avw.cpp : implementation of the CStringView class
//

#include "stdafx.h"
#include "resource.h"

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
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringView construction/destruction

CStringView::CStringView()
{
	// TODO: add construction code here
}

CStringView::~CStringView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CStringView drawing

void CStringView::OnDraw(CDC* pDC)
{
	int i, j, nHeight;
	char temp[10];
	CFont font;
	TEXTMETRIC tm;

	CPoemDoc* pDoc = GetDocument();
	// draw a border 8 x 10.5
	pDC->MoveTo(CPoint(0, 0));
	pDC->LineTo(CPoint(11505, 0));
	pDC->LineTo(CPoint(11505, -15105));
	pDC->LineTo(CPoint(0, -15105));
	pDC->LineTo(CPoint(0, 0));
	// draw horizontal and vertical rulers
	for(i = 0; i <= 8; i++) {
		wsprintf(temp, "%02d", i);
		pDC->TextOut(i * 1440, 0, temp);
	}
	for(i = 0; i <= 10; i++) {
		wsprintf(temp, "%02d", i);
		pDC->TextOut(0, -i * 1440, temp);
	}
	// print the poem .5" down and over
	// use Roman 10-point font
	font.CreateFont(-200, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_ROMAN, "Times New Roman");
	CFont* pOldFont = (CFont*) pDC->SelectObject(&font);
	pDC->GetTextMetrics(&tm);
	nHeight = tm.tmHeight + tm.tmExternalLeading;
//	TRACE("font height = %d, internal leading = %d\n",
//		 nHeight, tm.tmInternalLeading);
  	j = pDoc->m_stringArray.GetSize();
	for(i = 0; i < j; i++) {
		pDC->TextOut(720, -i * nHeight - 720, pDoc->m_stringArray[i]);
	}
	pDC->SelectObject(pOldFont);
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


void CStringView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	pDC->SetMapMode(MM_TWIPS);
	OnDraw(pDC);
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

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStringView message handlers


int CStringView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CSize totalSize = CSize(11520, 15120); // 8" x 10.5"
	CSize pageSize = CSize(totalSize.cx / 2, totalSize.cy / 2); // for page scroll
	CSize lineSize = CSize(totalSize.cx / 100, totalSize.cy / 100); // line scroll
	SetScrollSizes(MM_HIENGLISH, totalSize, pageSize, lineSize); // CScrollView function

	return 0;
}
