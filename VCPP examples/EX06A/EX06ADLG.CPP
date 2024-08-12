// ex06adlgcpp : implementation file
//

#include "stdafx.h"
#include "ex06a.h"
#include "ex06adlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog dialog

CEx06aDialog::CEx06aDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CEx06aDialog::IDD, pParent)
{
    //{{AFX_DATA_INIT(CEx06aDialog)
    m_nCat = -1;
    m_bInsDis = FALSE;
    m_bInsLife = FALSE;
    m_bInsMed = FALSE;
    m_lSsn = 0;
    //}}AFX_DATA_INIT
}

BOOL CEx06aDialog::OnInitDialog()
{
    CListBox* pLB = (CListBox*) GetDlgItem(IDC_DEPT);
    pLB->InsertString(-1, "Documentation");
    pLB->InsertString(-1, "Accounting");
    pLB->InsertString(-1, "Human Relations");
    pLB->InsertString(-1, "Security");

    CScrollBar* pSB = (CScrollBar*) GetDlgItem(IDC_LOYAL);
    pSB->SetScrollRange(nMin, nMax);
    pSB->SetScrollPos(m_nLoyal);

    pSB = (CScrollBar*) GetDlgItem(IDC_RELY);
    pSB->SetScrollRange(nMin, nMax);
    pSB->SetScrollPos(m_nRely);
    
    return CDialog::OnInitDialog();  // call after initialization
    // initialize any VB controls after base class OnInitDialog call
}

void CEx06aDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CEx06aDialog)
    DDX_Text(pDX, IDC_NAME, m_name);
    DDX_Text(pDX, IDC_BIO, m_bio);
    DDX_Radio(pDX, IDC_CAT, m_nCat);
    DDX_Check(pDX, IDC_DIS, m_bInsDis);
    DDX_LBString(pDX, IDC_DEPT, m_dept);
    DDX_CBString(pDX, IDC_EDUC, m_educ);
    DDX_Check(pDX, IDC_LIFE, m_bInsLife);
    DDX_Check(pDX, IDC_MED, m_bInsMed);
    DDX_CBString(pDX, IDC_LANG, m_lang);
    DDX_CBString(pDX, IDC_SKILL, m_skill);
    DDX_Text(pDX, IDC_SSN, m_lSsn);
    DDV_MinMaxLong(pDX, m_lSsn, 0, 999999999);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEx06aDialog, CDialog)
    //{{AFX_MSG_MAP(CEx06aDialog)
    ON_BN_CLICKED(IDC_OK, OnClickedOk)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_SPECIAL, OnSpecial)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06aDialog message handlers

/////////////////////////////////////////////////////////////////////////////
void CEx06aDialog::OnClickedOk()
{
    CScrollBar* pSB;

    TRACE("CEx06aDialog::OnClickedOK\n");
    pSB = (CScrollBar*) GetDlgItem(IDC_LOYAL);
    m_nLoyal = pSB->GetScrollPos();

    pSB = (CScrollBar*) GetDlgItem(IDC_RELY);
    m_nRely = pSB->GetScrollPos();

    CDialog::OnOK(); // does data exchange
}

/////////////////////////////////////////////////////////////////////////////
void CEx06aDialog::OnOK()
{
    // dummy OnOK function   
    TRACE("CEx06aDialog::OnOK\n");
}

/////////////////////////////////////////////////////////////////////////////
void CEx06aDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int nTemp1, nTemp2;
    nTemp1 = pScrollBar->GetScrollPos();
    switch(nSBCode) {
    case SB_THUMBPOSITION:
        pScrollBar->SetScrollPos(nPos);
        break;
    case SB_LINEUP:
        nTemp2 = (nMax - nMin) / 10;
        if ((nTemp1 - nTemp2) > nMin) {
          nTemp1 -= nTemp2;
        }
        else {
          nTemp1 = nMin;
        }
        pScrollBar->SetScrollPos(nTemp1);
        break;
    case SB_LINEDOWN:
        nTemp2 = (nMax - nMin) / 10;
        if ((nTemp1 + nTemp2) < nMax) {
          nTemp1 += nTemp2;
        }
        else {
          nTemp1 = nMax;
        }
        pScrollBar->SetScrollPos(nTemp1);
    }
 }

/////////////////////////////////////////////////////////////////////////////
void CEx06aDialog::OnSpecial()
{
    TRACE("CEx06aDialog::OnSpecial\n");
}
