#ifndef UNICODE
#define UNICODE
#endif 

#include <algorithm>
#include <iostream>
#include <windowsx.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <string>
#include <locale>
#include <codecvt>

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

        CW_USEDEFAULT, CW_USEDEFAULT, 645, 1000, 

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

std::vector<cells> OpenCells(std::vector<cells> &v, int number)
{
    for (int i = 0; i < 63; i++)
    {
        if (v[i].number == number)
        {
            if (v[i].bombsnear == 0)
            {
                if (v.size() > i + 1 && v[i + 1].posY == v[i].posY)
                {
                    if (v.size() > i + 1 && v[i + 1].isbomb == false)
                    {
                        if (v[i + 1].revealed == false)
                        {
                            v[i + 1].revealed = true;
                            if (v[i + 1].bombsnear == 0)
                            {
                                OpenCells(v, v[i + 1].number);
                            }
                        }
                    }
                }
                if (v.size() > i - 1 && v[i - 1].posY == v[i].posY)
                {
                    if (v.size() > i - 1 && v[i - 1].isbomb == false)
                    {
                        if (v[i - 1].revealed == false)
                        {
                            v[i - 1].revealed = true;
                            if (v[i - 1].bombsnear == 0)
                            {
                                OpenCells(v, v[i - 1].number);
                            }
                        }
                    }
                }
                if (v.size() > i + 8 && v[i + 8].posY == v[i + 7].posY)
                {
                    if (v.size() > i + 8 && v[i + 8].isbomb == false)
                    {
                        if (v[i + 8].revealed == false)
                        {
                            v[i + 8].revealed = true;
                            if (v[i + 8].bombsnear == 0)
                            {
                                OpenCells(v, v[i + 8].number);
                            }
                        }
                    }
                }
                if (v.size() > i - 8 && v[i - 8].posY == v[i - 7].posY)
                {
                    if (v.size() > i - 8 && v[i - 8].isbomb == false)
                    {
                        if (v[i - 8].revealed == false)
                        {
                            v[i - 8].revealed = true;
                            if (v[i - 8].bombsnear == 0)
                            {
                                OpenCells(v, v[i - 8].number);
                            }
                        }
                    }
                }
                if (v.size() > i + 7 && v[i + 6].posY == v[i + 7].posY)
                {
                    if (v.size() > i + 6 && v[i + 6].isbomb == false)
                    {
                        if (v[i + 6].revealed == false)
                        {
                            v[i + 6].revealed = true;
                            if (v[i + 6].bombsnear == 0)
                            {
                                OpenCells(v, v[i + 1].number);
                            }
                        }
                    }
                }
                if (v.size() > i - 7 && v[i - 6].posY == v[i - 7].posY)
                {
                    if (v.size() > i - 6 && v[i - 6].isbomb == false)
                    {
                        if (v[i - 6].revealed == false)
                        {
                            v[i - 6].revealed = true;
                            if (v[i - 6].bombsnear == 0)
                            {
                                OpenCells(v, v[i - 6].number);
                            }
                        }
                    }
                }
                if (v.size() > i - 7 && v[i - 7].isbomb == false)
                {
                    if (v[i - 7].revealed == false)
                    {
                        v[i - 7].revealed = true;
                        if (v[i - 7].bombsnear == 0)
                        {
                            OpenCells(v, v[i - 7].number);
                        }
                    }
                }
                if (v.size() > i + 7 && v[i + 7].isbomb == false)
                {
                    if (v[i + 7].revealed == false)
                    {
                        v[i + 7].revealed = true;
                        if (v[i + 7].bombsnear == 0)
                        {
                            OpenCells(v, v[i + 7].number);
                        }
                    }
                }
            }
        }
    }
    return v;
}



bool drawn = false;
bool win = false;
bool lose = false;

