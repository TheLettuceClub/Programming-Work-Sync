// ex12bdoc.h : interface of the CEx12bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx12bDoc : public CDocument
{
protected: // create from serialization only
	CEx12bDoc();
	DECLARE_DYNCREATE(CEx12bDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CEx12bDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx12bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
