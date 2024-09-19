#ifndef UNICODE
#define UNICODE
#endif 

#include <algorithm>
#include <iostream>
#include <windowsx.h>
#include <windows.h>
#include <vector>
#include <ctime>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);



    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Saper",
        WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,

        CW_USEDEFAULT, CW_USEDEFAULT, 645, 850,

        NULL,
        NULL,
        hInstance,
        NULL
    );
    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

struct cells
{
    int number;
    bool isbomb;
    bool revealed;
    bool flaged;
    int bombsnear;
    int topY;
    int topX;
    int botY;
    int botX;
    int posY;
    int posX;
};

std::vector<cells> v;

bool drawn = false;
bool win = false;
bool lose = false;

int bombs = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    std::time_t t = std::time(0);
    srand(t);
    bool activebomb;
    int randbomb;
    int cellnum = 0;
    struct cells c[63];
    int bombsamount = 0;
    int positionY = 0;
    int positionX = 0;
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        if (drawn == true && win == false && lose == false)
        {
            for (int j = 0; j < 810; j += 90)
            {
                positionY += 1;
                for (int i = 0; i < 630; i += 90)
                {
                    Rectangle(hdc, i, j, i + 90, j + 90);
                    c[cellnum] = { cellnum, false, false, false, 0, j, i, j + 90, i + 90, positionY, positionX };
                    v.push_back(c[cellnum]);
                    cellnum += 1;
                    positionX += 1;
                }
            }
            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                if (v[i].isbomb == true)
                {
                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));
                }
            }

            //Draw a color for mines near click

            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                if (v[i].revealed == true)
                {
                    if (v[i].bombsnear == 1)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(55, 38, 255));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 2)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(38, 143, 15));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 3)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(238, 0, 0));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 4)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(35, 3, 115));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 5)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(115, 3, 3));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 6)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(71, 156, 160));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 7)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(0, 0, 0));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 8)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(149, 149, 149));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 9)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(210, 70, 187));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                }
            }

            //draw a flag

            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                if (v[i].flaged == true)
                {
                    RECT rect = { v[i].topX + 20, v[i].topY + 20, v[i].botX - 20, v[i].botY - 20 };
                    HBRUSH  hbrush = CreateSolidBrush(RGB(255, 0, 0));
                    FillRect(hdc, &rect, (hbrush));
                    DeleteObject(hbrush);
                }
            }
        }

        //draw cells

        else if (lose == false && win == false)
        {
            for (int j = 0; j < 810; j += 90)
            {
                positionY += 1;
                for (int i = 0; i < 630; i += 90)
                {
                    Rectangle(hdc, i, j, i + 90, j + 90);
                    c[cellnum] = { cellnum, false, false, false, 0, j, i, j + 90, i + 90, positionY, positionX };
                    v.push_back(c[cellnum]);
                    cellnum += 1;
                    positionX += 1;
                }
            }
            //generate bombs
            while (bombs != 20)
            {
                randbomb = rand() % 63;
                if (v[randbomb].isbomb == true)
                {
                    while (v[randbomb].isbomb != false)
                    {
                        randbomb = rand() % 63;
                    }
                }
                else
                {
                    v[randbomb].isbomb = true;
                    bombs++;
                }
                RECT rect = { v[randbomb].topX, v[randbomb].topY, v[randbomb].botX, v[randbomb].botY };
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));
            }
            
            //calculate amount of bombs near cell

            for (int i = 0; i < 63; i++)
            {
                if (v.size() > i + 1 && v[i + 1].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i - 1 && v[i - 1].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i - 6 && v[i - 6].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i + 6 && v[i + 6].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i - 7 && v[i - 7].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i + 7 && v[i + 7].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i - 8 && v[i - 8].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i + 8 && v[i + 8].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
            }
        }
        
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        //get click coordinates
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;
        //find click coordinates
        for (int i = 0; i < 63; i++)
        {

            if (v.size() > i && pt.y >= v[i].topY && pt.y <= v[i].botY)
            {
                if (v.size() > i && pt.x >= v[i].topX && pt.x <= v[i].botX)
                {
                    std::cout << "chosen " << v[i].number << std::endl;
                    std::cout << "bombs " << bombs << std::endl;
                    //if already flaged -> unflag
                    if (v[i].flaged == true)
                    {
                        v[i].flaged = false;
                        if (v[i].isbomb == true)
                        {
                            bombs++;
                        }
                    }
                    v[i].revealed = true;
                    drawn = true;
                    //lose if clicked on bomb
                    if (v[i].isbomb == true)
                    {
                        lose = true;
                    }
                    break;
                }
            }
            //win
            if (bombs == 0)
            {
                win = true;
            }
        }
        InvalidateRect(hwnd, NULL, false);
    break;
    }
    case WM_RBUTTONDOWN:
    {
        //get click coordinates
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);
        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;
        //find click coordinates
        for (int i = 0; i < 63; i++)
        {

            if (v.size() > i && pt.y >= v[i].topY && pt.y <= v[i].botY)
            {
                if (v.size() > i && pt.x >= v[i].topX && pt.x <= v[i].botX)
                {
                    drawn = true;
                    //if already flaged -> unflag
                    if (v[i].flaged == true)
                    {
                        v[i].flaged = false;
                        if (v[i].isbomb == true)
                        {
                            bombs++;
                        }
                    }
                    else
                    {
                        //flag
                        if (v[i].isbomb == true)
                        {
                            v[i].flaged = true;
                            bombs--;
                        }
                        else
                        {
                            v[i].flaged = true;
                        }
                    }
                    //win
                    if (bombs == 0)
                    {
                        win = true;
                    }
                    InvalidateRect(hwnd, NULL, false);
                    break;
                }
            }
        }
        break;
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}