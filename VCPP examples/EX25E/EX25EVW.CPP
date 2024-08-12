// ex25evw.cpp : implementation of the CEx25eView class
//

#include "stdafx.h"
#include "ex25e.h"

#include "ex25edoc.h"
#include "ex25evw.h"
#include "cvariant.h"
#include "alarmdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx25eView

IMPLEMENT_DYNCREATE(CEx25eView, CView)

BEGIN_MESSAGE_MAP(CEx25eView, CView)
    //{{AFX_MSG_MAP(CEx25eView)
    ON_COMMAND(ID_CLOCKOLE_LOAD, OnClockLoad)
    ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_LOAD, OnUpdateClockLoad)
    ON_COMMAND(ID_CLOCKOLE_REFRESHTIME, OnClockRefreshtime)
    ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_REFRESHTIME, OnUpdateClockRefreshtime)
    ON_COMMAND(ID_EXCELOLE_EXECUTE, OnExcelExecute)
    ON_UPDATE_COMMAND_UI(ID_EXCELOLE_EXECUTE, OnUpdateExcelExecute)
    ON_COMMAND(ID_EXCELOLE_LOAD, OnExcelLoad)
    ON_UPDATE_COMMAND_UI(ID_EXCELOLE_LOAD, OnUpdateExcelLoad)
    ON_COMMAND(ID_CLOCKOLE_UNLOAD, OnClockUnload)
    ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_UNLOAD, OnUpdateClockUnload)
    ON_COMMAND(ID_DLLOLE_GETDATA, OnDllGetData)
    ON_UPDATE_COMMAND_UI(ID_DLLOLE_GETDATA, OnUpdateDllGetData)
    ON_COMMAND(ID_DLLOLE_LOAD, OnDllLoad)
    ON_UPDATE_COMMAND_UI(ID_DLLOLE_LOAD, OnUpdateDllLoad)
    ON_COMMAND(ID_DLLOLE_UNLOAD, OnDllUnload)
    ON_UPDATE_COMMAND_UI(ID_DLLOLE_UNLOAD, OnUpdateDllUnload)
    ON_COMMAND(ID_CLOCKOLE_CREATEALARM, OnClockCreateAlarm)
    ON_UPDATE_COMMAND_UI(ID_CLOCKOLE_CREATEALARM, OnUpdateClockCreateAlarm)
    ON_COMMAND(ID_MARKETOLE_GETAVERAGE, OnMarketGetAverage)
    ON_UPDATE_COMMAND_UI(ID_MARKETOLE_GETAVERAGE, OnUpdateMarketGetAverage)
    ON_COMMAND(ID_MARKETOLE_LOAD, OnMarketLoad)
    ON_UPDATE_COMMAND_UI(ID_MARKETOLE_LOAD, OnUpdateMarketLoad)
    ON_COMMAND(ID_MARKETOLE_UNLOAD, OnMarketUnload)
    ON_UPDATE_COMMAND_UI(ID_MARKETOLE_UNLOAD, OnUpdateMarketUnload)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// not needed if we use the ProgID -- copied from REG.DAT
const CLSID BASED_CODE CEx25eView::excelClsid =
    {0x00020841, 0x0000, 0x0000, {0xc0, 0x00, 0, 0, 0, 0, 0, 0x46 } };
/////////////////////////////////////////////////////////////////////////////
// CEx25eView construction/destruction

CEx25eView::CEx25eView()
{
    TRACE("Entering CEx25eView ctor\n");
}

CEx25eView::~CEx25eView()
{
    TRACE("Entering CEx25eView dtor\n");
}

/////////////////////////////////////////////////////////////////////////////
// CEx25eView drawing

void CEx25eView::OnDraw(CDC* pDC)
{
    CEx25eDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);

    // TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx25eView diagnostics

#ifdef _DEBUG
void CEx25eView::AssertValid() const
{
    CView::AssertValid();
}

