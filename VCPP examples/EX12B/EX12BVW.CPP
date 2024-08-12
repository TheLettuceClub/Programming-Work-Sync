// ex12bvw.cpp : implementation of the CEx12bView class
//

#include "stdafx.h"
#include "ex12b.h"

#include "ex12bdoc.h"
#include "ex12bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12bView

IMPLEMENT_DYNCREATE(CEx12bView, CEditView)

BEGIN_MESSAGE_MAP(CEx12bView, CEditView)
    //{{AFX_MSG_MAP(CEx12bView)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    ON_COMMAND_EX(IDM_SIZE_BASE, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 1, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 2, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 3, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 4, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 5, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 6, OnCommandSize)
    ON_COMMAND_EX(IDM_SIZE_BASE + 7, OnCommandSize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12bView construction/destruction

CEx12bView::CEx12bView()
{
    m_pFont = new CFont;
}

CEx12bView::~CEx12bView()
{
    delete m_pFont;
}

/////////////////////////////////////////////////////////////////////////////
// CEx12bView drawing

void CEx12bView::OnDraw(CDC* pDC)
{
    CEx12bDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx12bView diagnostics

#ifdef _DEBUG
void CEx12bView::AssertValid() const
{
    CEditView::AssertValid();
}

void CEx12bView::Dump(CDumpContext& dc) const
{
    CEditView::Dump(dc);
}

CEx12bDoc* CEx12bView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12bDoc)));
    return (CEx12bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12bView message handlers

int CEx12bView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CEditView::OnCreate(lpCreateStruct) != 0) {
        return -1;
    }
    
    ASSERT(m_pFont->CreateFont(-12, 0, 0, 0, 400, FALSE, FALSE, 0,
                               ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                               CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                               DEFAULT_PITCH | FF_SWISS, "Arial"));
    SetFont(m_pFont);
    
    return 0;
}

BOOL CEx12bView::OnCommandSize(UINT nID)
{
	int   nFontSize;
	CFont font;

	font.CreateStockObject(SYSTEM_FONT);
	SetFont(&font); // deselects any prior special font
	m_pFont->DeleteObject(); // deletes the deselected font

	nFontSize = 12 + (nID - (UINT) IDM_SIZE_BASE) * 2;
    VERIFY(m_pFont->CreateFont(-nFontSize, 0, 0, 0, 400, FALSE, FALSE, 0,
                               ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                               CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                               DEFAULT_PITCH | FF_SWISS, "Arial"));
    SetFont(m_pFont);
    return TRUE;
}
