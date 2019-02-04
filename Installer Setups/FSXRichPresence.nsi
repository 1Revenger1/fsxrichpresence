; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "P3D Discord Rich Presence"
!define PRODUCT_VERSION "1.1"
!define PRODUCT_PUBLISHER "1Revenger1"
!define PRODUCT_WEB_SITE "http://www.fsacdiscord.xyz"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
Function ReplaceLineStr
 Exch $R0 ; string to replace that whole line with
 Exch
 Exch $R1 ; string that line should start with
 Exch
 Exch 2
 Exch $R2 ; file
 Push $R3 ; file handle
 Push $R4 ; temp file
 Push $R5 ; temp file handle
 Push $R6 ; global
 Push $R7 ; input string length
 Push $R8 ; line string length
 Push $R9 ; global

  StrLen $R7 $R1

  GetTempFileName $R4

  FileOpen $R5 $R4 w
  FileOpen $R3 $R2 r

  ReadLoop:
  ClearErrors
   FileRead $R3 $R6
    IfErrors Done

   StrLen $R8 $R6
   StrCpy $R9 $R6 $R7 -$R8
   StrCmp $R9 $R1 0 +3

    FileWrite $R5 "$R0$\r$\n"
    Goto ReadLoop

    FileWrite $R5 $R6
    Goto ReadLoop

  Done:

  FileClose $R3
  FileClose $R5

  SetDetailsPrint none
   Delete $R2
   Rename $R4 $R2
  SetDetailsPrint both

 Pop $R9
 Pop $R8
 Pop $R7
 Pop $R6
 Pop $R5
 Pop $R4
 Pop $R3
 Pop $R2
 Pop $R1
 Pop $R0
FunctionEnd

SetCompressor lzma

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "..\..\..\Downloads\Main.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "License.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\Lockheed Martin\Prepar3D v3"
ShowInstDetails show
ShowUnInstDetails show

Section "MainSection" SEC01
  SetOutPath "$PROGRAMFILES\Lockheed Martin\Prepar3D v3"
  SetOverwrite ifnewer
  File "FSXRichPresence.dll"
  File "discord-rpc.dll"
  Push "$PROFILE\AppData\Roaming\Lockheed Martin\Prepar3D v3\dll.xml" ; file to modify
  Push "</SimBase.Document>" ; string that a line must begin with *WS Sensitive*
  Push "<Launch.Addon>$\r$\n<Name>FSXRpc</Name>$\r$\n<Disabled>False</Disabled>$\r$\n<Path>FSXRichPresence.dll</Path>$\r$\n</Launch.Addon>$\r$\n</SimBase.Document>  <Launch.Addon>$\r$\n        <Name>FSXRpc</Name>$\r$\n        <Disabled>False</Disabled>$\r$\n        <Path>FSXRpc\FSXRichPresence.dll</Path>$\r$\n    </Launch.Addon>$\r$\n</SimBase.Document>" ; string to replace whole line with
  Call ReplaceLineStr
  
SectionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  CreateDirectory "$SMPROGRAMS\P3D Discord Rich Presence"
  CreateShortCut "$SMPROGRAMS\P3D Discord Rich Presence\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd


Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\uninst.exe"
  Delete "$PROGRAMFILES\Lockheed Martin\Prepar3D v3\discord-rpc.dll"
  Delete "$PROGRAMFILES\Lockheed Martin\Prepar3D v3\FSXRichPresence.dll"

  Delete "$SMPROGRAMS\P3D Discord Rich Presence\Uninstall.lnk"

  RMDir "$SMPROGRAMS\P3D Discord Rich Presence"
  RMDir "$PROGRAMFILES\Lockheed Martin\Prepar3D v3"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  SetAutoClose true
SectionEnd