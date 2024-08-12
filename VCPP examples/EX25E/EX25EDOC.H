// ex25edoc.h : interface of the CEx25eDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx25eDoc : public CDocument
{
protected: // create from serialization only
	CEx25eDoc();
	DECLARE_DYNCREATE(CEx25eDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CEx25eDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx25eDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
