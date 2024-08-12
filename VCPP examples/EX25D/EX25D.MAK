# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX25D
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX25D\
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
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /FR /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui odbc commdlg.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui odbc commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX25D.DEF
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
		MAINFRM.SBR \
		CVARIANT.SBR \
		ALARM.SBR \
		EX25D.SBR \
		EX25DDOC.SBR \
		EX25DVW.SBR


STDAFX_DEP = c:\vcpp\ex25d\stdafx.h


MAINFRM_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\mainfrm.h


CVARIANT_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\cvariant.h


ALARM_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\alarm.h \
	c:\vcpp\ex25d\cvariant.h


EX25D_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\ex25d.h \
	c:\vcpp\ex25d\mainfrm.h \
	c:\vcpp\ex25d\about.h \
	c:\vcpp\ex25d\ex25ddoc.h \
	c:\vcpp\ex25d\cvariant.h \
	c:\vcpp\ex25d\ex25dvw.h


EX25DDOC_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\ex25d.h \
	c:\vcpp\ex25d\mainfrm.h \
	c:\vcpp\ex25d\about.h \
	c:\vcpp\ex25d\ex25ddoc.h \
	c:\vcpp\ex25d\cvariant.h \
	c:\vcpp\ex25d\alarm.h


EX25DVW_DEP = c:\vcpp\ex25d\stdafx.h \
	c:\vcpp\ex25d\ex25d.h \
	c:\vcpp\ex25d\ex25ddoc.h \
	c:\vcpp\ex25d\cvariant.h \
	c:\vcpp\ex25d\ex25dvw.h \
	c:\vcpp\ex25d\alarm.h


EX25D_RCDEP = c:\vcpp\ex25d\res\ex25d.ico \
	c:\vcpp\ex25d\res\ex25d.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

CVARIANT.OBJ:	CVARIANT.CPP $(CVARIANT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CVARIANT.CPP

ALARM.OBJ:	ALARM.CPP $(ALARM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ALARM.CPP

EX25D.OBJ:	EX25D.CPP $(EX25D_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25D.CPP

EX25DDOC.OBJ:	EX25DDOC.CPP $(EX25DDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25DDOC.CPP

EX25DVW.OBJ:	EX25DVW.CPP $(EX25DVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25DVW.CPP

EX25D.RES:	EX25D.RC $(EX25D_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX25D.RC


$(PROJ).EXE::	EX25D.RES

$(PROJ).EXE::	STDAFX.OBJ MAINFRM.OBJ CVARIANT.OBJ ALARM.OBJ EX25D.OBJ EX25DDOC.OBJ \
	EX25DVW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
MAINFRM.OBJ +
CVARIANT.OBJ +
ALARM.OBJ +
EX25D.OBJ +
EX25DDOC.OBJ +
EX25DVW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
J:\+
C:\MSVC15\LIB\+
C:\MSVC15\MFC\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX25D.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX25D.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX25D.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
