// matvw1.cpp : implementation of the CListView class
// OnDraw is for printing only
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//

#include "stdafx.h"
#include "resource.h"
#include "matpiece.h"
#include "matdlg.h"
#include "matdoc.h"
#include "listview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListView

IMPLEMENT_DYNCREATE(CListView, CView)

BEGIN_MESSAGE_MAP(CListView, CView)
    //{{AFX_MSG_MAP(CListView)
        ON_WM_CREATE()
        ON_WM_PAINT()
        ON_WM_SIZE()
        ON_LBN_DBLCLK(IDR_LISTBOX, OnListBoxDblClk)
        ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
        ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
    //}}AFX_MSG_MAP

    // Standard Print commands
        // REVIEW: later CODEWIZ will allow you to edit these in {{ }}
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListView construction/destruction

CListView::CListView() : m_drawOffset(50, -100)
{
    m_pListBox = new CListBox;
    m_pPiece = new CPiece; // 'working' piece object
    m_nPage = m_xChar = m_yChar = 0;
    m_pPrintFont = new CFont;
    m_nLinesPerPage = 3;   // should be computed from GetDeviceCaps

}

CListView::~CListView()
{
    delete m_pListBox;
    delete m_pPiece;
    delete m_pPrintFont;
}

/////////////////////////////////////////////////////////////////////////////
// CListView drawing

