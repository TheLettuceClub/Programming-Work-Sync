// ex24adoc.cpp : implementation of the CEx24aDoc class
//

#include "stdafx.h"
#include "ex24a.h"

#include "ex24aset.h"
#include "ex24adoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24aDoc

IMPLEMENT_DYNCREATE(CEx24aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx24aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx24aDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24aDoc construction/destruction

CEx24aDoc::CEx24aDoc()
{
    // TODO: add one-time construction code here
}

CEx24aDoc::~CEx24aDoc()
{
}

BOOL CEx24aDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx24aDoc serialization

void CEx24aDoc::Serialize(CArchive& ar)
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
// CEx24aDoc diagnostics

#ifdef _DEBUG
void CEx24aDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx24aDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24aDoc commands
