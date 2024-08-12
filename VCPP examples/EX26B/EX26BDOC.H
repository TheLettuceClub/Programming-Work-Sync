// ex26bdoc.h : interface of the CEx26bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx26bDoc : public CDocument
{
public:
	CObArray m_studentArray;
protected: // create from serialization only
	CEx26bDoc();
	DECLARE_DYNCREATE(CEx26bDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CEx26bDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL OnNewDocument();
	virtual void DeleteContents();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx26bDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
