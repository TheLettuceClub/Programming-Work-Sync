// matdoc.h : interface of the CMatDoc class
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
/////////////////////////////////////////////////////////////////////////////

class CMatplanDoc : public CDocument
{
	friend class CListView;
	friend class CPlanView;
private:
	CObArray m_pieceArray; // accessible to friends
protected:
	CMatplanDoc();   // called from serialization only
	DECLARE_SERIAL(CMatplanDoc)
// Implementation
public:
	virtual ~CMatplanDoc();
	virtual void Serialize(CArchive& ar);	// overridden for document i/o
#ifdef _DEBUG
	virtual	void AssertValid() const;
	virtual	void Dump(CDumpContext& dc) const;
#endif
protected:
	virtual void DeleteContents();

// Generated message map functions
protected:
	//{{AFX_MSG(CMatplanDoc)
		afx_msg void OnEditClearAll();
		afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
		afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
