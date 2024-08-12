# Microsoft Visual C++ generated build script - Do not modify

PROJ = MATPLAN
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX21A\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /f- /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10204 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /MAP  
LIBS_D_WEXE = oldnames libw mafxcwd mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw mlibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = MATPLAN.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		MATDLG.SBR \
		MATDOC.SBR \
		MATPIECE.SBR \
		MATPLAN.SBR \
		MAINFRM.SBR \
		LISTVIEW.SBR \
		PLANVIEW.SBR


STDAFX_DEP = c:\vcpp\ex21a\stdafx.h


MATDLG_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matpiece.h \
	c:\vcpp\ex21a\matdlg.h


MATDOC_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matpiece.h \
	c:\vcpp\ex21a\matdoc.h


MATPIECE_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matpiece.h


MATPLAN_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matplan.h \
	c:\vcpp\ex21a\matpiece.h \
	c:\vcpp\ex21a\matdlg.h \
	c:\vcpp\ex21a\mainfrm.h \
	c:\vcpp\ex21a\matdoc.h \
	c:\vcpp\ex21a\listview.h \
	c:\vcpp\ex21a\planview.h


MAINFRM_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matplan.h \
	c:\vcpp\ex21a\mainfrm.h


MATPLAN_RCDEP = c:\vcpp\ex21a\res\matplan.ico \
	c:\vcpp\ex21a\res\matdoc.ico \
	c:\vcpp\ex21a\res\matplan.rc2


LISTVIEW_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matpiece.h \
	c:\vcpp\ex21a\matdlg.h \
	c:\vcpp\ex21a\matdoc.h \
	c:\vcpp\ex21a\listview.h


PLANVIEW_DEP = c:\vcpp\ex21a\stdafx.h \
	c:\vcpp\ex21a\matpiece.h \
	c:\vcpp\ex21a\matdoc.h \
	c:\vcpp\ex21a\planview.h


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MATDLG.OBJ:	MATDLG.CPP $(MATDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATDLG.CPP

MATDOC.OBJ:	MATDOC.CPP $(MATDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATDOC.CPP

MATPIECE.OBJ:	MATPIECE.CPP $(MATPIECE_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATPIECE.CPP

MATPLAN.OBJ:	MATPLAN.CPP $(MATPLAN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MATPLAN.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

MATPLAN.RES:	MATPLAN.RC $(MATPLAN_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r MATPLAN.RC

LISTVIEW.OBJ:	LISTVIEW.CPP $(LISTVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c LISTVIEW.CPP

PLANVIEW.OBJ:	PLANVIEW.CPP $(PLANVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PLANVIEW.CPP


$(PROJ).EXE::	MATPLAN.RES

$(PROJ).EXE::	STDAFX.OBJ MATDLG.OBJ MATDOC.OBJ MATPIECE.OBJ MATPLAN.OBJ MAINFRM.OBJ \
	LISTVIEW.OBJ PLANVIEW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MATDLG.OBJ +
MATDOC.OBJ +
MATPIECE.OBJ +
MATPLAN.OBJ +
MAINFRM.OBJ +
LISTVIEW.OBJ +
PLANVIEW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) MATPLAN.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	MATPLAN.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) MATPLAN.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
