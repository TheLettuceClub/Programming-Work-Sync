# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX26B
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX26B\
USEMFC = 0
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
CFLAGS_D_WEXE = /W3 /AL /Od /D "_DEBUG" /D "_AFXDLL" /GA /GEf 
CFLAGS_R_WEXE = /nologo /W3 /AL /Od /D "_AFXDLL" /D "_AFXDLL" /GA /GEf 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL             
LIBS_D_WEXE = mfc250d ex26ad oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WEXE = mfc250 ex26a oldnames libw llibcew commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = EX26B.DEF
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
		EX26BDOC.SBR \
		EX26BVW.SBR \
		MAINFRM.SBR \
		EX26B.SBR \
		STUDLG.SBR


STDAFX_DEP = c:\vcpp\ex26b\stdafx.h


EX26BDOC_DEP = c:\vcpp\ex26b\stdafx.h \
	c:\vcpp\ex26b\ex26b.h \
	c:\vcpp\ex26b\student.h \
	c:\vcpp\ex26b\ex26bdoc.h


EX26BVW_DEP = c:\vcpp\ex26b\stdafx.h \
	c:\vcpp\ex26b\student.h \
	c:\vcpp\ex26b\ex26bdoc.h \
	c:\vcpp\ex26b\rowview.h \
	c:\vcpp\ex26b\ex26bvw.h \
	c:\vcpp\ex26b\studlg.h


MAINFRM_DEP = c:\vcpp\ex26b\stdafx.h \
	c:\vcpp\ex26b\ex26b.h \
	c:\vcpp\ex26b\persist.h \
	c:\vcpp\ex26b\mainfrm.h


EX26B_DEP = c:\vcpp\ex26b\stdafx.h \
	c:\vcpp\ex26b\ex26b.h \
	c:\vcpp\ex26b\persist.h \
	c:\vcpp\ex26b\mainfrm.h \
	c:\vcpp\ex26b\rowview.h \
	c:\vcpp\ex26b\student.h \
	c:\vcpp\ex26b\ex26bdoc.h \
	c:\vcpp\ex26b\ex26bvw.h


STUDLG_DEP = c:\vcpp\ex26b\stdafx.h \
	c:\vcpp\ex26b\studlg.h


EX26B_RCDEP = c:\vcpp\ex26b\res\ex26b.ico \
	c:\vcpp\ex26b\res\ex26b.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX26BDOC.OBJ:	EX26BDOC.CPP $(EX26BDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX26BDOC.CPP

EX26BVW.OBJ:	EX26BVW.CPP $(EX26BVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX26BVW.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX26B.OBJ:	EX26B.CPP $(EX26B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX26B.CPP

STUDLG.OBJ:	STUDLG.CPP $(STUDLG_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c STUDLG.CPP

EX26B.RES:	EX26B.RC $(EX26B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX26B.RC


$(PROJ).EXE::	EX26B.RES

$(PROJ).EXE::	STDAFX.OBJ EX26BDOC.OBJ EX26BVW.OBJ MAINFRM.OBJ EX26B.OBJ STUDLG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX26BDOC.OBJ +
EX26BVW.OBJ +
MAINFRM.OBJ +
EX26B.OBJ +
STUDLG.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX26B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX26B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX26B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
