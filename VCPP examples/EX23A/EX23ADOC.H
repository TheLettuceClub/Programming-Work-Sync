// ex23adoc.h : interface of the CEx23aDoc class
//
/////////////////////////////////////////////////////////////////////////////

class CEx23aDoc : public CDocument
{
friend class CEx23aView;
private:
	CDib* m_pDib; // like what we'd have in a collection
protected: // create from serialization only
	CEx23aDoc();
	DECLARE_DYNCREATE(CEx23aDoc)

public:
	virtual ~CEx23aDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
protected:
	virtual void DeleteContents();

// Generated message map functions
protected:
	//{{AFX_MSG(CEx23aDoc)
	afx_msg void OnEditClearAll();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
