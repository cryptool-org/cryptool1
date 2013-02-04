;--------------------------------
; some pre-include definitions (these *NEED* to be placed before any includes)
!define MULTIUSER_EXECUTIONLEVEL Highest
!define MULTIUSER_MUI

;Include Modern UI

  !include MultiUser.nsh
  !include MUI2.nsh
  !include "winver.nsh"
  !include "LogicLib.nsh"
  !include "WordFunc.nsh"
  !insertmacro WordFind
  !insertmacro un.WordFind

;--------------------------------
;General

  ;Name and file
  !define ProgramName "CrypTool"
  !define VersionInfo "1.4.31" ; no beta here to avoid line wrap in installer
  !define VersionFile "1_4_31" ; _beta_0x
  
  Name "${ProgramName} ${VersionInfo}"
  OutFile "SetupCrypTool_${VersionFile}_${LANGUAGE_STR}.exe"
  BrandingText "(c) 1998-2013 Contributors"
;  Icon "..\CrypTool\res\idr_main.ico" ; does not work for some reason

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${ProgramName}"   ; "$PROGRAMFILES\$(^NameDA)"

  Var ShortCutName
  
  Var IsAdministrator
  Var IsAllUsersInstallation
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_WELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_UNWELCOMEFINISHPAGE_BITMAP CrypTool.bmp
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP CrypToolH.bmp
  !define MUI_ICON "..\CrypTool\res\idr_main.ico"

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "setup-${LANGUAGE_STR}\license-${LANGUAGE_STR}.rtf"
  ; we need a custom welcome text for the multi-user page in German, otherwise parts of the standard text get cut off
  !if ${LANGUAGE_STR} == 'de' 
	!define MULTIUSER_INSTALLMODEPAGE_TEXT_TOP "Wählen Sie aus, ob Sie ${ProgramName} ${VersionInfo} nur für sich selbst oder für alle Benutzer dieses Systems installieren wollen. Klicken Sie auf Weiter, um fortzufahren."
  !endif
  ; we add a custom welcome text for English too, since that's the only way to stay consistent regardless of changes in NSIS
  !if ${LANGUAGE_STR} == 'en' 
	!define MULTIUSER_INSTALLMODEPAGE_TEXT_TOP "Select whether you want to install ${ProgramName} ${VersionInfo} for yourself only or for all users of this computer. Click Next to continue."
  !endif
  !define MUI_PAGE_CUSTOMFUNCTION_PRE SkipPageIfNotIsAdministrator
  !insertmacro MULTIUSER_PAGE_INSTALLMODE
  Page custom DetermineIsAllUsersInstallationPage
  !define MUI_PAGE_CUSTOMFUNCTION_PRE PrePageDirectory
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE mui.DirectoryLeave
  !insertmacro MUI_PAGE_DIRECTORY
  !define MUI_FINISHPAGE_NOAUTOCLOSE
  !insertmacro MUI_PAGE_INSTFILES
  !define MUI_FINISHPAGE_RUN CrypTool.exe
  !define MUI_FINISHPAGE_SHOWREADME ReadMe-${LANGUAGE_SUBST_STR}.txt
  !insertmacro MUI_PAGE_FINISH

  !insertmacro MUI_UNPAGE_WELCOME
  !define MUI_PAGE_CUSTOMFUNCTION_LEAVE un.mui.ConfirmLeave
  !insertmacro MUI_UNPAGE_CONFIRM
  !define MUI_UNFINISHPAGE_NOAUTOCLOSE
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Macros
 
  !macro RegUpdate value_old key_new value_new

  ReadRegDWORD $0 HKCU Software\Cryptool\Settings\${key_new} ${value_new}
  IfErrors 0 +5 
  ReadRegDWORD $0 HKCU Software\Cryptool\Settings ${value_old}
  IfErrors +3 
  WriteRegDWORD  HKCU Software\Cryptool\Settings\${key_new} ${value_new} $0
  DeleteRegValue HKCU Software\Cryptool\Settings ${value_old}

  !macroend

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
   !define SCN_UNINSTALL	"Deinstallieren"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.de/"
   !define UNINSTALL_PROMPT	"ist bereits installiert.$\n$\nBitte 'OK' klicken, um die vorherige Installation zu ersetzen; oder 'Abbrechen', um ein anderes Installationsverzeichnis zu wählen."
   !define UNINSTALL_PROMPT2    "Das Verzeichnis existiert bereits.$\n$\nBitte wählen Sie ein anderes, oder deinstallieren Sie das Programm in diesem Verzeichnis."
   !define UNINSTALL_CONFIRM	"Bei der Deinstallation werden alle Dateien im Programmverzeichnis gelöscht - auch von Ihnen erzeugte asymmetrische Schlüssel und gespeicherte Beispieldateien.$\n$\nWenn Sie die Deinstallation hier abbrechen, können Sie erzeugte Schlüssel mit dem bisher installierten CrypTool exportieren.$\n$\nSoll CrypTool wirklich deinstalliert werden?"
   !define UNINSTALL_RMPROGDIR_FAILED "Das Programmverzeichnis konnte nicht (vollständig) gelöscht werden.$\n$\nBitte löschen Sie es manuell."
