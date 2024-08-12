// ex24aset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx24aSet recordset

class CEx24aSet : public CRecordset
{
public:
	CEx24aSet(CDatabase* pDatabase = NULL);

// Field/Param Data
	//{{AFX_FIELD(CEx24aSet, CRecordset)
	long	m_StudentID;
	CString	m_Name;
	int		m_GradYear;
	//}}AFX_FIELD


// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	DECLARE_DYNAMIC(CEx24aSet)
};

