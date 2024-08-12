; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTableSelect
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ex24a.h"
VbxHeaderFile=ex24a.h
VbxImplementationFile=ex24a.cpp
LastPage=0

ClassCount=8
Class1=CColumns
Class2=CEx24aApp
Class3=CAboutDlg
Class4=CEx24aDoc
Class5=CEx24aView
Class6=CMainFrame
Class7=CRowView

ResourceCount=5
Resource1=IDD_QUERY_BAR
Resource2=IDR_EX24ATYPE
Resource3=IDD_ABOUTBOX
Resource4=IDR_MAINFRAME
Class8=CTableSelect
Resource5=IDD_TABLE_SELECT

[CLS:CColumns]
Type=0
HeaderFile=columnst.h
ImplementationFile=columnst.cpp

[CLS:CEx24aApp]
Type=0
HeaderFile=ex24a.h
ImplementationFile=ex24a.cpp

[CLS:CAboutDlg]
Type=0
HeaderFile=ex24a.cpp
ImplementationFile=ex24a.cpp

[CLS:CEx24aDoc]
Type=0
HeaderFile=ex24adoc.h
ImplementationFile=ex24adoc.cpp

[CLS:CEx24aView]
Type=0
HeaderFile=ex24avw.h
ImplementationFile=ex24avw.cpp

[CLS:CMainFrame]
Type=0
HeaderFile=mainfrm.h
ImplementationFile=mainfrm.cpp

[CLS:CRowView]
Type=0
HeaderFile=rowview.h
ImplementationFile=rowview.cpp

[DB:CColumns]
DB=1

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_EX24ATYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_CONNECT
Command10=ID_FILE_DISCONNECT
Command11=ID_FILE_MRU_FILE1
Command12=ID_APP_EXIT
Command13=ID_EDIT_UNDO
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_WINDOW_NEW
Command20=ID_WINDOW_CASCADE
Command21=ID_WINDOW_TILE_HORZ
Command22=ID_WINDOW_ARRANGE
Command23=ID_APP_ABOUT
CommandCount=23

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_QUERY_TABLES
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_QUERY_BAR]
Type=1
Class=?
ControlCount=5
Control1=IDC_REQUERY,button,1342242817
Control2=IDC_SORT,edit,1352728644
Control3=IDC_FILTER,edit,1352728644
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352

[DB:CEx24Set]
DB=1
ColumnCount=4
Column1=SHNUMBER,1,12,1
Column2=LASTNAME,1,20,1
Column3=FIRSTNAME,1,20,1
Column4=ZIPCODE,1,5,1

[DLG:IDD_TABLE_SELECT]
Type=1
Class=CTableSelect
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728835

[CLS:CTableSelect]
Type=0
HeaderFile=tablesel.h
ImplementationFile=tablesel.cpp
Filter=D
LastObject=IDC_LIST1

