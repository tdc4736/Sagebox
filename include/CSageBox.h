//#pragma warning( disable : 26444) 
#pragma once

#if !defined (_CSageBox_H_)
#define _CSageBox_H_
#pragma warning( disable : 4996) 

//#include "SageIncludes.h"

#include "Sage.h"
#include "SageOpt.h"
#include "CSageTypes.h"
#include "CWindow.h"
#include "CTextWidget.h"
#include "CMemClass.h"
#include "CSageMacros.h"
#include "CDialog.h"
#include "CJpeg.h"

// -------------------
// Main CSageBox Class
// -------------------
//
// CSageBox needs to be instantiated as the first object in SageBox.  For quick console-mode functions, only CSageBox is needed. 
//
// Once CSageBox is created, many utility functions become available, and visible windows (CWindow class) can be created that
// can host output, input, controls widgets, etc.
//
// SageBox has a few modes, depending on the type of application.
//
// Console
//
// SageBox can be used in console mode to supplement console-mode programmging with quick dialog and button functions,
// and Windows that can host the entire set of SageBox functions while still in console-mode.
//
// SandBox
//
// The SandBox mode allows regular C/C++ programming in the context of a window class, mixing
// console-mode style programming with windows functionality. 
// 
// In this mode, the console mode window can also be available so that the window(s) created by SageBox and the Console mode
// window an be used simultaneously.
//
// The SandBox window acts just like a Windows programs, with controls like sliders, buttons, etc., and can also be
// used in a more console-mode style setting with various console functions such as printf, write(), and various i/o
// routines, including "in" and "out" that recplicate C++ cin and cout, but with more functionality.
//
// Regular Windows -- Event Drive and Procedural (i.e. regular C/C++)
//
// SageBox applications can be written in a regular C/C++ procedural style without the use of event callbacks or overriding classes, as well as regular windows.
// A mix of the two is also possible, the idea being to start with an easy procedural program and then later migrate some or all of it to a more event-drive
// structure as needed.
//
// With Windows, not all functionality needs to be event-driven to be the most efficient, but in some cases that may be useful dependonding on the application.
//
// For most applications, start-up projects, and prototypush programs, simple procedural code with the use of EventLoop() works just fine and creates
// a bonafide windows application.
//
// As the program grows, it is an easy transition to making some or all of the program work in an event-driven source-code structure.
//
// Event-Driven, Canonical Windows
//
// Sagebox also facilitates writing canonical windows programs, with overrides and classes (i.e. Message Handlers) to intercept all Windows messages
// with or without overriding the window or control class. 
//
// With a Message Handler, you can specify where to send Windows messages without overriding the class, or the entire window or control can be overriden for more
// flexibility.
//
// SageBox also provides a large array of functions to work with the Windows operating system, as well as keeping track of event states as they occur.
//
// SageBox Tools
//
// This is still being implemented.  The tools in Sagebox extend beyond windows functionality and into general tools, such as image-processing, neural networking, and other tools that
// have been developed over the last few years.
//
// This is still being developed.  See functions available in CSageTools as well as CRawBitmap, Sage::CString, and so-forth.
//
namespace Sage
{

class CSageBox
{
public:
	CWindow * m_cWin = nullptr;

private:
	void Postamble(CWindow & cWin);
	void Preamble(CWindow & cWin);
	void CreateDefaultWindow();
    HANDLE m_hWinThread = nullptr;

	int m_iConsoleWinNum = 0;		// Used for positioning windows when ConsoleWin() is called
public:
	// The main SageBox Class
	//
	// note: Only instantiate one per-application.  Pass a reference or a pointer, or set
	// a pointer member variable to re-use in other functions and classes.
	//
	// Sagebox contains a number of console-based functions that can help with windowing functions
	// without creating a Window.  Use the CSageBox object to access these.
	//
	// All CSageBox functions are available through windows created by CSageBox
	//
	// For windows-based applications, the CSageBox object is not needed once it is instantiated, but
	// cannot be deleted until the end of the program, as it closes and destroys all windows, controls, widgets,
	// and memory created by any part of SageBox
	//
	CSageBox(const char * sAppName = nullptr);
	~CSageBox();
    void SetWinThread(HANDLE hThread);

