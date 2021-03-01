# Microsoft Developer Studio Project File - Name="rsstool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=rsstool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "rsstool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "rsstool.mak" CFG="rsstool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "rsstool - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "rsstool - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "rsstool - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "." /D "HAVE_CONFIG_H" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib libxml2.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "rsstool - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "rsstool - Win32 Release"
# Name "rsstool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MISC\codec.c
# End Source File
# Begin Source File

SOURCE=.\MISC\codec_base64.c
# End Source File
# Begin Source File

SOURCE=.\MISC\file.c
# End Source File
# Begin Source File

SOURCE=.\MISC\getopt.c
# End Source File
# Begin Source File

SOURCE=.\MISC\getopt2.c
# End Source File
# Begin Source File

SOURCE=.\MISC\hash.c
# End Source File
# Begin Source File

SOURCE=.\MISC\hash_crc.c
# End Source File
# Begin Source File

SOURCE=.\MISC\hash_md5.c
# End Source File
# Begin Source File

SOURCE=.\MISC\misc.c
# End Source File
# Begin Source File

SOURCE=.\MISC\net.c
# End Source File
# Begin Source File

SOURCE=.\MISC\property.c
# End Source File
# Begin Source File

SOURCE=.\MISC\rss.c
# End Source File
# Begin Source File

SOURCE=.\rsstool.c
# End Source File
# Begin Source File

SOURCE=.\rsstool_misc.c
# End Source File
# Begin Source File

SOURCE=.\rsstool_write.c
# End Source File
# Begin Source File

SOURCE=.\MISC\sql.c
# End Source File
# Begin Source File

SOURCE=.\MISC\sql_mysql.c
# End Source File
# Begin Source File

SOURCE=.\MISC\sql_odbc.c
# End Source File
# Begin Source File

SOURCE=.\MISC\string.c
# End Source File
# Begin Source File

SOURCE=.\misc\win32.c
# End Source File
# Begin Source File

SOURCE=.\MISC\xml.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MISC\codec.h
# End Source File
# Begin Source File

SOURCE=.\MISC\codec_base64.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\MISC\defines.h
# End Source File
# Begin Source File

SOURCE=.\MISC\file.h
# End Source File
# Begin Source File

SOURCE=.\MISC\getopt.h
# End Source File
# Begin Source File

SOURCE=.\MISC\getopt2.h
# End Source File
# Begin Source File

SOURCE=.\MISC\hash.h
# End Source File
# Begin Source File

SOURCE=.\MISC\hash_crc.h
# End Source File
# Begin Source File

SOURCE=.\MISC\hash_md5.h
# End Source File
# Begin Source File

SOURCE=.\MISC\itypes.h
# End Source File
# Begin Source File

SOURCE=.\MISC\misc.h
# End Source File
# Begin Source File

SOURCE=.\MISC\net.h
# End Source File
# Begin Source File

SOURCE=.\MISC\property.h
# End Source File
# Begin Source File

SOURCE=.\MISC\rss.h
# End Source File
# Begin Source File

SOURCE=.\rsstool.h
# End Source File
# Begin Source File

SOURCE=.\rsstool_defines.h
# End Source File
# Begin Source File

SOURCE=.\rsstool_misc.h
# End Source File
# Begin Source File

SOURCE=.\rsstool_write.h
# End Source File
# Begin Source File

SOURCE=.\MISC\sql.h
# End Source File
# Begin Source File

SOURCE=.\MISC\sql_mysql.h
# End Source File
# Begin Source File

SOURCE=.\MISC\sql_odbc.h
# End Source File
# Begin Source File

SOURCE=.\MISC\string.h
# End Source File
# Begin Source File

SOURCE=.\misc\win32.h
# End Source File
# Begin Source File

SOURCE=.\MISC\xml.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
