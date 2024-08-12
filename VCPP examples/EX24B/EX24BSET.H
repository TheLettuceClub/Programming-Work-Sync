// ex24bset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEx24bSet recordset

class CEx24bSet : public CRecordset
{
public:
	CStringArray m_arrayName;  // column names
	CPtrArray m_arrayValue;    // column values
	int m_nColWidth[MAXCOLS];
	int m_nDatType[MAXCOLS];

	CEx24bSet(CDatabase* pDatabase = NULL);
	~CEx24bSet();
	void Initialize(const char* pchTableName);

// Implementation
public:
	virtual CString GetDefaultSQL(); 	// Default SQL for Recordset
protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	DECLARE_DYNAMIC(CEx24bSet)
};

