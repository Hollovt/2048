// 2048.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "2048.h"
#include <string>
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
/*LPCWSTR ClassWin = L"ClassWin";
WCHAR ClassWinW;

LPCWSTR  ClassResult = L"ClassResult";
WCHAR  ClassResult;	*/


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);

BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND hWnd1;
HWND hWnd2;
HWND hWnd3;
HWND hWnd4;
int result = 0;
int max = 0;
bool end = false;
class Klocek
{
public:
	int value;
	int x;
	int y;
	int size;
};
int array[4][4];
int array_cpy[4][4];
int zeroes = 16;
int goal = 2048;
bool lose = false;
void refresh()
{
	InvalidateRect(hWnd1, NULL, NULL);
	InvalidateRect(hWnd2, NULL, NULL);
	UpdateWindow(hWnd1);
	UpdateWindow(hWnd2);
	
}
bool MoveToTop()
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!array[j][i])
			{
				for (int k = j + 1; k < 4; k++)
					if (array[k][i])
					{
						array[j][i] = array[k][i];
						array[k][i] = 0;
						
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (array[j][i] && array[j][i] == array[j + 1][i])
			{
				
				array[j][i] += array[j + 1][i];
				result += array[j][i];
				array[j + 1][i] = 0;
				res = true;
				

			}
		}
	return true;
} //
bool MoveToBot()
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (!array[j][i])
			{
				for (int k = j - 1; k >= 0; k--)
					if (array[k][i])
					{
						array[j][i] = array[k][i];
						array[k][i] = 0;
						res = true;
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j > 0; j--)
		{
			if (array[j][i] && array[j][i] == array[j - 1][i])
			{
				array[j][i] += array[j - 1][i];
				array[j - 1][i] = 0;
				result += array[j][i];
				res = true;
				
			}
		}
	return res;
}
bool MoveToLeft()
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!array[i][j])
			{
				for (int k = j + 1; k < 4; k++)
					if (array[i][k])
					{
						res = true;
						array[i][j] = array[i][k];
						array[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (array[i][j] && array[i][j] == array[i][j + 1])
			{
				
				array[i][j] += array[i][j + 1];
				array[i][j + 1] = 0;
				result += array[i][j];
				res = true;
				
			}
		}
	return res;
}
bool MoveToRight()
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (!array[i][j])
			{
				for (int k = j - 1; k >= 0; k--)
					if (array[i][k])
					{
						res = true;
						array[i][j] = array[i][k];
						array[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j > 0; j--)
		{
			if (array[i][j] && array[i][j] == array[i][j - 1])
			{
				
				array[i][j] += array[i][j - 1];
				array[i][j - 1] = 0;
				result += array[i][j];
				res = true;
				
			}
		}
	return res;
}
bool MoveToTop(int array[4][4])
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!array[j][i])
			{
				for (int k = j + 1; k < 4; k++)
					if (array[k][i])
					{
						array[j][i] = array[k][i];
						array[k][i] = 0;
						
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (array[j][i] && array[j][i] == array[j + 1][i])
			{
				
				array[j][i] += array[j + 1][i];
				array[j + 1][i] = 0;
				res = true;

			}
		}
	//	copy_tab();
	return res;
	
} //
bool MoveToBot(int array[4][4])
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (!array[j][i])
			{
				for (int k = j - 1; k >= 0; k--)
					if (array[k][i])
					{
						array[j][i] = array[k][i];
						array[k][i] = 0;
						
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j > 0; j--)
		{
			if (array[j][i] && array[j][i] == array[j - 1][i])
			{
				array[j][i] += array[j - 1][i];
				array[j - 1][i] = 0;
				
				res = true;
				
			}
		}
	return res;
	//copy_tab();
}
bool MoveToLeft(int array[4][4])
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!array[i][j])
			{
				for (int k = j + 1; k < 4; k++)
					if (array[i][k])
					{
						
						array[i][j] = array[i][k];
						array[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (array[i][j] && array[i][j] == array[i][j + 1])
			{

				array[i][j] += array[i][j + 1];
				array[i][j + 1] = 0;
				res = true;
				
			}
		}
	return res;
	//copy_tab();
}
bool MoveToRight(int array[4][4])
{
	bool res = false;
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (!array[i][j])
			{
				for (int k = j - 1; k >= 0; k--)
					if (array[i][k])
					{
						
						array[i][j] = array[i][k];
						array[i][k] = 0;
						break;
					}
			}

		}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j > 0; j--)
		{
			if (array[i][j] && array[i][j] == array[i][j - 1])
			{

				
				res = true;
				
			}
		}
	//copy_tab();
	return res;
}
int how_many_zeroes()
{
	int wynik = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (array[i][j] == 0)
				wynik++;
	return wynik;
}
int maks()
{
	int wynik = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			wynik = max(array[i][j], wynik);
	return wynik;
}
void copy_tab()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			array_cpy[i][j] = array[i][j];
		}
	}
}
void SetTransparency(HWND hwnd, std::uint8_t Transperancy)
{
	long wAttr = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, Transperancy, LWA_COLORKEY);
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY2048, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2048));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = CreateSolidBrush(RGB(250, 247, 238));
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2048);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   std::ifstream file("save.txt");
   int temp;
   std::string temp_str;
   for (int i = 0; i < 4; i++)
   {
	   for (int j = 0; j < 4; j++)
	   {
		   std::getline(file, temp_str);
		   temp = std::stoi(temp_str);
		   array[i][j] = temp;
	   }
   }
   std::getline(file, temp_str);
   temp = std::stoi(temp_str);
   result = temp;
   srand(time(NULL));
   hInst = hInstance; // Store instance handle in our global variable
   int size = 60;
   hWnd1 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	   CW_USEDEFAULT, 0, 305, 420, nullptr, nullptr, hInstance, nullptr);
   //hWnd2 = CreateWindowW(szWindowClass, szTitle, WS_BORDER,
	//   CW_USEDEFAULT, 0, 305, 420, hWnd1, nullptr, hInstance, nullptr);
   hWnd3 = CreateWindowW(szWindowClass, szTitle,
	   WS_VISIBLE | WS_CHILDWINDOW ,
	   0, 0, 305, 420,
	   hWnd1, NULL, hInst, NULL);
   /*hWnd4 = CreateWindowW(szWindowClass, szTitle,
	   WS_VISIBLE | WS_CHILDWINDOW,
	   0, 0, 305, 420,
	   hWnd2, NULL, hInst, NULL);*/
   

   if (!hWnd1 /*|| !hWnd2*/)
   {
	  return FALSE;
   }
   

   ShowWindow(hWnd1, nCmdShow);
  // ShowWindow(hWnd2, nCmdShow);
   UpdateWindow(hWnd1);
   //UpdateWindow(hWnd2);
   
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
			int wmId = LOWORD(wParam);
		HMENU hMenu = GetMenu(hWnd);

		// Parse the menu selections:
		int r;
		switch (wmId)
		{
		case ID_NEW_GAME:
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					array[i][j] = 0;
				}
			}
			end = false;
			lose = false;
			result = 0;
			srand(time(NULL));
			r = rand() % 16;
			array[r / 4][r % 4] = 2;
			zeroes--;
			refresh();
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			
			break;
		case ID_GOAL_16:
			goal = 16;

			break;
		case ID_GOAL_64:
			goal = 64;
			break;
		case ID_GOAL_2048:
			goal = 2048;
			break;
		case IDM_GOAL_8:
			goal = 8;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, GetStockObject(DC_PEN));
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		

		int size = 60;
		RECT rect2;
		rect2.top = 10;
		rect2.left = 10;
		rect2.right = rect2.left + 270;
		rect2.bottom = rect2.top + 50;
		COLORREF color2;
		color2 = RGB(204, 192, 174);
		
		SetTextColor(hdc, RGB(255,255,255));
		SetBkColor(hdc, color2);
		SetDCBrushColor(hdc, color2);
		SetDCPenColor(hdc, color2);
		RoundRect(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom, 10, 10);
		wchar_t s_result[10];
		_itow_s(result, s_result, 10);
		DrawText(hdc, s_result, -1, &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER );
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				RECT rect;
				rect.top = 80 + i * (size + 10);
				rect.left = (size + 10) * j + 10;
				rect.right = rect.left + size;
				rect.bottom = rect.top + size;
				COLORREF color;

				switch (array[i][j])
				{
				case 4:
					
					color = RGB(239, 225, 218);
					break;
				case 2:
					color = RGB(238, 228, 198);
					break;
				case 8:
					color = RGB(243, 179, 124);
					break;
				case 16:
					color = RGB(246, 153, 100);
					break;
				case 32:
					color = RGB(246, 125, 98);
					break;
				case 128:
					color = RGB(237, 206, 116);
					break;
				case 64:
					color = RGB(247, 93, 60);
					break;
				case 256:
					color = RGB(239, 204, 98);
					break;
				case 512:
					color = RGB(100, 100, 100);
					break;
				case 1024:
					color = RGB(150, 80, 180);
					break;
				case 2048:
					color = RGB(0, 0, 0);
					break;
				default:
					
					color = RGB(204, 192, 174);
				}
				SetBkColor(hdc, color);


				SetDCBrushColor(hdc, color);
				SetDCPenColor(hdc, color);
				RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, 10, 10);
				if (array[i][j] == 0)
					continue;
				int n = array[i][j];
				wchar_t s[10];
				_itow_s(n, s, 10);
				DrawText(hdc, s, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
		}
		int MAX = maks();
		wchar_t win[] = L"WIN!";
		wchar_t game_over[] = L"GAME OVER!";
		if (end )
		{
			
			color2 = RGB(0, 255, 0);
			SetBkColor(hdc, color2);
			SetDCBrushColor(hdc, color2);
			SetDCPenColor(hdc, color2);
			
			rect2.top = 0;
			rect2.left = 0;
			rect2.right = rect2.left + 305;
			rect2.bottom = rect2.top + 420;
			FillRect(hdc, &rect2, CreateSolidBrush(color2));
			long wAttr = GetWindowLong(hWnd3, GWL_EXSTYLE);
			long wAttr2 = GetWindowLong(hWnd2, GWL_EXSTYLE);
			SetWindowLong(hWnd3, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
			SetWindowLong(hWnd4, GWL_EXSTYLE, wAttr2 | WS_EX_LAYERED);

			SetLayeredWindowAttributes(hWnd3, 0, 255, 0x02);
			SetLayeredWindowAttributes(hWnd4, 0, 255, 0x02);
			DrawText(hdc, win, -1, &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			

		}
		if (lose)
		{
			color2 = RGB(255, 0, 0);
			SetBkColor(hdc, color2);
			SetDCBrushColor(hdc, color2);
			SetDCPenColor(hdc, color2);

			rect2.top = 0;
			rect2.left = 0;
			rect2.right = rect2.left + 305;
			rect2.bottom = rect2.top + 420;
			long wAttr = GetWindowLong(hWnd3, GWL_EXSTYLE);

			SetWindowLong(hWnd3, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);

			SetLayeredWindowAttributes(hWnd3, 0, 255, 0x02);
			DrawText(hdc, game_over, -1, &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{std::ofstream save("save.txt");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			save << array[i][j]<<std::endl;
		}
	}
	save << result;
	save.close();
	PostQuitMessage(0);
	break;
	}
	case WM_MOVE:
	{

		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		int srodek_w = desktop.bottom / 2;
		int srodek_s = desktop.right / 2;
		RECT rect;

		GetWindowRect(hWnd, &rect);
		
		/*if (hWnd == hWnd1)*/ MoveWindow(hWnd2, desktop.right - rect.right, desktop.bottom - rect.bottom, 305, 420, true);
		//else if (hWnd == hWnd2) MoveWindow(hWnd1, desktop.right - rect.right, desktop.bottom - rect.bottom, 305, 420, true);
		
		/*if(rect.top<srodek_w && rect.left<srodek_s && rect.right>srodek_s && rect.bottom>srodek_w)
		{
		long wAttr = GetWindowLong(hWnd1, GWL_EXSTYLE);
		long wAttr2 = GetWindowLong(hWnd2, GWL_EXSTYLE);
		SetWindowLong(hWnd1, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
		SetWindowLong(hWnd2, GWL_EXSTYLE, wAttr2 | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hWnd1, 0, 100, 0x02);
		SetLayeredWindowAttributes(hWnd2, 0, 100, 0x02);
		
		}
		else
		{
			long wAttr = GetWindowLong(hWnd1, GWL_EXSTYLE);
			long wAttr2 = GetWindowLong(hWnd2, GWL_EXSTYLE);
			SetWindowLong(hWnd1, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
			SetWindowLong(hWnd2, GWL_EXSTYLE, wAttr2 | WS_EX_LAYERED);
			SetLayeredWindowAttributes(hWnd1, 0, 255, 0x02);
			SetLayeredWindowAttributes(hWnd2, 0, 255, 0x02);
		}*/
		

		break;

	}
	case WM_CHAR:
	{
		srand(time(NULL));
		if (!end && !lose) {
			switch (wParam)
			{
			case 'w':
				MoveToTop();
				break;
			case 's':
				MoveToBot();
				break;
			case 'a':
				MoveToLeft();
				break;
			case 'd':
				MoveToRight();
				break;
			default:

				break;
			}
			bool get_random = true;
			int zeroes = how_many_zeroes();
			while (get_random && zeroes != 0)
			{
				int r = rand() % 16;
				if (array[r / 4][r % 4] == 0)
				{
					array[r / 4][r % 4] = 2;
					get_random = false;
					zeroes--;
				}
			}
			int MAX = maks();
			if (MAX >= goal)
			{
				end = true;

			}
			refresh();
			copy_tab();
			lose = true;
			zeroes = how_many_zeroes();
			if ( zeroes > 0 || MoveToTop(array_cpy) || MoveToBot(array_cpy) || MoveToLeft(array_cpy) || MoveToRight(array_cpy))
			{
				lose = false;
			}
			refresh();
			break;
		}
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
