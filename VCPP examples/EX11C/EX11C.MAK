# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX11C
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX11C\
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
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg olesvr olecli shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg olesvr olecli shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX11C.DEF
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
		EX11C.SBR \
		MAINFRM.SBR \
		EX11CDOC.SBR \
		EX11CVW.SBR \
		EX11CDLG.SBR


EX11C_RCDEP = c:\vcpp\ex11c\res\ex11c.ico \
	c:\vcpp\ex11c\res\ex11c.rc2


STDAFX_DEP = c:\vcpp\ex11c\stdafx.h


EX11C_DEP = c:\vcpp\ex11c\stdafx.h \
	c:\vcpp\ex11c\ex11c.h \
	c:\vcpp\ex11c\mainfrm.h \
	c:\vcpp\ex11c\ex11cdoc.h \
	c:\vcpp\ex11c\ex11cvw.h


MAINFRM_DEP = c:\vcpp\ex11c\stdafx.h \
	c:\vcpp\ex11c\ex11c.h \
	c:\vcpp\ex11c\mainfrm.h \
	c:\vcpp\ex11c\ex11cdlg.h


EX11CDOC_DEP = c:\vcpp\ex11c\stdafx.h \
	c:\vcpp\ex11c\ex11c.h \
	c:\vcpp\ex11c\ex11cdoc.h


EX11CVW_DEP = c:\vcpp\ex11c\stdafx.h \
	c:\vcpp\ex11c\ex11c.h \
	c:\vcpp\ex11c\ex11cdoc.h \
	c:\vcpp\ex11c\ex11cvw.h \
	c:\vcpp\ex11c\ex11cdlg.h


EX11CDLG_DEP = c:\vcpp\ex11c\stdafx.h \
	c:\vcpp\ex11c\ex11c.h \
	c:\vcpp\ex11c\ex11cdlg.h


all:	$(PROJ).EXE

EX11C.RES:	EX11C.RC $(EX11C_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX11C.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX11C.OBJ:	EX11C.CPP $(EX11C_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11C.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX11CDOC.OBJ:	EX11CDOC.CPP $(EX11CDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11CDOC.CPP

EX11CVW.OBJ:	EX11CVW.CPP $(EX11CVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11CVW.CPP

EX11CDLG.OBJ:	EX11CDLG.CPP $(EX11CDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX11CDLG.CPP


$(PROJ).EXE::	EX11C.RES

$(PROJ).EXE::	STDAFX.OBJ EX11C.OBJ MAINFRM.OBJ EX11CDOC.OBJ EX11CVW.OBJ EX11CDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX11C.OBJ +
MAINFRM.OBJ +
EX11CDOC.OBJ +
EX11CVW.OBJ +
EX11CDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX11C.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX11C.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX11C.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