void CListView::OnDraw(CDC* pDC)
{   // called for Print/Print Preview ONLY, not for display
    CPoint  point(0, 0);
    CPiece* pPiece;
    int     nLineMin, nLineMax; // zero-based line numbers

    CMatplanDoc* pDoc = GetDocument();
    nLineMin = (m_nPage - 1) * m_nLinesPerPage;
    nLineMax = nLineMin + m_nLinesPerPage - 1;
    if (nLineMax > pDoc->m_pieceArray.GetUpperBound()) {
        nLineMax = pDoc->m_pieceArray.GetUpperBound();
    }
    point += m_drawOffset;
    point.y -= m_yChar * 2;  // space for col head & blank line
    for (int i = nLineMin; i <= nLineMax; i++) {
        pPiece = (CPiece*) (pDoc->m_pieceArray.GetAt(i));
        point.y -= m_yChar;
        pPiece->PrintLine(pDC, point);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // application framework calls OnPrepareDC prior to OnPrint
    PrintPageHeader(pDC);
    m_nPage = pInfo->m_nCurPage; // for OnDraw's and
                                 // PrintPageFooter's benefit
    OnDraw(pDC);
    PrintPageFooter(pDC);
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{   // refreshes list box from array in document
    // when the application starts, this function is called
    //  before the window is shown
    CPiece* pPiece;

    m_pListBox->ResetContent(); // empty the list box
    CMatplanDoc* pDoc = GetDocument();
    int nCount  = pDoc->m_pieceArray.GetUpperBound();
    if (nCount  == -1) {
        StartNewList();
    }
    else {
        // copy all data from the document's piece array
        //  to the view's list box
        for (int i = 0; i <= nCount; i++) {
            pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
            pPiece->InsertInList(m_pListBox, -1); // AddString
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SetMapMode(MM_LOENGLISH);
    pDC->SelectObject(m_pPrintFont); // need to do it every page
}

/////////////////////////////////////////////////////////////////////////////
BOOL CListView::OnPreparePrinting(CPrintInfo* pInfo)
{
    // The print preview window needs to know what range of pages to
    // map to its scrollbar.  We supply that information here.

    CMatplanDoc* pDoc = GetDocument();
    pInfo->SetMaxPage(pDoc->m_pieceArray.GetUpperBound()
                    / m_nLinesPerPage + 1);
    return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    TEXTMETRIC tm;

    if (m_xChar == 0) {
        m_pPrintFont->CreateFont(30, 10, 0, 0, 400, FALSE, FALSE,
            0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_MODERN, "Courier New"); // TrueType
        pDC->SelectObject(m_pPrintFont);
        pDC->GetTextMetrics(&tm);
        m_xChar = tm.tmAveCharWidth;
        m_yChar = tm.tmHeight + tm.tmExternalLeading;
    }
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
    pDC->SelectStockObject(SYSTEM_FONT);
}

/////////////////////////////////////////////////////////////////////////////
int CListView::OnCreate(LPCREATESTRUCT lpcs)
{
    CRect rect;
    CFont font;

    // makes a list box the exact size of the window
    GetClientRect(&rect);
    rect.InflateRect(GetSystemMetrics(SM_CXBORDER),
                     GetSystemMetrics(SM_CYBORDER));
    m_pListBox->Create(WS_CHILD | WS_HSCROLL | WS_VSCROLL | WS_VISIBLE |
                       LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
                       rect, this, IDR_LISTBOX);
    // creates and attaches a fixed font to the list box

    font.CreateStockObject(SYSTEM_FIXED_FONT);
    m_pListBox->SetFont(&font);
    return CView::OnCreate(lpcs);
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnPaint()
{
    CPaintDC dc(this); // this statement is necessary to generate
                       //  the BeginPaint and EndPaint calls to
                       //  validate the rect
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnSize(UINT nType, int cx, int cy)
{
    CRect rect;

    if (m_pListBox) {
        GetClientRect(&rect);
        rect.InflateRect(GetSystemMetrics(SM_CXBORDER),
            GetSystemMetrics(SM_CYBORDER));
        m_pListBox->MoveWindow(rect);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CListView::OnListBoxDblClk()
{   // called only if the list box is not empty
    int i = m_pListBox->GetCurSel();
    m_pPiece->ExtractFromList(m_pListBox, i);
    m_pPiece->m_bNewList = FALSE;
    m_pDialog = new CMatplanDialog(this, m_pPiece);
    int rtn = m_pDialog->DoModal();
    switch(rtn) {
    case IDC_UPDATE:
        m_pListBox->DeleteString(i);
        m_pPiece->InsertInList(m_pListBox, i);
        m_pListBox->SetCurSel(i);
        UpdatePlanDocument();
        break;
    case IDC_DELETE:
        m_pListBox->DeleteString(i);
        m_pListBox->SetCurSel(i);
        UpdatePlanDocument();
        break;
    case IDC_INSERT:
        m_pPiece->InsertInList(m_pListBox, i);
        m_pListBox->SetCurSel(i);
        UpdatePlanDocument();
        break;
    case IDCANCEL:
        break;
    case IDOK:
    default:
        ASSERT(0);
        break;
    }
    delete m_pDialog;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CListView::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
    if (lParam == 0) {
        lParam = HID_BASE_RESOURCE + IDR_LISTVIEW;
    }
    // context already determined above--we don't modify it
    AfxGetApp()->WinHelp(lParam);
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
LRESULT CListView::OnHelpHitTest(WPARAM wParam, LPARAM lParam)
{
    return HID_BASE_RESOURCE + IDR_LISTVIEW;
}

/////////////////////////////////////////////////////////////////////////////
void CListView::PrintPageHeader(CDC* pDC)
{
    char temp[133];

    CPoint point(0, 0);
    pDC->TextOut(point.x, point.y, "Material Report");
    point += m_drawOffset;
    sprintf(temp, "%6.6s %6.6s %-30.30s%5.5s%5.5s%5.5s",
        "Lngth", "Width", "Description", "Sheet", "X", "Y");
    pDC->TextOut(point.x, point.y, temp);
}

/////////////////////////////////////////////////////////////////////////////
void CListView::PrintPageFooter(CDC* pDC)
{
    char temp[133];

    CPoint point(0, -500);
    CMatplanDoc* pDoc = GetDocument();
    sprintf(temp, "File %-60.60s Page %d",
            (const char*) pDoc->GetPathName(), m_nPage);
    pDC->TextOut(point.x, point.y, temp);
}

/////////////////////////////////////////////////////////////////////////////
// private functions

void CListView::UpdatePlanDocument()
{   // transfers all data from view (list box) to document
    CPiece* pPiece;
    int     i;

    CMatplanDoc* pDoc = GetDocument();

    // gets rid of the old piece list in the document
    for (i = pDoc->m_pieceArray.GetUpperBound(); i >= 0; i--) {
        pPiece = (CPiece*) pDoc->m_pieceArray.GetAt(i);
        delete pDoc->m_pieceArray.GetAt(i);
        pDoc->m_pieceArray.RemoveAt(i);
    }
    // copies all strings from view's list box to document's piece list
    int listLen = m_pListBox->GetCount();
    for (i = 0; i < listLen; i++) {
        pPiece = new CPiece;
        pPiece->ExtractFromList(m_pListBox, i);
        pDoc->m_pieceArray.SetAtGrow(i, pPiece);
    }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(this); // except ourselves
}

/////////////////////////////////////////////////////////////////////////////
void CListView::StartNewList()
{
    int rtn;

    m_pPiece->m_desc = "";
    m_pPiece->m_length = 0.0;
    m_pPiece->m_width = 0.0;
    m_pPiece->m_sheet = 0;
    m_pPiece->m_x = 0;
    m_pPiece->m_y = 0;
    m_pPiece->m_bNewList = TRUE;

    m_pDialog = new CMatplanDialog(this, m_pPiece);
    do {
        VERIFY((rtn = m_pDialog->DoModal()) != -1); // resource present?
    } while(rtn != IDC_INSERT && rtn != IDC_CANCEL);
    if (rtn == IDC_INSERT) {
        m_pPiece->InsertInList(m_pListBox, -1); // AddString
        m_pListBox->SetCurSel(0);
        UpdatePlanDocument();
    }
    delete m_pDialog;
}

/////////////////////////////////////////////////////////////////////////////
// CListView diagnostics

#ifdef _DEBUG
void CListView::AssertValid() const
{
    CView::AssertValid();
}

void CListView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

#endif //_DEBUG
