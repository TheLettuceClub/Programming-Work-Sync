# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX25B
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX25B\
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
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui commdlg.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew compobj storage ole2 ole2disp ole2nls mfcoleui odbc commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX25B.DEF
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
		EX25B.SBR \
		MARKET.SBR


EX25B_RCDEP = c:\vcpp\ex25b\res\ex25b.ico \
	c:\vcpp\ex25b\res\ex25b.rc2


STDAFX_DEP = c:\vcpp\ex25b\stdafx.h


EX25B_DEP = c:\vcpp\ex25b\stdafx.h \
	c:\vcpp\ex25b\ex25b.h


MARKET_DEP = c:\vcpp\ex25b\stdafx.h \
	c:\vcpp\ex25b\ex25b.h \
	c:\vcpp\ex25b\market.h


all:	$(PROJ).EXE

EX25B.RES:	EX25B.RC $(EX25B_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX25B.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX25B.OBJ:	EX25B.CPP $(EX25B_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX25B.CPP

MARKET.OBJ:	MARKET.CPP $(MARKET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MARKET.CPP


$(PROJ).EXE::	EX25B.RES

$(PROJ).EXE::	STDAFX.OBJ EX25B.OBJ MARKET.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX25B.OBJ +
MARKET.OBJ +
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
	$(RC) $(RESFLAGS) EX25B.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX25B.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX25B.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
