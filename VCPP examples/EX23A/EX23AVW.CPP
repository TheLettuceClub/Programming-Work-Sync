// ex23avw.cpp : implementation of the CEx23aView class
//

#include "stdafx.h"
#include "ex23a.h"

#include "cdib.h"
#include "ex23adoc.h"
#include "ex23avw.h"
#include "bitsdlg.h"

/************************************************************************/
#define DRAW_ALT 3 //1=StretchBlt, 2=BitBlt, 3=Stretch DIB, 4=Display DIB
/************************************************************************/

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx23aView

IMPLEMENT_DYNCREATE(CEx23aView, CScrollView)

BEGIN_MESSAGE_MAP(CEx23aView, CScrollView)
    //{{AFX_MSG_MAP(CEx23aView)
    ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
    ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
    ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
    ON_COMMAND(ID_EDIT_PASTE_FROM, OnEditPasteFrom)
    ON_COMMAND(ID_EDIT_COPY_TO, OnEditCopyTo)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY_TO, OnUpdateEditCopy)
    ON_COMMAND(ID_EDIT_CUT, OnEditCut)
    ON_COMMAND(ID_VIEW_SHRINK, OnViewShrink)
    ON_UPDATE_COMMAND_UI(ID_VIEW_SHRINK, OnUpdateViewShrink)
    ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopy)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx23aView construction/destruction

CEx23aView::CEx23aView() : m_totalSize(800, 1050) // 8" x 10.5" when printed
{
    m_pDisplayMemDC = new CDC;  // DC lasts for the life of the view
    m_bShrinkToFit = FALSE;
}

CEx23aView::~CEx23aView()
{
    // deletes bitmap currently selected and restores original bitmap
    delete m_pDisplayMemDC->SelectObject
           (CBitmap::FromHandle(m_hOldDisplayBitmap));
    delete m_pDisplayMemDC;
}

