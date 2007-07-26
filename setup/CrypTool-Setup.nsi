;Include Modern UI

  !include "MUI.nsh"
  !include "WordFunc.nsh"
  !insertmacro WordFind

;--------------------------------
;General

  ;Name and file
  !define ProgramName "CrypTool"
  !define VersionInfo "1.4.10 beta 6"
  
  Name "${ProgramName} ${VersionInfo}"
  OutFile "SetupCrypTool_${LANGUAGE_STR}.exe"
  BrandingText "(c) 1998-2007 Contributors"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${ProgramName}"   ; "$PROGRAMFILES\$(^NameDA)"

  Var ShortCutName
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_WELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP CrypToolH.bmp

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "setup-${LANGUAGE_STR}\license-${LANGUAGE_STR}.rtf"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN CrypTool.exe
  !define MUI_FINISHPAGE_SHOWREADME ReadMe-${LANGUAGE_STR}.txt
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
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool-Hilfe"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Zahlenhai"
   !define SCL_NUMBERSHARK	"Zahlenhai.exe"
   !define SCN_NUMBERSHARK_HELP "Zahlenhai-Hilfe"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Skript"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Präsentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
!else if ${LANGUAGE_STR} == 'en'
   !insertmacro MUI_LANGUAGE "English"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Number Shark"
   !define SCL_NUMBERSHARK	"Number Shark.exe"
   !define SCN_NUMBERSHARK_HELP "Number Shark Help"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
!else if ${LANGUAGE_STR} == 'pl'
   !insertmacro MUI_LANGUAGE "Polish"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"Number Shark"
   !define SCL_NUMBERSHARK	"Numbershark.exe"
   !define SCN_NUMBERSHARK_HELP "Number Shark Help"
   !define SCL_NUMBERSHARK_HELP "Numbershark_${LANGUAGE_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_STR}.txt"
!else
  !echo "ERROR: ...!"
  Abort ; EXIT
!endif

;--------------------------------
;Installer Sections

Section "CrypTool" 

  SetOutPath "$INSTDIR"

  ${WordFind} $INSTDIR "\" "-1*}" $ShortCutName  ; FIXME '\' at the string end
  
  ;Files to install
  File /r setup-${LANGUAGE_STR}\*.*

  ;Allow all users to write into pse and examples directory
  ExecWait 'cacls "$INSTDIR\pse"  /t /e /g USERS:w' 
  ExecWait 'cacls "$INSTDIR\examples"  /t /e /g USERS:w' 

  CreateDirectory "$SMPROGRAMS\$ShortCutName" 
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL_HELP}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL_HELP}"	
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK}.lnk" 	 "$INSTDIR\${SCL_NUMBERSHARK}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK_HELP}.lnk" "$INSTDIR\${SCL_NUMBERSHARK_HELP}"
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_AES_TOOL}.lnk" 	 "$INSTDIR\${SCL_AES_TOOL}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_SCRIPT}.lnk" 		 "$INSTDIR\${SCL_SCRIPT}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_PRESENTATION}.lnk" 	 "$INSTDIR\${SCL_PRESENTATION}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_README}.lnk" 		 "$INSTDIR\${SCL_README}"		
  CreateShortCut "$SMPROGRAMS\$ShortCutName\Unistall.lnk" 		 "$INSTDIR\Uninstall.exe"		

  ;File association for AES tool
  WriteRegStr HKCR ".aes" "" "AESToolFile"
  WriteRegStr HKCR "AESToolFile" "" "AES Tool File"
  WriteRegStr HKCR "AESToolFile\DefaultIcon" "" "$INSTDIR\aestool.exe,1"
  WriteRegStr HKCR "AESToolFile\shell" "" "open"
  WriteRegStr HKCR "AESToolFile\shell\open\command" "" '$INSTDIR\aestool.exe "%1"'

  ;Store installation folder
  WriteRegStr HKCU "Software\$ShortCutName" "" $INSTDIR

  ; Important general CrypTool registry container required for uninstall 
  ; $INSTDIR is the registry access key to get the startmenu folder information 
  WriteRegStr HKCU "Software\CrypTool" $INSTDIR $ShortCutName
  
  
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
  
; *******************
  
  Var /GLOBAL StartUpFolder
  ReadRegStr $StartUpFolder HKCU "Software\CrypTool" $INSTDIR

  RMDir /r "$INSTDIR"

  StrCmp $StartUpfolder "" +3 0
  RMDir /r "$SMPROGRAMS\$StartUpFolder" 
  DeleteRegKey HKCU "Software\$StartUpFolder"

; FIXME
  DeleteRegValue HKCU "Software\CrypTool" $INSTDIR

SectionEnd
