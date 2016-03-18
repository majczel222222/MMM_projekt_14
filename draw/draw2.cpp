// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>
#include <math.h>

#define MAX_LOADSTRING 100
#define TMR_1 1

using namespace std;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT skalay = 10;
INT skalax = 3;
int A = 0, a = 0, T = 0;

bool paint_sin = false, paint_sqr = false, paint_trg = false;

// buttons
HWND hwndButton;

std::vector<int> data_x;
std::vector<int> data_y;
std::vector<int> data_z;
std::vector<int> data_g;
std::vector<int> data_v_x, data_v_y, data_v_z;

RECT drawArea1 = { 0, 0, 1400, 900 };
RECT drawArea2;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);



/*
void inputData()
{
	std::ifstream source_file;

	double a_x, a_y, a_z, g, variable_x, variable_y, variable_z;

	std::string file_name = "outputRobotForwardB02.log";
	std::string useless_data;

	source_file.open(file_name.c_str());

	if (source_file.fail())
	{
		MessageBox(NULL, L"Nie mozna otworzyc pliku.", L"ERR", MB_ICONEXCLAMATION);
	};

	for (int j = 0; j < 2300; j++)
	{
		if (j == 0)
		{
			source_file.seekg(+22, std::ios_base::cur);
		}
		else
		{
			source_file.seekg(+21, std::ios_base::cur);
		}

		source_file >> a_x >> a_y >> a_z;

		a_x = a_x *1000;
		a_y = a_y *1000;
		a_z = a_z *1000;
		g = sqrt((a_x)*(a_x)+(a_y)*(a_y)+(a_z)*(a_z));

		getline(source_file, useless_data);

		useless_data.clear();

		data_x.push_back(a_x);
		data_y.push_back(a_y);
		data_z.push_back(a_z);
		data_g.push_back(g);

	}	


	source_file.close();


	variable_x = 0;
	variable_y = 0;
	variable_z = 0;

	int var_x = 0, var_y = 0, var_z = 0;

	for (int i = 0; i < 2300; i++)
	{
		var_x = data_x[i];

		variable_x = variable_x + var_x * 0.04;

		data_v_x.push_back(variable_x);
		
		var_y = data_y[i];

		variable_y = variable_y + var_y * 0.04;

		data_v_y.push_back(variable_y);

		var_z = data_z[i];

		variable_z = variable_z + var_z * 0.04;

		data_v_z.push_back(variable_z);

	}


}
*/


