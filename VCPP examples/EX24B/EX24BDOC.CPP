// ex24bdoc.cpp : implementation of the CEx24bDoc class
//

#include "stdafx.h"
#include "ex24b.h"

#include "ex24bset.h"
#include "ex24bdoc.h"
#include "tablesel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24bDoc

IMPLEMENT_DYNCREATE(CEx24bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24bDoc, CDocument)
    //{{AFX_MSG_MAP(CEx24bDoc)
    ON_COMMAND(IDC_REQUERY, OnRequery)
    ON_UPDATE_COMMAND_UI(IDC_REQUERY, OnUpdateRequery)
    ON_COMMAND(ID_FILE_CONNECT, OnFileConnect)
    ON_UPDATE_COMMAND_UI(ID_FILE_CONNECT, OnUpdateFileConnect)
    ON_COMMAND(ID_FILE_DISCONNECT, OnFileDisconnect)
    ON_UPDATE_COMMAND_UI(ID_FILE_DISCONNECT, OnUpdateFileDisconnect)
    ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24bDoc construction/destruction

CEx24bDoc::CEx24bDoc()
{
    m_bConnected = FALSE;
    m_pEx24bSet = NULL;
}

CEx24bDoc::~CEx24bDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::DeleteContents()
{
}       

/////////////////////////////////////////////////////////////////////////////
BOOL CEx24bDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
      return FALSE;
    m_strConnect = "ODBC;";   // default database
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CEx24bDoc::OnOpenDocument(const char* pszPathName)
{
    if (!CDocument::OnOpenDocument(pszPathName))
      return FALSE;
    SetModifiedFlag(); //  this ensures a later call to SaveModified
    return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
BOOL CEx24bDoc::SaveModified()
{
    if (m_bConnected) {
      AfxMessageBox("Can't close document while connected"
                    " -- use File ODBC Disconnect");
      return FALSE;
    }
    return TRUE;
}
    
/////////////////////////////////////////////////////////////////////////////
// CEx24bDoc serialization

void CEx24bDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
      ar << m_strConnect << m_strTableName << m_strFilter << m_strSort;
    }
    else {
      ar >> m_strConnect >> m_strTableName >> m_strFilter >> m_strSort;
    }
}


/////////////////////////////////////////////////////////////////////////////
// CEx24bDoc diagnostics

#ifdef _DEBUG
void CEx24bDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx24bDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::GetFilterSort()
{    // get filter and sort strings from dialog bar
    char text[201];   
    CDialogBar* pBar = (CDialogBar*)
      AfxGetApp()->m_pMainWnd->GetDlgItem(ID_QUERY_BAR);
    pBar->GetDlgItemText(IDC_FILTER, text, 200);
    m_strFilter = text;
    pBar->GetDlgItemText(IDC_SORT, text, 200);
    m_strSort = text;
}

void CEx24bDoc::PutFilterSort()
{    // write filter and sort strings to dialog bar
    CDialogBar* pBar = (CDialogBar*)
      AfxGetApp()->m_pMainWnd->GetDlgItem(ID_QUERY_BAR);
    pBar->SetDlgItemText(IDC_FILTER, m_strFilter);
    pBar->SetDlgItemText(IDC_SORT, m_strSort);
}

/////////////////////////////////////////////////////////////////////////////
// CEx24bDoc commands

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnRequery()
{ 
    char errorMsg[201];

    BeginWaitCursor();
    GetFilterSort();
    m_pEx24bSet->m_strFilter = m_strFilter;
    m_pEx24bSet->m_strSort = m_strSort;
    m_pEx24bSet->Close();  // do this instead for
                           //  now -- less efficient
    TRY {
      m_pEx24bSet->Open(CRecordset::snapshot,
                        m_strTableName, CRecordset::readOnly);
    }
    CATCH(CDBException, e) {
      sprintf(errorMsg, "ODBC %s", (const char*) e->m_strError);
      AfxMessageBox(errorMsg);
    }
    END_CATCH
    
    UpdateAllViews(NULL); 
    EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnUpdateRequery(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bConnected);
}

void CEx24bDoc::OnFileConnect()
{
    char errorMsg[201];

    BeginWaitCursor();
    if (m_database.Open(NULL, FALSE, TRUE, m_strConnect) == 0) {
      EndWaitCursor();
      return;
    }
    m_strConnect = m_database.GetConnect();
    
    CTableSelect tableDlg(&m_database);
    tableDlg.m_strSelection = m_strTableName;

    if (tableDlg.DoModal() != IDOK) {
      m_database.Close();  // escape route
      EndWaitCursor();
      return;
    }
    m_strTableName = tableDlg.m_strSelection;

    m_pEx24bSet = new CEx24bSet(&m_database);
    m_pEx24bSet->Initialize(m_strTableName);  // get column info 
    m_pEx24bSet->m_strFilter = m_strFilter;
    m_pEx24bSet->m_strSort = m_strSort;
    PutFilterSort();

    TRY {   
      m_pEx24bSet->Open(CRecordset::snapshot, m_strTableName,
                        CRecordset::readOnly);
    }
    CATCH(CDBException, e) {
      sprintf(errorMsg, "ODBC %s", (const char*) e->m_strError);
      AfxMessageBox(errorMsg);
      UpdateAllViews(NULL);
      m_bConnected = FALSE;
      EndWaitCursor();
      return;
    }
    END_CATCH
    UpdateAllViews(NULL);
    m_bConnected = TRUE;
    EndWaitCursor();
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnUpdateFileConnect(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnFileDisconnect()
{
    GetFilterSort();
    delete m_pEx24bSet; // destructor calls Close
    m_database.Close();
    m_pEx24bSet = NULL;
    m_bConnected = FALSE;
    UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnUpdateFileDisconnect(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_bConnected);
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bDoc::OnUpdateAppExit(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_bConnected);
}

