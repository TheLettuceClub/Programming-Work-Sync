// ex12avw.cpp : implementation of the CEx12aView class
//

#include "stdafx.h"
#include "ex12a.h"

#include "ex12adoc.h"
#include "ex12avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12aView

IMPLEMENT_DYNCREATE(CEx12aView, CEditView)

BEGIN_MESSAGE_MAP(CEx12aView, CEditView)
    //{{AFX_MSG_MAP(CEx12aView)
    ON_COMMAND(ID_FONT_FIXED, OnFontFixed)
    ON_UPDATE_COMMAND_UI(ID_FONT_FIXED, OnUpdateFontFixed)
    ON_COMMAND(ID_FONT_SYSTEM, OnFontSystem)
    ON_UPDATE_COMMAND_UI(ID_FONT_SYSTEM, OnUpdateFontSystem)
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12aView construction/destruction

CEx12aView::CEx12aView()
{
    m_nFont = SYSTEM_FONT;
}

CEx12aView::~CEx12aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView drawing

void CEx12aView::OnDraw(CDC* pDC)
{
    CEx12aDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView printing

BOOL CEx12aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // default CEditView preparation
    return CEditView::OnPreparePrinting(pInfo);
}

void CEx12aView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // Default CEditView begin printing.
    CEditView::OnBeginPrinting(pDC, pInfo);
}

void CEx12aView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    // Default CEditView end printing
    CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aView diagnostics

#ifdef _DEBUG
void CEx12aView::AssertValid() const
{
    CEditView::AssertValid();
}

void CEx12aView::Dump(CDumpContext& dc) const
{
    CEditView::Dump(dc);
}

CEx12aDoc* CEx12aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx12aDoc)));
    return (CEx12aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12aView message handlers

void CEx12aView::OnFontFixed()
{
    CFont font;

    font.CreateStockObject(SYSTEM_FIXED_FONT);
    SetFont(&font);
    m_nFont = SYSTEM_FIXED_FONT;
}

void CEx12aView::OnUpdateFontFixed(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nFont == SYSTEM_FIXED_FONT);
}

void CEx12aView::OnFontSystem()
{
	CFont font;

    font.CreateStockObject(SYSTEM_FONT);
    SetFont(&font);
    m_nFont = SYSTEM_FONT;
}

void CEx12aView::OnUpdateFontSystem(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_nFont == SYSTEM_FONT);
}


BOOL CEx12aView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style = AFX_WS_DEFAULT_VIEW | WS_VSCROLL |
               ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL;
    return CEditView::PreCreateWindow(cs);
}
