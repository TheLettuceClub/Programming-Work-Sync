// studoc.h : interface of the CStudentDoc class

class CStudentDoc : public CDocument
{
    DECLARE_DYNCREATE(CStudentDoc)
private:
    CObList m_studentList;
protected: // create from serialization only
    CStudentDoc();

// Attributes
public:
    CObList* GetList() {
        return &m_studentList;
    }

// Operations
public:

// Implementation
public:
    virtual ~CStudentDoc();
    virtual void Serialize(CArchive& ar); // overridden for document
                                          //  i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL OnNewDocument();
    virtual void DeleteContents();
// Generated message map functions
protected:
    //{{AFX_MSG(CStudentDoc)
    afx_msg void OnEditClearAll();
    afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////
