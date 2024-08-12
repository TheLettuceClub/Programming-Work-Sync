// ex18bdoc.h : interface of the CEx18bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx18bDoc : public CDocument
{
public:
    CRect  m_ellipseArray[50];
    int    m_nEllipseQty;
    static const int NEAR nLinesPerPage;
protected: // create from serialization only
    CEx18bDoc();
    DECLARE_DYNCREATE(CEx18bDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
    virtual ~CEx18bDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CEx18bDoc)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
