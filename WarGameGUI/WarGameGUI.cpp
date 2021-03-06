// WarGameGUI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "WarGameGUI.h"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <string>
#include <sstream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_LOADSTRING 100
#define BUTTON_ID 1001

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];    // the main window class name
static HWND hButton;
TCHAR greeting[] = _T("Hello, World !");
WNDPROC OldButtonProc;
HWND textfield;
HWND hWnd;

const size_t deckSize = 52;

int randomNumGen(int i)
{
	return std::rand() % i;
}

vector<int> generateDeck(size_t dSize)
{
	vector<int> deck;

	for (int x = 0; x < dSize / 13; x++)
	{
		for (int i = 1; i <= dSize / 4; i++)
		{
			deck.push_back(i);
		}
	}
	cout << "Generated Deck" << endl;
	return deck;
}

vector<string> simulateGame()
{
	int turns = 0;
	std::srand(unsigned(std::time(0)));
	std::vector<int> deck = generateDeck(deckSize);

	std::random_shuffle(deck.begin(), deck.end(), randomNumGen);

	std::string item = "";
	std::string winner = "0";

	for (int x = 0; x < deck.size(); x++)
	{
		item += deck[x];
	}

	std::wstring it(item.begin(), item.end());

	//MessageBox(hWnd, it.c_str(), L"THe ting", MB_OK);


	std::vector<int> mOne;
	std::vector<int> mTwo;


	for (int i = 0; i < 26; i++)
	{
		mOne.push_back(deck[i]);
	}

	for (int i = 26; i < deck.size(); i++)
	{
		mTwo.push_back(deck[i]);
	}

	// std::cout << mOne.size() << std::endl;
	// std::cout << mTwo.size() << std::endl;

	while (true)
	{
		//std::cout << "Turns " << turns << " mOne: " << mOne[0] << " mTwo " << mTwo[0] << " Size " << mOne.size() << " Size " << mTwo.size() << std::endl;

		if (mOne.size() == 0)
		{
			std::cout << "Player two is the winner with " << turns << " Turns" << std::endl;
			winner = "2";
			break;
		}
		else if (mTwo.size() == 0)
		{
			std::cout << "Player one is the winner with " << turns << " Turns" << std::endl;
			winner = "1";
			break;
		}

		int One = mOne[0];
		int Two = mTwo[0];

		if (One > Two)
		{
			mOne.push_back(Two);
			mOne.push_back(One);

			mOne.erase(mOne.begin());
			mTwo.erase(mTwo.begin());
		}
		else if (Two > One)
		{
			mTwo.push_back(One);
			mTwo.push_back(Two);

			mTwo.erase(mTwo.begin());
			mOne.erase(mOne.begin());
		}
		else if (One == Two)
		{
			if (mOne.size() >= 5 && mTwo.size() >= 5 && mOne[3] != mTwo[3])
			{
				int One = mOne[3];
				int Two = mTwo[3];

				std::vector<int> pOne;
				std::vector<int> pTwo;

				for (int i = 0; i < 3; i++)
				{
					pOne.push_back(mOne[i]);
					mOne.erase(mOne.begin());
				}

				for (int i = 0; i < 3; i++)
				{
					pTwo.push_back(mTwo[i]);
					mTwo.erase(mTwo.begin());
				}

				//  std::cout << mOne[4] << std::endl;
				// std::cout << mTwo[4] << std::endl;


				if (One > Two)
				{
					for (int x = 0; x < pOne.size(); x++) { mOne.push_back(pOne[x]); }
					for (int x = 0; x < pOne.size(); x++) { mOne.push_back(pTwo[x]); }
				}
				else if (Two > One)
				{
					for (int x = 0; x < pTwo.size(); x++) { mTwo.push_back(pOne[x]); }
					for (int x = 0; x < pTwo.size(); x++) { mTwo.push_back(pTwo[x]); }
				}
				/*
				std::cout << "One" << mOne.size() << std::endl;
				std::cout << "Two" << mTwo.size() << std::endl;
				std::cout << "Total" << mOne.size() + mTwo.size() << std::endl;
				std::cout << std::endl;
				*/
			}
			else
			{
				rotate(mOne.begin(), mOne.end() - 1, mOne.end());
				rotate(mTwo.begin(), mTwo.end() - 1, mTwo.end());
			}

		}
		turns++;

	}
	vector<string> retOutput;
	retOutput.push_back(std::to_string(turns));
	retOutput.push_back(winner);

	return retOutput;
}

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
    LoadStringW(hInstance, IDC_WARGAMEGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WARGAMEGUI));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WARGAMEGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WARGAMEGUI);
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

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   SetWindowPos(hWnd, NULL, 100, 100, 300, 400, NULL);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		hButton = CreateWindow(L"Button", L"Run Simulation", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 75, 150, 150, 50, hWnd, (HMENU)1, NULL, NULL);
		textfield = CreateWindow(L"STATIC", L"Number of Turns", WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 100, 150, 20, hWnd, NULL, NULL, NULL);

		//OldButtonProc = (WNDPROC)SetWindowLong(hButton, GWL_WNDPROC, (LONG)ButtonProc);

    case WM_COMMAND:
        {
		switch (LOWORD(wParam))
		{
		case 1:
			vector<string> simulate = simulateGame();
			string output = "";
			int turns = std::stoi(simulate[0]);

			if (simulate[1] == "1") { output = "Player One is the winner with %s turns total in the game", simulate[0]; }

			wchar_t istr[32];
			_itow_s(turns, istr, 10);

			textfield = CreateWindow(L"STATIC", istr , WS_VISIBLE | WS_CHILD | WS_BORDER, 75, 100, 150, 20, hWnd, NULL, NULL, NULL);
			break;

		}
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
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
				
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			//TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

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
