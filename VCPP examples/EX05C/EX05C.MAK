# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX05C
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX05C\
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
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX05C.DEF
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
		EX05C.SBR \
		MAINFRM.SBR \
		EX05CDOC.SBR \
		EX05CVW.SBR


EX05C_RCDEP = c:\vcpp\ex05c\res\ex05c.ico \
	c:\vcpp\ex05c\res\toolbar.bmp \
	c:\vcpp\ex05c\res\ex05c.rc2


STDAFX_DEP = c:\vcpp\ex05c\stdafx.h


EX05C_DEP = c:\vcpp\ex05c\stdafx.h \
	c:\vcpp\ex05c\ex05c.h \
	c:\vcpp\ex05c\mainfrm.h \
	c:\vcpp\ex05c\ex05cdoc.h \
	c:\vcpp\ex05c\ex05cvw.h


MAINFRM_DEP = c:\vcpp\ex05c\stdafx.h \
	c:\vcpp\ex05c\ex05c.h \
	c:\vcpp\ex05c\mainfrm.h


EX05CDOC_DEP = c:\vcpp\ex05c\stdafx.h \
	c:\vcpp\ex05c\ex05c.h \
	c:\vcpp\ex05c\ex05cdoc.h


EX05CVW_DEP = c:\vcpp\ex05c\stdafx.h \
	c:\vcpp\ex05c\ex05c.h \
	c:\vcpp\ex05c\ex05cdoc.h \
	c:\vcpp\ex05c\ex05cvw.h


all:	$(PROJ).EXE

EX05C.RES:	EX05C.RC $(EX05C_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX05C.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX05C.OBJ:	EX05C.CPP $(EX05C_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05C.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX05CDOC.OBJ:	EX05CDOC.CPP $(EX05CDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05CDOC.CPP

EX05CVW.OBJ:	EX05CVW.CPP $(EX05CVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX05CVW.CPP


$(PROJ).EXE::	EX05C.RES

$(PROJ).EXE::	STDAFX.OBJ EX05C.OBJ MAINFRM.OBJ EX05CDOC.OBJ EX05CVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX05C.OBJ +
MAINFRM.OBJ +
EX05CDOC.OBJ +
EX05CVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX05C.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX05C.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX05C.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
