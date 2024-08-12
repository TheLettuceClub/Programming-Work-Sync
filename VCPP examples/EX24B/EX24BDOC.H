// ex24bdoc.h : interface of the CEx24bDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx24bDoc : public CDocument
{
public:
    CEx24bSet* m_pEx24bSet;
    CDatabase  m_database;
    CString    m_strTableName;
    CString    m_strConnect;
    CString    m_strFilter;
    CString    m_strSort;
    BOOL       m_bConnected;

protected: // create from serialization only
    CEx24bDoc();
    DECLARE_DYNCREATE(CEx24bDoc)

public:
    virtual ~CEx24bDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif
protected:
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument(const char* pszPathName);
    virtual BOOL SaveModified();
public:
    virtual void DeleteContents();
    void GetFilterSort();
    void PutFilterSort();
// Generated message map functions
protected:
    //{{AFX_MSG(CEx24bDoc)
    afx_msg void OnRequery();
    afx_msg void OnUpdateRequery(CCmdUI* pCmdUI);
    afx_msg void OnFileConnect();
    afx_msg void OnUpdateFileConnect(CCmdUI* pCmdUI);
    afx_msg void OnFileDisconnect();
    afx_msg void OnUpdateFileDisconnect(CCmdUI* pCmdUI);
    afx_msg void OnUpdateAppExit(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
