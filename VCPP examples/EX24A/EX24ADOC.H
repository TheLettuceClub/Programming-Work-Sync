// ex24adoc.h : interface of the CEx24aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx24aDoc : public CDocument
{
public:
    CEx24aSet m_ex24aSet;
protected: // create from serialization only
    CEx24aDoc();
    DECLARE_DYNCREATE(CEx24aDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
    virtual ~CEx24aDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CEx24aDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
