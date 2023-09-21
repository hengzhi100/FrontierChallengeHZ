#include "FrontierUI.h"
#include "FrontierChallengeHZ.h"

void FCDrawGrid(HDC hdc)
{
    // Draw vertical lines
    for (int i = 0; i <= GRID_SIZE; ++i)
    {
        MoveToEx(hdc, i * GRID_CELL_SIZE, 0, NULL);
        LineTo(hdc, i * GRID_CELL_SIZE, GRID_SIZE * GRID_CELL_SIZE);
    }

    // Draw horizontal lines
    for (int i = 0; i <= GRID_SIZE; ++i)
    {
        MoveToEx(hdc, 0, i * GRID_CELL_SIZE, NULL);
        LineTo(hdc, GRID_SIZE * GRID_CELL_SIZE, i * GRID_CELL_SIZE);
    }
}

void FCDrawButton(HWND hWnd, int btnIndex,LPCWSTR title, HMENU menu_ID) {
    // Create a button


    HWND hButton = CreateWindow(
        L"BUTTON",                      // Window class name
        title,                   // Button text
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
        10 + GRID_SIZE * GRID_CELL_SIZE,                            // x position
        10 + btnIndex* (30+5),                            // y position
        100,                           // Button width
        30,                            // Button height
        hWnd,                          // Parent window
        menu_ID,         
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL                           // No additional parameters
    );
}


void DrawPositionInput(HWND hWnd, int btnIndex) {

    int startX = 10 + GRID_SIZE * GRID_CELL_SIZE;
    int startY = 10 + btnIndex * (30 + 5);
    int spaceGap = 20;
    int labelWith = 20;
    int facingLableWidth = 50;
    int inputBoxWith = 50;
    int dropDownBoxWith = 100;

    HWND hLabelX = CreateWindowEx(
        0,                        // Extended style
        L"STATIC",                // Predefined class; Unicode assumed 
        L"X:",                    // Window title (label text)
        WS_CHILD | WS_VISIBLE,    // Styles 
        startX,              // x position (adjusted to position it before the edit control)
        startY, // y position (adjusted for vertical centering with the edit box)
        labelWith,                       // Width (should be sufficient for the "X:" text)
        20,                       // Height
        hWnd,                     // Parent window    
        NULL,                     // No menu ID for the static control
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);                    // Pointer not needed.

    startX += labelWith;
    // Create an Edit box for the X coordinate
    HWND hEditX = CreateWindowEx(
        WS_EX_CLIENTEDGE,    // Extended style
        L"EDIT",              // Predefined class; Unicode assumed 
        NULL,                // No window title 
        WS_CHILD | WS_VISIBLE | ES_NUMBER,  // Styles 
        startX,                  // x position 
        startY,                  // y position 
        inputBoxWith,                  // Width
        20,                  // Height
        hWnd,                // Parent window    
        (HMENU)IDC_FCINPUT_X,   // Edit control ID
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);               // Pointer not needed.
    SetWindowText(hEditX, L"0");


    startX += inputBoxWith + spaceGap;
    HWND hLabelY = CreateWindowEx(
        0,                        // Extended style
        L"STATIC",                // Predefined class; Unicode assumed 
        L"Y:",                    // Window title (label text)
        WS_CHILD | WS_VISIBLE,    // Styles 
        startX,              // x position (adjusted to position it before the edit control)
        startY, // y position (adjusted for vertical centering with the edit box)
        labelWith,                       // Width (should be sufficient for the "X:" text)
        20,                       // Height
        hWnd,                     // Parent window    
        NULL,                     // No menu ID for the static control
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);                    // Pointer not needed.

    startX += labelWith;
    
    // Create an Edit box for the Y coordinate
    HWND hEditY = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | ES_NUMBER,
        startX,                  // Adjust the position as needed
        startY,
        inputBoxWith,
        20,
        hWnd,
        (HMENU)IDC_FCINPUT_Y,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);
    SetWindowText(hEditY, L"0");

    startX += inputBoxWith + spaceGap;
    HWND hLabelFacing = CreateWindowEx(
        0,                        // Extended style
        L"STATIC",                // Predefined class; Unicode assumed 
        L"Facing:",                    // Window title (label text)
        WS_CHILD | WS_VISIBLE,    // Styles 
        startX,              // x position (adjusted to position it before the edit control)
        startY, // y position (adjusted for vertical centering with the edit box)
        facingLableWidth,                       // Width (should be sufficient for the "X:" text)
        20,                       // Height
        hWnd,                     // Parent window    
        NULL,                     // No menu ID for the static control
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);                    // Pointer not needed.

    startX += facingLableWidth;

    HWND hComboBox = CreateWindowEx(
        0,
        L"COMBOBOX",         // The class name for combo box
        NULL,
        WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST, // Styles
        startX,                 // x position 
        startY,                 // y position, adjust as needed
        dropDownBoxWith,                // Width
        200,                // Height
        hWnd,               // Parent window
        (HMENU)IDC_FCINPUT_FACING,   // The control's ID
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);              // Pointer not needed.

    SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"East");
    SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"West");
    SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"South");
    SendMessageA(hComboBox, CB_ADDSTRING, 0, (LPARAM)"North");

    //Set initial value "east"
    SendMessage(hComboBox, CB_SETCURSEL, 0, 0);

}

FCPosition GetUserInputPostion(HWND hWnd) {

    FCPosition userInputPosition;

    wchar_t bufferX[20] = {0};
    wchar_t bufferY[20] = { 0 };
    wchar_t facingText[20] = { 0 };

    // Retrieve x and y from Edit controls
    GetDlgItemText(hWnd, (int)IDC_FCINPUT_X, bufferX, sizeof(bufferX)/sizeof(wchar_t));
    GetDlgItemText(hWnd, (int)IDC_FCINPUT_Y, bufferY, sizeof(bufferY)/sizeof(wchar_t));

    int coordinateX = _wtoi(bufferX);
    int coordinateY = _wtoi(bufferY);

    // Get selected item from ComboBox
    HWND hComboBox = GetDlgItem(hWnd, (int)IDC_FCINPUT_FACING);
    int idx = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);  // Get selected index

    if (idx != CB_ERR) // Ensure something is selected
    {
        SendMessage(hComboBox, CB_GETLBTEXT, idx,(LPARAM)facingText);
    }
   return FCPosition(coordinateX,coordinateY, facingText);
}

void DrawPosition(HDC hdc, FCPosition fcPosition)
{
    // Define the bounding rectangle for the circle
    int positionX = fcPosition.coordinate.x;
    int positionY = fcPosition.coordinate.y;
    int facingX = fcPosition.facing.x;
    int facingY = fcPosition.facing.y;;

    //reverse according requirement.
    facingY = 0 - facingY;

    int centerX = positionX * GRID_CELL_SIZE +  GRID_CELL_SIZE / 2;
    int centerY = (GRID_SIZE - positionY - 1) * GRID_CELL_SIZE + GRID_CELL_SIZE / 2;

    int radius = GRID_CELL_SIZE/2 - GRID_CELL_SIZE /8;
    int left = centerX - radius;
    int top = centerY - radius;
    int right = centerX + radius;
    int bottom = centerY + radius;

    // Draw the circle
    Ellipse(hdc, left, top, right, bottom);


    MoveToEx(hdc, centerX, centerY, NULL);
    LineTo(hdc, centerX + facingX * GRID_CELL_SIZE, centerY + facingY * GRID_CELL_SIZE);

}