// ex14adoc.h : interface of the CEx14aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx14aDoc : public CDocument
{
protected: // create from serialization only
	CEx14aDoc();
	DECLARE_DYNCREATE(CEx14aDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CEx14aDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx14aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
