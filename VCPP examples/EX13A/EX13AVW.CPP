// ex13avw.cpp : implementation of the CEx13aView class
//

#include "stdafx.h"
#include "ex13a.h"

#include "ex13adoc.h"
#include "ex13avw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13aView

IMPLEMENT_DYNCREATE(CEx13aView, CView)

BEGIN_MESSAGE_MAP(CEx13aView, CView)
    //{{AFX_MSG_MAP(CEx13aView)
    ON_COMMAND(ID_DRAW_CIRCLE, OnDrawCircle)
    ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, OnUpdateDrawCircle)
    ON_COMMAND(ID_DRAW_PATTERN, OnDrawPattern)
    ON_UPDATE_COMMAND_UI(ID_DRAW_PATTERN, OnUpdateDrawPattern)
    ON_COMMAND(ID_DRAW_SQUARE, OnDrawSquare)
    ON_UPDATE_COMMAND_UI(ID_DRAW_SQUARE, OnUpdateDrawSquare)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13aView construction/destruction

CEx13aView::CEx13aView() : m_rect(0, 0, 100, 100)
{
    m_bCircle = TRUE;
    m_bPattern = FALSE;
}

CEx13aView::~CEx13aView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CEx13aView drawing

void CEx13aView::OnDraw(CDC* pDC)
{
	CBrush brush(HS_BDIAGONAL, 0L); // brush with diagonal pattern

    if (m_bPattern) {
      pDC->SelectObject(&brush);
    }
    else {
      pDC->SelectStockObject(WHITE_BRUSH);
    }
    if (m_bCircle) {
      pDC->Ellipse(m_rect);
    }
    else {
      pDC->Rectangle(m_rect);
    }
    pDC->SelectStockObject(WHITE_BRUSH); // deselects brush if selected
}

/////////////////////////////////////////////////////////////////////////////
// CEx13aView diagnostics

#ifdef _DEBUG
void CEx13aView::AssertValid() const
{
    CView::AssertValid();
}

void CEx13aView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx13aDoc* CEx13aView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx13aDoc)));
    return (CEx13aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13aView message handlers

void CEx13aView::OnDrawCircle()
{
	m_bCircle = TRUE;
	m_rect += CPoint(25, 25);
	InvalidateRect(m_rect);
}

void CEx13aView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(!m_bCircle);
}

void CEx13aView::OnDrawPattern()
{
    UINT id, style;
    int nCount, i, image;

    m_bPattern = m_bPattern ^ 1;
    // the following code lists the attributes of all toolbar buttons
    // GetParentFrame works in SDI applications only
    CToolBar* pTool = (CToolBar*)
        GetParentFrame()->GetDescendantWindow(AFX_IDW_TOOLBAR);
    TRACE("Toolbar entries:\n");
    nCount = pTool->GetCount();
    for (i = 0; i < nCount; i++) {
        pTool->GetButtonInfo(i, id, style, image);
        TRACE("  index = %d, command ID = %lx, button style = %lx\n",
        i, id, style);
    }
}

void CEx13aView::OnUpdateDrawPattern(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bPattern);
}

void CEx13aView::OnDrawSquare()
{
	m_bCircle = FALSE;
	m_rect += CPoint(25, 25);
	InvalidateRect(m_rect);
}

void CEx13aView::OnUpdateDrawSquare(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bCircle);
}
