// ex12adoc.cpp : implementation of the CEx12aDoc class
//

#include "stdafx.h"
#include "ex12a.h"

#include "ex12adoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc

IMPLEMENT_DYNCREATE(CEx12aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx12aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx12aDoc)
    ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc construction/destruction

CEx12aDoc::CEx12aDoc() : m_text("Hello")
{
}

CEx12aDoc::~CEx12aDoc()
{
}

BOOL CEx12aDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc serialization

void CEx12aDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // TODO: add storing code here
    }
    else
    {
        // TODO: add loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc diagnostics

#ifdef _DEBUG
void CEx12aDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx12aDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12aDoc commands

void CEx12aDoc::OnEditClearall()
{
    AfxMessageBox("Document cleared");
    m_text = "";
}

void CEx12aDoc::OnUpdateEditClearall(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_text.IsEmpty());
}
