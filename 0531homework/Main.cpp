#include "stdafx.h"

#define WIDTH 30
#define HEIGHT 20
#define STARTLENGTH 3

void gotoxy(int x, int y);
void Start();
void Reset();
bool Update();
void Render();

enum class Direction
{
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};

struct Food
{
    int x;
    int y;
    bool isFood;
};

struct Player
{
    int x;
    int y;
    Direction pDirection;
};

Food food;
Player player;

int Score = 0;

Stopwatch currentTime;

int main()
{
    Start();
    Reset();

    while (Update())
    {
        Render();
    }

	return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Start()
{
    system("Snake game");
    system("mode con:cols=100 lines=30");

    {
        HANDLE hConsole;
        CONSOLE_CURSOR_INFO ConsoleCursor;

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        ConsoleCursor.bVisible = 0;
        ConsoleCursor.dwSize = 1;

        SetConsoleCursorInfo(hConsole, &ConsoleCursor);
    }

    std::cout << "Áö··ÀÌ °ÔÀÓ" << std::endl;

    system("pause");
    system("cls");
}

void Reset()
{
    currentTime.Start();

    food.x = Math::Random(1, WIDTH - 1);
    food.y = Math::Random(1, HEIGHT - 1);
    food.isFood = true;

    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;
    player.pDirection = Direction::RIGHT;
}

bool Update()
{
    if (_kbhit())
    {
        int key;

        key = _getch();

        if (key == 224)
        {
            key = _getch();

            player.pDirection = static_cast<Direction>(key);

            
            // ÇÃ·¹ÀÌ¾î ¸Ó¸®¶û ¸ÔÀÌ ºÎµúÇûÀ»¶§, º®ÀÌ¶û ºÎµúÇûÀ»¶§
        }
    }
    return true;
}

void Render()
{
    system("cls");

    gotoxy(food.x, food.y);
    std::cout << "££";

    // ÇÃ·¹ÀÌ¾î ¸Ó¸® ~ ²¿¸® ±¸Çö
    switch (player.pDirection)
    {
        case Direction::UP :
            player.y--;
            break;
        case Direction::LEFT:
            player.x--;
            break;
        case Direction::RIGHT:
            player.x++;
            break;
        case Direction::DOWN:
            player.y++;
            break;
    }

    gotoxy(player.x, player.y);
    std::cout << "¡Ú";

    for (int i = 0; i < WIDTH + 1; i++)
    {
        gotoxy(i, 0);
        std::cout << "¡Ø";

        for (int j = 0; j < HEIGHT + 1; j++)
        {
            gotoxy(i, j);
            if(i==0 || i==WIDTH)
                std::cout << "¡Ø";
        }
        gotoxy(i, HEIGHT + 1);
        std::cout << "¡Ø";
    }

    std:: cout << std::endl;
    std::cout << "Á¡¼ö : " << Score;

    Sleep(500);
    Score += 100;
}