// ex15adoc.cpp : implementation of the CEx15aDoc class
//

#include "stdafx.h"
#include "ex15a.h"
#include "student.h"
#include "ex15adoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx15aDoc

IMPLEMENT_DYNCREATE(CEx15aDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx15aDoc, CDocument)
    //{{AFX_MSG_MAP(CEx15aDoc)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        //    DO NOT EDIT what you see in these blocks of generated code!
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx15aDoc construction/destruction

CEx15aDoc::CEx15aDoc()
{
    TRACE("Document object constructed\n");
    m_student.m_name = "default value";
    m_student.m_lGrade = 0L;
}

CEx15aDoc::~CEx15aDoc()
{
#ifdef _DEBUG
    Dump(afxDump);
#endif
}

BOOL CEx15aDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // TODO: add reinitialization code here
    // (SDI documents will reuse this document)

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CEx15aDoc serialization

void CEx15aDoc::Serialize(CArchive& ar)
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
// CEx15aDoc diagnostics

#ifdef _DEBUG
void CEx15aDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CEx15aDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
    dc << "\n" << m_student << "\n";
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx15aDoc commands