!else if ${LANGUAGE_STR} == 'en'
   !insertmacro MUI_LANGUAGE "English"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_STR}.chm"
   !define SCN_NUMBERSHARK	"NumberShark"
   !define SCL_NUMBERSHARK	"NumberShark.exe"
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
   !define SCN_UNINSTALL	"Uninstall"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.org/"
   !define UNINSTALL_PROMPT	"is already installed. $\n$\nClick 'OK' to remove the \
  previous version or 'Cancel' to choose another installation directory."
   !define UNINSTALL_PROMPT2    "This directory already exists.$\n$\nPlease select another directory, or uninstall the program in this directory first."
   !define UNINSTALL_CONFIRM	"The uninstallation will delete all files in the installation directory - even asymmetric keys generated by you and saved example files.$\n$\nIf you cancel now you'll be able to export generated keys with your existing CrypTool installation.$\n$\nDo you really want to uninstall CrypTool?"
   !define UNINSTALL_RMPROGDIR_FAILED "The program directory could not be deleted (completely).$\n$\nPlease remove it manually."
!else if ${LANGUAGE_STR} == 'pl'
   !insertmacro MUI_LANGUAGE "Polish"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_NUMBERSHARK	"NumberShark"
   !define SCL_NUMBERSHARK	"NumberShark.exe"
   !define SCN_NUMBERSHARK_HELP "NumberShark Help"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_SUBST_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_SUBST_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_SUBST_STR}.txt"
   !define SCN_UNINSTALL	"Usunac"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.pl/"
   !define UNINSTALL_PROMPT	"jest ju¿ zainstalowany. $\n$\nKliknij 'OK', ¿eby usun¹æ poprzedni¹ wersje \
 lub 'Anuluj', aby okreœliæ inny katalog instalacji."
   !define UNINSTALL_PROMPT2    "Taki katalog ju¿ istnieje. $\n$\nWybierz inny katalog, albo odinstaluj program z tego katalogu."
   !define UNINSTALL_CONFIRM	"Odinstalowanie programu oznacza skasowanie wszystkich plików w katalogu instalacyjnym (tak¿e wygenerowanych przez Ciebie kluczy asymetrycznych i zapisanych przyk³adów).$\n$\n Przerywaj¹c ten proces mo¿esz skopiowaæ te pliki w bezpieczne miejsce.$\n$\nCzy chcesz kontynuowaæ odinstalowywanie programu CrypTool?"
   !define UNINSTALL_RMPROGDIR_FAILED "Katalog programu nie mogl byc usuniety (w calosci).$\n$\nNalezy usunac go recznie."
!else if ${LANGUAGE_STR} == 'es'
   !insertmacro MUI_LANGUAGE "Spanish"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "Ayuda de CrypTool"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_NUMBERSHARK	"NumberShark"
   !define SCL_NUMBERSHARK	"NumberShark.exe"
   !define SCN_NUMBERSHARK_HELP "Ayuda de Number Shark"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_SUBST_STR}.pdf"
   !define SCN_PRESENTATION	"Presentación"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_STR}.pdf"
   !define SCN_README		"Leeme"
   !define SCL_README 		"ReadMe-${LANGUAGE_SUBST_STR}.txt"
   !define SCN_UNINSTALL	"Desinstalar"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.es/"
   !define UNINSTALL_PROMPT	"ya se encuentra instalado. $\n$\nHaga click en 'Aceptar' para desinstalar la \
  versión anterior o 'Cancelar' para seleccionar otro directorio de instalación."
   !define UNINSTALL_PROMPT2    "El directorio ya existe.$\n$\nPor favor, seleccione otro o desinstale el programa en el directorio actual."
   !define UNINSTALL_CONFIRM	"La desinstalación eliminará todos los archivos en este directorio - incluso clave asimétricas que haya generado y archivos de ejemplo guardados.$\n$\nSi cancela ahora será capaz de exportar las claves generadas en su instalación actual de CrypTool.$\n$\n¿Está seguro que desea continuar con el proceso de desinstalación?"
   !define UNINSTALL_RMPROGDIR_FAILED "El directorio del programa no pudo ser eliminado (completamente).$\n$\nPor favor, remover manualmente."
