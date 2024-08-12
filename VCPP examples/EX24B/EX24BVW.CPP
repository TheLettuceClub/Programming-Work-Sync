// ex24bvw.cpp : implementation of the CEx24bView class
//

#include "stdafx.h"
#include "ex24b.h"

#include "ex24bset.h"
#include "ex24bdoc.h"
#include "rowview.h"
#include "ex24bvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24bView

IMPLEMENT_DYNCREATE(CEx24bView, CRowView)

BEGIN_MESSAGE_MAP(CEx24bView, CRowView)
    //{{AFX_MSG_MAP(CEx24bView)
    ON_WM_SETFOCUS()
    ON_WM_MOUSEACTIVATE()
    //}}AFX_MSG_MAP
    // Standard printing commands
    ON_COMMAND(ID_FILE_PRINT, CRowView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRowView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24bView construction/destruction

CEx24bView::CEx24bView()
{
    m_pSet = NULL;
}

CEx24bView::~CEx24bView()
{
}

/////////////////////////////////////////////////////////////////////////////
void CEx24bView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{
    // called when the user executes a new query
    // can't set m_pSet in OnInitialUpdate because
    //  it's NULL then
    m_pSet = GetDocument()->m_pEx24bSet;
    ScrollToPosition(CPoint(0, 0));
    UpdateScrollSizes();
    Invalidate(TRUE);
    m_nSelectedRow = -1;
}

///////////////////////////////////////////////////////////////
// CRowView overrides

///////////////////////////////////////////////////////////////
void CEx24bView::OnDrawRow(CDC* pDC, int nRow,
                           int y, BOOL bSelected)
{
    int x = 0;
    int i;
    int nFields = (int) m_pSet->m_nFields; 
    CRecordsetStatus rStatus;
    char errorMsg[201];
    
    if (nRow == 0) {    // title row
      for (i = 0; i < nFields; i++) {
        pDC->TextOut(x, y, m_pSet->m_arrayName[i]);
        x += m_pSet->m_nColWidth[i] * m_nCharWidth;
      }   
    }
    else {
      m_pSet->GetStatus(rStatus);
      TRY {
        m_pSet->Move(nRow - (int) rStatus.m_lCurrentRecord - 1);
        if (m_pSet->IsEOF()) {
          m_pSet->MoveLast();
        }
        else { 
          DrawDataRow(pDC, y);
        }
      }
      CATCH(CDBException, e) {
        sprintf(errorMsg, "ODBC %s SHUT DOWN THE APP NOW!!!",
               (const char*) e->m_strError);
        AfxMessageBox(errorMsg);
        // figure out some way to escape from here
      }
      END_CATCH
    }
}

void CEx24bView::DrawDataRow(CDC* pDC, int y)
{
    int     x = 0;
    char    temp[101];
    CString strTime;
    int     nFields = (int) m_pSet->m_nFields;

    for (int i = 0; i < nFields; i++) {
      switch (m_pSet->m_nDatType[i]) {
      case SQL_BIT:
          *((BOOL*) m_pSet->m_arrayValue[i]) ?            
             pDC->TextOut(x, y, "T") : pDC->TextOut(x, y, "F");
          break;
      case SQL_TINYINT:
          sprintf(temp, "%d",
                 (int) *((BYTE*) m_pSet->m_arrayValue[i]));
          pDC->TextOut(x, y, temp);
          break;
      case SQL_SMALLINT:
          sprintf(temp, "%d",
                *((int*) m_pSet->m_arrayValue[i]));
          pDC->TextOut(x, y, temp);
          break;
      case SQL_INTEGER:
          sprintf(temp, "%ld",
                *((long*) m_pSet->m_arrayValue[i]));
          pDC->TextOut(x, y, temp);
          break;
      case SQL_REAL:
          sprintf(temp, "%10.2f",
                 (double) *((float*) m_pSet->m_arrayValue[i]));
          pDC->TextOut(x, y, temp);
          break;
      case SQL_FLOAT:
      case SQL_DOUBLE:
          sprintf(temp, "%10.2f",
                *((double*) m_pSet->m_arrayValue[i]));
          pDC->TextOut(x, y, temp);
          break;
      case SQL_DATE:
      case SQL_TIME:
      case SQL_TIMESTAMP:
          strTime = ((CTime*)
            m_pSet->m_arrayValue[i])->Format("%A, %B %d, %Y");
          pDC->TextOut(x, y, temp);
          break;
      case SQL_BINARY:
      case SQL_VARBINARY:
          pDC->TextOut(x, y, "binary");
          break;
      case SQL_DECIMAL:
      case SQL_NUMERIC:
      case SQL_CHAR:
      case SQL_VARCHAR:
          pDC->TextOut(x, y,
                     *((CString*) m_pSet->m_arrayValue[i]));
          break;
      case SQL_LONGVARCHAR:
      case SQL_LONGVARBINARY:
          pDC->TextOut(x, y, "long binary");
          break;
      default:
          ASSERT(FALSE);
      }
      x += m_pSet->m_nColWidth[i] * m_nCharWidth;
    }   
}

///////////////////////////////////////////////////////////////
void CEx24bView::GetRowWidthHeight(CDC* pDC, int& nRowWidth,
                                   int& nRowHeight,
                                   int& nCharWidth)
{
    TEXTMETRIC tm;

    pDC->GetTextMetrics(&tm);
    nCharWidth = tm.tmAveCharWidth;
    nRowWidth = 0;
    if (m_pSet != NULL) {
      for (int i = 0; i < (int) m_pSet->m_nFields; i++) {
        nRowWidth += m_pSet->m_nColWidth[i];
      }
    }
    nRowWidth *= nCharWidth;
    nRowHeight = tm.tmHeight;
}

///////////////////////////////////////////////////////////////
int CEx24bView::GetActiveRow()
{
    return m_nSelectedRow;
}

///////////////////////////////////////////////////////////////
int CEx24bView::GetRowCount()
{
    CRecordsetStatus rStatus;
    int nRows = 0;
    if (m_pSet != NULL && m_pSet->IsOpen()) {
      m_pSet->GetStatus(rStatus);
      if (rStatus.m_bRecordCountFinal) {       
        nRows = (int) m_pSet->GetRecordCount() + 1;
      }
      else {
        nRows = MAXROWS;
      }
    }
    return nRows;
}

///////////////////////////////////////////////////////////////
void CEx24bView::ChangeSelectionNextRow(BOOL bNext)
{
    if (bNext && (m_nSelectedRow < min(GetRowCount() - 1,
                  LastViewableRow() - 2))) {
      m_nSelectedRow++;
    }
    if (!bNext && m_nSelectedRow) {
      m_nSelectedRow--;
    }
    UpdateRow(m_nSelectedRow);
}

///////////////////////////////////////////////////////////////
void CEx24bView::ChangeSelectionToRow(int nRow)
{
    if ((nRow >= 0) && (nRow < min(GetRowCount(),
         LastViewableRow() - 1))) {
      m_nSelectedRow = nRow;
    }
    UpdateRow(m_nSelectedRow);
}

///////////////////////////////////////////////////////////////
// CEx24bView diagnostics

#ifdef _DEBUG
void CEx24bView::AssertValid() const
{
    CRowView::AssertValid();
}

void CEx24bView::Dump(CDumpContext& dc) const
{
    CRowView::Dump(dc);
}

///////////////////////////////////////////////////////////////
CEx24bDoc* CEx24bView::GetDocument() // non-debug version
                                     //  is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx24bDoc)));
    return (CEx24bDoc*) m_pDocument;
}

#endif //_DEBUG

///////////////////////////////////////////////////////////////
// CEx24bView message handlers

///////////////////////////////////////////////////////////////
void CEx24bView::OnSetFocus(CWnd* pOldWnd)
{
    // updates dialog bar filter and sort strings
    GetDocument()->PutFilterSort();
    CRowView::OnSetFocus(pOldWnd);
}

///////////////////////////////////////////////////////////////
int CEx24bView::OnMouseActivate(CWnd* pDesktopWnd,
                                UINT nHitTest, UINT message)
{
    SetFocus(); 
    return CRowView::OnMouseActivate(pDesktopWnd, nHitTest,
                                     message);
}

