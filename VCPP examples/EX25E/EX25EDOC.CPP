// ex25edoc.cpp : implementation of the CEx25eDoc class
//

#include "stdafx.h"
#include "ex25e.h"

#include "ex25edoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25eDoc

IMPLEMENT_DYNCREATE(CEx25eDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx25eDoc, CDocument)
	//{{AFX_MSG_MAP(CEx25eDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx25eDoc construction/destruction

CEx25eDoc::CEx25eDoc()
{
	// TODO: add one-time construction code here
}

CEx25eDoc::~CEx25eDoc()
{
}

BOOL CEx25eDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx25eDoc serialization

void CEx25eDoc::Serialize(CArchive& ar)
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
// CEx25eDoc diagnostics

#ifdef _DEBUG
void CEx25eDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx25eDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25eDoc commands
