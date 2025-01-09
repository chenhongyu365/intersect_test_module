// $Id: blend_smoke_test.hxx,v 1.4 2002/01/28 16:53:03 rocon Exp $
/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/

// ACIS_Win.cpp : Defines the entry point for the application.
//

#include "ACIS_Win.h"

#include "stdafx.h"

#define MAX_LOADSTRING 100

// ACIS includes
#include "ACIS_mesh.hxx"
#include "acis/acis.hxx"
#include "acis/acistype.hxx"
#include "acis/fileinfo.hxx"
#include "acis/kernapi.hxx"
#include "acis/license.hxx"
#include "acis/lists.hxx"
#include "acis/spa_unlock_result.hxx"
#include "acis_utils.hpp"

// Global Variables:
HINSTANCE hInst;                      // current instance
TCHAR szTitle[MAX_LOADSTRING];        // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

ACIS_fp find_which_ACIS(WORD id);
bool CreateMeshFromEntityList(ENTITY_LIST& el, AcisMesh::DisplayData& dd);

DWORD WINAPI display_AcisMesh(void* data) {
    AcisMesh::DisplayData* dd = static_cast<AcisMesh::DisplayData*>(data);
    if(nullptr == dd) {
        return 0;
    }
    AcisMesh Afm(dd);
    dd = 0;
    Afm.Display();

    return 0;
}

// end ACIS forward declarations

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;
    HACCEL hAccelTable;

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_ACIS_WIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if(!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    // Initialize GLFW
    if(glfwInit() != 1) {
        MessageBox(NULL, L"Could not initialize GLFW, exiting", L"Fatal Error!", NULL);
        exit(1);
    }
    // Initialize ACIS on the main thread
    if(initialize_acis() != 2) {
        MessageBox(NULL, L"Could not initialize ACIS, exiting", L"Fatal Error!", NULL);
        exit(1);
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ACIS_WIN));

    // Main message loop:
    while(GetMessage(&msg, NULL, 0, 0)) {
        if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ACIS_WIN));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_ACIS_WIN);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    HWND hWnd;

    hInst = hInstance;  // Store instance handle in our global variable

    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 500, 200, NULL, NULL, hInstance, NULL);

    if(!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}
// The application must manage all OpenGL window threads.
// We use the threadHandles vector for this.
static std::vector<HANDLE> threadHandles;
// The user must close all OpenGL windows before the application can properly shut down.
// If any are left open, we remind with a message box, then wait for the user to close them.
// The thread handles for each OpenGL window must also be closed.
void cleanup_OpenGL_windows() {
    std::vector<HANDLE>::iterator it;
    bool all_closed = true;
    for(it = threadHandles.begin(); it != threadHandles.end(); it++) {
        DWORD ret_val = WaitForSingleObject(*it, 0);
        if(0 != ret_val) {
            all_closed = false;
            MessageBox(NULL, L"Close all OpenGL Windows before exiting!", L"Action required!", NULL);
            break;
        }
    }
    if(!all_closed) {
        WaitForMultipleObjects((DWORD)threadHandles.size(), threadHandles.data(), 1, INFINITE);
    }
    for(it = threadHandles.begin(); it != threadHandles.end(); it++) {
        CloseHandle(*it);
    }
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    outcome result(0);
    ENTITY_LIST ents;
    ACIS_fp fp = nullptr;

    switch(message) {
        case WM_COMMAND:
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            // Parse the menu selections:
            switch(wmId) {
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                    break;
                case IDM_EXIT:
                    // Ensure all OpenGL windows are closed & close the corresponding thread handles.
                    cleanup_OpenGL_windows();
                    // Close the GUI
                    DestroyWindow(hWnd);
                    // terminate glfw
                    glfwTerminate();
                    // terminate ACIS
                    terminate_acis(2);
                    break;
                default:
                    fp = find_which_ACIS(wmId);
                    if(nullptr != fp) {
                        ENTITY_LIST el;
                        // Set a breakpoint on the line below to step into the ACIS example.
                        outcome result = fp(el, NULL);
                        process(result);
                        AcisMesh::DisplayData* dd = new AcisMesh::DisplayData;
                        // Generate the facet data
                        if(CreateMeshFromEntityList(el, *dd)) {
                            // Create a thread which displays the facet data
                            HANDLE myHandle = CreateThread(NULL, 0, display_AcisMesh, dd, 0, NULL);
                            if(myHandle) {
                                threadHandles.push_back(myHandle);
                            }
                        } else {
                            delete dd;
                        }
                        dd = nullptr;
                        fp = nullptr;
                        result = api_del_entity_list(el);
                        process(result);
                    } else {
                        return DefWindowProc(hWnd, message, wParam, lParam);
                    }
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code here...
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            // Ensure all OpenGL windows are closed & close the corresponding thread handles.
            cleanup_OpenGL_windows();
            // terminate glfw
            glfwTerminate();
            // terminate ACIS
            terminate_acis(2);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch(message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
