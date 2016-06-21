#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
using namespace std;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//The basic function of a window program, like the main() function for console applications.
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	// Give a value to CLASS_NAME string. The type is such that can accomodate UTF-16 characters with up to two bytes each.
	const wchar_t CLASS_NAME[] = L"Sample Window Class"; //We put the L in frond of the string to declare use of UTF-16 characters. 

	WNDCLASS wc = {};

	//Fill in the fields of wc class.
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	//Registers the wc WINDCLASS with the operating system.
	RegisterClass(&wc);

	// Create the window and return its handler.
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Μάθε να προγραμματίζεις παράθυρα",    // Window title
		WS_OVERLAPPEDWINDOW,            // Window style is an overlapped window.
		
		// Size and position
		500,							//Default values for size and location appear below.
		500,							//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		400,
		200,
		

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	); 

	//If handler NULL no window creater exit the procedure.
	if (hwnd == NULL)
	{
		return 0;
	}

	// Displays the window with handler hwmd, according to nCmdShow.
	ShowWindow(hwnd, nCmdShow);
	
	// The loop checks messages. Every message is related to an event and stored in a queue maintained by the OS. 
	MSG msg = {};							//Createς a variable that will be used to store a message.
	while (GetMessage(&msg, NULL, 0, 0))	//Check the queue for a message and store it in the variable.
	{
		TranslateMessage(&msg);				//Translates keystrokes into characters.
		DispatchMessage(&msg);				//Whenever is executed windows executes WindowProc function.
	}
	return 0;
}

/*All the parameters are part of the message retrieved from the queue. Depending o the event stored in the last
message retrieved from the queue performs various aperations. */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)           //Checks the identifier of the message that came from the queue.
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //Breaks the while loop of the previous function.
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}