// Arcanoid.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Events.h"
#include "Game.h"

#define MAX_LOADSTRING 100

int btn_num = -1;
int last_btn = -1;
Brick* bricks;
Ball* ball;
Racket* racket;
Button* buttons;
Bonus* bonuses;
int bonus_sum;


// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

   

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ARCANOID, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    buttons = SystemInit(buttons);
    DrawMenu(buttons, btn_num);



    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ARCANOID));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, NULL, 0, 0))
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARCANOID));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+3);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      WINDOW_X_POS, WINDOW_Y_POS, WINDOW_WIDTH, FIELD_HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TIMER:
    {
        if (StartGameAtt(GET, NULL) != 0)
        {
            MoveBall(buttons);
        }
        bonus_sum = GetBonusSum();
        DrawBonuses(bonuses, bonus_sum);
    } break;
    

    case WM_KEYDOWN:
    {
        switch (wParam)
        {

        case VK_LEFT:
        {
            if (StartGameAtt(GET, NULL) == 0)
            {
                if ((racket->centre.x - RACKET_SIZE) >= RIGHT_INDENT)
                {
                    DeleteBall(ball);
                    DeleteRacket(racket);
                    racket->centre.x -= racket->speed;
                    ball->position.x -= racket->speed;
                    DrawRacket(racket);
                    DrawBall(ball);
                    LastMoveAtt(SET, -1);
                }
            }
            else
            {
                if ((racket->centre.x - RACKET_SIZE) >= RIGHT_INDENT)
                {
                    DeleteRacket(racket);
                    racket->centre.x -= racket->speed;
                    DrawRacket(racket);
                    ReflSpeedAtt(SET, -racket->speed);
                }
            }
            if (racket->centre.x - RACKET_SIZE < RIGHT_INDENT)
            {
                DeleteBall(ball);
                DeleteRacket(racket);
                racket->centre.x = RIGHT_INDENT + RACKET_SIZE;
                DrawRacket(racket);
                DrawBall(ball);
                DrawBorder();
            }
            SetBall(ball);
            SetRacket(racket);


        } break;

        case VK_RIGHT:
        {
            if (StartGameAtt(GET, NULL) == 0)
            {
                if ((racket->centre.x + RACKET_SIZE) <= FIELD_WIDTH + RIGHT_INDENT)
                {
                    DeleteBall(ball);
                    DeleteRacket(racket);
                    racket->centre.x += racket->speed;
                    ball->position.x += racket->speed;
                    DrawRacket(racket);
                    DrawBall(ball);
                    LastMoveAtt(SET, 1);
                }
                if (racket->centre.x + RACKET_SIZE > WINDOW_WIDTH - RIGHT_INDENT - BORDER_WIDTH)
                {
                    DeleteBall(ball);
                    DeleteRacket(racket);
                    racket->centre.x = WINDOW_WIDTH - RIGHT_INDENT - RACKET_SIZE;
                    ball->position.x = WINDOW_WIDTH - RIGHT_INDENT - RACKET_SIZE;
                    DrawRacket(racket);
                    DrawBall(ball);
                    DrawBorder();
                }

            }
            else
            {
                if ((racket->centre.x + RACKET_SIZE) <= FIELD_WIDTH + RIGHT_INDENT)
                {
                    DeleteRacket(racket);
                    racket->centre.x += racket->speed;
                    DrawRacket(racket);
                    ReflSpeedAtt(SET, racket->speed);
                }
                if (racket->centre.x + RACKET_SIZE > WINDOW_WIDTH - RIGHT_INDENT - BORDER_WIDTH)
                {
                    DeleteRacket(racket);
                    racket->centre.x = WINDOW_WIDTH - RIGHT_INDENT - RACKET_SIZE;
                    DrawRacket(racket);
                    DrawBorder();
                }
            }
            SetBall(ball);
            SetRacket(racket);

        } break;
        case VK_SPACE:
        {
            StartGameAtt(SET, 1);
            SetTimer(hWnd, TIMER, 10, NULL);
        } break;

        case VK_UP:
        {
            if (btn_num > 0)
            {
                last_btn = btn_num;
                btn_num--;
                DrawBtn(hWnd, buttons, btn_num, last_btn);
            }
        } break;
        case VK_DOWN:
        {
            if (btn_num < 5)
            {
                last_btn = btn_num;
                btn_num++;
                DrawBtn(hWnd, buttons, btn_num, last_btn);
            }
        } break;
        case VK_RETURN:
        {
            if (strstr(buttons[btn_num].name, START) != NULL)
            {
                srand(time(NULL));
                SetDiff(rand() % 3 + 1);
                bonuses = NewLevel();
                bricks = GetGameElement(GET_BRICKS);
                racket = GetGameElement(GET_RACKET);
                ball = GetGameElement(GET_BALL);
                btn_num = -1;
            }
            if (strstr(buttons[btn_num].name, END) != NULL)
            {
                DestroyWindow(hWnd);
            }
            if (strstr(buttons[btn_num].name, OPTIONS) != NULL)
            {
                DrawMenu(buttons, btn_num);
                btn_num = 3;
                last_btn = 3;
                DrawBtn(hWnd, buttons, btn_num, last_btn);
            }
            else
            {
                if ((strstr(buttons[btn_num].name, EASY) != NULL) || (strstr(buttons[btn_num].name, MEDIUM) != NULL) || (strstr(buttons[btn_num].name, HARD) != NULL))
                {
                    SetDiff(btn_num - 2);
                    bonuses = NewLevel();
                    bricks = GetGameElement(GET_BRICKS);
                    racket = GetGameElement(GET_RACKET);
                    ball = GetGameElement(GET_BALL);
                    btn_num = -1;
                }
            }
            
            
        } break;

        }
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
   
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
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
