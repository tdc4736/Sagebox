// -------------------------- 
// SageBox -- Windows Sandbox
// --------------------------
//
// This is a template for a Sandbox version of a Win32/Win64 SageBox application.
//
// For documentation and help on this source file, right-click on "SandboxHelp.h" and select "Go do document WinSandbox.h"
//

#include "CSageBox.h"

// WinMain() -- Main Entry Point for Windows Applications
//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nCmdShow)
{
    CSageBox cSageBox;                              // Create the main SageBox object.  Do this only once.
    auto& cWin = cSageBox.NewWindow();              // Create as many of these as you like.
 
    cWin.printf("Hello World! -- Press Window Close Button to End Program.\n");
    cWin.Write("Hello World!",Font("Arial,100") << CenterXY());

    while(cWin.EventLoop());     // Wait for window to close.  cWin.WaitforClose() can also be called without the while loop. 
}

