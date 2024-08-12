# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX08A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX08A\
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
DEFFILE = EX08A.DEF
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
		EX08A.SBR \
		MAINFRM.SBR \
		EX08ADOC.SBR \
		EX08AVW.SBR \
		EX08ADLG.SBR


EX08A_RCDEP = c:\vcpp\ex08a\res\ex08a.ico \
	c:\vcpp\ex08a\res\ex08a.rc2


STDAFX_DEP = c:\vcpp\ex08a\stdafx.h


EX08A_DEP = c:\vcpp\ex08a\stdafx.h \
	c:\vcpp\ex08a\ex08a.h \
	c:\vcpp\ex08a\mainfrm.h \
	c:\vcpp\ex08a\ex08adoc.h \
	c:\vcpp\ex08a\ex08avw.h


MAINFRM_DEP = c:\vcpp\ex08a\stdafx.h \
	c:\vcpp\ex08a\ex08a.h \
	c:\vcpp\ex08a\mainfrm.h


EX08ADOC_DEP = c:\vcpp\ex08a\stdafx.h \
	c:\vcpp\ex08a\ex08a.h \
	c:\vcpp\ex08a\ex08adoc.h


EX08AVW_DEP = c:\vcpp\ex08a\stdafx.h \
	c:\vcpp\ex08a\ex08a.h \
	c:\vcpp\ex08a\ex08adoc.h \
	c:\vcpp\ex08a\ex08adlg.h \
	c:\vcpp\ex08a\ex08avw.h


EX08ADLG_DEP = c:\vcpp\ex08a\stdafx.h \
	c:\vcpp\ex08a\ex08a.h \
	c:\vcpp\ex08a\ex08adlg.h


all:	$(PROJ).EXE

EX08A.RES:	EX08A.RC $(EX08A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX08A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX08A.OBJ:	EX08A.CPP $(EX08A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX08A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX08ADOC.OBJ:	EX08ADOC.CPP $(EX08ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX08ADOC.CPP

EX08AVW.OBJ:	EX08AVW.CPP $(EX08AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX08AVW.CPP

EX08ADLG.OBJ:	EX08ADLG.CPP $(EX08ADLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX08ADLG.CPP


$(PROJ).EXE::	EX08A.RES

$(PROJ).EXE::	STDAFX.OBJ EX08A.OBJ MAINFRM.OBJ EX08ADOC.OBJ EX08AVW.OBJ EX08ADLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX08A.OBJ +
MAINFRM.OBJ +
EX08ADOC.OBJ +
EX08AVW.OBJ +
EX08ADLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX08A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX08A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX08A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
