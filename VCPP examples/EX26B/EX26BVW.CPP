// ex26bvw.cpp : implementation of the CEx26bView class
//

#include "stdafx.h"
#include "student.h"
#include "ex26bdoc.h"
#include "rowview.h"
#include "ex26bvw.h"
#include "resource.h"
#include "studlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
BEGIN_MESSAGE_MAP(CEx26bView, CRowView)
    //{{AFX_MSG_MAP(CEx26bView)
        ON_WM_LBUTTONDBLCLK()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CEx26bView, CRowView)

/////////////////////////////////////////////////////////////////////////////
CEx26bView::CEx26bView()
{
    m_nSelectedStudent = 0;

    CString strRes;
    strRes.LoadString(IDS_TOO_MANY_ROWS);
    TRACE("resource string = %s\n", (const char*) strRes);
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, 
                                   int& nRowHeight, int& nCharWidth)
{
    TEXTMETRIC tm;
    pDC->GetTextMetrics(&tm);
    nCharWidth = tm.tmAveCharWidth;
    nRowWidth = nCharWidth * ROW_WIDTH;
    nRowHeight = tm.tmHeight * 1; // 1 line of text
}

/////////////////////////////////////////////////////////////////////////////
int CEx26bView::GetActiveRow()
{
    CEx26bDoc* pDoc = GetDocument();
    return m_nSelectedStudent;
}

/////////////////////////////////////////////////////////////////////////////
int CEx26bView::GetRowCount()
{
    CEx26bDoc* pDoc = GetDocument();
    int nRows = pDoc->m_studentArray.GetSize();
    return nRows;
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::ChangeSelectionNextRow(BOOL bNext)
{
    if (bNext && (m_nSelectedStudent < min(GetRowCount() - 1,
        LastViewableRow() - 2))) {
        m_nSelectedStudent++;
    }
    if (!bNext && m_nSelectedStudent) {
        m_nSelectedStudent--;
    }
    UpdateRow(m_nSelectedStudent);
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::ChangeSelectionToRow(int nRow)
{
    if ((nRow >= 0) && (nRow < min(GetRowCount(), LastViewableRow() - 1))) {
        m_nSelectedStudent = nRow;
    }
    UpdateRow(m_nSelectedStudent);
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{                       
    // OnUpdate() is called whenever the document has changed and,
    // therefore, the view needs to redisplay some or all of itself.
    UpdateScrollSizes();
    Invalidate(lHint == 0L);
}

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::OnDrawRow(CDC* pDC, int nRow, int y, BOOL bSelected)
{
    // Gets the data for the specific student.
    CStudent* pStudent = (CStudent*)
                         (GetDocument()->m_studentArray[nRow]);

    TEXTMETRIC tm;
    pDC->GetTextMetrics(&tm);
    char grade[10];

    // Displays the student record in one line of text
    pDC->TextOut(STUDENT_NAME_COL*tm.tmAveCharWidth, y, pStudent->m_name);
    _itoa((int) (pStudent->m_lGrade), grade, 10);
    pDC->TextOut(STUDENT_GRADE_COL*tm.tmAveCharWidth, y, grade, strlen(grade));
}

/////////////////////////////////////////////////////////////////////////////
// CEx26bView diagnostics

#ifdef _DEBUG
void CEx26bView::AssertValid() const
{
    CView::AssertValid();
}

void CEx26bView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
void CEx26bView::OnLButtonDblClk(UINT, CPoint point)
{
    LONG lHint = 1L;

// Brings up a dialog for the selected student record
// First click selected the row, so we don't have to here.
    CStudent* pStudent1;
    CStudent* pStudent2;
    int ret;

    CEx26bDoc* pDoc = GetDocument();
    if (GetRowCount()) { // there's at least one student record
        CStudentDialog dlg(IDB_UPDATE);
        pStudent1 = (CStudent*)
                    (pDoc->m_studentArray[m_nSelectedStudent]);
        dlg.m_name = pStudent1->m_name;
        dlg.m_lGrade = pStudent1->m_lGrade;
        ret = dlg.DoModal();
        switch(ret) {
        case IDB_UPDATE:
            pStudent1->m_name = dlg.m_name;
            pStudent1->m_lGrade = dlg.m_lGrade;
            break;
        case IDB_INSERT:
            pStudent2 = new CStudent(dlg.m_name, dlg.m_lGrade);
            pDoc->m_studentArray.InsertAt(m_nSelectedStudent, pStudent2);
            break;
        case IDB_DELETE:
            pDoc->m_studentArray.RemoveAt(m_nSelectedStudent);
            lHint = 0L;
            break;
        case IDB_CANCEL:
            break;
        default:
            ASSERT(0);
            break;
        }
    }
    else {
        CStudentDialog dlg(IDB_INSERT);
        pStudent2 = new CStudent("", 0); // array was empty
        dlg.m_name = pStudent2->m_name;
        dlg.m_lGrade = pStudent2->m_lGrade;
        ret = dlg.DoModal();
        if (ret == IDB_INSERT) {
            pStudent2->m_name = dlg.m_name;
            pStudent2->m_lGrade = dlg.m_lGrade;
            pDoc->m_studentArray.InsertAt(0, pStudent2);
        }
    }
    pDoc->SetModifiedFlag();
    pDoc->UpdateAllViews(NULL, lHint);
}
