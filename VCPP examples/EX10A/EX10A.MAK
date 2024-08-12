# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX10A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX10A\
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
DEFFILE = EX10A.DEF
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
		EX10A.SBR \
		MAINFRM.SBR \
		EX10ADOC.SBR \
		EX10AVW.SBR


EX10A_RCDEP = c:\vcpp\ex10a\res\ex10a.ico \
	c:\vcpp\ex10a\hlp\appexit.bmp \
	c:\vcpp\ex10a\res\ex10a.rc2


STDAFX_DEP = c:\vcpp\ex10a\stdafx.h


EX10A_DEP = c:\vcpp\ex10a\stdafx.h \
	c:\vcpp\ex10a\ex10a.h \
	c:\vcpp\ex10a\mainfrm.h \
	c:\vcpp\ex10a\ex10adoc.h \
	c:\vcpp\ex10a\ex10avw.h


MAINFRM_DEP = c:\vcpp\ex10a\stdafx.h \
	c:\vcpp\ex10a\ex10a.h \
	c:\vcpp\ex10a\mainfrm.h


EX10ADOC_DEP = c:\vcpp\ex10a\stdafx.h \
	c:\vcpp\ex10a\ex10a.h \
	c:\vcpp\ex10a\ex10adoc.h


EX10AVW_DEP = c:\vcpp\ex10a\stdafx.h \
	c:\vcpp\ex10a\ex10a.h \
	c:\vcpp\ex10a\ex10adoc.h \
	c:\vcpp\ex10a\ex10avw.h


all:	$(PROJ).EXE

EX10A.RES:	EX10A.RC $(EX10A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX10A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX10A.OBJ:	EX10A.CPP $(EX10A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX10ADOC.OBJ:	EX10ADOC.CPP $(EX10ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10ADOC.CPP

EX10AVW.OBJ:	EX10AVW.CPP $(EX10AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX10AVW.CPP


$(PROJ).EXE::	EX10A.RES

$(PROJ).EXE::	STDAFX.OBJ EX10A.OBJ MAINFRM.OBJ EX10ADOC.OBJ EX10AVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX10A.OBJ +
MAINFRM.OBJ +
EX10ADOC.OBJ +
EX10AVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX10A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX10A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX10A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
