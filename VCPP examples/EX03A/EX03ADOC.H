// ex03adoc.h : interface of the CEx03aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx03aDoc : public CDocument
{
protected: // create from serialization only
	CEx03aDoc();
	DECLARE_DYNCREATE(CEx03aDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CEx03aDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx03aDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
