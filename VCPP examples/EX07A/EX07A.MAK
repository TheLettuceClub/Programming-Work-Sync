# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX07A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX07A\
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
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew commdlg olesvr olecli shell 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew commdlg olesvr olecli shell 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX07A.DEF
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
		EX07A.SBR \
		MAINFRM.SBR \
		EX07ADOC.SBR \
		EX07AVW.SBR \
		EX07ADLG.SBR


EX07A_RCDEP = c:\vcpp\ex07a\res\ex07a.ico \
	c:\vcpp\ex07a\res\ex07a.rc2


STDAFX_DEP = c:\vcpp\ex07a\stdafx.h


EX07A_DEP = c:\vcpp\ex07a\stdafx.h \
	c:\vcpp\ex07a\ex07a.h \
	c:\vcpp\ex07a\mainfrm.h \
	c:\vcpp\ex07a\ex07adoc.h \
	c:\vcpp\ex07a\ex07avw.h


MAINFRM_DEP = c:\vcpp\ex07a\stdafx.h \
	c:\vcpp\ex07a\ex07a.h \
	c:\vcpp\ex07a\mainfrm.h


EX07ADOC_DEP = c:\vcpp\ex07a\stdafx.h \
	c:\vcpp\ex07a\ex07a.h \
	c:\vcpp\ex07a\ex07adoc.h


EX07AVW_DEP = c:\vcpp\ex07a\stdafx.h \
	c:\vcpp\ex07a\ex07a.h \
	c:\vcpp\ex07a\ex07adoc.h \
	c:\vcpp\ex07a\ex07avw.h \
	c:\vcpp\ex07a\ex07adlg.h


EX07ADLG_DEP = c:\vcpp\ex07a\stdafx.h \
	c:\vcpp\ex07a\ex07a.h \
	c:\vcpp\ex07a\ex07adlg.h


all:	$(PROJ).EXE

EX07A.RES:	EX07A.RC $(EX07A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX07A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX07A.OBJ:	EX07A.CPP $(EX07A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX07ADOC.OBJ:	EX07ADOC.CPP $(EX07ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07ADOC.CPP

EX07AVW.OBJ:	EX07AVW.CPP $(EX07AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07AVW.CPP

EX07ADLG.OBJ:	EX07ADLG.CPP $(EX07ADLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX07ADLG.CPP


$(PROJ).EXE::	EX07A.RES

$(PROJ).EXE::	STDAFX.OBJ EX07A.OBJ MAINFRM.OBJ EX07ADOC.OBJ EX07AVW.OBJ EX07ADLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX07A.OBJ +
MAINFRM.OBJ +
EX07ADOC.OBJ +
EX07AVW.OBJ +
EX07ADLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX07A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX07A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX07A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
