// studoc.h : interface of the CStudentDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CStudentDoc : public CDocument
{
private:
    CObList m_studentList;
protected: // create from serialization only
    CStudentDoc();
    DECLARE_DYNCREATE(CStudentDoc)

// Implementation
public:
    virtual ~CStudentDoc();
    CObList* GetList() {
        return &m_studentList;
    }
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument(const char* pszPathName);
    virtual void DeleteContents();

// Generated message map functions
protected:
    //{{AFX_MSG(CStudentDoc)
    afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
