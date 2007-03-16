;Include Modern UI

  !include "MUI.nsh"
  !include "WordFunc.nsh"
  !insertmacro WordFind

;--------------------------------
;General

  !define VersionInfo "1.4.10"
  !define CopyrightInfo "Copyright (C) Deutsche Bank AG 1998 - 2007"
  
  ;Name and file
  Name "CrypTool"
  OutFile "SetupCrypTool_${LANGUAGE_STR}.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\$(^NameDA)"

  Var ShortCutName
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "setup-${LANGUAGE_STR}\license-${LANGUAGE_STR}.rtf"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Select Language  

!ifndef LANGUAGE_STR
   !echo "ERROR: Please define LANGUAGE_STR with /D option!" 
   Abort ; EXIT
!endif

!if ${LANGUAGE_STR} == 'de' 
   !insertmacro MUI_LANGUAGE "German"
!else if ${LANGUAGE_STR} == 'en'
   !insertmacro MUI_LANGUAGE "English"
!else if ${LANGUAGE_STR} == 'pl'
   !insertmacro MUI_LANGUAGE "Polish"
!else
  !echo "ERROR: ...!"
  Abort ; EXIT
!endif

;--------------------------------
;Installer Sections

Section "CrypTool" 

  SetOutPath "$INSTDIR"
  

  ${WordFind} $INSTDIR "\" "-1*}" $ShortCutName
  
  ;Files to install
  File /r setup-${LANGUAGE_STR}\*.*
 

 
 ; OLD 
 ; CreateDirectory "$SMPROGRAMS\CrypTool" 
 ; CreateShortCut "$SMPROGRAMS\CrypTool\CrypTool.lnk" "$INSTDIR\CrypTool.exe"
 ; CreateShortCut "$SMPROGRAMS\CrypTool\Unistall.lnk" "$INSTDIR\Uninstall.exe"
 ; CreateShortCut "$SMPROGRAMS\CrypTool\NumberShark.lnk" "$INSTDIR\Number Shark.exe"
 ; CreateShortCut "$SMPROGRAMS\CrypTool\Animal.lnk" "$INSTDIR\animal.bat"
 ; CreateShortCut "$SMPROGRAMS\CrypTool\AESTool.lnk" "$INSTDIR\aestool.exe"

  CreateDirectory "$SMPROGRAMS\$ShortCutName" 
  CreateShortCut "$SMPROGRAMS\$ShortCutName\CrypTool.lnk" "$INSTDIR\CrypTool.exe"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\CrypTool-Help.lnk" "$INSTDIR\CrypTool-${LANGUAGE_STR}.chm"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\NumberShark.lnk" "$INSTDIR\Number Shark.exe"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\NumberShark-Help.lnk" "$INSTDIR\Number Shark-$LANGUAGE_STR}.chm"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\AESTool.lnk" "$INSTDIR\aestool.exe"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\Script.lnk" "$INSTDIR\script-${LANGUAGE_STR}.pdf"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\Presentation.lnk" "$INSTDIR\CrypToolPresentation-${LANGUAGE_STR}.pdf"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\ReadMe.lnk" "$INSTDIR\ReadMe-${LANGUAGE_STR}.txt"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\Unistall.lnk" "$INSTDIR\Uninstall.exe"


  ;Store installation folder
  WriteRegStr HKCU "Software\CrypTool" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  ; LangString DESC_SecInst ${LANG_POLISH} "Install section."

  ;Assign language strings to sections
  ; !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  ; !insertmacro MUI_DESCRIPTION_TEXT ${SecInst} $(DESC_SecInst)
  ; !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"
  
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\$ShortCutName" 

; FIXME
;  DeleteRegKey HKCU "Software\$ShortCutName"

SectionEnd
