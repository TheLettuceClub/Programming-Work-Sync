// Ex25bitm.cpp

#include "stdafx.h"
#include "ex25b.h"

// Disable excessive compiler warning
#pragma warning(disable: 4355)  // this used in base initializer list
/////////////////////////////////////////////////////////////////////////////
CEx25bDoc::CEx25bDoc() : m_item(this)
{
}

/////////////////////////////////////////////////////////////////////////////
COleServerItem* CEx25bDoc::OnGetEmbeddedItem()
{
    TRACE("Entering CEx25bDoc::OnGetEmbeddedItem\n");
    ASSERT(m_docItemList.GetCount() == 1);
    return &m_item;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CEx25bItem::CEx25bItem(CEx25bDoc* pContainerDoc)
    : COleServerItem(pContainerDoc)
{
    m_bModified = FALSE;
    // bounds necessary for clients such as WRITE  
    CClientDC dcTmp(NULL);
    dcTmp.SetMapMode(MM_HIMETRIC);
    m_rectBounds.SetRect(0, 0, ::GetSystemMetrics(SM_CXICON),
                         ::GetSystemMetrics(SM_CYICON));
    dcTmp.DPtoLP(&m_rectBounds);        // rectBounds in HIMETRIC
}

/////////////////////////////////////////////////////////////////////////////
OLESTATUS CEx25bItem::OnDoVerb(UINT nVerb, BOOL bShow, BOOL bTakeFocus)
{
    if (nVerb == 0) {
        return OnRead();
    }
    return OnShow(bShow);
}

/////////////////////////////////////////////////////////////////////////////
OLESTATUS CEx25bItem::OnShow(BOOL /* bTakeFocus */)
{
    // window shown here instead of in InitInstance
    CMainWnd* pMainWnd = (CMainWnd*) AfxGetApp()->m_pMainWnd;
    pMainWnd->ShowWindow(SW_SHOW);
    pMainWnd->UpdateWindow();
    pMainWnd->m_wndEdit.SetWindowText(m_noteText);
    pMainWnd->m_wndEdit.SetFocus();
    return OLE_OK;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CEx25bItem::OnGetTextData(CString& rStringReturn)
{
    // REVIEW: When is this called?
    TRACE("Entering CEx25bItem::OnGetTextData\n");
    rStringReturn = m_noteText;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Drawing items into bitmap or metafile
BOOL CEx25bItem::OnDraw(CDC* pDC)
{
    ASSERT_VALID(pDC);
    pDC->SetWindowExt(::GetSystemMetrics(SM_CXICON),
                      ::GetSystemMetrics(SM_CYICON));
    pDC->DrawIcon(0, 0, AfxGetApp()->LoadIcon(IDR_MAINFRAME));
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
OLESTATUS CEx25bItem::OnRead()
{
    TRACE("Entering CEx25bItem::OnRead\n");
    CReadDialog dlg(this);
    dlg.DoModal();
    return OLE_OK;
}

/////////////////////////////////////////////////////////////////////////////
void CEx25bItem::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
        ar << m_noteText;
    }
    else {
        ar >> m_noteText;
    }                    
}
