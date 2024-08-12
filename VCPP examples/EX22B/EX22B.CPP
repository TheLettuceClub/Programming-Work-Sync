#include "stdafx.h"
#include "ex22b.h"

CEx22bApp NEAR theApp;
                 
BOOL CEx22bApp::InitInstance()
{
    m_dialog.DoModal(); // returns when Exit button clicked
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CEx22bDialog, CDialog)
    //{{AFX_MSG_MAP(CEx22bDialog)
    ON_BN_CLICKED(ID_COMPUTE, OnCompute)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////
CEx22bDialog::CEx22bDialog() : CDialog(CEx22bDialog::IDD)
{
    //{{AFX_DATA_INIT(CEx22bDialog)
    m_d1 = 0;
    m_d2 = 0;
    m_d3 = 0;
    m_nOpr = 0; // changed from default -1
    //}}AFX_DATA_INIT
}

/////////////////////////////////////////////////////////////////////////
void CEx22bDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx22bDialog)
    DDX_Text(pDX, IDC_EDIT1, m_d1);
    DDX_Text(pDX, IDC_EDIT2, m_d2);
    DDX_Text(pDX, IDC_EDIT3, m_d3);
    DDX_Radio(pDX, IDC_RADIO1, m_nOpr);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////
void CEx22bDialog::OnCompute()
{
    UpdateData(TRUE);
    switch (m_nOpr) {
    case 0:  // add
        m_d3 = m_d1 + m_d2;
        break;
    case 1:  // subtract
        m_d3 = m_d1 - m_d2;
        break;
    case 2:  // multiply
        m_d3 = m_d1 * m_d2;
        break;
    case 3:  // divide
        if (m_d2 != 0.0) {
            m_d3 = m_d1 / m_d2;
        }
        else {
            AfxMessageBox("Divide by zero");
            m_d3 = 0.0;
        }
        break;
    default:
        TRACE("default m_nOpr = %d\n", m_nOpr);
    }
    UpdateData(FALSE);
}
