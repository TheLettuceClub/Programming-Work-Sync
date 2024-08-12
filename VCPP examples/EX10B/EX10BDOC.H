// ex10bdoc.h : interface of the CEx10bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx10bDoc : public CDocument
{
protected: // create from serialization only
	CEx10bDoc();
	DECLARE_DYNCREATE(CEx10bDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CEx10bDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx10bDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
