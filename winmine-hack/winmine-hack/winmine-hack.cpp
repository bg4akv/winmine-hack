// winmine-hack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <stdio.h> 

int _tmain(int argc, _TCHAR* argv[])
{
	HWND hwnd;
	HANDLE hPr;
	DWORD dProc;
	byte w, h;
	int x, y;
	byte buf;
	int pX;
	int pY;
	
	hwnd = FindWindow(NULL, "É¨À×");
	if (hwnd == NULL) {
		MessageBox(NULL, "Please load game first!", NULL, MB_OK);
		return 0;
	}

	GetWindowThreadProcessId(hwnd, &dProc);
	hPr = OpenProcess(PROCESS_ALL_ACCESS, false, dProc);
	if (hPr == NULL) {
		MessageBox(NULL, "Could not open game process!", NULL, MB_OK);
		return 0;
	}

	ReadProcessMemory(hPr, (LPWORD) 0x1005334, &w, 1, NULL);
	ReadProcessMemory(hPr, (LPWORD) 0x1005338, &h, 1, NULL);
	for (y = 0; y < h; y++) {
		for (x = 0; x < w; x++) {
			Sleep(1000);
			ReadProcessMemory(hPr, (LPWORD) (0x1005361 + y*32 + x), &buf, 1, NULL);
			pX = (x + 1) * 16;
			pY = (y + 1) * 16 + 48;
			if (buf == 0x8f) {
				PostMessage(hwnd, WM_RBUTTONDOWN, NULL, ((pY<<16) + pX));
				PostMessage(hwnd, WM_RBUTTONUP, NULL, ((pY<<16) + pX));
				buf = '*';
			} else {
				PostMessage(hwnd, WM_LBUTTONDOWN, NULL, ((pY<<16) + pX));
				PostMessage(hwnd, WM_LBUTTONUP, NULL, ((pY<<16) + pX));
				buf = 'o';
			}
			printf("%c ", buf);
		}
		printf("\n");
	}

	system("pause");
	return 0;
}

