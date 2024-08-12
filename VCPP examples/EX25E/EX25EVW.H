// ex25evw.h : interface of the CEx25eView class
//
/////////////////////////////////////////////////////////////////////////////
#include "app.h"
#include "range.h"
#include "wksheet.h" 
#include "wkbooks.h"
#include "clockc.h"
#include "alarmc.h"
#include "dllcont.h"
#include "marketc.h"

class CEx25eView : public CView
{
public:
    static const CLSID BASED_CODE excelClsid;
    CDLLControl m_dllControl;
    CMarketControl m_marketc;
    Workbooks m_workbooks;
    Worksheet m_worksheet;
    Range m_range[5];
    CAlarmControl m_alarmc;
// sequence is important!
    CClockControl m_clockc;  // deleted first -- takes alarm with it
    Application m_excel;
protected: // create from serialization only
    CEx25eView();
    DECLARE_DYNCREATE(CEx25eView)

// Attributes
public:
    CEx25eDoc* GetDocument();
// Operations
public:

// Implementation
public:
    virtual ~CEx25eView();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
    //{{AFX_MSG(CEx25eView)
    afx_msg void OnClockLoad();
    afx_msg void OnUpdateClockLoad(CCmdUI* pCmdUI);
    afx_msg void OnClockRefreshtime();
    afx_msg void OnUpdateClockRefreshtime(CCmdUI* pCmdUI);
    afx_msg void OnExcelExecute();
    afx_msg void OnUpdateExcelExecute(CCmdUI* pCmdUI);
    afx_msg void OnExcelLoad();
    afx_msg void OnUpdateExcelLoad(CCmdUI* pCmdUI);
    afx_msg void OnClockUnload();
    afx_msg void OnUpdateClockUnload(CCmdUI* pCmdUI);
    afx_msg void OnDllGetData();
    afx_msg void OnUpdateDllGetData(CCmdUI* pCmdUI);
    afx_msg void OnDllLoad();
    afx_msg void OnUpdateDllLoad(CCmdUI* pCmdUI);
    afx_msg void OnDllUnload();
    afx_msg void OnUpdateDllUnload(CCmdUI* pCmdUI);
    afx_msg void OnClockCreateAlarm();
    afx_msg void OnUpdateClockCreateAlarm(CCmdUI* pCmdUI);
    afx_msg void OnMarketGetAverage();
    afx_msg void OnUpdateMarketGetAverage(CCmdUI* pCmdUI);
    afx_msg void OnMarketLoad();
    afx_msg void OnUpdateMarketLoad(CCmdUI* pCmdUI);
    afx_msg void OnMarketUnload();
    afx_msg void OnUpdateMarketUnload(CCmdUI* pCmdUI);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex25evw.cpp
inline CEx25eDoc* CEx25eView::GetDocument()
   { return (CEx25eDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