!else if ${LANGUAGE_STR} == 'rs'
   !insertmacro MUI_LANGUAGE "SerbianLatin"
   !define SCN_CRYPTOOL		"CrypTool"
   !define SCL_CRYPTOOL		"CrypTool.exe"
   !define SCN_CRYPTOOL_HELP    "CrypTool Help"
   !define SCL_CRYPTOOL_HELP	"CrypTool-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_NUMBERSHARK	"NumberShark"
   !define SCL_NUMBERSHARK	"NumberShark.exe"
   !define SCN_NUMBERSHARK_HELP "Number Shark Help"
   !define SCL_NUMBERSHARK_HELP "NumberShark-${LANGUAGE_SUBST_STR}.chm"
   !define SCN_AES_TOOL		"AES-Tool"
   !define SCL_AES_TOOL		"aestool.exe"
   !define SCN_SCRIPT		"Script"
   !define SCL_SCRIPT		"script-${LANGUAGE_SUBST_STR}.pdf"
   !define SCN_PRESENTATION	"Presentation"
   !define SCL_PRESENTATION	"CrypToolPresentation-${LANGUAGE_SUBST_STR}.pdf"
   !define SCN_README		"ReadMe"
   !define SCL_README 		"ReadMe-${LANGUAGE_SUBST_STR}.txt"
   !define SCN_UNINSTALL	"Uninstall"
   !define SCL_UNINSTALL	"Uninstall.exe"
   !define URL		"http://www.cryptool.org/"
   !define UNINSTALL_PROMPT	"vec instaliran. $\n$\nKliknite 'OK' da biste uklonili \
  prethodnu verziju ili 'Otkaži' za odabir instalacionog direktorijuma."
   !define UNINSTALL_PROMPT2    "Ovaj direktorijum vec postoji.$\n$\nMolim odaberite drugi direktorijum, ili prvo deinstalirajte program u ovom direktorijumu."
   !define UNINSTALL_CONFIRM	"Deinstalacija ce obrisati sve datoteke iz ovog direktorijuma - cak i asimetricne kljuceve koje ste generisali, kao i primere.$\n$\nAko otkažete sada, bicete u mogucnosti da izvezete kljuceve iz svoje postojece CrypTool instalacije.$\n$\nDa li stvarno želite da deinstalirate CrypTool?"
   !define UNINSTALL_RMPROGDIR_FAILED "Direktorijum programa nije mogao biti obrisan (u potpunosti).$\n$\nMolim uklonite ga rucno."
!else
  !echo "ERROR: ...!"
  Abort ; EXIT
!endif

;--------------------------------
; Installer Section

