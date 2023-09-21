// FrontierChallengeHZ.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "FrontierChallengeHZ.h"
#include "windows.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Global value for robot position.
FCPosition  currentFCPosition;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_FRONTIERCHALLENGEHZ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRONTIERCHALLENGEHZ));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRONTIERCHALLENGEHZ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FRONTIERCHALLENGEHZ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   //Init for the current position of robot.
   currentFCPosition = FCPosition(0, 0, ID_FACING_EAST);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDC_FCBUTTON_REPORT:
                MessageBox(hWnd,currentFCPosition.getReport().c_str(), L"Report", MB_OK);
                break;
            case IDC_FCBUTTON_LEFT:
                {
                    currentFCPosition.faceLeft();
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                break;
            case IDC_FCBUTTON_RIGHT:
            {
                currentFCPosition.faceRight();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
            case IDC_FCBUTTON_MOVE:
            {
                if (currentFCPosition.move()) {
                    InvalidateRect(hWnd, NULL, TRUE);
                }
                else {
                    MessageBox(hWnd, L"No, You are going to fall!", L"Notification", MB_OK);
                }
                
            }
            break;

            //placing to correct position
            case IDC_FCBUTTON_PLACE:
            {
                FCPosition newFCPosition = GetUserInputPostion(hWnd);
                if (newFCPosition.checkCoordinateBoundry(newFCPosition.coordinate)) {
                    currentFCPosition = newFCPosition;
                }
                else {
                    MessageBox(hWnd, L"No, You can not send robot out of table!", L"Notification", MB_OK);
                }

                // Request a redraw of the window
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }   
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
    {
        FCDrawButton(hWnd, 0, L"Left", (HMENU)IDC_FCBUTTON_LEFT);
        FCDrawButton(hWnd, 1, L"Right", (HMENU)IDC_FCBUTTON_RIGHT);
        FCDrawButton(hWnd, 2, L"Move", (HMENU)IDC_FCBUTTON_MOVE);
        FCDrawButton(hWnd, 3, L"Report", (HMENU)IDC_FCBUTTON_REPORT);
        DrawPositionInput(hWnd,5);
        FCDrawButton(hWnd,6, L"Place", (HMENU)IDC_FCBUTTON_PLACE);
        return 0;
    }       
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            FCDrawGrid(hdc);
            DrawPosition(hdc, currentFCPosition);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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
