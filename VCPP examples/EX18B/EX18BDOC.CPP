// ex18bdoc.cpp : implementation of the CEx18bDoc class
//

#include "stdafx.h"
#include "ex18b.h"

#include "ex18bdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc

IMPLEMENT_DYNCREATE(CEx18bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx18bDoc, CDocument)
    //{{AFX_MSG_MAP(CEx18bDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc construction/destruction

CEx18bDoc::CEx18bDoc()
{
    int n1, n2, n3;
    // make 50 random circles
    srand((unsigned) time(NULL));
    m_nEllipseQty = 50;
    for (int i = 0; i < m_nEllipseQty; i++) {
      n1 = (int) ((long) rand() * 600L / RAND_MAX);
      n2 = (int) ((long) rand() * 600L / RAND_MAX);
      n3 = (int) ((long) rand() * 50L  / RAND_MAX);
      m_ellipseArray[i] = CRect(n1, -n2, n1 + n3, -(n2 + n3));
    }
}

const int NEAR CEx18bDoc::nLinesPerPage = 12;


CEx18bDoc::~CEx18bDoc()
{
}

BOOL CEx18bDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc serialization

void CEx18bDoc::Serialize(CArchive& ar)
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
// CEx18bDoc diagnostics

#ifdef _DEBUG
void CEx18bDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx18bDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx18bDoc commands
