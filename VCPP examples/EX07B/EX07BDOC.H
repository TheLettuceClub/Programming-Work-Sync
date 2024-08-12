// ex07bdoc.h : interface of the CEx07bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx07bDoc : public CDocument
{
protected: // create from serialization only
	CEx07bDoc();
	DECLARE_DYNCREATE(CEx07bDoc)

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CEx07bDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual	BOOL	OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx07bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
