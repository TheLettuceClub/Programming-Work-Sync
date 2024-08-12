// ex05cdoc.h : interface of the CEx05cDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx05cDoc : public CDocument
{
protected: // create from serialization only
	CEx05cDoc();
	DECLARE_DYNCREATE(CEx05cDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CEx05cDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx05cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
