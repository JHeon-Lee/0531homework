#include "stdafx.h"

#define WIDTH 30
#define HEIGHT 20
#define STARTLENGTH 3
#define MAXLENGTH 100

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
};

struct PlayerHead
{
    int x;
    int y;
    Direction pDirection;
};

struct PlayerTail
{
    int x;
    int y;
    bool isTail;
};

Food food;
PlayerHead head;
PlayerTail tail[MAXLENGTH];

int Score = 0;
int lengthCount = 0;

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

    std::cout << "������ ����" << std::endl;

    system("pause");
    system("cls");
}

void Reset() // �ʱ�ȭ
{
    currentTime.Start();

    food.x = Math::Random(1, WIDTH - 1);
    food.y = Math::Random(1, HEIGHT - 1);

    head.x = WIDTH / 2;
    head.y = HEIGHT / 2;
    head.pDirection = Direction::RIGHT;

    for (int i = 0; i < MAXLENGTH; i++)
    {
        if (i < STARTLENGTH - 1)
        {
            tail[i].x = WIDTH / 2 - i - 1;
            tail[i].y = HEIGHT / 2;
            tail[i].isTail = true;
        }
        else
            tail[i].isTail = false;
    }
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

            head.pDirection = static_cast<Direction>(key);
        }
    }

    if (head.x > WIDTH - 1 || head.x < 1 || head.y > HEIGHT - 1 || head.y < 1) // ���� ����� ���
        return false;

    if (head.x == food.x && head.y == food.y) // ���̿� ����� ���
    {
        food.x = Math::Random(1, WIDTH - 1);
        food.y = Math::Random(1, HEIGHT - 1);

        lengthCount++;
        tail[STARTLENGTH + lengthCount].isTail = true;
    }

    return true;
}

void Render()
{
    system("cls");

    // �����̰� �����̴� �κ�
    int tempX(tail[0].x);
    int tempY(tail[0].y);
    tail[0].x = head.x;
    tail[0].y = head.y;

    for (int i = 1; i < MAXLENGTH; i++)
    {
        if (tail[i].isTail == true)
        {
            int tempX2(tail[i].x);
            int tempY2(tail[i].y);
            tail[i].x = tempX;
            tail[i].y = tempY;
            tempX = tempX2;
            tempY = tempY2;
        }
    }

    // �Ӹ� ���� ����
    switch (head.pDirection)
    {
        case Direction::UP :
            head.y--;
            break;
        case Direction::LEFT:
            head.x--;
            break;
        case Direction::RIGHT:
            head.x++;
            break;
        case Direction::DOWN:
            head.y++;
            break;
    }

    // ��º�
    gotoxy(food.x, food.y);
    std::cout << "��";

    gotoxy(head.x, head.y);
    std::cout << "��";

    for (int i = 0; i < MAXLENGTH; i++)
    {
        if (tail[i].isTail == true)
        {
            gotoxy(tail[i].x, tail[i].y);
            std::cout << "��";
        }
    }

    for (int i = 0; i < WIDTH + 1; i++)
    {
        gotoxy(i, 0);
        std::cout << "��";

        for (int j = 0; j < HEIGHT + 1; j++)
        {
            gotoxy(i, j);
            if(i==0 || i==WIDTH)
                std::cout << "��";
        }
        gotoxy(i, HEIGHT);
        std::cout << "��";
    }

    std:: cout << std::endl;
    std::cout << "���� : " << Score;

    Sleep(300);
    Score += 100;

    // ����� ����� ��� ����
    for (int i = 0; i < MAXLENGTH; i++)
    {
        if (head.x == tail[i].x && head.y == tail[i].y)
            exit(0);
    }
}