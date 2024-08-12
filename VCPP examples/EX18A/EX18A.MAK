# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX18A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX18A\
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
DEFFILE = EX18A.DEF
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
		EX18A.SBR \
		MAINFRM.SBR \
		POEMDOC.SBR \
		STRINGVW.SBR


EX18A_RCDEP = c:\vcpp\ex18a\res\ex18a.ico \
	c:\vcpp\ex18a\res\poemdoc.ico \
	c:\vcpp\ex18a\res\toolbar.bmp \
	c:\vcpp\ex18a\res\ex18a.rc2


STDAFX_DEP = c:\vcpp\ex18a\stdafx.h


EX18A_DEP = c:\vcpp\ex18a\stdafx.h \
	c:\vcpp\ex18a\ex18a.h \
	c:\vcpp\ex18a\mainfrm.h \
	c:\vcpp\ex18a\poemdoc.h \
	c:\vcpp\ex18a\stringvw.h


MAINFRM_DEP = c:\vcpp\ex18a\stdafx.h \
	c:\vcpp\ex18a\ex18a.h \
	c:\vcpp\ex18a\mainfrm.h


POEMDOC_DEP = c:\vcpp\ex18a\stdafx.h \
	c:\vcpp\ex18a\ex18a.h \
	c:\vcpp\ex18a\poemdoc.h


STRINGVW_DEP = c:\vcpp\ex18a\stdafx.h \
	c:\vcpp\ex18a\ex18a.h \
	c:\vcpp\ex18a\poemdoc.h \
	c:\vcpp\ex18a\stringvw.h


all:	$(PROJ).EXE

EX18A.RES:	EX18A.RC $(EX18A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX18A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX18A.OBJ:	EX18A.CPP $(EX18A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX18A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

POEMDOC.OBJ:	POEMDOC.CPP $(POEMDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c POEMDOC.CPP

STRINGVW.OBJ:	STRINGVW.CPP $(STRINGVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STRINGVW.CPP


$(PROJ).EXE::	EX18A.RES

$(PROJ).EXE::	STDAFX.OBJ EX18A.OBJ MAINFRM.OBJ POEMDOC.OBJ STRINGVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX18A.OBJ +
MAINFRM.OBJ +
POEMDOC.OBJ +
STRINGVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX18A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX18A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX18A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