wchar_t* int_to_wchar_t(int i, string dodatek)
{
	string napis = to_string(i) + dodatek;
	size_t newsize = napis.length() + 1;
	wchar_t * wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, napis.c_str(), _TRUNCATE);
	return wcstring;
}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);

	Pen pen(Color(255, 0, 0, 0), 1);
	Pen pen_1(Color(255, 255, 0, 0), 1);
	Pen pen_2(Color(255, 0, 255, 0), 1);
	Pen pen_3(Color(255, 0, 0, 255), 1);

	Font text(&FontFamily(L"Arial"), 20);
	Font text3(&FontFamily(L"Arial"), 10);

	SolidBrush text2(Color(255, 0, 0, 255));

	/*schemat rysowania osi
	OX (X1, Y1, X2, Y2)
	OY
	Grot na OYL 
	Grot na OYR
	Grot na OXL
	Grot na OXR
	*/

	//rysowanie osi dla sygnału wejściowego

	graphics.DrawLine(&pen, 20, 110, 840, 110);
	graphics.DrawLine(&pen, 20, 30, 20, 190);
	graphics.DrawLine(&pen, 16, 34, 20, 30);
	graphics.DrawLine(&pen, 20, 30, 24, 34);
	graphics.DrawLine(&pen, 836, 106, 840, 110);
	graphics.DrawLine(&pen, 840, 110, 836, 114);

	//rysowanie osi dla uchybu 

	graphics.DrawLine(&pen, 20, 300, 840, 300);
	graphics.DrawLine(&pen, 20, 220, 20, 380);
	graphics.DrawLine(&pen, 16, 224, 20, 220);
	graphics.DrawLine(&pen, 20, 220, 24, 224);
	graphics.DrawLine(&pen, 836, 296, 840, 300);
	graphics.DrawLine(&pen, 840, 300, 836, 304);

	//rysowanie osi dla wyjścia

	graphics.DrawLine(&pen, 20, 500, 840, 500);
	graphics.DrawLine(&pen, 20, 420, 20, 580);
	graphics.DrawLine(&pen, 16, 424, 20, 420);
	graphics.DrawLine(&pen, 20, 420, 24, 424);
	graphics.DrawLine(&pen, 836, 496, 840, 500);
	graphics.DrawLine(&pen, 840, 500, 836, 504);

	
	for (int i = 1; i < 2300; i++)
	{
		if (paint_sin) graphics.DrawLine(&pen_1, i, -(i ^ 11) + 110 * (i ^ 9) - 7920 * (i ^ 7) + 332640 * (i ^ 5) - 6652800 * (i ^ 3) + 39916800 * i, i, -((i + 1) ^ 11) + 110 * ((i + 1) ^ 9) - 7920 * ((i + 1) ^ 7) + 332640 * ((i + 1) ^ 5) - 6652800 * ((i + 1) ^ 3) + 39916800 * (i + 1));
		
	}

   //rysowanie sygnału prostokatnego

   if (paint_sqr) graphics.DrawLine(&pen_1, 20, 60, 220, 60);
   if (paint_sqr) graphics.DrawLine(&pen_1, 220, 60, 220, 160);
   if (paint_sqr) graphics.DrawLine(&pen_1, 220, 160, 420, 160);
   if (paint_sqr) graphics.DrawLine(&pen_1, 420, 160, 420, 60);
   if (paint_sqr) graphics.DrawLine(&pen_1, 420, 60, 620, 60);
   if (paint_sqr) graphics.DrawLine(&pen_1, 620, 60, 620, 160);
   if (paint_sqr) graphics.DrawLine(&pen_1, 620, 160, 820, 160);
   if (paint_sqr) graphics.DrawLine(&pen_1, 820, 160, 820, 60);
   if (paint_sqr) graphics.DrawLine(&pen_1, 820, 60, 840, 60);

   //rysowanie sygnały trójkątnego

   if (paint_trg) graphics.DrawLine(&pen_1, 20, 160, 120, 60);
   if (paint_trg) graphics.DrawLine(&pen_1, 120, 60, 220, 160);
   if (paint_trg) graphics.DrawLine(&pen_1, 220, 160, 320, 60);
   if (paint_trg) graphics.DrawLine(&pen_1, 320, 60, 420, 160);
   if (paint_trg) graphics.DrawLine(&pen_1, 420, 160, 520, 60);
   if (paint_trg) graphics.DrawLine(&pen_1, 520, 60, 620, 160);
   if (paint_trg) graphics.DrawLine(&pen_1, 620, 160, 720, 60);
   if (paint_trg) graphics.DrawLine(&pen_1, 720, 60, 820, 160);
   if (paint_trg) graphics.DrawLine(&pen_1, 820, 160, 840, 140);

	graphics.DrawString(L"Sygnał wejściowy: ", -1, &text, PointF(900, 80), &text2);

	graphics.DrawString(L"A = ", -1, &text, PointF(900, 180), &text2);
	graphics.DrawString(int_to_wchar_t(A, " "), -1, &text, PointF(950, 180), &text2);

	graphics.DrawString(L"a = ", -1, &text, PointF(900, 280), &text2);
	graphics.DrawString(int_to_wchar_t(a, " "), -1, &text, PointF(950, 280), &text2);

	graphics.DrawString(L"T = ", -1, &text, PointF(900, 380), &text2);
	graphics.DrawString(int_to_wchar_t(T, " "), -1, &text, PointF(950, 380), &text2);

	graphics.DrawString(L"Sygnał wejściowy: ", -1, &text, PointF(20, 0), &text2);

	graphics.DrawString(L"Uchyb: ", -1, &text, PointF(20, 190), &text2);

	graphics.DrawString(L"Sygnał wyjściowy: ", -1, &text, PointF(20, 385), &text2);






}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}	

int OnCreate(HWND window)
{
	SetTimer(window, TMR_1, 25, 0);
	//inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Sin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 40, 70, 40, hWnd, (HMENU)ID_BUTTON_in_sin, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Prostokat"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 80, 70, 40, hWnd, (HMENU)ID_BUTTON_in_sqr, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Trojkat"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 1170, 120, 70, 40, hWnd, (HMENU)ID_BUTTON_in_trg, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 160, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_A_inc, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 200, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_A_dec, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 260, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_a_inc, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 300, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_a_dec, hInstance, NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Zwieksz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 360, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_T_inc, hInstance, NULL);
	hwndButton = CreateWindow(TEXT("button"), TEXT("Zmniejsz"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 980, 400, 70, 40, hWnd, (HMENU)ID_BUTTON_Param_T_dec, hInstance, NULL);

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON_in_sin:
			paint_sin = true, paint_sqr = false, paint_trg = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_in_sqr:
			paint_sin = false, paint_sqr = true, paint_trg = false; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_in_trg:
			paint_sin = false, paint_sqr = false, paint_trg = true; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_A_inc:
			A++; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_A_dec:
			if (A <= 0) MessageBox(NULL, L"Nie mozna wprowadzic ujemnego parametru", L"ERR", MB_ICONEXCLAMATION);
			else A--; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_a_inc:
			a++; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_a_dec:
			if (a <= 0) MessageBox(NULL, L"Nie mozna wprowadzic ujemnego parametru", L"ERR", MB_ICONEXCLAMATION);
			else a--; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_T_inc:
			T++; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON_Param_T_dec:
			if (T <= 0) MessageBox(NULL, L"Nie mozna wprowadzic ujemnego parametru", L"ERR", MB_ICONEXCLAMATION);
			else T--; repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea2);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
