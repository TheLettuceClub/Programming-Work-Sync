# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX24B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX24B\
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
CFLAGS_R_WEXE = /nologo /f- /G2 /W3 /AL /O1 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:8192 /SEG:256 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:8192 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd mlibcew odbc commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw lafxcw llibcew odbc commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = EX24B.DEF
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
		MAINFRM.SBR \
		ROWVIEW.SBR \
		COLUMNST.SBR \
		TABLESEL.SBR \
		EX24B.SBR \
		EX24BDOC.SBR \
		EX24BSET.SBR \
		EX24BVW.SBR \
		TABLESET.SBR


STDAFX_DEP = c:\vcpp\ex24b\stdafx.h


MAINFRM_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\ex24b.h \
	c:\vcpp\ex24b\mainfrm.h


ROWVIEW_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\rowview.h


COLUMNST_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\columnst.h


TABLESEL_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\tablesel.h \
	c:\vcpp\ex24b\tableset.h


EX24B_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\ex24b.h \
	c:\vcpp\ex24b\mainfrm.h \
	c:\vcpp\ex24b\ex24bset.h \
	c:\vcpp\ex24b\ex24bdoc.h \
	c:\vcpp\ex24b\rowview.h \
	c:\vcpp\ex24b\ex24bvw.h


EX24BDOC_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\ex24b.h \
	c:\vcpp\ex24b\ex24bset.h \
	c:\vcpp\ex24b\ex24bdoc.h \
	c:\vcpp\ex24b\tablesel.h


EX24BSET_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\ex24b.h \
	c:\vcpp\ex24b\ex24bset.h \
	c:\vcpp\ex24b\columnst.h


EX24BVW_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\ex24b.h \
	c:\vcpp\ex24b\ex24bset.h \
	c:\vcpp\ex24b\ex24bdoc.h \
	c:\vcpp\ex24b\rowview.h \
	c:\vcpp\ex24b\ex24bvw.h


TABLESET_DEP = c:\vcpp\ex24b\stdafx.h \
	c:\vcpp\ex24b\tableset.h


EX24B_RCDEP = c:\vcpp\ex24b\res\ex24b.ico \
	c:\vcpp\ex24b\res\ex24bdoc.ico \
	c:\vcpp\ex24b\res\ex24b.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

ROWVIEW.OBJ:	ROWVIEW.CPP $(ROWVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ROWVIEW.CPP

COLUMNST.OBJ:	COLUMNST.CPP $(COLUMNST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c COLUMNST.CPP

TABLESEL.OBJ:	TABLESEL.CPP $(TABLESEL_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TABLESEL.CPP

EX24B.OBJ:	EX24B.CPP $(EX24B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24B.CPP

EX24BDOC.OBJ:	EX24BDOC.CPP $(EX24BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24BDOC.CPP

EX24BSET.OBJ:	EX24BSET.CPP $(EX24BSET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24BSET.CPP

EX24BVW.OBJ:	EX24BVW.CPP $(EX24BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24BVW.CPP

TABLESET.OBJ:	TABLESET.CPP $(TABLESET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TABLESET.CPP

EX24B.RES:	EX24B.RC $(EX24B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX24B.RC


$(PROJ).EXE::	EX24B.RES

$(PROJ).EXE::	STDAFX.OBJ MAINFRM.OBJ ROWVIEW.OBJ COLUMNST.OBJ TABLESEL.OBJ EX24B.OBJ \
	EX24BDOC.OBJ EX24BSET.OBJ EX24BVW.OBJ TABLESET.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MAINFRM.OBJ +
ROWVIEW.OBJ +
COLUMNST.OBJ +
TABLESEL.OBJ +
EX24B.OBJ +
EX24BDOC.OBJ +
EX24BSET.OBJ +
EX24BVW.OBJ +
TABLESET.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX24B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX24B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX24B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