int bombs = 0;
int flags = 20;

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
            RECT intflags = { 120, 900, 150, 1000 };
            RECT textflags = { 80, 880, 110, 980 };
            Rectangle(hdc, 117, 899, 140, 917);
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes("Flags left: ");
            DrawText(hdc, wide.c_str(), -1, &textflags, DT_SINGLELINE | DT_NOCLIP);
            DrawText(hdc, std::to_wstring(flags).c_str(), -1, &intflags, DT_SINGLELINE | DT_NOCLIP);
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
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
            /*for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                if (v[i].isbomb == true)
                {
                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));
                }
            }*/

            //Draw a color for mines near click

            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                if (v[i].revealed == true)
                {
                    if (v[i].bombsnear == 0)
                    {
                        HBRUSH  hbrush = CreateSolidBrush(RGB(192, 192, 192));
                        FillRect(hdc, &rect, (hbrush));
                        DeleteObject(hbrush);
                    }
                    else if (v[i].bombsnear == 1)
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

        else if (drawn == false && lose == false && win == false)
        {
            RECT intflags = { 120, 880, 150, 980 };
            RECT textflags = { 60, 860, 110, 960 };
            Rectangle(hdc, 117, 879, 140, 897);
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring wide = converter.from_bytes("Flags left: ");
            DrawText(hdc, wide.c_str(), -1, &textflags, DT_SINGLELINE | DT_NOCLIP);
            DrawText(hdc, std::to_wstring(flags).c_str(), -1, &intflags, DT_SINGLELINE | DT_NOCLIP);
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
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
                    while (v[randbomb].isbomb == true)
                    {
                        randbomb = rand() % 63;
                    }
                }
                v[randbomb].isbomb = true;
                bombs++;
                /*RECT rect = { v[randbomb].topX, v[randbomb].topY, v[randbomb].botX, v[randbomb].botY };
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));*/
            }
            
            //calculate amount of bombs near cell

            for (int i = 0; i < 63; i++)
            {
                if (v.size() > i + 1 && v[i + 1].posY == v[i].posY)
                {
                    if (v.size() > i + 1 && v[i + 1].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i - 1 && v[i - 1].posY == v[i].posY)
                {
                    if (v.size() > i - 1 && v[i - 1].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i + 8 && v[i + 8].posY == v[i + 7].posY)
                {
                    if (v.size() > i + 8 && v[i + 8].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i - 8 && v[i - 8].posY == v[i - 7].posY)
                {
                    if (v.size() > i - 8 && v[i - 8].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i + 7 && v[i + 6].posY == v[i + 7].posY)
                {
                    if (v.size() > i + 6 && v[i + 6].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i - 7 && v[i - 6].posY == v[i - 7].posY)
                {
                    if (v.size() > i - 6 && v[i - 6].isbomb == true)
                    {
                        v[i].bombsnear += 1;
                    }
                }
                if (v.size() > i - 7 && v[i - 7].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
                if (v.size() > i + 7 && v[i + 7].isbomb == true)
                {
                    v[i].bombsnear += 1;
                }
            }

        }

        else if (win == true)
        {
            for (int j = 0; j < 810; j += 90)
            {
                for (int i = 0; i < 630; i += 90)
                {
                    Rectangle(hdc, i, j, i + 90, j + 90);
                }
            }
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(0, 255, 0));
                FillRect(hdc, &rect, (hbrush));
                Sleep(10);
            }
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(0, 255, 0));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(0, 255, 0));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(0, 255, 0));
                FillRect(hdc, &rect, (hbrush));
            }
        }
        else if (lose = true)
        {
            for (int j = 0; j < 810; j += 90)
            {
                for (int i = 0; i < 630; i += 90)
                {
                    Rectangle(hdc, i, j, i + 90, j + 90);
                }
            }
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 0, 0));
                FillRect(hdc, &rect, (hbrush));
                Sleep(10);
            }
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 0, 0));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 0, 0));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &rect, (hbrush));
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].topX, v[i].topY, v[i].botX, v[i].botY };
                HBRUSH  hbrush = CreateSolidBrush(RGB(255, 0, 0));
                FillRect(hdc, &rect, (hbrush));
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
        /*AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;*/
        //find click coordinates
        int l = 0;
        for (int i = 0; i < 63; i++)
        {

            if (v.size() > i && pt.y >= v[i].topY && pt.y <= v[i].botY)
            {
                if (v.size() > i && pt.x >= v[i].topX && pt.x <= v[i].botX)
                {
                    OpenCells(v, v[i].number);
                    /*std::cout << "chosen " << v[i].number << std::endl;
                    std::cout << "bombs " << bombs << std::endl;
                    std::cout << "Flags: " << flags << std::endl;*/
                    //if already flaged -> unflag
                    if (v[i].flaged == true)
                    {
                        v[i].flaged = false;
                        flags++;
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
        if (300 < pt.x && pt.x < 330 && 865 < pt.y && pt.y < 895)
        {
            drawn = false;
            bombs = 0;
            v.clear();
            win = false;
            lose = false;
            flags = 20;
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
        /*AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;*/
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
                        flags++;
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
                            flags--;
                        }
                        else
                        {
                            v[i].flaged = true;
                            flags--;
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