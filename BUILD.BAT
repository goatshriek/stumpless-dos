WCC SRC\STMPLSS.C
WCC SRC\MAIN.C -i=SRC\
WLINK name MAIN.EXE file *.OBJ
MKDIR UTIL
MKDIR UTIL\STMPLSS
UPX -9 -oUTIL\STMPLSS\STMPLSS.EXE MAIN.EXE
MKDIR SOURCE
MKDIR SOURCE\STMPLSS
ZIP -9 -r SOURCE\STMPLSS\SOURCES.ZIP APPINFO BUILD.BAT COPYING CITATION.CFF LINKS SRC
ZIP -9 -r STMPLSS.ZIP APPINFO LINKS UTIL SOURCE
