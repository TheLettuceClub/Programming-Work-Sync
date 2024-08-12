# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX13A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX13A\
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
DEFFILE = EX13A.DEF
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
		EX13A.SBR \
		MAINFRM.SBR \
		EX13ADOC.SBR \
		EX13AVW.SBR


EX13A_RCDEP = c:\vcpp\ex13a\res\ex13a.ico \
	c:\vcpp\ex13a\res\idr_main.bmp \
	c:\vcpp\ex13a\res\ex13a.rc2


STDAFX_DEP = c:\vcpp\ex13a\stdafx.h


EX13A_DEP = c:\vcpp\ex13a\stdafx.h \
	c:\vcpp\ex13a\ex13a.h \
	c:\vcpp\ex13a\mainfrm.h \
	c:\vcpp\ex13a\ex13adoc.h \
	c:\vcpp\ex13a\ex13avw.h


MAINFRM_DEP = c:\vcpp\ex13a\stdafx.h \
	c:\vcpp\ex13a\ex13a.h \
	c:\vcpp\ex13a\mainfrm.h


EX13ADOC_DEP = c:\vcpp\ex13a\stdafx.h \
	c:\vcpp\ex13a\ex13a.h \
	c:\vcpp\ex13a\ex13adoc.h


EX13AVW_DEP = c:\vcpp\ex13a\stdafx.h \
	c:\vcpp\ex13a\ex13a.h \
	c:\vcpp\ex13a\ex13adoc.h \
	c:\vcpp\ex13a\ex13avw.h


all:	$(PROJ).EXE

EX13A.RES:	EX13A.RC $(EX13A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX13A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX13A.OBJ:	EX13A.CPP $(EX13A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX13ADOC.OBJ:	EX13ADOC.CPP $(EX13ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13ADOC.CPP

EX13AVW.OBJ:	EX13AVW.CPP $(EX13AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX13AVW.CPP


$(PROJ).EXE::	EX13A.RES

$(PROJ).EXE::	STDAFX.OBJ EX13A.OBJ MAINFRM.OBJ EX13ADOC.OBJ EX13AVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX13A.OBJ +
MAINFRM.OBJ +
EX13ADOC.OBJ +
EX13AVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX13A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX13A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX13A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
