// poemdoc.h : interface of the CPoemDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CPoemDoc : public CDocument
{
public:
    CStringArray m_stringArray;
protected: // create from serialization only
    CPoemDoc();
    DECLARE_DYNCREATE(CPoemDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
    virtual void DeleteContents();
    virtual ~CPoemDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CPoemDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
