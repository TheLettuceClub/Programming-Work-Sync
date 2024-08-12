// ex15avw.cpp : implementation of the CEx15aView class
//

#include "stdafx.h"
#include "ex15a.h"
#include "student.h"
#include "ex15adoc.h"
#include "ex15avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx15aView

IMPLEMENT_DYNCREATE(CEx15aView, CFormView)

BEGIN_MESSAGE_MAP(CEx15aView, CFormView)
    //{{AFX_MSG_MAP(CEx15aView)
    ON_BN_CLICKED(IDC_ENTER, OnEnter)
    ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx15aView construction/destruction

CEx15aView::CEx15aView()
    : CFormView(CEx15aView::IDD)
{
    //{{AFX_DATA_INIT(CEx15aView)
    m_lGrade = 0;
    m_name = "";
    //}}AFX_DATA_INIT
    // TODO: add construction code here
}

CEx15aView::~CEx15aView()
{
}

void CEx15aView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx15aView)
    DDX_Text(pDX, IDC_GRADE, m_lGrade);
    DDV_MinMaxLong(pDX, m_lGrade, 0, 100);
    DDX_Text(pDX, IDC_NAME, m_name);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx15aView diagnostics

#ifdef _DEBUG
void CEx15aView::AssertValid() const
{
    CFormView::AssertValid();
}

void CEx15aView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

CEx15aDoc* CEx15aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx15aDoc)));
    return (CEx15aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx15aView message handlers

void CEx15aView::OnEnter()
{
    CEx15aDoc* pDoc = GetDocument();
    UpdateData(TRUE);
    pDoc->m_student.m_lGrade = m_lGrade;
    pDoc->m_student.m_name = m_name;
}

void CEx15aView::OnEditClearall()
{
    GetDocument()->m_student = CStudent(); // "blank" student
                                           //  object
    UpdateEntry();
}

void CEx15aView::OnUpdateEditClearall(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(((CEx15aDoc*) GetDocument())->m_student !=
      CStudent()); // blank?
}

void CEx15aView::OnInitialUpdate()
{   // called on startup
    UpdateEntry();
}

void CEx15aView::UpdateEntry()
{   // called from OnInitialUpdate and OnEditClearall
    CEx15aDoc* pDoc = GetDocument();
    m_lGrade = pDoc->m_student.m_lGrade;
    m_name = pDoc->m_student.m_name;
    UpdateData(FALSE); // calls DDX
    ((CDialog*) this)->
      GotoDlgCtrl(GetDlgItem(IDC_NAME)); // note parenthesis usage
}
