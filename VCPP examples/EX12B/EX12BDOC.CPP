// ex12bdoc.cpp : implementation of the CEx12bDoc class
//

#include "stdafx.h"
#include "ex12b.h"

#include "ex12bdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx12bDoc

IMPLEMENT_DYNCREATE(CEx12bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx12bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx12bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx12bDoc construction/destruction

CEx12bDoc::CEx12bDoc()
{
	// TODO: add one-time construction code here
}

CEx12bDoc::~CEx12bDoc()
{
}

BOOL CEx12bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx12bDoc serialization

void CEx12bDoc::Serialize(CArchive& ar)
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
// CEx12bDoc diagnostics

#ifdef _DEBUG
void CEx12bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx12bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx12bDoc commands