Section "CrypTool" 
	; set the installation folder (set by the user via GUI)
	SetOutPath $INSTDIR
	; set the files to be installed
	File /r setup-${LANGUAGE_STR}\*.*
	; allow all users to write into pse and examples directory
	ExecWait 'cacls "$INSTDIR\pse"  /t /e /g USERS:w' 
	ExecWait 'cacls "$INSTDIR\examples"  /t /e /g USERS:w' 
	; determine the shortcut name
	${WordFind} $INSTDIR "\" "-1*}" $ShortCutName  ; FIXME '\' at the string end
	; populate the start menu
	Call populateStartMenu
	; set file association for AES tool
	WriteRegStr HKCR ".aes" "" "AESToolFile"
	WriteRegStr HKCR "AESToolFile" "" "AES Tool File"
	WriteRegStr HKCR "AESToolFile\DefaultIcon" "" "$INSTDIR\aestool.exe,0"
	WriteRegStr HKCR "AESToolFile\shell" "" "open"
	WriteRegStr HKCR "AESToolFile\shell\open\command" "" '$INSTDIR\aestool.exe "%1"'
	; open with:
	WriteRegStr HKCR "Applications\aestool.exe\shell\open\command" "" '$INSTDIR\aestool.exe "%1"'
	; add CrypTool to "Add or Remove Programs" in appwiz.cpl
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
				 "DisplayName" "$ShortCutName ${VersionInfo}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
				 "DisplayVersion" "${VersionInfo}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
				 "URLUpdateInfo" "${URL}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
				 "UninstallString" "$INSTDIR\uninstall.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
				 "DisplayIcon" "$INSTDIR\CrypTool.exe,0"  
	; some registry updates
	!insertmacro RegUpdate NoTipps Options\StartingOptions NoTipps
	!insertmacro RegUpdate SampleTextFile Options\StartingOptions SampleTextFile
	!insertmacro RegUpdate ADFGVX_IntroDialogue Cryptool\Settings\ADFGVX ShowIntro
	!insertmacro RegUpdate CRT_IntroDialogue Cryptool\Settings\CrtSecretSharing ShowIntro
	!insertmacro RegUpdate firstPosNull Cryptool\Settings\Hill OrdChrOffset
	!insertmacro RegUpdate useFirstCharFromAlph Cryptool\Settings\Hill PaddingDefaultChr
	!insertmacro RegUpdate ownCharForPadding Cryptool\Settings\Hill PaddingOwnChr
	!insertmacro RegUpdate alphCode Cryptool\Settings\Hill EditKeyChrMatrix
	!insertmacro RegUpdate DH_IntroDialogue Cryptool\Settings\DiffieHellman ShowIntro
	!insertmacro RegUpdate DH_InfoDialogue Crytool\Settings\DiffieHellman ShowInfo
	!insertmacro RegUpdate SignatureAttackHashAlgorithmID Cryptool\Settings\SignatureAttack HashAlgorithmID
	!insertmacro RegUpdate SignatureAttackSignificantBitLength Cryptool\Settings\SignatureAttack SignificantBitLength
	!insertmacro RegUpdate SignatureAttackModificationMethod Cryptool\Settings\SignatureAttack ModificationMethod
	!insertmacro RegUpdate SignatureAttackCheck1 Cryptool\Settings\SignatureAttack ModfiyBlankEOL
	!insertmacro RegUpdate SignatureAttackCheck3 Cryptool\Settings\SignatureAttack ModifyDoubleBlank
	!insertmacro RegUpdate SignatureAttackAttMethod Cryptool\Settings\SignatureAttack ModifyCharSet
	!insertmacro RegUpdate SignatureAttackTestMode Cryptool\Settings\SignatureAttack PerformTestRun
	!insertmacro RegUpdate SignificantBitLengthMIN Cryptool\Settings\SignatureAttack SignificantBitLengthMin
	!insertmacro RegUpdate SignificantBitLengthMAX Cryptool\Settings\SignatureAttack SignificantBitLengthMax
	!insertmacro RegUpdate SignificantBitLengthJump Cryptool\Settings\SignatureAttack SignificantBitLengthJump
	!insertmacro RegUpdate HashAlgorithmIDMIN Cryptool\Settings\SignatureAttack HashAlgorithmIDMin
	!insertmacro RegUpdate HashAlgorithmIDMAX Cryptool\Settings\SignatureAttack HashAlgorithmIDMax
	!insertmacro RegUpdate Attempts Cryptool\Settings\SignatureAttack Attempts
	!insertmacro RegUpdate AttemptsMAX Cryptool\Settings\SignatureAttack AttemptsMax 
	!insertmacro RegUpdate SignatureAttackHarmlessFile Cryptool\Settings\SignatureAttack HarmlessFile
	!insertmacro RegUpdate SignatureAttackDangerousFile Cryptool\Settings\SignatureAttack DangerousFile
	!insertmacro RegUpdate PQM_GL_MinimumLength Cryptool\Settings\PasswordGuidelines MinimumLength
	!insertmacro RegUpdate PQM_GL_MinimumDigits Cryptool\Settings\PasswordGuidelines MinimumDigits 
	!insertmacro RegUpdate PQM_GL_MinimumSpecial Cryptool\Settings\PasswordGuidelines MinimumSpecial
	!insertmacro RegUpdate PQM_GL_SpecialGroup Cryptool\Settings\PasswordGuidelines SpecialGroup
	!insertmacro RegUpdate RANDOM_GENERATOR_DATASIZE Cryptool\Settings\RandomGenerator GenerateBytes
	!insertmacro RegUpdate RANDOM_GENERATOR_ICG_N Cryptool\Settings\RandomGenerator ParamICG_N
	!insertmacro RegUpdate RANDOM_GENERATOR_ICG_P1 Cryptool\Settings\RandomGenerator ParamICG_P1
	!insertmacro RegUpdate RANDOM_GENERATOR_ICG_P2 Cryptool\Settings\RandomGenerator ParamICG_P2
	!insertmacro RegUpdate RANDOM_GENERATOR_OUTPUT_INTERNALSTATE Cryptool\Settings\RandomGenerator ShowInternalRandState
	!insertmacro RegUpdate RANDOM_GENERATOR_SEED Cryptool\Settings\RandomGenerator RandSeed
	!insertmacro RegUpdate RANDOM_GENERATOR_TYPE_ID Cryptool\Settings\RandomGenerator SelGenerator
	!insertmacro RegUpdate RANDOM_GENERATOR_LCG_P1 Cryptool\Settings\RandomGenerator ParamLCG_P1
	!insertmacro RegUpdate RANDOM_GENERATOR_LCG_P2 Cryptool\Settings\RandomGenerator ParamLCG_P2
	!insertmacro RegUpdate RANDOM_GENERATOR_LCG_N Cryptool\Settings\RandomGenerator ParamLCG_N
	!insertmacro RegUpdate RANDOM_GENERATOR_X2MODN_N Cryptool\Settings\RandomGenerator ParamX2MODN_N
	!insertmacro RegUpdate SecretSharing_Intro CrypTool\Settings\SecretSharing ShowIntro
	!insertmacro RegUpdate HybridEncryptionSCASignificantBits Cryptool\Settings\SideChannelAttack BitlengthSecret
	!insertmacro RegUpdate SCA_Keyword Cryptool\Settings\SideChannelAttack Keyword
	!insertmacro RegUpdate CreateReport_Top Cryptool\Settings\SizingDialog CreateReportTop
	!insertmacro RegUpdate CreateReport_Left Cryptool\Settings\SizingDialog CreateReportLeft
	!insertmacro RegUpdate CreateReport_Bottom Cryptool\Settings\SizingDialog CreateReportBottom
	!insertmacro RegUpdate CreateReport_Right Cryptool\Settings\SizingDialog CreateReportRight
	!insertmacro RegUpdate ShowPermutationKey Cryptool\Settings\Permutation ShowPermutationKey
	; write the uninstaller
	WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

