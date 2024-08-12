// ex12adoc.h : interface of the CEx12aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx12aDoc : public CDocument
{
private:
    CString m_text; // representation of edit text
protected: // create from serialization only
    CEx12aDoc();
    DECLARE_DYNCREATE(CEx12aDoc)

// Attributes
public:
// Operations
public:

// Implementation
public:
    virtual ~CEx12aDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    virtual BOOL OnNewDocument();

// Generated message map functions
protected:
    //{{AFX_MSG(CEx12aDoc)
    afx_msg void OnEditClearall();
    afx_msg void OnUpdateEditClearall(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