    // Quick Console Window functions (same as NewWindow, just smaller)
	//
	// This creates quick small window (around 800x600), where NewWindow creates a much larger window. 
	// There isn't any other difference
	//
	CWindow & ConsoleWin(int iX,int iY,const char * sTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// Quick Console Window functions (same as NewWindow, just smaller)
	//
	// This creates quick small window (around 800x600), where NewWindow creates a much larger window. 
	// There isn't any other difference
	//
	CWindow & ConsoleWin(const char * sTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// Quick Console Window functions (same as NewWindow, just smaller)
	//
	// This creates quick small window (around 800x600), where NewWindow creates a much larger window. 
	// There isn't any other difference
	//
	CWindow & ConsoleWin(cwfOpt & cwOpt);

	// NewWindow -- Create a new popup window.
    // This creates a regular window with all of the functions and properties of the parent window.
    //
    // The Event properties (i.e. through EventLoop() and WaitforEvent() also run through the parent.
    // Therefore, the Parent's WaitforEvent() and EventLoop() can be used to check for the new window's events.
    //
    // A subclassed window object may be passed in to override event callbacks, Main(), and other CWindow components.
    // This object is deleted automatically (i.e. the object passed in)
    //
    // SetMessageHandler() can be used to override event messages without overriding the window class
    //
    // When the User presses the 'X' window close button, a WindowClosing() for the new window will come back as true, and a 
    // CloseButtonPressed() event will be triggerred.
    //
	CWindow & NewWindow(CWindow * cWin,int iX,int iY,int iWidth,int iHeight,const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());
	// NewWindow -- Create a new popup window.
    // This creates a regular window with all of the functions and properties of the parent window.
    //
    // The Event properties (i.e. through EventLoop() and WaitforEvent() also run through the parent.
    // Therefore, the Parent's WaitforEvent() and EventLoop() can be used to check for the new window's events.
    //
    // A subclassed window object may be passed in to override event callbacks, Main(), and other CWindow components.
    // This object is deleted automatically (i.e. the object passed in)
    //
    // SetMessageHandler() can be used to override event messages without overriding the window class
    //
    // When the User presses the 'X' window close button, a WindowClosing() for the new window will come back as true, and a 
    // CloseButtonPressed() event will be triggerred.
    //
	CWindow & NewWindow(CWindow * cWin,const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// NewWindow -- Create a new popup window.
    // This creates a regular window with all of the functions and properties of the parent window.
    //
    // The Event properties (i.e. through EventLoop() and WaitforEvent() also run through the parent.
    // Therefore, the Parent's WaitforEvent() and EventLoop() can be used to check for the new window's events.
    //
    // A subclassed window object may be passed in to override event callbacks, Main(), and other CWindow components.
    // This object is deleted automatically (i.e. the object passed in)
    //
    // SetMessageHandler() can be used to override event messages without overriding the window class
    //
    // When the User presses the 'X' window close button, a WindowClosing() for the new window will come back as true, and a 
    // CloseButtonPressed() event will be triggerred.
    //
	CWindow & NewWindow(int iX,int iY,int iWidth,int iHeight,const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// NewWindow -- Create a new popup window.
    // This creates a regular window with all of the functions and properties of the parent window.
    //
    // The Event properties (i.e. through EventLoop() and WaitforEvent() also run through the parent.
    // Therefore, the Parent's WaitforEvent() and EventLoop() can be used to check for the new window's events.
    //
    // A subclassed window object may be passed in to override event callbacks, Main(), and other CWindow components.
    // This object is deleted automatically (i.e. the object passed in)
    //
    // SetMessageHandler() can be used to override event messages without overriding the window class
    //
    // When the User presses the 'X' window close button, a WindowClosing() for the new window will come back as true, and a 
    // CloseButtonPressed() event will be triggerred.
    //
	CWindow & NewWindow(const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// Main() -- Creates a new window from a newly created class and runs the windows Main() function.
	//
	// This is designed to be used with the QuickConsole macro, where the defined classname is used in the Main() function
	//
	// For example, Main(new MyWindowClass,100,200) will create the MyWindowClass object and run MyWindowClass.Main()
	//
	// Do not delete the MyWindowClass object (notice that there is no object saved).  Once attached to a new window
	// through CSageBox, SageBox manages it and deletes the object when the window is destroyed.
	//
	int Main(CWindow * cWin,int iX,int iY,int iWidth,int iHeight,const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

	// Main() -- Creates a new window from a newly created class and runs the windows Main() function.
	//
	// This is designed to be used with the QuickConsole macro, where the defined classname is used in the Main() function
	//
	// For example, Main(new MyWindowClass,100,200) will create the MyWindowClass object and run MyWindowClass.Main()
	//
	// Do not delete the MyWindowClass object (notice that there is no object saved).  Once attached to a new window
	// through CSageBox, SageBox manages it and deletes the object when the window is destroyed.
	//
	int Main(CWindow * cWin,const char * sWinTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

    // This is used to register a widget with SageBox.
    // The primary use for this is for the widget to register with Sagebox when called by Sagebox.
    // 
    // When Sagebox calls the Widget::Register() function, the widget calls this function,
    // which fille the provided RegistryID with an ID for the widget that it can use to work with dialog boxes
    // created by Sagelight.
    //
    // Note:: this is not a user function and is used by SageBox and Widgets
    // 
	int RegisterWidget(int & iRegistryID);

    // This is used to register a widget with SageBox.
    // The primary use for this is for the widget to register with Sagebox when called by Sagebox.
    // 
    // When Sagebox calls the Widget::Register() function, the widget calls this function,
    // which fille the provided RegistryID with an ID for the widget that it can use to work with dialog boxes
    // created by Sagelight.
    //
    // Note:: this is not a user function and is used by SageBox and Widgets
    // 
	CDialog & NewDialog(int iX,int iY,int iWidth = 0,int iHeight = 0,const char * sTitle = nullptr,const cwfOpt & cwOpt = cwfOpt());

    // This is used to register a widget with SageBox.
    // The primary use for this is for the widget to register with Sagebox when called by Sagebox.
    // 
    // When Sagebox calls the Widget::Register() function, the widget calls this function,
    // which fille the provided RegistryID with an ID for the widget that it can use to work with dialog boxes
    // created by Sagelight.
    //
    // Note:: this is not a user function and is used by SageBox and Widgets
    // 
	CDialog & NewDialog(int iX,int iY,int iWidth,int iHeight,const cwfOpt & cwOpt);

    // This is used to register a widget with SageBox.
    // The primary use for this is for the widget to register with Sagebox when called by Sagebox.
    // 
    // When Sagebox calls the Widget::Register() function, the widget calls this function,
    // which fille the provided RegistryID with an ID for the widget that it can use to work with dialog boxes
    // created by Sagelight.
    //
    // Note:: this is not a user function and is used by SageBox and Widgets
    // 
	CDialog & NewDialog(int iX,int iY,const char * sTitle,const cwfOpt & cwOpt = cwfOpt());

    // This is used to register a widget with SageBox.
    // The primary use for this is for the widget to register with Sagebox when called by Sagebox.
    // 
    // When Sagebox calls the Widget::Register() function, the widget calls this function,
    // which fille the provided RegistryID with an ID for the widget that it can use to work with dialog boxes
    // created by Sagelight.
    //
    // Note:: this is not a user function and is used by SageBox and Widgets
    // 
	CDialog & NewDialog(int iX,int iY,const cwfOpt & cwOpt = cwfOpt());

	// dialog functions. See documentation by pressing "dialog." for function list, or see CWindow for documentation
	//
	CWindow::WinDialog dialog;

    // EventLoop() -- Wait for a user event.  Even though the main SageBox window is not visible, all other controls
	// run through this EventLoop.
    //
    // This is the Main Event Loop for procedurally-driven programs to capture events without using event callbacks.
    //
    // EventLoop() returns for relavent events from the user.  It does not return for all Windows events, only those that affect the running of the
    // program.  All Windows message events can be intercepted by subclassing the window or using SetMessageHandler() to capture all messages.
    //
    //
    // EventLoop() returns if the window is closing with the WaitEvent::WindowClosing status. 
	// For the main (hidden) SageBox window, this must be exited to close the program since the window
	// does not display and there is now way to close it by choice.
    // 
    // Important Note:  Make sure EventLoop() does not return until it sees events.  With empty windows or corrupted windows, EventLoop()
    // can enter a processor-using wild loop.   When testing, it is a good idea to have printfs() to the window or console to make sure
    // only events are returned and it is not caught in a spining loop. 
    //
	bool EventLoop(Sage::WaitEvent * eStatus = nullptr); 

    // QuickButton() -- Put up a quick button and information line. 
    //
    // This is used for quick Input-and-Go buttons, to stop program execution and get a quick button to continue.
    // QuickButton() simply puts up a "press to continue" message with an Ok button.
    //
    // The text can be is changed by setting sText.
    // The ProgramName (if it is set) is set in the title bar, unless sTitleBar is set other text
    //
    // QuickButton() is similar to dialog.Info(), but uses a smaller font.
    // 
    // Multiple lines may be entered with '\n', and long lines are automatically broken into multiple lines
    //
	dllvirt void QuickButton(const char * sText = nullptr,const char * sTitleBar = nullptr) dllvoid;

    // WinMessageBox() -- Bring up a standard Windows Message Box. 
    //
    // This follows the same format as ::MessageBox() in windows and simply calls it in the same way. 
    //
    // This allows more "Windows-like" messages, information, warnings, etc.
    //
    // Example: WinMessageBox("This is the message","This is the title",MB_OK | MB_ICONINFO)
    //
	int WinMessageBox(const char * sMessage,const char * sTitle,unsigned int dwFlags);

    // Sets the Program/Application name.  This can also be set when initiating Sagebox, i.e. CSageBox("My Application"); 
    //
    // The Application name is used in various window title bars in SageBox.  With no Program Name set, either the window title is blank or a default
    // text string is used.
    //
	void SetProgramName(const char * sAppName); 

    // Gets the program name set in SageBox through either the SageBox constructor (i.e. CSageBox("My Application") or through GetProgramName();
    //
    const char * GetProgramName();

    // GetInteger() -- Creates an Edit Box at the current console cursor (X,Y) point and waits for the user to enter an integer
    //
    // Pressing <CR> or the window closing will return from GetInteger().  Empty input (ESC or empty line) is treated as a 0 unless it is disabled with options listed below.
    //
        // GetInteger() will return immediately of WindowClosing() is true, allowing multiple console input functions in the code, as they will all fall through so you may
    // handle WindowClosing() without handling multiple Console Input functions
    //
    // --> iDefault -- the iDefault parameter sets the default value for input, and will set the input caret at the end of the line.
    //
    // Parameters in sControl
    //
    // --> Min()            -- Set minimum value.  A value entered below this value will generate an error and prompt the user to enter another value
    // --> Max()            -- Set maximum value.  A value entered below this value will generate an error and prompt the user to enter another value
    // --> Range()          -- Set minimum and maximum value.  A value entered outside this range will generate an error and prompt the user to enter another value
    // --> WinColors()      -- Sets a color scheme to a the current window colors, blending the box (i.e. there is no input box)
    // --> ColorsBW()       -- (default) Sets a color scheme to a white background with black text, allowing the box to stand out. The default color is the current windows background color
    //                         and text color, showing the input as the same color of the window text displayed in the window.
    //
    // --> fgColor()        -- Sets the color to any defined color in the system, i.e. "TextColor=Red", or TextColor=MyDefinedColor" this may be abbreviated as "fgColor=" or "bg="
    // --> bgColor()        -- Sets the background color for the text, i.e. "BgColor=lightgray" or "BgColor=MyDefinedColor"
    // --> NoEscDefault()   -- When set, pressing the ESC will clear the entire line and not reset to any default text
    // --> NoEsc()          -- When set, the ESC key does nothing.  Default behavior causes the ESC key to either clear the text line or reset it to the default text (see: "NoEscDefault")
    // --> AddBorder()      -- Put a border around the input box.  Default behavior is no border.  "Border" puts a small border around the input box for Clarity.
    // --> ThickBorder()    -- Puts a thick border around the input box, appearing more like a window rather than an input box.
    // --> NoBlankEntry()   -- Does not return unless some text is entered (i.e. will not return on a blank line).  If the Window is closing (WindowClosing() is true), GetString() will return regardless.
    //
	int GetInteger(const char * sTitle,bool & bCancelled,const cwfOpt & cwOptions = cwfOpt());

    // GetInteger() -- Creates an Edit Box at the current console cursor (X,Y) point and waits for the user to enter an integer
    //
    // Pressing <CR> or the window closing will return from GetInteger().  Empty input (ESC or empty line) is treated as a 0 unless it is disabled with options listed below.
    //
        // GetInteger() will return immediately of WindowClosing() is true, allowing multiple console input functions in the code, as they will all fall through so you may
    // handle WindowClosing() without handling multiple Console Input functions
    //
    // --> iDefault -- the iDefault parameter sets the default value for input, and will set the input caret at the end of the line.
    //
    // Parameters in sControl
    //
    // --> Min()            -- Set minimum value.  A value entered below this value will generate an error and prompt the user to enter another value
    // --> Max()            -- Set maximum value.  A value entered below this value will generate an error and prompt the user to enter another value
    // --> Range()          -- Set minimum and maximum value.  A value entered outside this range will generate an error and prompt the user to enter another value
    // --> WinColors()      -- Sets a color scheme to a the current window colors, blending the box (i.e. there is no input box)
    // --> ColorsBW()       -- (default) Sets a color scheme to a white background with black text, allowing the box to stand out. The default color is the current windows background color
    //                         and text color, showing the input as the same color of the window text displayed in the window.
    //
    // --> fgColor()        -- Sets the color to any defined color in the system, i.e. "TextColor=Red", or TextColor=MyDefinedColor" this may be abbreviated as "fgColor=" or "bg="
    // --> bgColor()        -- Sets the background color for the text, i.e. "BgColor=lightgray" or "BgColor=MyDefinedColor"
    // --> NoEscDefault()   -- When set, pressing the ESC will clear the entire line and not reset to any default text
    // --> NoEsc()          -- When set, the ESC key does nothing.  Default behavior causes the ESC key to either clear the text line or reset it to the default text (see: "NoEscDefault")
    // --> AddBorder()      -- Put a border around the input box.  Default behavior is no border.  "Border" puts a small border around the input box for Clarity.
    // --> ThickBorder()    -- Puts a thick border around the input box, appearing more like a window rather than an input box.
    // --> NoBlankEntry()   -- Does not return unless some text is entered (i.e. will not return on a blank line).  If the Window is closing (WindowClosing() is true), GetString() will return regardless.
    //
	int GetInteger(const char * sTitle = nullptr,const cwfOpt & cwOptions = cwfOpt());

    // console.GetFloat() -- Get a floating-point value from the user, in an inline console-style input (i.e. as part of a text line rather than a windowed box)
    //
    // This function will get a small set of input from the user (typical a window of 15 characters or so) and return the floating point value once the user presses return.
    //
    // Basic Forms:
    //
    // --> double MyValue = GetFloat().                        -- Get a float value with default options
    // --> double MyValue = GetFloat(123.56).                -- Get a float value with default set to 123.56
    // --> double MyValue = GetFloat(<<options>>).            -- Get a float value with an option string and no default (see examples below)
    // --> double MyValue = GetFloat(123.56,<<options>>).    -- Get a float value with a default set to 123.56 and also specify options (see examples below)
    //
    // Inputs (all optional):
    //
    //        fDefault        - Default value that will be placed in the box when it first appears.  The user can then change it
    //      sOptions        - Text-based options to control the input and output
    //        cwOptions        - opt::Option()-style options -- you can use Text or opt::-style options, depending on your preference.
    //
    // --> Example: double MyValue = GetFloat(123.56,"range=-100,100,colorsBW")
    //              double Myalue = GetFloat(123.56,opt::Range(-100,100) | opt::ColorsBW())
    //
    // Both of these examples perform the same function: Set a default of "123.56", set a range of -100,100, and tell the box to have a white background with black text
    //
    //--> Available Options
    //
    // Range            -- Range of the value (i.e. Range(-100,100)).  If the input is outside the range, an error message appears telling the user to enter a number within the range specified.
    // MinValue            -- Sets the minimum value (i.e. MinValue(-100)).  If the input is less than the MinValue, an error message appears telling the user to enter a number above the MinValue
    // MaxValue            -- Sets the Maximum Value allowed.  If the input is greater than the MaxValue, an error message appears elling the user to enter a number less then the MinValue
    // ColorsBW            -- Sets the background of the box to white, with black text.  This can make the box more visible.  Otherwise, the box is the windows background color and current text color
    // NoBorder            -- Default is a thin border for visibility.  the "NoBorder" option will remove the border so the text looks more like normal text in the overall text output line.
    // ThickBorder        -- Provides a recessed window that looks more like an input window, but still in the text line.
    // NoBlankLine        -- Does not allow the user to enter a blank line.  When this is off (default), when the user presses enter with a blank line, the default value is returned (or 0 when here was no default set)
    // 
    // --> Examples
    //
    // --> double MyValue = console.GetFloat()                                                 -- Gets a float with default display set and no default alue
    // --> double MyValue = console.GetFloat(123.56)                                           -- Gets a float with default display set and with default value = 123.56
    // --> double MyValue = console.GetFloat(123.56,"NoBorder,MinValue=-100");                 -- string-style options
    // --> double MyValue = console.GetFloat(123.56,opt::NoBorder() | opt::MinValue(-100))     -- opt::-style options
    //
    // ** You can also use in >> MyValue to use C++ input stream style
    //
    // --> Same examples as above (assuming MyValue is defined as "double MyValue" ahead of the call):
    //
    // --> in >> MyValue                                                                       -- Gets a float with default display set and no default alue
    // --> in >> opt::Default(123.56) >> MyValue                                               -- Gets a float with default display set and with default value = 123.56
    // --> in >> opt::Default(123.56) >> opt::NoBorder() >> opt::MinValue(-100) >> MyValue;    -- opt::-style options
    // --> in >> Default(123.56) >> NoBorder() >> MinValue(-100) >> MyValue;                   -- opt::-style options (when "using namespace opt" is specified)
    //
    // After a certain point, it makes sense to use console.GetFloat() (over stream-style "in >> MyValue) when a large amount of options are used.  
    // For simple calls and prototyping, using "in >> MyValue" or things like "in >> opt::ColorwsBW >> MyValue" can be much quicker and easier to read, but
    // can be more clear using console.GetFLoat() when many options are being used (see above examples).
    //
    // There are 4 different function prototypes so that options can be omitted when not required.
    //
	dllvirt double GetFloat(const char * sTitle,bool & bCancelled,const cwfOpt & cwOptions = cwfOpt()) dllfloat;

    // console.GetFloat() -- Get a floating-point value from the user, in an inline console-style input (i.e. as part of a text line rather than a windowed box)
    //
    // This function will get a small set of input from the user (typical a window of 15 characters or so) and return the floating point value once the user presses return.
    //
    // Basic Forms:
    //
    // --> double MyValue = GetFloat().                        -- Get a float value with default options
    // --> double MyValue = GetFloat(123.56).                -- Get a float value with default set to 123.56
    // --> double MyValue = GetFloat(<<options>>).            -- Get a float value with an option string and no default (see examples below)
    // --> double MyValue = GetFloat(123.56,<<options>>).    -- Get a float value with a default set to 123.56 and also specify options (see examples below)
    //
    // Inputs (all optional):
    //
    //        fDefault        - Default value that will be placed in the box when it first appears.  The user can then change it
    //      sOptions        - Text-based options to control the input and output
    //        cwOptions        - opt::Option()-style options -- you can use Text or opt::-style options, depending on your preference.
    //
    // --> Example: double MyValue = GetFloat(123.56,"range=-100,100,colorsBW")
    //              double Myalue = GetFloat(123.56,opt::Range(-100,100) | opt::ColorsBW())
    //
    // Both of these examples perform the same function: Set a default of "123.56", set a range of -100,100, and tell the box to have a white background with black text
    //
    //--> Available Options
    //
    // Range            -- Range of the value (i.e. Range(-100,100)).  If the input is outside the range, an error message appears telling the user to enter a number within the range specified.
    // MinValue            -- Sets the minimum value (i.e. MinValue(-100)).  If the input is less than the MinValue, an error message appears telling the user to enter a number above the MinValue
    // MaxValue            -- Sets the Maximum Value allowed.  If the input is greater than the MaxValue, an error message appears elling the user to enter a number less then the MinValue
    // ColorsBW            -- Sets the background of the box to white, with black text.  This can make the box more visible.  Otherwise, the box is the windows background color and current text color
    // NoBorder            -- Default is a thin border for visibility.  the "NoBorder" option will remove the border so the text looks more like normal text in the overall text output line.
    // ThickBorder        -- Provides a recessed window that looks more like an input window, but still in the text line.
    // NoBlankLine        -- Does not allow the user to enter a blank line.  When this is off (default), when the user presses enter with a blank line, the default value is returned (or 0 when here was no default set)
    // 
    // --> Examples
    //
    // --> double MyValue = console.GetFloat()                                                 -- Gets a float with default display set and no default alue
    // --> double MyValue = console.GetFloat(123.56)                                           -- Gets a float with default display set and with default value = 123.56
    // --> double MyValue = console.GetFloat(123.56,"NoBorder,MinValue=-100");                 -- string-style options
    // --> double MyValue = console.GetFloat(123.56,opt::NoBorder() | opt::MinValue(-100))     -- opt::-style options
    //
    // ** You can also use in >> MyValue to use C++ input stream style
    //
    // --> Same examples as above (assuming MyValue is defined as "double MyValue" ahead of the call):
    //
    // --> in >> MyValue                                                                       -- Gets a float with default display set and no default alue
    // --> in >> opt::Default(123.56) >> MyValue                                               -- Gets a float with default display set and with default value = 123.56
    // --> in >> opt::Default(123.56) >> opt::NoBorder() >> opt::MinValue(-100) >> MyValue;    -- opt::-style options
    // --> in >> Default(123.56) >> NoBorder() >> MinValue(-100) >> MyValue;                   -- opt::-style options (when "using namespace opt" is specified)
    //
    // After a certain point, it makes sense to use console.GetFloat() (over stream-style "in >> MyValue) when a large amount of options are used.  
    // For simple calls and prototyping, using "in >> MyValue" or things like "in >> opt::ColorwsBW >> MyValue" can be much quicker and easier to read, but
    // can be more clear using console.GetFLoat() when many options are being used (see above examples).
    //
    // There are 4 different function prototypes so that options can be omitted when not required.
    //
    virtual double GetFloat(const char * sTitle = nullptr,const cwfOpt & cwOptions = cwfOpt());


    // GetString() -- Creates an Edit Box at the current console cursor (X,Y) point and waits for the user to enter text an press return.
    //
    // Pressing <CR> or the window closing will return from GetString().  Empty input is defined by a "" string.  Check return value [0] == 0 for no string entry. Unlike some functions, NULLPTR is not returned. 
    //
    // Pressing ESC will clear the text entry, remaining in the edit box for more input.  When there is a default set of text, the text will revert to the original default.
    //
    // GetString() will return immediately of WindowClosing() is true, allowing multiple console input functions in the code, as they will all fall through so you may
    // handle WindowClosing() without handling multiple Console Input functions
    //
    // --> sDefaut -- the sDefault parameter sets the default text for the text input, and will set the input caret at the end of the line.
    //
    // Parameters in sControl
    //
    // --> WinColors()      -- Sets a color scheme to a the current window colors, blending the box (i.e. there is no input box)
    // --> ColorsBW()       -- (default) Sets a color scheme to a white background with black text, allowing the box to stand out. The default color is the current windows background color
    //                         and text color, showing the input as the same color of the window text displayed in the window.
    //
    // --> fgColor()        -- Sets the color to any defined color in the system, i.e. "TextColor=Red", or TextColor=MyDefinedColor" this may be abbreviated as "fgColor=" or "bg="
    // --> bgColor()        -- Sets the background color for the text, i.e. "BgColor=lightgray" or "BgColor=MyDefinedColor"
    // --> Width()          -- Sets the width of the window in pixels.  The default sets the input window to the remainer of the window width from 
    //                         the start point (current console write position), which may seem too big.  "Width=100" sets the box with to 100 pixels, "With=50" sets it to 50, etc. 
    // --> CharWidth()      -- Sets the width of the window to number of chars in "CharWidth" based on average character width for the current font.
    //                         For example, "CharWidth=10" sizes the edit box to the width of 10 characters for the current font. This setting does not affect the number of characters
    //                         entered in the box, unless the "noscroll" option is set. 
    //                         If the "noscroll" option is set, input stops at the end of the box. Otherwise, the text will scroll horizontally as more text is entered
    // --> MaxChars()       -- Sets maximum number of characters that can be entered, regardless of window size (overrules "CharWidth" when "CharWidth" allows more characters
    //                         than "MaxChars".  For example, "MaxChars=10" will allow no more than 10 characters to be entered, regardless of input box size.
    // --> AllowScroll()    -- Allows horizontal scrolling in the input box
    //                         box.  Default behavior is to scroll text horizontally so that any number of characters can be entered in any size input box.
    // --> NoEscDefault()   -- When set, pressing the ESC will clear the entire line and not reset to any default text
    // --> NoEsc()          -- When set, the ESC key does nothing.  Default behavior causes the ESC key to either clear the text line or reset it to the default text (see: "NoEscDefault")
    // --> AddBorder()      -- Put a border around the input box.  Default behavior is no border.  "Border" puts a small border around the input box for Clarity.
    // --> ThickBorder()    -- Puts a thick border around the input box, appearing more like a window rather than an input box.
    // --> NoBlankEntry()   -- Does not return unless some text is entered (i.e. will not return on a blank line).  If the Window is closing (WindowClosing() is true), GetString() will return regardless.
    //
    // Examples:
    //
    // auto MyString = MyWindow.Console.GetString();    -- Gets a string using defaults
    // auto MyString = MyConsole.GetString(SageOpt_Colors("bw") SageOpt_CharWidth(10) SageOpt_BgColor("Yellow") SageOpt_BlankDefault);
    //
	CString GetString(const char * sTitle,bool & bCancelled,const cwfOpt & cwOptions = cwfOpt());

    // GetString() -- Creates an Edit Box at the current console cursor (X,Y) point and waits for the user to enter text an press return.
    //
    // Pressing <CR> or the window closing will return from GetString().  Empty input is defined by a "" string.  Check return value [0] == 0 for no string entry. Unlike some functions, NULLPTR is not returned. 
    //
    // Pressing ESC will clear the text entry, remaining in the edit box for more input.  When there is a default set of text, the text will revert to the original default.
    //
    // GetString() will return immediately of WindowClosing() is true, allowing multiple console input functions in the code, as they will all fall through so you may
    // handle WindowClosing() without handling multiple Console Input functions
    //
    // --> sDefaut -- the sDefault parameter sets the default text for the text input, and will set the input caret at the end of the line.
    //
    // Parameters in sControl
    //
    // --> WinColors()      -- Sets a color scheme to a the current window colors, blending the box (i.e. there is no input box)
    // --> ColorsBW()       -- (default) Sets a color scheme to a white background with black text, allowing the box to stand out. The default color is the current windows background color
    //                         and text color, showing the input as the same color of the window text displayed in the window.
    //
    // --> fgColor()        -- Sets the color to any defined color in the system, i.e. "TextColor=Red", or TextColor=MyDefinedColor" this may be abbreviated as "fgColor=" or "bg="
    // --> bgColor()        -- Sets the background color for the text, i.e. "BgColor=lightgray" or "BgColor=MyDefinedColor"
    // --> Width()          -- Sets the width of the window in pixels.  The default sets the input window to the remainer of the window width from 
    //                         the start point (current console write position), which may seem too big.  "Width=100" sets the box with to 100 pixels, "With=50" sets it to 50, etc. 
    // --> CharWidth()      -- Sets the width of the window to number of chars in "CharWidth" based on average character width for the current font.
    //                         For example, "CharWidth=10" sizes the edit box to the width of 10 characters for the current font. This setting does not affect the number of characters
    //                         entered in the box, unless the "noscroll" option is set. 
    //                         If the "noscroll" option is set, input stops at the end of the box. Otherwise, the text will scroll horizontally as more text is entered
    // --> MaxChars()       -- Sets maximum number of characters that can be entered, regardless of window size (overrules "CharWidth" when "CharWidth" allows more characters
    //                         than "MaxChars".  For example, "MaxChars=10" will allow no more than 10 characters to be entered, regardless of input box size.
    // --> AllowScroll()    -- Allows horizontal scrolling in the input box
    //                         box.  Default behavior is to scroll text horizontally so that any number of characters can be entered in any size input box.
    // --> NoEscDefault()   -- When set, pressing the ESC will clear the entire line and not reset to any default text
    // --> NoEsc()          -- When set, the ESC key does nothing.  Default behavior causes the ESC key to either clear the text line or reset it to the default text (see: "NoEscDefault")
    // --> AddBorder()      -- Put a border around the input box.  Default behavior is no border.  "Border" puts a small border around the input box for Clarity.
    // --> ThickBorder()    -- Puts a thick border around the input box, appearing more like a window rather than an input box.
    // --> NoBlankEntry()   -- Does not return unless some text is entered (i.e. will not return on a blank line).  If the Window is closing (WindowClosing() is true), GetString() will return regardless.
    //
    // Examples:
    //
    // auto MyString = MyWindow.Console.GetString();    -- Gets a string using defaults
    // auto MyString = MyConsole.GetString(SageOpt_Colors("bw") SageOpt_CharWidth(10) SageOpt_BgColor("Yellow") SageOpt_BlankDefault);
    //
	CString GetString(const char * sTitle,const cwfOpt & cwOptions = cwfOpt());

    // Duplication of C++ console-mode getline()
    //
    // This is the same as GetString() except that the sring input is specified in the function call.
    // This is to duplicate the C++ getline() function.
    //
    // CString and std::string are supported.
    //
    // See GetString() for option usage.
    //
    void getline(CString & cString,const cwfOpt & cwOpt = cwfOpt());

    // Duplication of C++ console-mode getline()
    //
    // This is the same as GetString() except that the sring input is specified in the function call.
    // This is to duplicate the C++ getline() function.
    //
    // CString and std::string are supported.
    //
    // See GetString() for option usage.
    //
	void getline(std::string & cString,const cwfOpt & cwOpt = cwfOpt());

	// Dialog Info/Question Windows

	void InfoDialog(const char * sTitle,const cwfOpt & cwOptions = cwfOpt());
	bool YesNoDialog(const char * sTitle,const cwfOpt & cwOptions = cwfOpt());
	Sage::DialogResult YesNoCancelDialog(const char * sTitle,const cwfOpt & cwOptions = cwfOpt());
	bool OkCancelDialog(const char * sTitle,const cwfOpt & cwOptions = cwfOpt());

	// Please Wait Window Functions

    // PleaseWaitWindow() - Open Please Wait Window
    //
    // Input String:
    //
    // --> Input String can be text-based, i.e. PleaseWaitWindow("ProgressBar,HideCancel") or Opt Strings, i.e. PleaseWaitWindow(opts::ProgressBar() | opt::HideCancel());
    // ----> One string puts a subtitle under "Please Wait...", i.e. PleaseWaitWindow("System is doing something"); 
    // ----> Two Strings replaces "Please Wait.." with text, then puts sub-title for second line, i.e. PleaseWaitWindow("Wait a few seconds...\nSystem is doing something");
    // ----> Inserting a Sring with '+' changes title bar text, i.e. PleaseWaitWindow('+My Program\nWait a few seconds...\nSystem is doing something") sets "My Program" as small window title.
    //
    // Options:
    //
    // ----> CancelOk            - Adds a Cancel button.  This can be chacked with PleaseWaitCancelled()
    // ----> HideCancel            - Adds a hidden cancel button that can be shown or re-hidden.  Can be used to delay cancel ability. Also Useful with PleaseWaitGetOk().
    // ----> ProgressBar        - Adds a Progress Bar that can be updated with SetPleaseWaitProgress()
    //
    // Examples:
    // ----> PleaseWaitWindow();    -- Opens a simple please wait window, with no button.  Closed with ClosePleaseWaitWindow();
    // ----> PleaseWaitWindow(opt::ProgressBar()) or PleaseWaitWindow("progressbar") -- Opens a Please Wait Window with a progress bar
    // ----> PleaseWaitWindow("System is Calculating Information",opt::CancelOk()) -- Opens a Please Wait Window with a subtitle and cancel button (which may be checked with PleaseWaitCancelled())
    // ----> Typically accessed as a dialog function, i.e. MyWindow->dialog.PleaseWaitWindow();
    //
	void PleaseWaitWindow(const char * sText = nullptr,const char * sOptions = nullptr);

    // PleaseWaitWindow() - Open Please Wait Window
    //
    // Input String:
    //
    // --> Input String can be text-based, i.e. PleaseWaitWindow("ProgressBar,HideCancel") or Opt Strings, i.e. PleaseWaitWindow(opts::ProgressBar() | opt::HideCancel());
    // ----> One string puts a subtitle under "Please Wait...", i.e. PleaseWaitWindow("System is doing something"); 
    // ----> Two Strings replaces "Please Wait.." with text, then puts sub-title for second line, i.e. PleaseWaitWindow("Wait a few seconds...\nSystem is doing something");
    // ----> Inserting a Sring with '+' changes title bar text, i.e. PleaseWaitWindow('+My Program\nWait a few seconds...\nSystem is doing something") sets "My Program" as small window title.
    //
    // Options:
    //
    // ----> CancelOk            - Adds a Cancel button.  This can be chacked with PleaseWaitCancelled()
    // ----> HideCancel            - Adds a hidden cancel button that can be shown or re-hidden.  Can be used to delay cancel ability. Also Useful with PleaseWaitGetOk().
    // ----> ProgressBar        - Adds a Progress Bar that can be updated with SetPleaseWaitProgress()
    //
    // Examples:
    // ----> PleaseWaitWindow();    -- Opens a simple please wait window, with no button.  Closed with ClosePleaseWaitWindow();
    // ----> PleaseWaitWindow(opt::ProgressBar()) or PleaseWaitWindow("progressbar") -- Opens a Please Wait Window with a progress bar
    // ----> PleaseWaitWindow("System is Calculating Information",opt::CancelOk()) -- Opens a Please Wait Window with a subtitle and cancel button (which may be checked with PleaseWaitCancelled())
    // ----> Typically accessed as a dialog function, i.e. MyWindow->dialog.PleaseWaitWindow();
    //
	void PleaseWaitWindow(const char * sText,const cwfOpt cwOptions);

    // PleaseWaitWindow() - Open Please Wait Window
    //
    // Input String:
    //
    // --> Input String can be text-based, i.e. PleaseWaitWindow("ProgressBar,HideCancel") or Opt Strings, i.e. PleaseWaitWindow(opts::ProgressBar() | opt::HideCancel());
    // ----> One string puts a subtitle under "Please Wait...", i.e. PleaseWaitWindow("System is doing something"); 
    // ----> Two Strings replaces "Please Wait.." with text, then puts sub-title for second line, i.e. PleaseWaitWindow("Wait a few seconds...\nSystem is doing something");
    // ----> Inserting a Sring with '+' changes title bar text, i.e. PleaseWaitWindow('+My Program\nWait a few seconds...\nSystem is doing something") sets "My Program" as small window title.
    //
    // Options:
    //
    // ----> CancelOk            - Adds a Cancel button.  This can be chacked with PleaseWaitCancelled()
    // ----> HideCancel            - Adds a hidden cancel button that can be shown or re-hidden.  Can be used to delay cancel ability. Also Useful with PleaseWaitGetOk().
    // ----> ProgressBar        - Adds a Progress Bar that can be updated with SetPleaseWaitProgress()
    //
    // Examples:
    // ----> PleaseWaitWindow();    -- Opens a simple please wait window, with no button.  Closed with ClosePleaseWaitWindow();
    // ----> PleaseWaitWindow(opt::ProgressBar()) or PleaseWaitWindow("progressbar") -- Opens a Please Wait Window with a progress bar
    // ----> PleaseWaitWindow("System is Calculating Information",opt::CancelOk()) -- Opens a Please Wait Window with a subtitle and cancel button (which may be checked with PleaseWaitCancelled())
    // ----> Typically accessed as a dialog function, i.e. MyWindow->dialog.PleaseWaitWindow();
    //
	void PleaseWaitWindow(const cwfOpt cwOptions);

    // ClosePlaseWait() -- Hides and Closes opened Please Wait Window
    //
	void ClosePleaseWait();

    // PleaseWaitCancelled() -- Returns true if the Cancel button was pressed on the Please Wait Window.  False, if not or Please Wait Window is not active.
    //
	bool PleaseWaitCancelled(Sage::Peek peek = Sage::Peek::No);

    // PleaseWaitGetOk() -- Changes "Cancel" button to "Ok" button and waits for the button to be pressed.  This is useful when a function has completed and you want to
    //                      make sure the user knows it is finish.
    //
    // This function returns TRUE when the butto is pressed, if the Cancel button exists (i.e. either "CancelOk" or "HideCancel" was specified).  Otherwise, TRUE is returned immediately
    //
	bool PleaseWaitGetOk();

    // PleaseWaitShowCancel() -- Shows (or Hides) the Cancel button.   If opt::CancelOk() or opt::HideCancel() is set in the PleaseWaitWindow() call, PleaseWaitShowCancel() will
    // hide or show the cancel button. 
    //
    // Input:
    //
    // PleaseWaitShowCancel(true) -- Shows the cancel button
    // PleaseWaitShowCancel(false) -- Hide the cancel button
    //
	bool PleaseWaitShowCancel(bool bShow = true);

    // SetPleaseWaitProgress() -- Sets the progress bar percent on the Please Wait Window
    //
    // This will set the bar to the percentage specified. For example, PleaseWaitProgress(57) will set the progress bar to 57% and print "57%" in the middle of the progress bar.
    //
    // Input:
    // --> iPercent: Percent completed, from 0-100
    // --> sMessage: When specified, replaces the percent display with the message.  This is useful for initialization or completion, for example:
    //      SetPleaseWaitProgress(100,"Finished.") will place "finished" on the progress bar instead of 100%
    //
    // Example:
    //    ----> SetPleaseWaitProgress(10,"Finished.");
    //    ----> PleaseWaitGetOk(); 
    //
    // --> These two lines show the progress bar full with the label "finished" within the progress bar.  The second line then changes the "Cancel" button to "Ok" and waits for the user to press it.
    //
    void SetPleaseWaitProgress(int iPercent,char * sMessage = nullptr);


    // Open a file through the windows dialog, allowing setting title, file types, and other criteria.
    // 
    // CString comes back empty if no file is chosen.
    // If CString is specified in the function, a bool is returned: TRUE if there is a filename,
    // FALSE if aborted by the user.
    // 
    // Use GetOpenFleStruct() or declare stOpenFileStruct to fill the structure.
    //
    // See notes on stOpenFilestruct to fill the requirements properly.
    //
    // This blocks program execution until the user selects a file or cancels.
    //
    // For a quick open, use GetOpenFile() with only file types, such as GetOpenFile("*.bmp;*.jpg"), etc.
    // Note: Use ';' to separate types.
    //
	CString GetOpenFile(Sage::stOpenFileStruct & stFile);

    // Open a file through the windows dialog, allowing setting title, file types, and other criteria.
    // 
    // CString comes back empty if no file is chosen.
    // If CString is specified in the function, a bool is returned: TRUE if there is a filename,
    // FALSE if aborted by the user.
    // 
    // Use GetOpenFleStruct() or declare stOpenFileStruct to fill the structure.
    //
    // See notes on stOpenFilestruct to fill the requirements properly.
    //
    // This blocks program execution until the user selects a file or cancels.
    //
    // For a quick open, use GetOpenFile() with only file types, such as GetOpenFile("*.bmp;*.jpg"), etc.
    // Note: Use ';' to separate types.
    //
    CString GetOpenFile(const char * sTypes = nullptr);
	
    // Open a file through the windows dialog, allowing setting title, file types, and other criteria.
    // 
    // CString comes back empty if no file is chosen.
    // If CString is specified in the function, a bool is returned: TRUE if there is a filename,
    // FALSE if aborted by the user.
    // 
    // Use GetOpenFleStruct() or declare stOpenFileStruct to fill the structure.
    //
    // See notes on stOpenFilestruct to fill the requirements properly.
    //
    // This blocks program execution until the user selects a file or cancels.
    //
    // For a quick open, use GetOpenFile() with only file types, such as GetOpenFile("*.bmp;*.jpg"), etc.
    // Note: Use ';' to separate types.
    //
	bool GetOpenFile(Sage::stOpenFileStruct & stFile,CString & csFilename);
    // Open a file through the windows dialog, allowing setting title, file types, and other criteria.
    // 
    // CString comes back empty if no file is chosen.
    // If CString is specified in the function, a bool is returned: TRUE if there is a filename,
    // FALSE if aborted by the user.
    // 
    // Use GetOpenFleStruct() or declare stOpenFileStruct to fill the structure.
    //
    // See notes on stOpenFilestruct to fill the requirements properly.
    //
    // This blocks program execution until the user selects a file or cancels.
    //
    // For a quick open, use GetOpenFile() with only file types, such as GetOpenFile("*.bmp;*.jpg"), etc.
    // Note: Use ';' to separate types.
    //
	bool GetOpenFile(const char * sTypes,CString & csFilename);

    // Open a file through the windows dialog, allowing setting title, file types, and other criteria.
    // 
    // CString comes back empty if no file is chosen.
    // If CString is specified in the function, a bool is returned: TRUE if there is a filename,
    // FALSE if aborted by the user.
    // 
    // Use GetOpenFleStruct() or declare stOpenFileStruct to fill the structure.
    //
    // See notes on stOpenFilestruct to fill the requirements properly.
    //
    // This blocks program execution until the user selects a file or cancels.
    //
    // For a quick open, use GetOpenFile() with only file types, such as GetOpenFile("*.bmp;*.jpg"), etc.
    // Note: Use ';' to separate types.
    //
	bool GetOpenFile(CString & csFilename);

    // GetOpenFileStruct() -- Return an stOpenFileStruct to set for using an GetOpenFile() or GetSaveFile() dialog.
    //
    // This is a shortcut for declaring a structure directly, so that auto& stStruct = GetOpenFileStruct() can be used
    // more easily.
    //
    Sage::stOpenFileStruct GetOpenFileStruct();

    // QuickThumbnail() -- Create and display a window with a thumbnail of bitmap data.
    //
    // This is used for development to show thumbnails of bitmap data in memory, in various forms and in various ways.
    //
    // The bitmap can be display by percentage, maximum width, height, etc.
    // See Sage::ThumbType for all variations
    //
    // If there is an error in the data (i.e. an empty bitmap), the window is not opened.
    // 
    // A RawBitmap_t or CSageBitmap must currently be provided.
    // Raw data and more data types (such as float, float mono, 16-bit bitmaps, etc.) will be supported in a future release.
    //
    bool QuickThumbnail(Sage::RawBitmap_t & stBitmap,int iWidth,int iHeight,Sage::ThumbType eType,const char * sTitle = nullptr);

    // QuickThumbnail() -- Create and display a window with a thumbnail of bitmap data.
    //
    // This is used for development to show thumbnails of bitmap data in memory, in various forms and in various ways.
    //
    // The bitmap can be display by percentage, maximum width, height, etc.
    // See Sage::ThumbType for all variations
    //
    // If there is an error in the data (i.e. an empty bitmap), the window is not opened.
    // 
    // A RawBitmap_t or CSageBitmap must currently be provided.
    // Raw data and more data types (such as float, float mono, 16-bit bitmaps, etc.) will be supported in a future release.
    //
	bool QuickThumbnail(Sage::RawBitmap_t & stBitmap,int iWidth,int iHeight,const char * sTitle = nullptr);

        // QuickThumbnail() -- Create and display a window with a thumbnail of bitmap data.
    //
    // This is used for development to show thumbnails of bitmap data in memory, in various forms and in various ways.
    //
    // The bitmap can be display by percentage, maximum width, height, etc.
    // See Sage::ThumbType for all variations
    //
    // If there is an error in the data (i.e. an empty bitmap), the window is not opened.
    // 
    // A RawBitmap_t or CSageBitmap must currently be provided.
    // Raw data and more data types (such as float, float mono, 16-bit bitmaps, etc.) will be supported in a future release.
    //
    bool QuickThumbnail(CSageBitmap & cBitmap,int iWidth,int iHeight,Sage::ThumbType eType,const char * sTitle = nullptr);

    // QuickThumbnail() -- Create and display a window with a thumbnail of bitmap data.
    //
    // This is used for development to show thumbnails of bitmap data in memory, in various forms and in various ways.
    //
    // The bitmap can be display by percentage, maximum width, height, etc.
    // See Sage::ThumbType for all variations
    //
    // If there is an error in the data (i.e. an empty bitmap), the window is not opened.
    // 
    // A RawBitmap_t or CSageBitmap must currently be provided.
    // Raw data and more data types (such as float, float mono, 16-bit bitmaps, etc.) will be supported in a future release.
    //
	bool QuickThumbnail(CSageBitmap & cBitmap,int iWidth,int iHeight,const char * sTitle = nullptr);


    // BitmapWindow() -- Create a window (popup or embedded) designed to show bitmaps.
    //
    // This can create a popup window or embedded window, with a bitmap included to display on creation.
    // When no location (iX,iY) is given the window pops up automatially (i.e. a separate window).
    // Otherwise, when iX and iY are given, the window is embedded into the parent window unless:
    //
    // When Popup() (i.e. opt::Popup()) is given as an option, the window is not embedded and a new popup window is 
    // created.
    //
    // The window is sized to the input bitmap.
    //
    // Once the window is created, it may be treated as any window.
    // Note: With Bitmap Popup Windows(), when the 'X' is pressed, the window is automatically closed
    // unlike regular CWindow windows where the 'X' button sets a notification and WindowClosing() status.
    //
	CWindow & BitmapWindow(Sage::RawBitmap_t & stBitmap,const cwfOpt & cwOpt = cwfOpt());

    // BitmapWindow() -- Create a window (popup or embedded) designed to show bitmaps.
    //
    // This can create a popup window or embedded window, with a bitmap included to display on creation.
    // When no location (iX,iY) is given the window pops up automatially (i.e. a separate window).
    // Otherwise, when iX and iY are given, the window is embedded into the parent window unless:
    //
    // When Popup() (i.e. opt::Popup()) is given as an option, the window is not embedded and a new popup window is 
    // created.
    //
    // The window is sized to the input bitmap.
    //
    // Once the window is created, it may be treated as any window.
    // Note: With Bitmap Popup Windows(), when the 'X' is pressed, the window is automatically closed
    // unlike regular CWindow windows where the 'X' button sets a notification and WindowClosing() status.
    //
	CWindow & BitmapWindow(CSageBitmap & cBitmap,const cwfOpt & cwOpt = cwfOpt());

    // BitmapWindow() -- Create a window (popup or embedded) designed to show bitmaps.
    //
    // This can create a popup window or embedded window, with a bitmap included to display on creation.
    // When no location (iX,iY) is given the window pops up automatially (i.e. a separate window).
    // Otherwise, when iX and iY are given, the window is embedded into the parent window unless:
    //
    // When Popup() (i.e. opt::Popup()) is given as an option, the window is not embedded and a new popup window is 
    // created.
    //
    // The window is sized to the input bitmap.
    //
    // Once the window is created, it may be treated as any window.
    // Note: With Bitmap Popup Windows(), when the 'X' is pressed, the window is automatically closed
    // unlike regular CWindow windows where the 'X' button sets a notification and WindowClosing() status.
    //
	CWindow & BitmapWindow(int iX,int iY,CSageBitmap & cBitmap,const cwfOpt & cwOpt = cwfOpt());

    // BitmapWindow() -- Create a window (popup or embedded) designed to show bitmaps.
    //
    // This can create a popup window or embedded window, with a bitmap included to display on creation.
    // When no location (iX,iY) is given the window pops up automatially (i.e. a separate window).
    // Otherwise, when iX and iY are given, the window is embedded into the parent window unless:
    //
    // When Popup() (i.e. opt::Popup()) is given as an option, the window is not embedded and a new popup window is 
    // created.
    //
    // The window is sized to the input bitmap.
    //
    // Once the window is created, it may be treated as any window.
    // Note: With Bitmap Popup Windows(), when the 'X' is pressed, the window is automatically closed
    // unlike regular CWindow windows where the 'X' button sets a notification and WindowClosing() status.
    //
	CWindow & BitmapWindow(int iX,int iY,Sage::RawBitmap_t & stBitmap,const cwfOpt & cwOpt = cwfOpt());

    // ReadJpegFile -- Read a jpeg file and store it into a CSageBitmap. 
    // This reads standard 8-bit jpeg (3-channel or monochrome).
    // If the file does not exist or is in an unsupported format, CSageBitmap will come back empty.
    // Use GetJpegError() to get the status of the last ReadJpegFile() call, which will
    // give information on why the Bitmap came back empty.
    //
    // if (bSuccess) is supplied, it is filled with true for a successful read, otherwise false.
    //
	CSageBitmap ReadJpegFile(const char * sPath,bool * bSuccess = nullptr);

    // ReadJpegFile -- Read a jpeg file and store it into a CSageBitmap. 
    // This reads standard 8-bit jpeg (3-channel or monochrome).
    // If the file does not exist or is in an unsupported format, CSageBitmap will come back empty.
    // Use GetJpegError() to get the status of the last ReadJpegFile() call, which will
    // give information on why the Bitmap came back empty.
    //
    // if (bSuccess) is supplied, it is filled with true for a successful read, otherwise false.
    //
	CSageBitmap ReadJpegMem(const unsigned char * sData,int iDataLength,bool * bSuccess);

    // Returns the last Jpeg status.  This will return CJpeg::Status::Ok if there was no error, 
    // or an indication of what went wrong with the last call, such as CJpeg::Status::EmptyFilePath or CJpeg::Status::FileNotFound
    //
    CJpeg::Status GetJpegError();

};
}; // namespace Sage;



#endif // _CSageBox_H_