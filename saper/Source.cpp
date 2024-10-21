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

class cells
{
public:
    int GetNum()
    {
        return number;
    }
    void SetNum(int num)
    {
        this->number = num;
    }
    bool BombCheck()
    {
        return isbomb;
    }
    void SetBomb(bool bomb)
    {
        isbomb = bomb;
    }
    bool RevealedCheck()
    {
        return revealed;
    }
    void SetRevealed(bool rev)
    {
        revealed = rev;
    }
    bool FlaggedCheck()
    {
        return flaged;
    }
    void SetFlagged(bool flag)
    {
        flaged = flag;
    }
    int BombNearCheck()
    {
        return bombsnear;
    }
    void SetBombsNear(int bombsnear)
    {
        this->bombsnear = bombsnear;
    }
    void AddBombNear()
    {
        bombsnear++;
    }
    int GetTopY()
    {
        return topY;
    }
    void SetTopY(int topY)
    {
        this->topY = topY;
    }
    int GetTopX()
    {
        return topX;
    }
    void SetTopX(int topX)
    {
        this->topX = topX;
    }
    int GetBotY()
    {
        return botY;
    }
    void SetBotY(int botY)
    {
        this->botY = botY;
    }
    int GetBotX()
    {
        return botX;
    }
    void SetBotX(int botX)
    {
        this->botX = botX;
    }
    int GetPosY()
    {
        return posY;
    }
    void SetPosY(int posY)
    {
        this->posY = posY;
    }
    int GetPosX()
    {
        return posX;
    }
    void SetPosX(int posX)
    {
        this->posX = posX;
    }

private:
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

void FillRectColor(HDC hdc, RECT rect, int red, int green, int blue)
{
    HBRUSH  hbrush = CreateSolidBrush(RGB(red, green, blue));
    FillRect(hdc, &rect, (hbrush));
    DeleteObject(hbrush);
}

std::vector<cells> OpenCells(std::vector<cells> &v, int number)
{
    for (int i = 0; i < 63; i++)
    {
        if (v[i].GetNum() == number)
        {
            if (v[i].BombNearCheck() == 0)
            {
                if (v.size() > i + 1 && v[i + 1].GetPosY() == v[i].GetPosY())
                {
                    if (v.size() > i + 1 && v[i + 1].BombCheck() == false)
                    {
                        if (v[i + 1].RevealedCheck() == false)
                        {
                            v[i + 1].SetRevealed(true);
                            if (v[i + 1].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i + 1].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i - 1 && v[i - 1].GetPosY() == v[i].GetPosY())
                {
                    if (v.size() > i - 1 && v[i - 1].BombCheck() == false)
                    {
                        if (v[i - 1].RevealedCheck() == false)
                        {
                            v[i - 1].SetRevealed(true);
                            if (v[i - 1].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i - 1].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i + 8 && v[i + 8].GetPosY() == v[i + 7].GetPosY())
                {
                    if (v.size() > i + 8 && v[i + 8].BombCheck() == false)
                    {
                        if (v[i + 8].RevealedCheck() == false)
                        {
                            v[i + 8].SetRevealed(true);
                            if (v[i + 8].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i + 8].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i - 8 && v[i - 8].GetPosY() == v[i - 7].GetPosY())
                {
                    if (v.size() > i - 8 && v[i - 8].BombCheck() == false)
                    {
                        if (v[i - 8].RevealedCheck() == false)
                        {
                            v[i - 8].SetRevealed(true);
                            if (v[i - 8].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i - 8].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i + 7 && v[i + 6].GetPosY() == v[i + 7].GetPosY())
                {
                    if (v.size() > i + 6 && v[i + 6].BombCheck() == false)
                    {
                        if (v[i + 6].RevealedCheck() == false)
                        {
                            v[i + 6].SetRevealed(true);
                            if (v[i + 6].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i + 1].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i - 7 && v[i - 6].GetPosY() == v[i - 7].GetPosY())
                {
                    if (v.size() > i - 6 && v[i - 6].BombCheck() == false)
                    {
                        if (v[i - 6].RevealedCheck() == false)
                        {
                            v[i - 6].SetRevealed(true);
                            if (v[i - 6].BombNearCheck() == 0)
                            {
                                OpenCells(v, v[i - 6].GetNum());
                            }
                        }
                    }
                }
                if (v.size() > i - 7 && v[i - 7].BombCheck() == false)
                {
                    if (v[i - 7].RevealedCheck() == false)
                    {
                        v[i - 7].SetRevealed(true);
                        if (v[i - 7].BombNearCheck() == 0)
                        {
                            OpenCells(v, v[i - 7].GetNum());
                        }
                    }
                }
                if (v.size() > i + 7 && v[i + 7].BombCheck() == false)
                {
                    if (v[i + 7].RevealedCheck() == false)
                    {
                        v[i + 7].SetRevealed(true);
                        if (v[i + 7].BombNearCheck() == 0)
                        {
                            OpenCells(v, v[i + 7].GetNum());
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
    cells c;
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
                    c.SetNum(cellnum);
                    c.SetBomb(false);
                    c.SetRevealed(false);
                    c.SetFlagged(false);
                    c.SetBombsNear(0);
                    c.SetTopY(j);
                    c.SetTopX(i);
                    c.SetBotY(j + 90);
                    c.SetBotX(i + 90);
                    c.SetPosY(positionY);
                    c.SetPosX(positionX);
                    v.push_back(c);
                    cellnum += 1;
                    positionX += 1;
                }
            }
            //reveal bombs after click
            /*for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                if (v[i].BombCheck() == true)
                {
                    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));
                }
            }*/

            //Draw a color for mines near click

            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                if (v[i].RevealedCheck() == true)
                {
                    if (v[i].BombNearCheck() == 0)
                    {
                        FillRectColor(hdc, rect, 192, 192, 192);
                    }
                    else if (v[i].BombNearCheck() == 1)
                    {
                        FillRectColor(hdc, rect, 55, 38, 255);
                    }
                    else if (v[i].BombNearCheck() == 2)
                    {
                        FillRectColor(hdc, rect, 38, 143, 15);
                    }
                    else if (v[i].BombNearCheck() == 3)
                    {
                        FillRectColor(hdc, rect, 238, 0, 0);
                    }
                    else if (v[i].BombNearCheck() == 4)
                    {
                        FillRectColor(hdc, rect, 35, 3, 115);
                    }
                    else if (v[i].BombNearCheck() == 5)
                    {
                        FillRectColor(hdc, rect, 115, 3, 3);
                    }
                    else if (v[i].BombNearCheck() == 6)
                    {
                        FillRectColor(hdc, rect, 71, 156, 160);
                    }
                    else if (v[i].BombNearCheck() == 7)
                    {
                        FillRectColor(hdc, rect, 0, 0, 0);
                    }
                    else if (v[i].BombNearCheck() == 8)
                    {
                        FillRectColor(hdc, rect, 149, 149, 149);
                    }
                }
            }

            //draw a flag

            for (size_t i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                if (v[i].FlaggedCheck() == true)
                {
                    RECT rect = { v[i].GetTopX() + 20, v[i].GetTopY() + 20, v[i].GetBotX() - 20, v[i].GetBotY() - 20};
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
                    c.SetNum(cellnum);
                    c.SetBomb(false);
                    c.SetRevealed(false);
                    c.SetFlagged(false);
                    c.SetBombsNear(0);
                    c.SetTopY(j);
                    c.SetTopX(i);
                    c.SetBotY(j + 90);
                    c.SetBotX(i + 90);
                    c.SetPosY(positionY);
                    c.SetPosX(positionX);
                    v.push_back(c);
                    cellnum += 1;
                    positionX += 1;
                }
            }
            //generate bombs
            while (bombs != 20)
            {
                randbomb = rand() % 63;
                if (v[randbomb].BombCheck() == true)
                {
                    while (v[randbomb].BombCheck() == true)
                    {
                        randbomb = rand() % 63;
                    }
                }
                v[randbomb].SetBomb(true);
                bombs++;
                //reveal bombs before click
                /*RECT rect = { v[randbomb].GetTopX(), v[randbomb].GetTopY(), v[randbomb].GetBotX(), v[randbomb].GetBotY() };
                FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 9));*/
            }
            
            //calculate amount of bombs near cell

            for (int i = 0; i < 63; i++)
            {
                if (v.size() > i + 1 && v[i + 1].GetPosY() == v[i].GetPosY())
                {
                    if (v.size() > i + 1 && v[i + 1].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i - 1 && v[i - 1].GetPosY() == v[i].GetPosY())
                {
                    if (v.size() > i - 1 && v[i - 1].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i + 8 && v[i + 8].GetPosY() == v[i + 7].GetPosY())
                {
                    if (v.size() > i + 8 && v[i + 8].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i - 8 && v[i - 8].GetPosY() == v[i - 7].GetPosY())
                {
                    if (v.size() > i - 8 && v[i - 8].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i + 7 && v[i + 6].GetPosY() == v[i + 7].GetPosY())
                {
                    if (v.size() > i + 6 && v[i + 6].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i - 7 && v[i - 6].GetPosY() == v[i - 7].GetPosY())
                {
                    if (v.size() > i - 6 && v[i - 6].BombCheck() == true)
                    {
                        v[i].AddBombNear();
                    }
                }
                if (v.size() > i - 7 && v[i - 7].BombCheck() == true)
                {
                    v[i].AddBombNear();
                }
                if (v.size() > i + 7 && v[i + 7].BombCheck() == true)
                {
                    v[i].AddBombNear();
                }
            }

        }

        //win
        else if (win == true)
        {
            for (int j = 0; j < 810; j += 90)
            {
                for (int i = 0; i < 630; i += 90)
                {
                    Rectangle(hdc, i, j, i + 90, j + 90);
                }
            }
            //draw restart button
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
            //draw win
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 0, 255, 0);
                Sleep(10);
            }
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 0, 255, 0);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 0, 255, 0);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 0, 255, 0);
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
            //draw restart button
            RECT gamerest = { 305, 870, 325, 890 };
            Rectangle(hdc, 300, 865, 330, 895);
            HBRUSH  hbrush = CreateSolidBrush(RGB(255, 255, 0));
            FillRect(hdc, &gamerest, (hbrush));
            DeleteObject(hbrush);
            //draw win
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 0, 0);
                Sleep(10);
            }
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 0, 0);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 0, 0);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 255, 255);
            }
            Sleep(200);
            for (int i = 0; i < 63; i++)
            {
                RECT rect = { v[i].GetTopX(), v[i].GetTopY(), v[i].GetBotX(), v[i].GetBotY() };
                FillRectColor(hdc, rect, 255, 0, 0);
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
        //create console in ram to cout coords of click
        /*AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;*/
        //find click coordinates
        int l = 0;
        for (int i = 0; i < 63; i++)
        {

            if (v.size() > i && pt.y >= v[i].GetTopY() && pt.y <= v[i].GetBotY())
            {
                if (v.size() > i && pt.x >= v[i].GetTopX() && pt.x <= v[i].GetBotX())
                {
                    OpenCells(v, v[i].GetNum());
                    /*std::cout << "chosen " << v[i].number << std::endl;
                    std::cout << "bombs " << bombs << std::endl;
                    std::cout << "Flags: " << flags << std::endl;*/
                    //if already flaged -> unflag
                    if (v[i].FlaggedCheck() == true)
                    {
                        v[i].SetFlagged(false);
                        flags++;
                        if (v[i].BombCheck() == true)
                        {
                            bombs++;
                        }
                    }
                    v[i].SetRevealed(true);
                    drawn = true;
                    //lose if clicked on bomb
                    if (v[i].BombCheck() == true)
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
        //create console in ram to cout coords of click
        /*AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
        std::cout << "X:" << " " << pt.x << " " << "Y:" << " " << pt.y << std::endl;*/
        //find click coordinates
        
        for (int i = 0; i < 63; i++)
        {

            if (v.size() > i && pt.y >= v[i].GetTopY() && pt.y <= v[i].GetBotY())
            {
                if (v.size() > i && pt.x >= v[i].GetTopX()&& pt.x <= v[i].GetBotX())
                {
                    drawn = true;
                    //if already flaged -> unflag
                    if (v[i].FlaggedCheck() == true)
                    {
                        v[i].SetFlagged(false);
                        flags++;
                        if (v[i].BombCheck() == true)
                        {
                            bombs++;
                        }
                    }
                    else
                    {
                        //flag
                        if (v[i].BombCheck() == true)
                        {
                            v[i].SetFlagged(true);
                            bombs--;
                            flags--;
                        }
                        else
                        {
                            v[i].SetFlagged(true);
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