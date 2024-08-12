# Microsoft Visual C++ generated build script - Do not modify

PROJ = EX25A
DEBUG = 1
PROGTYPE = 3
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\VCPP\EX25A\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = SHIP.CPP    
RC = rc
CFLAGS_D_WTTY = /nologo /G2 /Mq /W3 /AM /Od /D "_DEBUG" 
CFLAGS_R_WTTY = /nologo /Gs /G2 /Mq /W3 /AM /Ox /D "NDEBUG" /FR 
LFLAGS_D_WTTY = /NOLOGO /NOD /NOE /PACKC:57344 /ALIGN:16 /ONERROR:NOEXE  
LFLAGS_R_WTTY = /NOLOGO /NOD /PACKC:57344 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WTTY = mafxcwd oldnames libw mlibcewq commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WTTY = mafxcw mafxcr oldnames libw mlibcewq commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WTTY)
LFLAGS = $(LFLAGS_D_WTTY)
LIBS = $(LIBS_D_WTTY)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
DEFFILE=C:\MSVC\BIN\CL.DEF
!else
CFLAGS = $(CFLAGS_R_WTTY)
LFLAGS = $(LFLAGS_R_WTTY)
LIBS = $(LIBS_R_WTTY)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
DEFFILE=C:\MSVC\BIN\CL.DEF
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = SHIP.SBR \
		CLIENT.SBR


SHIP_DEP = c:\vcpp\ex25a\ship.h


CLIENT_DEP = c:\vcpp\ex25a\ship.h


all:	$(PROJ).EXE

SHIP.OBJ:	SHIP.CPP $(SHIP_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c SHIP.CPP

CLIENT.OBJ:	CLIENT.CPP $(CLIENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c CLIENT.CPP


$(PROJ).EXE::	SHIP.OBJ CLIENT.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
SHIP.OBJ +
CLIENT.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
c:\msvc\lib\+
c:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@


run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
