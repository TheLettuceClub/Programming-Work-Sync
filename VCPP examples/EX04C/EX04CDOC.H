// ex04cdoc.h : interface of the CEx04cDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx04cDoc : public CDocument
{
protected: // create from serialization only
	CEx04cDoc();
	DECLARE_DYNCREATE(CEx04cDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
	virtual ~CEx04cDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnNewDocument();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04cDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
