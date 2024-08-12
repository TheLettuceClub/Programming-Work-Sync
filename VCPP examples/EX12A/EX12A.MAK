# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX12A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX12A\
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
DEFFILE = EX12A.DEF
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
		EX12A.SBR \
		MAINFRM.SBR \
		EX12ADOC.SBR \
		EX12AVW.SBR


EX12A_RCDEP = c:\vcpp\ex12a\res\ex12a.ico \
	c:\vcpp\ex12a\res\ex12a.rc2


STDAFX_DEP = c:\vcpp\ex12a\stdafx.h


EX12A_DEP = c:\vcpp\ex12a\stdafx.h \
	c:\vcpp\ex12a\ex12a.h \
	c:\vcpp\ex12a\mainfrm.h \
	c:\vcpp\ex12a\ex12adoc.h \
	c:\vcpp\ex12a\ex12avw.h


MAINFRM_DEP = c:\vcpp\ex12a\stdafx.h \
	c:\vcpp\ex12a\ex12a.h \
	c:\vcpp\ex12a\mainfrm.h


EX12ADOC_DEP = c:\vcpp\ex12a\stdafx.h \
	c:\vcpp\ex12a\ex12a.h \
	c:\vcpp\ex12a\ex12adoc.h


EX12AVW_DEP = c:\vcpp\ex12a\stdafx.h \
	c:\vcpp\ex12a\ex12a.h \
	c:\vcpp\ex12a\ex12adoc.h \
	c:\vcpp\ex12a\ex12avw.h


all:	$(PROJ).EXE

EX12A.RES:	EX12A.RC $(EX12A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX12A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX12A.OBJ:	EX12A.CPP $(EX12A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX12ADOC.OBJ:	EX12ADOC.CPP $(EX12ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12ADOC.CPP

EX12AVW.OBJ:	EX12AVW.CPP $(EX12AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX12AVW.CPP


$(PROJ).EXE::	EX12A.RES

$(PROJ).EXE::	STDAFX.OBJ EX12A.OBJ MAINFRM.OBJ EX12ADOC.OBJ EX12AVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX12A.OBJ +
MAINFRM.OBJ +
EX12ADOC.OBJ +
EX12AVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX12A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX12A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX12A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
