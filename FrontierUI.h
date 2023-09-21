#pragma once
#include <Windows.h>
#include "FCPosition.h"

#define _USE_MATH_DEFINES
#include <cmath>

void FCDrawGrid(HDC hdc);
void FCDrawButton(HWND hWnd, int btnIndex, LPCWSTR title, HMENU menu_ID);
void DrawPositionInput(HWND hWnd, int btnIndex);
void DrawPosition(HDC hdc,FCPosition fcPosition);
FCPosition GetUserInputPostion(HWND hWnd);


