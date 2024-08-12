// matdoc.cpp : implementation of the CMatDoc class
//
// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//

#include "stdafx.h"
#include "matpiece.h"

//#include "ex19c.h"
#include "resource.h"
#include "matdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CMatplanDoc, CDocument, 0 /* schema number*/ )

BEGIN_MESSAGE_MAP(CMatplanDoc, CDocument)
    //{{AFX_MSG_MAP(CMatplanDoc)
    ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
    ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
 
/////////////////////////////////////////////////////////////////////////////
// CMatplanDoc construction/destruction
CMatplanDoc::CMatplanDoc()
{
    m_pieceArray.SetSize(0, 20); // allocate mem 20 elements at a time
}

CMatplanDoc::~CMatplanDoc()
{
}

////////////////////////////////////////////////////////////////////////////
// CMatplanDoc serialization

void CMatplanDoc::Serialize(CArchive& ar)
{
    m_pieceArray.Serialize(ar);
}

////////////////////////////////////////////////////////////////////////////
void CMatplanDoc::DeleteContents()
{
    for (int i = m_pieceArray.GetUpperBound(); i >= 0; i--) {
        delete m_pieceArray.GetAt(i);
    }
    m_pieceArray.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CMatplanDoc commands

void CMatplanDoc::OnEditClearAll()
{   // gets rid of the old piece array in the document
    DeleteContents();
    SetModifiedFlag();
    UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
void CMatplanDoc::OnUpdateEditClearAll(CCmdUI* pCmdUI)
{ // grays Clear All choice if document array is empty
    pCmdUI->Enable(m_pieceArray.GetUpperBound() != -1);
}

/////////////////////////////////////////////////////////////////////////////
void CMatplanDoc::OnUpdateFileSave(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(IsModified());
}

/////////////////////////////////////////////////////////////////////////////
// CMatplanDoc diagnostics

#ifdef _DEBUG
void CMatplanDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CMatplanDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

