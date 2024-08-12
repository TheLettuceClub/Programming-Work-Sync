// matdiag.cpp

#include "stdafx.h"
#include "resource.h"
#include "matpiece.h"
#include "matdlg.h"

BEGIN_MESSAGE_MAP(CMatplanDialog, CDialog)
    //{{AFX_MSG_MAP(CMatplanDialog)
        ON_BN_CLICKED(IDC_CANCEL, OnClickedCancel)
        ON_BN_CLICKED(IDC_CLEAR, OnClear)
        ON_BN_CLICKED(IDC_DELETE, OnDelete)
        ON_BN_CLICKED(IDC_INSERT, OnInsert)
        ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
        ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////
CMatplanDialog::CMatplanDialog(CWnd* pParentWnd, CPiece* pPiece)
        : CModalDialog(CMatplanDialog::IDD, pParentWnd)
{
    m_pPiece = pPiece; // this replaces ClassWizard's initialization
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::DoDataExchange(CDataExchange* pDX)
{
    // no data map here because we're using a CPiece object
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LENGTH, m_pPiece->m_length);
    DDV_MinMaxDouble(pDX, m_pPiece->m_length, 0.0, 96.0);
    DDX_Text(pDX, IDC_WIDTH, m_pPiece->m_width);
    DDV_MinMaxDouble(pDX, m_pPiece->m_width, 0.0, 96.0);
    DDX_Text(pDX, IDC_DESC, m_pPiece->m_desc);
    DDX_Text(pDX, IDC_SHEET, m_pPiece->m_sheet);
    DDV_MinMaxLong(pDX, m_pPiece->m_sheet, 0, 8);
    DDX_Text(pDX, IDC_X, m_pPiece->m_x);
    DDV_MinMaxLong(pDX, m_pPiece->m_x, 0, 800);
    DDX_Text(pDX, IDC_Y, m_pPiece->m_y);
    DDV_MinMaxLong(pDX, m_pPiece->m_y, -800, 0);

    if (m_pPiece->m_bNewList) {
        SetDefID(IDC_INSERT);
    }
    else {
        SetDefID(IDC_UPDATE);
    }
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnClickedCancel()
{
    CDialog::OnCancel();
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnClear()
{
    m_pPiece->m_length = m_pPiece->m_width = 0.0;
    m_pPiece->m_desc = "";
    m_pPiece->m_sheet = m_pPiece->m_x = m_pPiece->m_y = 0;
    UpdateData(FALSE);
    SetDefID(IDC_INSERT); // insert is the next logical operation
    GotoDlgCtrl(GetDlgItem(IDC_LENGTH));
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnInsert()
{
    if (!UpdateData(TRUE))
        return; // returns on error
    EndDialog(IDC_INSERT);
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnDelete()
{
    EndDialog(IDC_DELETE);
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnUpdate()
{
    if (!UpdateData(TRUE)) return; // returns on error
    EndDialog(IDC_UPDATE);
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDialog::OnCancel()
{
    if (AfxMessageBox("Exit Dialog? (F1 for help)", MB_OKCANCEL,
                      IDP_EXIT_DLG) == IDOK)
    {
        CDialog::OnCancel();
    }
}
