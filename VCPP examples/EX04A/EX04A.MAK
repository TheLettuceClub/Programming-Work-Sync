# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX04A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX04A\
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
DEFFILE = EX04A.DEF
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
		EX04A.SBR \
		MAINFRM.SBR \
		EX04ADOC.SBR \
		EX04AVW.SBR


EX04A_RCDEP = c:\vcpp\ex04a\res\ex04a.ico \
	c:\vcpp\ex04a\res\toolbar.bmp \
	c:\vcpp\ex04a\res\ex04a.rc2


STDAFX_DEP = c:\vcpp\ex04a\stdafx.h


EX04A_DEP = c:\vcpp\ex04a\stdafx.h \
	c:\vcpp\ex04a\ex04a.h \
	c:\vcpp\ex04a\mainfrm.h \
	c:\vcpp\ex04a\ex04adoc.h \
	c:\vcpp\ex04a\ex04avw.h


MAINFRM_DEP = c:\vcpp\ex04a\stdafx.h \
	c:\vcpp\ex04a\ex04a.h \
	c:\vcpp\ex04a\mainfrm.h


EX04ADOC_DEP = c:\vcpp\ex04a\stdafx.h \
	c:\vcpp\ex04a\ex04a.h \
	c:\vcpp\ex04a\ex04adoc.h


EX04AVW_DEP = c:\vcpp\ex04a\stdafx.h \
	c:\vcpp\ex04a\ex04a.h \
	c:\vcpp\ex04a\ex04adoc.h \
	c:\vcpp\ex04a\ex04avw.h


all:	$(PROJ).EXE

EX04A.RES:	EX04A.RC $(EX04A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX04A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX04A.OBJ:	EX04A.CPP $(EX04A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX04ADOC.OBJ:	EX04ADOC.CPP $(EX04ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04ADOC.CPP

EX04AVW.OBJ:	EX04AVW.CPP $(EX04AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX04AVW.CPP


$(PROJ).EXE::	EX04A.RES

$(PROJ).EXE::	STDAFX.OBJ EX04A.OBJ MAINFRM.OBJ EX04ADOC.OBJ EX04AVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX04A.OBJ +
MAINFRM.OBJ +
EX04ADOC.OBJ +
EX04AVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX04A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX04A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX04A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
