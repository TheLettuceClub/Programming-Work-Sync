// ex24aset.cpp : implementation file
//

#include "stdafx.h"
#include "ex24a.h"
#include "ex24aset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24aSet

IMPLEMENT_DYNAMIC(CEx24aSet, CRecordset)

CEx24aSet::CEx24aSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx24aSet)
	m_StudentID = 0;
	m_Name = "";
	m_GradYear = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
}


CString CEx24aSet::GetDefaultConnect()
{
	return "ODBC;DSN=Student Registration;";
}

CString CEx24aSet::GetDefaultSQL()
{
	return "STUDENT";
}

void CEx24aSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx24aSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, "StudentID", m_StudentID);
	RFX_Text(pFX, "Name", m_Name);
	RFX_Int(pFX, "GradYear", m_GradYear);
	//}}AFX_FIELD_MAP
}
