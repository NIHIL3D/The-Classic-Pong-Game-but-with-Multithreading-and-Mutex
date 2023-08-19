#include <iostream>
#include "raylib.h"
#include <thread>
#include <mutex>

using namespace std;

int player1_score = 0;
int player2_score = 0;

class Ball 
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth())
        {
            player1_score++;
            Resetball();
        }
        if (x - radius <= 0)
        {
            player2_score++;
            Resetball();
        }
    }

    void Resetball()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = { -1, 1 };
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
    }

    virtual void Update() = 0;
};

class Player2Paddle : public Paddle
{
public:
    void Update()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y += speed;
        }
        LimitMovement();
    }
};

class Player1Paddle : public Paddle
{
public:
    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        LimitMovement();
    }
};

Ball ball;
Player1Paddle player1;
Player2Paddle player2;
mutex mtx;

void Player1Thread()
{
    while (!WindowShouldClose())
    {
        mtx.lock();
        player1.Update();
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Player2Thread()
{
    while (!WindowShouldClose())
    {
        mtx.lock();
        player2.Update();
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main()
{
    cout << "Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player1.width = 25;
    player1.height = 120;
    player1.x = screen_width - player1.width - 10;
    player1.y = screen_height / 2 - player1.height / 10;
    player1.speed = 1;

    player2.width = 25;
    player2.height = 120;
    player2.x = 10;
    player2.y = screen_height / 2 - player2.height / 2;
    player2.speed = 1;

    thread player1Thread(Player1Thread);
    thread player2Thread(Player2Thread);

    while (!WindowShouldClose())
    {
        mtx.lock();
        ball.Update();
        mtx.unlock();

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player1.x, player1.y, player1.width, player1.height }))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height }))
        {
            ball.speed_x *= -1;
        }

        BeginDrawing();

        ClearBackground(BLACK);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player1.Draw();
        player2.Draw();
        DrawText(TextFormat("%i", player1_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player2_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    player1Thread.join();
    player2Thread.join();

    CloseWindow();
    return 0;
}
