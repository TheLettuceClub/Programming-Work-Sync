// ex15adoc.h : interface of the CEx15aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx15aDoc : public CDocument
{
public:
    CStudent m_student;
protected: // create from serialization only
    CEx15aDoc();
    DECLARE_DYNCREATE(CEx15aDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
    virtual ~CEx15aDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CEx15aDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
