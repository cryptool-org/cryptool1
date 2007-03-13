;Include Modern UI

  !include "MUI.nsh"
  !include LogicLib.nsh

;--------------------------------
;General

  !define VersionInfo "1.4.10"
  !define CopyrightInfo "Copyright (C) Deutsche Bank AG 1998 - 2007"
;  !define LANGUAGE_STR "de"  
  
  ;Name and file
  Name "CrypTool"
  OutFile "SetupCrypTool_${LANGUAGE_STR}.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\CrypTool"

;--------------------------------
;Select Language  // FIXME ?!?!

;  !insertmacro MUI_LANGUAGE "German"

!ifndef LANGUAGE_STR
   !echo "ERROR: Please define LANGUAGE_STR with /D option!" 
   ; EXIT
!endif



!if ${LANGUAGE_STR} == 'de' 
   !insertmacro MUI_LANGUAGE "German"
!else if ${LANGUAGE_STR} == 'en'
   !insertmacro MUI_LANGUAGE "English"
!else if ${LANGUAGE_STR} == 'pl'
   !insertmacro MUI_LANGUAGE "Polish"
!else
  !echo "ERROR: ...!"
  ; EXIT
!endif

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "..\licence-de.txt"
;  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  


;--------------------------------
;Installer Sections

Section "CrypTool" SecInst

  SetOutPath "$INSTDIR"
  
  ;Files to install
  File /r *.*

  CreateDirectory "$SMPROGRAMS\CrypTool" 
  CreateShortCut "$SMPROGRAMS\CrypTool\CrypTool.lnk" "$INSTDIR\CrypTool.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\Unistall.lnk" "$INSTDIR\Uninstall.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\NumberShark.lnk" "$INSTDIR\Number Shark.exe"
  CreateShortCut "$SMPROGRAMS\CrypTool\Animal.lnk" "$INSTDIR\animal.bat"
  CreateShortCut "$SMPROGRAMS\CrypTool\AESTool.lnk" "$INSTDIR\aestool.exe"

  ;Store installation folder
  WriteRegStr HKCU "Software\CrypTool" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecInst ${LANG_POLISH} "Install section."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SecInst} $(DESC_SecInst)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\CrypTool" 

  DeleteRegKey HKCU "Software\CrypTool"

SectionEnd