/////////////////////////////////////////////////////////////////////////////
void CEx23aView::OnDraw(CDC* pDC)
{
    CRect clientRect;
    
    GetClientRect(clientRect); // device coords
    pDC->DPtoLP(clientRect);   // logical
    
#if DRAW_ALT == 1
    TRACE("Drawing alternative 1 - StretchBlt from bitmap\n");
    if (GetDocument()->m_pDib->GetMonoColors(dwFore, dwBack)) {
        pDC->SetBkColor(dwBack);
        pDC->SetTextColor(dwFore);
    }
    if (m_bShrinkToFit | pDC->IsPrinting()) {
        pDC->StretchBlt(0, 0, m_totalSize.cx, m_totalSize.cy,
                        m_pDisplayMemDC, 0, 0, m_bmSize.cx,
                        m_bmSize.cy, SRCCOPY);
    }
    else {
        // The previous StretchBlt call works fine, but this one's faster.
        // It draws only the portion of the bitmap that's in the window.
        // not so good for Print Preview, however.
        pDC->StretchBlt(clientRect.left, clientRect.top,
                        clientRect.Width(), clientRect.Height(),
                        m_pDisplayMemDC,
                        (int) ((long) m_bmSize.cx * (long) clientRect.left /
                               (long) m_totalSize.cx),
                        (int) ((long) m_bmSize.cy * (long) clientRect.top /
                               (long) m_totalSize.cy),
                        (int) ((long) m_bmSize.cx * (long) clientRect.Width() /
                               (long) m_totalSize.cx),
                        (int) ((long) m_bmSize.cy * (long) clientRect.Height() /
                               (long) m_totalSize.cy), SRCCOPY);
    }
#endif

#if DRAW_ALT == 2
    TRACE("Drawing alternative 2 - BitBlt from bitmap\n");
    if (GetDocument()->m_pDib->GetMonoColors(dwFore, dwBack)) {
        pDC->SetBkColor(dwBack);
        pDC->SetTextColor(dwFore);
    }
    pDC->BitBlt(0, 0, m_bmSize.cx, m_bmSize.cy,
                m_pDisplayMemDC, 0, 0, SRCCOPY);  
#endif

#if DRAW_ALT == 3
    // CPoint origin: +y = down
    TRACE("Drawing alternative 3 - Stretch DIB\n");
    GetDocument()->m_pDib->Stretch(pDC, CPoint(0, 0), m_bmSize);
#endif

#if DRAW_ALT == 4
    // CPoint origin: +y = down
    TRACE("Drawing alternative 4 - Display DIB\n");
    GetDocument()->m_pDib->Display(pDC, CPoint(0, 0));
#endif

#if (DRAW_ALT == 2) || (DRAW_ALT == 4)
    // print the filename at the bottom of the screen/paper
    CFont titleFont;
    titleFont.CreateFont(50, 0, 0, 0, 400, FALSE, FALSE, 0,
                         ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                         DEFAULT_PITCH | FF_SWISS, "Arial");
    pDC->SelectObject(&titleFont);
    pDC->TextOut(0, 1000, GetDocument()->GetTitle());
    pDC->SelectStockObject(SYSTEM_FONT);
#endif 
    // shows bits-per-pixel in status bar (subject to overwrite by menu code)
    char text[40];
    int nBits = GetDocument()->m_pDib->GetColorBits();
    wsprintf(text, "Bits per pixel = %d", nBits);
    CStatusBar* pStatus = (CStatusBar*)
        AfxGetApp()->m_pMainWnd->GetDlgItem(AFX_IDW_STATUS_BAR);
    if (pStatus && nBits) {
        pStatus->SetPaneText(0, text);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CEx23aView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    // custom MM_LOENGLISH with positive y down
    int nHsize = (int) (pDC->GetDeviceCaps(HORZSIZE) * 1000L / 254L);
    int nVsize = (int) (pDC->GetDeviceCaps(VERTSIZE) * 1000L / 254L);
    pDC->SetMapMode(MM_ANISOTROPIC);
    pDC->SetWindowExt(nHsize, nVsize);
    pDC->SetViewportExt(pDC->GetDeviceCaps(HORZRES),
                        pDC->GetDeviceCaps(VERTRES));
    OnDraw(pDC);
}

///////////////////////////////////////////////////////////////////
void CEx23aView::OnInitialUpdate()
{
    TRACE("CEx23aView::OnInitialUpdate\n");
    if (m_bShrinkToFit) {
        SetScaleToFitSize(m_totalSize);
    }
    else {
        SetScrollSizes(MM_TEXT, m_totalSize);
    }
    CScrollView::OnInitialUpdate();
}
 
void CEx23aView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    delete GetDocument()->m_pDib->MakeBitmap(m_pDisplayMemDC, m_bmSize);
    if (!m_bShrinkToFit) {
        ScrollToPosition(CPoint(0, 0));
    }
    Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
BOOL CEx23aView::OnPreparePrinting(CPrintInfo* pInfo)
{
    pInfo->SetMaxPage(1);
    return DoPreparePrinting(pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CEx23aView message handlers
int CEx23aView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CScrollView::OnCreate(lpCreateStruct)) {
        return -1;
    }

    // 'prime the pump' with an empty bitmap
    CClientDC dc(this);
    m_pDisplayMemDC->CreateCompatibleDC(&dc);
    CBitmap* pEmptyBitmap = new CBitmap;
    pEmptyBitmap->CreateCompatibleBitmap(&dc, 0, 0);
    CBitmap* pOldBitmap =
         (CBitmap*) m_pDisplayMemDC->SelectObject(pEmptyBitmap);
    // so we'll have an old bitmap to switch to at the end
    m_hOldDisplayBitmap = (HBITMAP) pOldBitmap->GetSafeHandle();
    return 0;
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnEditCopy()
{
    CBitmap* pBitmap = 
        GetDocument()->m_pDib->MakeBitmap(m_pDisplayMemDC, m_bmSize);
    if (pBitmap) {
        VERIFY(OpenClipboard());
        VERIFY(::EmptyClipboard());
        VERIFY(::SetClipboardData(CF_BITMAP, pBitmap->Detach()));
        VERIFY(::CloseClipboard());
        delete pBitmap;
    }
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnEditCut()
{
    OnEditCopy();
    GetDocument()->OnEditClearAll();
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnEditCopyTo()
{
    // copy DIB to a .BMP file
    CFileDialog dlg(FALSE, "bmp");
    if (dlg.DoModal() != IDOK) {
        return;
    }
    CFile file;
    if (!file.Open(dlg.GetPathName(), CFile::modeCreate |
        CFile::modeWrite)) {
        AfxMessageBox("Edit Copy To: Can't open file");
        return;
    }
    GetDocument()->m_pDib->Write(&file);  // get the DIB out of
                                          //  the document
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnEditPaste()
{
    VERIFY(OpenClipboard());
    // list the available clipboard formats
    UINT uFormat = 0;
    do {
        TRACE(" format = %lx\n", (long) uFormat); // first time always 0
    }
    while(uFormat = ::EnumClipboardFormats(uFormat));
    //
    // update command UI should keep us out of here if not CF_BITMAP
    if (::IsClipboardFormatAvailable(CF_BITMAP)) {
        // select the clipboard bitmap into the mem device context
        // then delete the old DIB and create the new DIB in the document
        // finally, make a new bitmap from the DIB
        // the internal bitmap can be displayed in OnDraw
        BITMAP bm;

        HBITMAP hBitmap = (HBITMAP) ::GetClipboardData(CF_BITMAP);
        ASSERT(hBitmap);
        CBitmap* pSourceBitmap = CBitmap::FromHandle(hBitmap); // temporary object
        pSourceBitmap->GetObject(sizeof(bm), &bm);
        
        int nBits = bm.bmPlanes * bm.bmBitsPixel; // bits per pixel
        TRACE("bits = %d\n", nBits);
        ASSERT((nBits == 1) || (nBits == 4) || (nBits == 8) || (nBits == 24));
        // allow user to change the # of bits per pixel
        CBitsDialog bdlg;  // system modal dialog
        if (nBits == 1) {
            bdlg.m_nBits = 0;
        }
        else 
            if (nBits == 4) {
                bdlg.m_nBits = 1;
            }
        else 
            if (nBits == 8) {
                bdlg.m_nBits = 2;
            }
        else {
            bdlg.m_nBits = 3;
        }
        if (bdlg.DoModal() == IDOK) {
            int nBitArray[4] = { 1, 4, 8, 24 };
            nBits = nBitArray[bdlg.m_nBits];
            delete m_pDisplayMemDC->SelectObject(pSourceBitmap);
            CEx23aDoc* pDoc = GetDocument();
            delete pDoc->m_pDib;
            pDoc->m_pDib = new CDib(m_pDisplayMemDC, nBits,
                                    bdlg.m_bCompression); 
            pDoc->m_pDib->MakeBitmap(m_pDisplayMemDC, m_bmSize);
            pDoc->SetModifiedFlag();

            Invalidate();
        }
    }
    VERIFY(::CloseClipboard());
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnEditPasteFrom()
{
    // paste from a .BMP file
    // we convert DIB to GDI bitmap, then select into m_pDisplayMemDC
    // no need for BitBlt here--only in OnDraw
    CFileDialog dlg(TRUE, "bmp", "*.bmp");
    if (dlg.DoModal() != IDOK) {
        return;
    }
    CFile file;
    if (!file.Open(dlg.GetPathName(), CFile::modeRead)) {
        AfxMessageBox("Edit Paste From: Can't open file");
        return;
    }
    CEx23aDoc* pDoc = GetDocument();
    delete pDoc->m_pDib;
    pDoc->m_pDib = new CDib; // replace the document's DIB
    if (!pDoc->m_pDib->Read(&file)) {
        AfxMessageBox("Edit Paste From: Can't read file");
        return;
    }
    delete pDoc->m_pDib->MakeBitmap(m_pDisplayMemDC, m_bmSize);
    pDoc->SetModifiedFlag();
    Invalidate();
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
    // show menu choice & toolbar button only if bitmap exists on clipboard
    VERIFY(OpenClipboard());
    pCmdUI->Enable(IsClipboardFormatAvailable(CF_BITMAP));
    VERIFY(::CloseClipboard());
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
    // serves Copy, Cut, and Copy To
    pCmdUI->Enable(GetDocument()->m_pDib->GetLength() > 0L);
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnViewShrink()
{
    // toggles 'shrink-to-fit' mode
    m_bShrinkToFit ^= 1;
    if (m_bShrinkToFit) {
        SetScaleToFitSize(m_totalSize);
    }
    else {
        SetScrollSizes(MM_TEXT, m_totalSize);
    }
}

///////////////////////////////////////////////////////////////////////////
void CEx23aView::OnUpdateViewShrink(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_bShrinkToFit);
}
