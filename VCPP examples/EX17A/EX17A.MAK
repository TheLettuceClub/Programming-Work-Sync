# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX17A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = 
R_RCDEFINES = 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX17A\
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
CFLAGS_D_WEXE = /nologo /Gs /G2 /Zp1 /W3 /AM /Od /D "_DEBUG" /GA /Fp"..\stdafx.pch" 
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA /Fp"..\stdafx.pch" 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw mafxcwd commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = oldnames libw mafxcw commdlg shell olecli olesvr mlibcew libw commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo /z 
RESFLAGS = /nologo /t 
RUNFLAGS = 
DEFFILE = EX17A.DEF
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
		EX17A.SBR \
		MAINFRM.SBR \
		STUDOC.SBR \
		STUVIEW.SBR \
		STUDENT.SBR


EX17A_RCDEP = c:\vcpp\ex17a\res\ex17a.ico \
	c:\vcpp\ex17a\res\studoc.ico \
	c:\vcpp\ex17a\res\ex17a.rc2


STDAFX_DEP = c:\vcpp\ex17a\stdafx.h


EX17A_DEP = c:\vcpp\ex17a\stdafx.h \
	c:\vcpp\ex17a\ex17a.h \
	c:\vcpp\ex17a\mainfrm.h \
	c:\vcpp\ex17a\student.h \
	c:\vcpp\ex17a\studoc.h \
	c:\vcpp\ex17a\stuview.h


MAINFRM_DEP = c:\vcpp\ex17a\stdafx.h \
	c:\vcpp\ex17a\ex17a.h \
	c:\vcpp\ex17a\mainfrm.h


STUDOC_DEP = c:\vcpp\ex17a\stdafx.h \
	c:\vcpp\ex17a\studoc.h


STUVIEW_DEP = c:\vcpp\ex17a\stdafx.h \
	c:\vcpp\ex17a\student.h \
	c:\vcpp\ex17a\studoc.h \
	c:\vcpp\ex17a\stuview.h


STUDENT_DEP = c:\vcpp\ex17a\stdafx.h \
	c:\vcpp\ex17a\student.h


all:	$(PROJ).EXE

EX17A.RES:	EX17A.RC $(EX17A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX17A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX17A.OBJ:	EX17A.CPP $(EX17A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX17A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

STUDOC.OBJ:	STUDOC.CPP $(STUDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDOC.CPP

STUVIEW.OBJ:	STUVIEW.CPP $(STUVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUVIEW.CPP

STUDENT.OBJ:	STUDENT.CPP $(STUDENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDENT.CPP


$(PROJ).EXE::	EX17A.RES

$(PROJ).EXE::	STDAFX.OBJ EX17A.OBJ MAINFRM.OBJ STUDOC.OBJ STUVIEW.OBJ STUDENT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX17A.OBJ +
MAINFRM.OBJ +
STUDOC.OBJ +
STUVIEW.OBJ +
STUDENT.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX17A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX17A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX17A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