void CEx25eView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CEx25eDoc* CEx25eView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx25eDoc)));
    return (CEx25eDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx25eView message handlers
//     Excel ////////////////////////////////////////////////////////////////
void CEx25eView::OnExcelExecute()
{
    TRACE("Entering CEx25eView::OnOleAutoExecuteCode\n");
    LPDISPATCH pRange, pWorkbooks;
    
    CWnd* pWnd = CWnd::FindWindow("XLMAIN", NULL);
    if (pWnd != NULL) {
      TRACE("Excel window found\n");
      pWnd->ShowWindow(SW_SHOWNORMAL);
      pWnd->UpdateWindow();
      pWnd->BringWindowToTop();
    }

    m_excel.SetSheetsInNewWorkbook(1);
    
    VERIFY(pWorkbooks = m_excel.Workbooks());
    m_workbooks.AttachDispatch(pWorkbooks);

    LPDISPATCH pWorkbook = NULL;
    if (m_workbooks.GetCount() == 0) {
      // Add returns a Workbook pointer, but we dont have a Workbook class
      pWorkbook = m_workbooks.Add(); // save the pointer for later release
    }
    LPDISPATCH pWorksheet = m_excel.Worksheets(CVariant("sheet1"));
    VERIFY(pWorksheet != NULL);

    m_worksheet.AttachDispatch(pWorksheet);
    m_worksheet.Select();

    VERIFY(pRange = m_worksheet.Range(CVariant("A1")));
    m_range[0].AttachDispatch(pRange);

    VERIFY(pRange = m_worksheet.Range(CVariant("A2")));
    m_range[1].AttachDispatch(pRange);
    
    VERIFY(pRange = m_worksheet.Range(CVariant("A3")));
    m_range[2].AttachDispatch(pRange);

    VERIFY(pRange = m_worksheet.Range(CVariant("A3"), CVariant("C5")));
    m_range[3].AttachDispatch(pRange);

    VERIFY(pRange = m_worksheet.Range(CVariant("A6")));
    m_range[4].AttachDispatch(pRange);
    
    m_range[4].SetValue(CVariant(1994, 4, 24, 15, 47, 8));
    CVariant timeDate = m_range[4].GetValue();
    CVariant varDate, stringDate;
    if (timeDate.ChangeType(VT_DATE, varDate)) {  // allows for returned R8 date
      if (varDate.ChangeType(VT_BSTR, stringDate)) {
        TRACE("string date = %s\n", stringDate.bstrVal);
      }
    }
    m_range[0].SetValue(CVariant("test string"));
    
    CVariant vResult0 = m_range[0].GetValue();
    if (vResult0.vt == VT_BSTR) {
      TRACE("vResult0 = %s\n", vResult0.bstrVal);
    }

    m_range[1].SetValue(CVariant(3.14159));
    
    CVariant vResult1 = m_range[1].GetValue();
    if (vResult1.vt == VT_R8) {
      TRACE("vResult1 = %f\n", vResult1.dblVal);
    }
    
    m_range[2].SetFormula(CVariant("=$A2*2.0"));
    // European programmers substitute '2,0' for '2.0'
    
    CVariant vResult2 = m_range[2].GetValue();
    if (vResult2.vt == VT_R8) {
      TRACE("vResult2 = %f\n", vResult2.dblVal);
    }

    CVariant vResult2a = m_range[2].GetFormula();
    if (vResult2a.vt == VT_BSTR) {
      TRACE("vResult2a = %s\n", vResult2a.bstrVal);
    }
    
    m_range[3].FillRight();
    m_range[3].FillDown();
    
// cleanup  
    if (pWorkbook != NULL) {
      pWorkbook->Release();
    }
}

void CEx25eView::OnExcelLoad()
{   // if Excel is already running, attach to it, otherwise start it
    LPDISPATCH pDisp;
    LPUNKNOWN  pUnk;
    CLSID      clsid;
    TRACE("Entering CEx25eView::OnExcelLoad\n");
    BeginWaitCursor();
    ::CLSIDFromProgID("excel.application.5", &clsid); // from REG.DAT
    if (::GetActiveObject(clsid, NULL, &pUnk) == S_OK) {
//  if (::GetActiveObject(excelClsid, NULL, &pUnk) == S_OK) {
      TRACE("attaching\n");
      VERIFY(pUnk->QueryInterface(IID_IDispatch,
            (void FAR* FAR*) &pDisp) == S_OK);
      m_excel.AttachDispatch(pDisp);
      pUnk->Release();
    } 
    else {
      TRACE("creating\n");
      VERIFY(m_excel.CreateDispatch("excel.application.5") == TRUE);
//      VERIFY(m_excel.CreateDispatch(excelClsid) == TRUE);
    }
    // the following code demonstrates use of GetTypeInfoCount
    // Excel has a type library, so nInfo should be 1
    UINT nInfo;
    VERIFY(m_excel.m_lpDispatch->GetTypeInfoCount(&nInfo) == S_OK);
    TRACE("GetTypeInfoCount: nInfo = %d\n", nInfo); 
    EndWaitCursor();
}

void CEx25eView::OnUpdateExcelLoad(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_excel.m_lpDispatch == NULL);
}

void CEx25eView::OnUpdateExcelExecute(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_excel.m_lpDispatch != NULL);
}

///    Clock //////////////////////////////////////////////////////////////
void CEx25eView::OnClockLoad()
{
    BeginWaitCursor();
    VERIFY(m_clockc.CreateDispatch("ex25d.document") == TRUE);
    CVariant vFig0 = m_clockc.GetFigure(0);  // testing
    CVariant time =  m_clockc.GetTime(); // testing

    // the following code demonstrates use of GetTypeInfoCount
    // not implemented in MFC OLE Automation
    UINT nInfo;
    VERIFY(GetScode(m_clockc.m_lpDispatch->GetTypeInfoCount(&nInfo))
        == E_NOTIMPL);

    int nh, nm, ns;
    time.GetHMS(nh, nm, ns);
    m_clockc.SetFigure(0, CVariant("twelve"));
    m_clockc.SetFigure(1, CVariant("three"));
    m_clockc.SetFigure(2, CVariant("six"));
    m_clockc.SetFigure(3, CVariant("nine"));

    OnClockRefreshtime();
    m_clockc.ShowWin();
    EndWaitCursor();
}

