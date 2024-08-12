# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX24A
DEBUG = 1
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX24A\
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
CFLAGS_R_WEXE = /nologo /Gs /G2 /W3 /AM /O1 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:10240 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = mafxcwd oldnames libw mlibcew odbc commdlg.lib shell.lib 
LIBS_R_WEXE = mafxcw oldnames libw mlibcew odbc commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = EX24A.DEF
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
		EX24A.SBR \
		MAINFRM.SBR \
		EX24ADOC.SBR \
		EX24AVW.SBR \
		EX24ASET.SBR


EX24A_RCDEP = c:\vcpp\ex24a\res\ex24a.ico \
	c:\vcpp\ex24a\res\toolbar.bmp \
	c:\vcpp\ex24a\res\ex24a.rc2


STDAFX_DEP = c:\vcpp\ex24a\stdafx.h


EX24A_DEP = c:\vcpp\ex24a\stdafx.h \
	c:\vcpp\ex24a\ex24a.h \
	c:\vcpp\ex24a\mainfrm.h \
	c:\vcpp\ex24a\ex24aset.h \
	c:\vcpp\ex24a\ex24adoc.h \
	c:\vcpp\ex24a\ex24avw.h


MAINFRM_DEP = c:\vcpp\ex24a\stdafx.h \
	c:\vcpp\ex24a\ex24a.h \
	c:\vcpp\ex24a\mainfrm.h


EX24ADOC_DEP = c:\vcpp\ex24a\stdafx.h \
	c:\vcpp\ex24a\ex24a.h \
	c:\vcpp\ex24a\ex24aset.h \
	c:\vcpp\ex24a\ex24adoc.h


EX24AVW_DEP = c:\vcpp\ex24a\stdafx.h \
	c:\vcpp\ex24a\ex24a.h \
	c:\vcpp\ex24a\ex24aset.h \
	c:\vcpp\ex24a\ex24adoc.h \
	c:\vcpp\ex24a\ex24avw.h


EX24ASET_DEP = c:\vcpp\ex24a\stdafx.h \
	c:\vcpp\ex24a\ex24a.h \
	c:\vcpp\ex24a\ex24aset.h


all:	$(PROJ).EXE

EX24A.RES:	EX24A.RC $(EX24A_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r EX24A.RC

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

EX24A.OBJ:	EX24A.CPP $(EX24A_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24A.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

EX24ADOC.OBJ:	EX24ADOC.CPP $(EX24ADOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24ADOC.CPP

EX24AVW.OBJ:	EX24AVW.CPP $(EX24AVW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24AVW.CPP

EX24ASET.OBJ:	EX24ASET.CPP $(EX24ASET_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c EX24ASET.CPP


$(PROJ).EXE::	EX24A.RES

$(PROJ).EXE::	STDAFX.OBJ EX24A.OBJ MAINFRM.OBJ EX24ADOC.OBJ EX24AVW.OBJ EX24ASET.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
EX24A.OBJ +
MAINFRM.OBJ +
EX24ADOC.OBJ +
EX24AVW.OBJ +
EX24ASET.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) EX24A.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	EX24A.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) EX24A.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
