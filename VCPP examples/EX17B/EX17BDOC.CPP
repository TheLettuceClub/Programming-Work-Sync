// ex17bdoc.cpp : implementation of the CEx17bDoc class
//

#include "stdafx.h"
#include "ex17b.h"

#include "ex17bdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx17bDoc

IMPLEMENT_DYNCREATE(CEx17bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx17bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx17bDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx17bDoc construction/destruction

CEx17bDoc::CEx17bDoc()
{
	// TODO: add one-time construction code here
}

CEx17bDoc::~CEx17bDoc()
{
}

BOOL CEx17bDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx17bDoc serialization

void CEx17bDoc::Serialize(CArchive& ar)
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
// CEx17bDoc diagnostics

#ifdef _DEBUG
void CEx17bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx17bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx17bDoc commands