void CEx25eView::OnUpdateClockLoad(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_clockc.m_lpDispatch == NULL);
}

void CEx25eView::OnClockRefreshtime()
{
    CTime now = CTime::GetCurrentTime();
    m_clockc.SetTime(CVariant(0, 0, 0, now.GetHour(), now.GetMinute(),
        now.GetSecond()));
    m_clockc.RefreshWin();
}

void CEx25eView::OnUpdateClockRefreshtime(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_clockc.m_lpDispatch != NULL);
}

void CEx25eView::OnClockUnload()
{
    m_clockc.ReleaseDispatch(); // server exits and releases alarm object
}

void CEx25eView::OnUpdateClockUnload(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_clockc.m_lpDispatch != NULL);
}

void CEx25eView::OnClockCreateAlarm()
{
    TRACE("Entering CEx25eView::OnClockCreateAlarm\n");

    // the following code demonstrates use of
    //  GetIDsOfNames -- not required
    char   FAR* szMember = "CreateAlarm";
    DISPID dispid;
    VERIFY(m_clockc.m_lpDispatch->GetIDsOfNames(IID_NULL,
           &szMember, 1, 0, &dispid) == S_OK);
    TRACE("GetIDsOfNames: dispid = %d\n", dispid); 
    
    CAlarmDialog dlg;
    if (dlg.DoModal() == IDOK) {
      LPDISPATCH pAlarm = m_clockc.CreateAlarm(CVariant(0, 0,
              0, dlg.m_hours, dlg.m_minutes, dlg.m_seconds));
      m_alarmc.AttachDispatch(pAlarm);     // releases prior
                                           //  object!
      m_clockc.RefreshWin();
    
      CVariant vTime = m_alarmc.GetTime(); // test property
                                           //  access
      CVariant vStringTime;
      vTime.ChangeType(VT_BSTR, vStringTime);
      TRACE("Leaving CEx25eView::OnClockCreateAlarm -- time = %s\n",
             vStringTime.bstrVal);
    }
}

void CEx25eView::OnUpdateClockCreateAlarm(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_clockc.m_lpDispatch != NULL);
}

//    DLL    /////////////////////////////////////////////////////////////
void CEx25eView::OnDllGetData()
{
    m_dllControl.DisplayDialog();
    CVariant vData = m_dllControl.GetTextData();
    ASSERT(vData.vt == VT_BSTR);
    long lData = m_dllControl.GetLongData();
    TRACE("CEx25eView::OnDllGetData -- long = %ld, text = %s\n",
           lData, (const char FAR*) vData.bstrVal);
}

void CEx25eView::OnUpdateDllGetData(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_dllControl.m_lpDispatch != NULL);
}

void CEx25eView::OnDllLoad()
{
    BeginWaitCursor();
    VERIFY(m_dllControl.CreateDispatch("ex25c.auto") == TRUE);
    m_dllControl.SetTextData(CVariant("test"));  // testing
    m_dllControl.SetLongData(79L);               // testing
    EndWaitCursor();
}

void CEx25eView::OnUpdateDllLoad(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_dllControl.m_lpDispatch == NULL);
}

void CEx25eView::OnDllUnload()
{
    TRACE("Entering CEx25eView::OnDllUnload\n");
    m_dllControl.ReleaseDispatch();  // works!
}

void CEx25eView::OnUpdateDllUnload(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_dllControl.m_lpDispatch != NULL);
}

//   Market //////////////////////////////////////////////////////////////
void CEx25eView::OnMarketGetAverage()
{
    BeginWaitCursor();
    int nAvg = m_marketc.GetIndustrialsAverage(
               CVariant(1994, 8, 1, 0, 0, 0));
    TRACE("CEx25eView::OnMarketGetAverage -- nAvg = %d\n",
           nAvg);
    EndWaitCursor();
}

void CEx25eView::OnUpdateMarketGetAverage(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_marketc.m_lpDispatch != NULL);
}

void CEx25eView::OnMarketLoad()
{
    BeginWaitCursor();
    VERIFY(m_marketc.CreateDispatch("ex25b.market") == TRUE);
    EndWaitCursor();
}

void CEx25eView::OnUpdateMarketLoad(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_marketc.m_lpDispatch == NULL);
}

void CEx25eView::OnMarketUnload()
{
    BeginWaitCursor();
    m_marketc.ReleaseDispatch();
    EndWaitCursor();
}

void CEx25eView::OnUpdateMarketUnload(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(m_marketc.m_lpDispatch != NULL);
}
