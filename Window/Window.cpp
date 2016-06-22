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
void CreateMenu(HWND hwnd);

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
		L"Προγραμματισμός παραθύρων",    // Window title
		WS_OVERLAPPEDWINDOW,            // Window style is an overlapped window.
		
		// Size and position
		500,							//Default values for size and location appear below.
		500,							//CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		600,
		400,
		

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
	UpdateWindow(hwnd);
	
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
	case WM_CREATE: { //Here we add everything we want to appear in our window.
		CreateMenu(hwnd);
		//Add a text box with text "ΑΡΧΙΚΗ ΤΙΜΗ" that can be modified.
		CreateWindowEx(0, TEXT("EDIT"), TEXT("ΑΡΧΙΚΗ ΤΙΜΗ"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 10, 200 , 20, hwnd, (HMENU)NULL, NULL, NULL);
		//Add a button.
		CreateWindowEx(0, TEXT("BUTTON"), TEXT("Εντάξει"), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 80, 28, hwnd, (HMENU)NULL, NULL, NULL);
		
		CreateWindowEx(0, TEXT("STATIC"), TEXT("Τι γίνεται;"), WS_VISIBLE | WS_CHILD, 10, 80, 80, 28, hwnd, (HMENU)NULL, NULL, NULL);
		return 0;
	}
	case WM_DESTROY:   //Sent when a window is being destroyed. It destroys also the child windows.
		PostQuitMessage(0);  //Breaks the while loop of the previous function.
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps); //Prepares the window with hwnd handler for painting and fills the ps structure with the appropriate data. 

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); //The FillRect function fills a rectangle by using the specified brush. This function includes the left and top borders.

		EndPaint(hwnd, &ps); //Marks the end of painting in the specified window.
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//Creates the menu of the window "Μάθε να προγραμματίζεις παράθυρα".
void CreateMenu(HWND hwnd) {
	HMENU hMenubar = CreateMenu();
	HMENU hFile = CreateMenu();
	HMENU hOptions = CreateMenu();

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, L"Αρχείο");
	AppendMenu(hFile, MF_STRING, NULL, L"Έξοδος");

	AppendMenu(hMenubar, MF_POPUP, NULL, L"Επεξεργασία");

	AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hOptions, L"Επιλογές");
	AppendMenu(hOptions, MF_STRING, NULL, L"Επιλογή 1");

	AppendMenu(hOptions, MF_STRING, NULL, L"Επιλογή 2");
	

	SetMenu(hwnd, hMenubar);
}