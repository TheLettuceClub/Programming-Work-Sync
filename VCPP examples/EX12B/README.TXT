========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : EX12B
========================================================================

AppWizard has generated this EX12B application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your EX12B application.


EX12B.MAK
    This project file is compatible with the Visual C++ Workbench.

    It is also compatible with the NMAKE program provided with the
    Professional Edition of Visual C++.

    To build a debug version of the program from the MS-DOS prompt, type
	nmake DEBUG=1 /f EX12B.MAK
    or to build a release version of the program, type
	nmake DEBUG=0 /f EX12B.MAK

EX12B.H
    This is the main include file for the application.  It includes other
    project specific includes (including RESOURCE.H) and declares the
    CEx12bApp application class.

EX12B.CPP
    This is the main application source file that contains the application
    class CEx12bApp.

EX12B.RC
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited with App Studio.

RES\EX12B.ICO
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file EX12B.RC.

RES\EX12B.RC2
    This file contains resources that are not edited by App Studio.  Initially
    this contains a VERSIONINFO resource that you can customize for your
    application.  You should place other non-App Studio editable resources
    in this file.

EX12B.DEF
    This file contains information about the application that must be
    provided to run with Microsoft Windows.  It defines parameters
    such as the name and description of the application, and the size
    of the initial local heap.  The numbers in this file are typical
    for applications developed with the Microsoft Foundation Class Library.
    The default stack size can be adjusted by editing the project file.

EX12B.CLW
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to generate and edit message maps and dialog data
    maps and to generate prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MAINFRM.H, MAINFRM.CPP
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

RES\TOOLBAR.BMP
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the
    CMainFrame class.  Edit this toolbar bitmap along with the
    array in MAINFRM.CPP to add more toolbar buttons.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

EX12BDOC.H, EX12BDOC.CPP - the document
    These files contain your CEx12bDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CEx12bDoc::Serialize).

EX12BVW.H, EX12BVW.CPP - the view of the document
    These files contain your CEx12bView class.
    CEx12bView objects are used to view CEx12bDoc objects.

    




/////////////////////////////////////////////////////////////////////////////
Other standard files:

STDAFX.H, STDAFX.CPP
    These files are used to build a precompiled header (PCH) file
    named STDAFX.PCH and a precompiled types (PCT) file named STDAFX.OBJ.

RESOURCE.H
    This is the standard header file, which defines new resource IDs.
    App Studio reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
