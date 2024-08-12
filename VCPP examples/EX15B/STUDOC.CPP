// studoc.cpp : implementation of the CStudentDoc class

#include "stdafx.h"
#include "resource.h"

#include "student.h"
#include "studoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc

//IMPLEMENT_SERIAL(CStudentDoc, CDocument, 0)
IMPLEMENT_DYNCREATE(CStudentDoc, CDocument)

BEGIN_MESSAGE_MAP(CStudentDoc, CDocument)
    //{{AFX_MSG_MAP(CStudentDoc)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc construction/destruction

CStudentDoc::CStudentDoc()
{
#ifdef _DEBUG
    afxDump.SetDepth(1); // ensure dump of list elements
#endif
}

CStudentDoc::~CStudentDoc()
{
}

/////////////////////////////////////////////////////////////////////////////
BOOL CStudentDoc::OnNewDocument()
{
    TRACE("Entering CStudentDoc::OnNewDocument\n");
    if (!CDocument::OnNewDocument())
      return FALSE;
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc serialization

void CStudentDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring()) {
      // any other document variables to archive
    }
    else {
      // any other document variables from archive
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDoc::DeleteContents()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif
    while (m_studentList.GetHeadPosition()) {
      delete m_studentList.RemoveHead();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc diagnostics

#ifdef _DEBUG
void CStudentDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CStudentDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
    dc << "\n" << m_studentList << "\n";
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStudentDoc commands


void CStudentDoc::OnEditClearAll()
{
    DeleteContents();
    UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(!m_studentList.IsEmpty());
}
