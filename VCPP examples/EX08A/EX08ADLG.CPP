// ex08adlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex08a.h"
#include "ex08adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08aDialog dialog

CEx08aDialog::CEx08aDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CEx08aDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CEx08aDialog)
    m_pVBGrid = NULL;
    m_cellValue = "";
    //}}AFX_DATA_INIT
}

void CEx08aDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx08aDialog)
    DDX_VBControl(pDX, IDC_GRID1, m_pVBGrid);
    DDX_Text(pDX, IDC_VALUE, m_cellValue);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx08aDialog, CDialog)
    //{{AFX_MSG_MAP(CEx08aDialog)
    ON_VBXEVENT(VBN_SELCHANGE, IDC_GRID1, OnSelchangeGrid1)
    ON_BN_CLICKED(IDC_ADDROW, OnAddrow)
    ON_BN_CLICKED(IDC_DELETEROW, OnDeleterow)
    ON_BN_CLICKED(IDC_UPDATEVALUE, OnUpdatevalue)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08aDialog message handlers

void CEx08aDialog::OnSelchangeGrid1(UINT, int, CWnd*, LPVOID)
{
    if (m_pVBGrid) {
      m_cellValue = m_pVBGrid->GetStrProperty("Text");
      UpdateData(FALSE); // calls DoDataExchange to update edit control
      GotoDlgCtrl(GetDlgItem(IDC_VALUE)); // position edit control
    }
}

void CEx08aDialog::OnCancel()
{
    // TODO: Add extra cleanup here
    
    CDialog::OnCancel();
}

void CEx08aDialog::OnOK()
{
    int i, j;
    
    for (i = 1; i < 8; i++) {
      m_pVBGrid->SetNumProperty("Col", i);
      for (j = 1; j < 11; j++) {
        m_pVBGrid->SetNumProperty("Row", j);
        m_dArray[i][j] = atof(m_pVBGrid->GetStrProperty("Text"));
      }
    }
    CDialog::OnOK();
}

BOOL CEx08aDialog::OnInitDialog()
{
    CRect rect;
    char  temp[20];
    int   i, j;
    long  lColWidth, lRowHeight;
    
    VERIFY(CDialog::OnInitDialog());
    VERIFY(m_pVBGrid->GetNumProperty("Cols") == 8L); // set in App Studio
    VERIFY(m_pVBGrid->GetNumProperty("Rows") == 12L);
    CClientDC dc(this);
    m_pVBGrid->GetClientRect(rect); // device coordinates
    lColWidth = m_pVBGrid->GetNumProperty("ColWidth", 0);
    lRowHeight = m_pVBGrid->GetNumProperty("RowHeight", 0);
    lColWidth  = (1440L * (long) rect.right) /
                 (8L * (long) dc.GetDeviceCaps(LOGPIXELSX)) - 20L;
    lRowHeight = (1440L * (long) rect.bottom) /
                 (12L * (long) dc.GetDeviceCaps(LOGPIXELSY)) - 20L;
    
    m_pVBGrid->SetNumProperty("Row", 0);
    for (i = 0; i < 8; i++) {
      m_pVBGrid->SetNumProperty("ColWidth", lColWidth, i);
      if (i) { // column headings
        m_pVBGrid->SetNumProperty("Col", i);
        m_pVBGrid->SetStrProperty("Text", CString('A' + i - 1));
      }
    }
    m_pVBGrid->SetNumProperty("Col", 0);
    for (j = 0; j < 12; j++) {
      m_pVBGrid->SetNumProperty("RowHeight", lRowHeight, j);
      m_pVBGrid->SetNumProperty("FixedAlignment", 2, j); // centered
      m_pVBGrid->SetNumProperty("ColAlignment", 1, j);   // right
      if (j) { // row headings
        m_pVBGrid->SetNumProperty("Row", j); 
        sprintf(temp, "%d", j);
        m_pVBGrid->SetStrProperty("Text", temp);
      }
    }            
    // sets the spreadsheet values from m_dArray
    for (i = 1; i < 8; i++) {
      m_pVBGrid->SetNumProperty("Col", i);
      for (j = 1; j < 11; j++) {
        m_pVBGrid->SetNumProperty("Row", j);
        sprintf(temp, "%8.2f", m_dArray[i][j]);
        m_pVBGrid->SetStrProperty("Text", temp);
      }                    
    }
    ComputeSums();
    // be sure there's a selected cell
    m_pVBGrid->SetNumProperty("Col", 1L);
    m_pVBGrid->SetNumProperty("Row", 1L);
    m_cellValue = m_pVBGrid->GetStrProperty("Text");
    UpdateData(FALSE); // calls DoDataExchange to update edit control
    return TRUE;
}

void CEx08aDialog::ComputeSums()
{
    int    i, j, nRows;
    double sum;
    char   temp[30];
    
    // adds up each column and puts the sum in the bottom row
    // row count could have been changed by add row/delete row
    nRows = (int) m_pVBGrid->GetNumProperty("Rows");
    for (i = 1; i < 8; i++) {
      m_pVBGrid->SetNumProperty("Col", i);
      sum = 0.0;
      for (j = 1; j < nRows - 1; j++) {
        m_pVBGrid->SetNumProperty("Row", j);
        sum += atof(m_pVBGrid->GetStrProperty("Text"));
      }
      sprintf(temp, "%8.2f", sum);
      m_pVBGrid->SetNumProperty("Row", nRows - 1);
      m_pVBGrid->SetStrProperty("Text", temp);
    }
}

void CEx08aDialog::OnAddrow()
{
    if (m_pVBGrid->GetNumProperty("CellSelected") == 0) {
      AfxMessageBox("No cell selected");
      return;
    }
    LONG i = m_pVBGrid->GetNumProperty("Row");
    m_pVBGrid->AddItem("new row", i);
    ComputeSums();
}

void CEx08aDialog::OnDeleterow()
{
    if (m_pVBGrid->GetNumProperty("CellSelected") == 0) {
      AfxMessageBox("No cell selected");
      return;
    }
    LONG i = m_pVBGrid->GetNumProperty("Row");
    m_pVBGrid->RemoveItem(i);
    ComputeSums();
}

void CEx08aDialog::OnUpdatevalue()
{
    char   temp[30];
    double value;
    LONG   lRow, lCol;
    
    if (m_pVBGrid->GetNumProperty("CellSelected" == 0)) {
      AfxMessageBox("No cell selected");
      return;
    }
    UpdateData(TRUE);
    value = atof(m_cellValue);
    sprintf(temp, "%8.2f", value);
    
    // saves current cell selection
    lCol = m_pVBGrid->GetNumProperty("Col");
    lRow = m_pVBGrid->GetNumProperty("Row");
    
    m_pVBGrid->SetStrProperty("Text", temp); // copies new value to
                                             //  the selected cell  
    ComputeSums();
    
    // restores current cell selection
    m_pVBGrid->SetNumProperty("Col", lCol);
    m_pVBGrid->SetNumProperty("Row", lRow);
}
