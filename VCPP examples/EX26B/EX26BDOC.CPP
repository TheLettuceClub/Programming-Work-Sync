// ex26bdoc.cpp : implementation of the CEx26bDoc class
//

#include "stdafx.h"
#include "ex26b.h"
#include "student.h"

#include "ex26bdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc

IMPLEMENT_DYNCREATE(CEx26bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx26bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx26bDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc construction/destruction

CEx26bDoc::CEx26bDoc()
{
	m_studentArray.SetSize(0, 100); // allocates memory in 100-element chunks
}

CEx26bDoc::~CEx26bDoc()
{
}

BOOL CEx26bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
/*	// logic to 'fill up' the document to test boundary conditions
	CStudent* pStudent;
	for(int i = 0; i < 2500; i++) {
		pStudent = new CStudent;
		pStudent->m_name = "Elvis";
		pStudent->m_nGrade = i / 25;
		m_studentArray.SetAtGrow(i, pStudent);
	}
*/
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bDoc::DeleteContents()
{
	int j = m_studentArray.GetUpperBound();
	for(int i = 0; i <= j; i++) {
		delete m_studentArray[i];  // delete the objects
	}
	m_studentArray.RemoveAll(); // remove the pointers
}

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc serialization

void CEx26bDoc::Serialize(CArchive& ar)
{
	m_studentArray.Serialize(ar);
}


/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc diagnostics

#ifdef _DEBUG
void CEx26bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx26bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx26bDoc commands

void CEx26bDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsModified());
}
