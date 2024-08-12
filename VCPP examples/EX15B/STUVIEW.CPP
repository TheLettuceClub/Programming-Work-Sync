// stuview.cpp : implementation of the CStudentView class

#include "stdafx.h"
#include "resource.h"

#include "student.h"
#include "studoc.h"
#include "stuview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentView

IMPLEMENT_DYNCREATE(CStudentView, CFormView)

BEGIN_MESSAGE_MAP(CStudentView, CFormView)
    //{{AFX_MSG_MAP(CStudentView)
    ON_COMMAND(ID_POS_HOME, OnCommandHome)
    ON_UPDATE_COMMAND_UI(ID_POS_HOME, OnUpdateCommandHome)
    ON_COMMAND(ID_POS_END, OnCommandEnd)
    ON_UPDATE_COMMAND_UI(ID_POS_END, OnUpdateCommandEnd)
    ON_COMMAND(ID_POS_PREV, OnCommandPrev)
    ON_UPDATE_COMMAND_UI(ID_POS_PREV, OnUpdateCommandPrev)
    ON_COMMAND(ID_POS_NEXT, OnCommandNext)
    ON_UPDATE_COMMAND_UI(ID_POS_NEXT, OnUpdateCommandNext)
    ON_COMMAND(ID_POS_DEL, OnCommandDel)
    ON_UPDATE_COMMAND_UI(ID_POS_DEL, OnUpdateCommandDel)
    ON_COMMAND(ID_POS_INS, OnCommandIns)
    ON_BN_CLICKED(IDC_CLEAR, OnClear)
    //}}AFX_MSG_MAP
    // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentView construction/destruction

CStudentView::CStudentView()
    : CFormView(CStudentView::IDD)
{
    TRACE("Entering CStudentView constructor\n");
    //{{AFX_DATA_INIT(CStudentView)
    m_lGrade = 0;
    //}}AFX_DATA_INIT
    m_position = NULL;
}

CStudentView::~CStudentView()
{
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnInitialUpdate()
{
    // called on startup, on File New, and on File Open
    TRACE("Entering CStudentView::OnInitialUpdate\n");
    OnUpdate(this, NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
    // called by OnInitialUpdate and by UpdateAllViews
    TRACE("Entering CStudentView::OnUpdate\n");
    m_pList = GetDocument()->GetList();
    m_position = m_pList->GetHeadPosition();
    GetEntry(m_position); // initial data for view
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnDraw(CDC* pDC)
{
    CStudentDoc* pDoc = GetDocument();

    // TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CStudentView diagnostics

#ifdef _DEBUG
void CStudentView::AssertValid() const
{
    CFormView::AssertValid();
}

void CStudentView::Dump(CDumpContext& dc) const
{
    CFormView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStudentView commands

void CStudentView::DoDataExchange(CDataExchange* pDX)
{
    TRACE("Entering CStudentView::DoDataExchange\n");
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CStudentView)
    DDX_Text(pDX, IDC_NAME, m_name);
    DDV_MaxChars(pDX, m_name, 20);
    DDX_Text(pDX, IDC_GRADE, m_lGrade);
    DDV_MinMaxLong(pDX, m_lGrade, 0, 100);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandHome()
{
    // need to deal with the list empty condition
    TRACE("Entering CStudentView::OnCommandHome\n");
    if (!m_pList->IsEmpty()) {
      m_position = m_pList->GetHeadPosition();
      GetEntry(m_position);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandNext()
{
    POSITION pos;

    TRACE("Entering CStudentView::OnCommandNext\n");
    if ((pos = m_position) != NULL) {
      m_pList->GetNext(pos);
      if (pos) {
        GetEntry(pos);
        m_position = pos;
      }
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandEnd()
{
    TRACE("Entering CStudentView::OnCommandEnd\n");
    if (!m_pList->IsEmpty()) {
      m_position = m_pList->GetTailPosition();
      GetEntry(m_position);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandPrev()
{
    POSITION pos;

    TRACE("Entering CStudentView::OnCommandPrev\n");
    if ((pos = m_position) != NULL) {
      m_pList->GetPrev(pos);
      if (pos) {
        GetEntry(pos);
        m_position = pos;
      }
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandDel()
{
    // deletes current entry and positions to next one or head
    POSITION pos;

    TRACE("Entering CStudentView::OnCommandDel\n");
    if ((pos = m_position) != NULL) {
      m_pList->GetNext(pos);
      if (pos == NULL) {
        pos = m_pList->GetHeadPosition();
        TRACE("GetHeadPos = %ld\n", pos);
        if (pos == m_position) {
          pos = NULL;
        }
      }
      GetEntry(pos);
      CObject* ps = m_pList->GetAt(m_position);
      m_pList->RemoveAt(m_position);
      delete ps;
      m_position = pos;
      GetDocument()->SetModifiedFlag();
      GetDocument()->UpdateAllViews(this);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnCommandIns()
{
    TRACE("Entering CStudentView::OnCommandIns\n");
    InsertEntry(m_position);
    GetDocument()->SetModifiedFlag();
    GetDocument()->UpdateAllViews(this);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdateCommandHome(CCmdUI* pCmdUI)
{
    // called during IDLE processing
    POSITION pos;

    // enables button if list not empty and not at home already
    pos = m_pList->GetHeadPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdateCommandEnd(CCmdUI* pCmdUI)
{
    // called during IDLE processing
    POSITION pos;

    // enables button if list not empty and not at end already
    pos = m_pList->GetTailPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdateCommandPrev(CCmdUI* pCmdUI)
{
    // called during IDLE processing
    POSITION pos;

    // enables button if list not empty and previous item(s) exist
    if ((pos = m_position) != NULL) {
      m_pList->GetPrev(pos);
    }
    pCmdUI->Enable((m_position != NULL) && (pos != NULL));
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdateCommandNext(CCmdUI* pCmdUI)
{
    // called during IDLE processing
    POSITION pos;

    // enables button if list not empty and following item(s) exist
    if ((pos = m_position) != NULL) {
      m_pList->GetNext(pos);
    }
    pCmdUI->Enable((m_position != NULL) && (pos != NULL));
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnUpdateCommandDel(CCmdUI* pCmdUI)
{
    // called during IDLE processing
    pCmdUI->Enable(m_position != NULL);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::OnClear()
{
    TRACE("Entering CStudentView::OnClickedClear\n");
    ClearEntry();
}

/////////////////////////////////////////////////////////////////////////////
// protected virtual functions

void CStudentView::GetEntry(POSITION position)
{
    if (position) {
      CStudent* pStudent = (CStudent*) m_pList->GetAt(position);
      m_name = pStudent->m_name;
      m_lGrade = pStudent->m_lGrade;
    }
    else {
      ClearEntry();
    }
    UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::InsertEntry(POSITION position)
{
    if (UpdateData(TRUE)) {
      // UpdateData returns FALSE if it detects a user error
      CStudent* pStudent = new CStudent;
      pStudent->m_name = m_name;
      pStudent->m_lGrade = m_lGrade;
      m_position = m_pList->InsertAfter(m_position, pStudent);
    }
}

/////////////////////////////////////////////////////////////////////////////
void CStudentView::ClearEntry()
{
    m_name = "";
    m_lGrade = 0;
    UpdateData(FALSE);
    ((CDialog*) this)->GotoDlgCtrl(GetDlgItem(IDC_NAME));
}