;--------------------------------
; Uninstaller Section

Section "Uninstall"
	; determine the short cut name
	${un.WordFind} $INSTDIR "\" "-1*}" $ShortCutName
	; to avoid errors, we don't want to delete the old installation 
	; directory if it doesn't exist (due to user removal, for example)
	IfFileExists "$INSTDIR" rmdir rmdirDone
rmdir:
	ClearErrors
	RMDir /r "$INSTDIR"
	IfErrors 0 rmdirDone
	MessageBox MB_OK|MB_ICONEXCLAMATION "${UNINSTALL_RMPROGDIR_FAILED}"
rmdirDone:
	StrCmp $ShortCutName "" failSafe 0
	SetShellVarContext all
	IfFileExists $SMPROGRAMS\$ShortCutName\*.* 0 rmdirSMCurrent
	ClearErrors
	RMDir /r "$SMPROGRAMS\$ShortCutName" 
	IfErrors 0 rmdirSMDone
rmdirSMCurrent:
	SetShellVarContext current
	RMDir /r "$SMPROGRAMS\$ShortCutName" 
rmdirSMDone:
	; Remove CrypTool to "Add or Remove Programs" in appwiz.cpl
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName"
failSafe:
	DeleteRegKey HKCR ".aes"
	DeleteRegKey HKCR "AESToolFile" 
	DeleteRegKey HKCR "Applications\aestool.exe"
SectionEnd

Function .onInit
	; initialize multi-user plugin
	!insertmacro MULTIUSER_INIT	
	; check whether user is an administrator
	Call DetermineIsAdministrator
FunctionEnd

Function un.onInit
	; initialize multi-user plugin
	!insertmacro MULTIUSER_UNINIT
FunctionEnd

; determine whether user is an administrator
Function DetermineIsAdministrator
    userInfo::getAccountType
    pop $0
	strCmp $0 "Admin" +3
	StrCpy $IsAdministrator "No"
    return
    StrCpy $IsAdministrator "Yes"
FunctionEnd

; determine if we have an all-users installation (called after the installation mode page)
Function DetermineIsAllUsersInstallationPage
	StrCpy $IsAllUsersInstallation "No"
	StrCmp $MultiUser.InstallMode "CurrentUser" +2
	StrCpy $IsAllUsersInstallation "Yes"
FunctionEnd

