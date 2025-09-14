; Smart Mavi Manager Windows Installer Script
; Created for NSIS (Nullsoft Scriptable Install System)

!define APP_NAME "Smart Mavi Manager"
!define COMP_NAME "Smart Mavi Solutions"
!define WEB_SITE "https://smartmavi.com"
!define VERSION "2.0.0.0"
!define COPYRIGHT "© 2025 Smart Mavi Solutions"
!define DESCRIPTION "Professional Schedule Generator"
!define INSTALLER_NAME "SmartMaviManager_v2.0.0_Setup.exe"
!define MAIN_APP_EXE "SmartMaviGUI.exe"
!define INSTALL_TYPE "SetShellVarContext current"
!define REG_ROOT "HKCU"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

Name "${APP_NAME}"
Caption "${APP_NAME} v${VERSION} Setup"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\${APP_NAME}"

VIProductVersion "${VERSION}"
VIAddVersionKey "ProductName" "${APP_NAME}"
VIAddVersionKey "CompanyName" "${COMP_NAME}"
VIAddVersionKey "LegalCopyright" "${COPYRIGHT}"
VIAddVersionKey "FileDescription" "${DESCRIPTION}"
VIAddVersionKey "FileVersion" "${VERSION}"

ShowInstDetails show
ShowUninstDetails show

; Modern UI
!include "MUI2.nsh"

; Interface Settings
!define MUI_ABORTWARNING
!define MUI_ICON "logo.ico"
!define MUI_UNICON "logo.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "welcome.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP "welcome.bmp"

; Pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "LICENSE.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; Languages
!insertmacro MUI_LANGUAGE "English"

; Sections
Section "Core Application" SEC01
    SetOutPath "$INSTDIR"
    SetOverwrite ifnewer
    
    ; Main executable
    File "SmartMaviGUI.exe"
    File "logo.png"
    File "README_GUI.md"
    
    ; Qt5 Runtime Libraries (to be bundled)
    File "Qt5Core.dll"
    File "Qt5Gui.dll" 
    File "Qt5Widgets.dll"
    File "Qt5PrintSupport.dll"
    
    ; Visual C++ Runtime (if needed)
    File "msvcp140.dll"
    File "vcruntime140.dll"
    
    ; Platform plugins
    SetOutPath "$INSTDIR\platforms"
    File "platforms\qwindows.dll"
    
    SetOutPath "$INSTDIR"
SectionEnd

Section "Desktop Shortcut" SEC02
    CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
SectionEnd

Section "Start Menu Shortcuts" SEC03
    CreateDirectory "$SMPROGRAMS\${APP_NAME}"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
    CreateShortCut "$SMPROGRAMS\${APP_NAME}\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
SectionEnd

Section -Post
    WriteUninstaller "$INSTDIR\Uninstall.exe"
    WriteRegStr "${REG_ROOT}" "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "DisplayName" "${APP_NAME}"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "UninstallString" "$INSTDIR\Uninstall.exe"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "DisplayVersion" "${VERSION}"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "Publisher" "${COMP_NAME}"
    WriteRegStr "${REG_ROOT}" "${UNINSTALL_PATH}" "URLInfoAbout" "${WEB_SITE}"
SectionEnd

; Section Descriptions
LangString DESC_SecCore ${LANG_ENGLISH} "Core application files and Qt5 runtime libraries"
LangString DESC_SecDesktop ${LANG_ENGLISH} "Create a desktop shortcut for quick access"
LangString DESC_SecStartMenu ${LANG_ENGLISH} "Create Start Menu shortcuts"

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} $(DESC_SecCore)
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} $(DESC_SecDesktop)
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC03} $(DESC_SecStartMenu)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

; Uninstaller
Section Uninstall
    Delete "$INSTDIR\${MAIN_APP_EXE}"
    Delete "$INSTDIR\logo.png"
    Delete "$INSTDIR\README_GUI.md"
    Delete "$INSTDIR\Qt5Core.dll"
    Delete "$INSTDIR\Qt5Gui.dll"
    Delete "$INSTDIR\Qt5Widgets.dll"
    Delete "$INSTDIR\Qt5PrintSupport.dll"
    Delete "$INSTDIR\msvcp140.dll"
    Delete "$INSTDIR\vcruntime140.dll"
    Delete "$INSTDIR\platforms\qwindows.dll"
    Delete "$INSTDIR\Uninstall.exe"
    
    RMDir "$INSTDIR\platforms"
    RMDir "$INSTDIR"
    
    Delete "$SMPROGRAMS\${APP_NAME}\*.*"
    RMDir "$SMPROGRAMS\${APP_NAME}"
    Delete "$DESKTOP\${APP_NAME}.lnk"
    
    DeleteRegKey "${REG_ROOT}" "${REG_APP_PATH}"
    DeleteRegKey "${REG_ROOT}" "${UNINSTALL_PATH}"
SectionEnd

; Functions
Function .onInit
    ; Check for previous installation
    ReadRegStr $R0 "${REG_ROOT}" "${UNINSTALL_PATH}" "UninstallString"
    StrCmp $R0 "" done
    
    MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
    "${APP_NAME} is already installed. $\n$\nClick 'OK' to remove the previous version or 'Cancel' to cancel this upgrade." \
    IDOK uninst
    Abort
    
    uninst:
        ClearErrors
        Exec $R0
    done:
FunctionEnd
