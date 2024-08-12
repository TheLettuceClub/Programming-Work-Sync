// ex23adoc.cpp : implementation of the CEx23aDoc class
//

#include "stdafx.h"
#include "ex23a.h"

#include "cdib.h"
#include "ex23adoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx23aDoc

IMPLEMENT_DYNCREATE(CEx23aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx23aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx23aDoc)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx23aDoc construction/destruction

CEx23aDoc::CEx23aDoc()
{
    m_pDib = new CDib;
}

CEx23aDoc::~CEx23aDoc()
{
    delete m_pDib;
}

void CEx23aDoc::DeleteContents()
{
    delete m_pDib;
    m_pDib = new CDib;
}

/////////////////////////////////////////////////////////////////////////////
// CEx23aDoc serialization

void CEx23aDoc::Serialize(CArchive& ar)
{
    m_pDib->Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CEx23aDoc commands

void CEx23aDoc::OnEditClearAll()
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
}

void CEx23aDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    // disables disk toolbar button when document is unmodified
    pCmdUI->Enable(IsModified());   
}