; at this point we have the variables "IsAdministrator" and "IsAllUsersInstallation" set;
; depending on those two variables and the operating system at hand we decide where to put 
; our installation folder ($INSTDIR); the trick is that we choose user-writable directories 
; so that even non-admin users can install for all users
Function PrePageDirectory
	; default initialization (unchanged for admins)
	StrCpy $INSTDIR "$PROGRAMFILES\${ProgramName}"
	; check if we need to alter the default installation folder
	${If} $IsAdministrator == "No"
		${If} $IsAllUsersInstallation == "Yes"
			${If} ${IsWinXP}
				ExpandEnvStrings $0 "%ALLUSERSPROFILE%"
			${ElseIf} ${IsWinVista}
				ExpandEnvStrings $0 "%PROGRAMDATA%"
			${ElseIf} ${IsWin7}
				ExpandEnvStrings $0 "%PROGRAMDATA%"
			${Else}
				ExpandEnvStrings $0 "%PROGRAMDATA%"
			${EndIf}
			StrCpy $INSTDIR "$0\${ProgramName}"
		${Else}
			StrCpy $INSTDIR "$LOCALAPPDATA\${ProgramName}"
		${EndIf}
	${EndIf}
FunctionEnd

; this function is called to manually "skip" the installation mode page for non-privileged users
Function SkipPageIfNotIsAdministrator
	StrCmp $IsAdministrator "No" +1 +2
	Abort
FunctionEnd

Function mui.DirectoryLeave
	; determine the short cut name
	${WordFind} $INSTDIR "\" "-1*}" $ShortCutName	
	
	ReadRegStr $R0 HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\$ShortCutName" \
	"UninstallString"
	StrCmp $R0 "" done

	MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
	"$ShortCutName ${UNINSTALL_PROMPT}" \
	IDOK uninst
	Abort
  
;Run the uninstaller
uninst:
  ClearErrors
  ;We need to copy the uninstaller to a temp file manually, because 
  ; - ExecWait '$R0 _?=$INSTDIR' fails to delete the (running) installer
  ; - ExecWait '$R0' copies the installer to a temp file, but does not wait until it is finished
  ${WordFind} $R0 "\" "-1{" $R2 ; extract path from $R0 to $R2
  GetTempFileName $R1 ; create a temporary file $R1
  CopyFiles $R0 $R1.exe
  ExecWait '"$R1.exe" _?=$R2' ; call copy of uninstaller with target directory $R2

  IfErrors 0 done

  ; flomar, 02/10/2010
  ; Something went wrong in case we get here. So, if there is no 
  ; installation directory, the error was probably caused by the 
  ; user manually removing the CrypTool installation directory. 
  ; Therefore we skip any further checks and go right to the 
  ; installation routine.
  IfFileExists $INSTDIR 0 install
  Abort ; Abort if uninstall failed

done:
  Delete $R1 ; delete (empty) file
  Delete $R1.exe ; delete temporary uninstaller copy
  IfFileExists $INSTDIR\*.* 0 install
  MessageBox MB_OK \
  "${UNINSTALL_PROMPT2}" \
  IDOK 0
  Abort
  
install:
 
FunctionEnd

Function un.mui.ConfirmLeave

  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${UNINSTALL_CONFIRM}" \
  IDOK continue
  Abort
 
continue:

FunctionEnd

Function populateStartMenu
	; determine shell var context (the interpretation of $SMPROGRAMS with regards to user privilege
	${If} $IsAdministrator == "Yes"
		SetShellVarContext all
	${Else}
		SetShellVarContext current
	${EndIf}
	
	; create and populate start menu
	CreateDirectory "$SMPROGRAMS\$ShortCutName"
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL}"
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_CRYPTOOL_HELP}.lnk" 	 "$INSTDIR\${SCL_CRYPTOOL_HELP}"	
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK}.lnk" 	 "$INSTDIR\${SCL_NUMBERSHARK}"		
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_NUMBERSHARK_HELP}.lnk" "$INSTDIR\${SCL_NUMBERSHARK_HELP}"
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_AES_TOOL}.lnk" 	 "$INSTDIR\${SCL_AES_TOOL}"		
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_SCRIPT}.lnk" 		 "$INSTDIR\${SCL_SCRIPT}"		
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_PRESENTATION}.lnk" 	 "$INSTDIR\${SCL_PRESENTATION}"		
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_README}.lnk" 		 "$INSTDIR\${SCL_README}"		
	CreateShortCut "$SMPROGRAMS\$ShortCutName\${SCN_UNINSTALL}.lnk" 	 "$INSTDIR\${SCL_UNINSTALL}"		
FunctionEnd

