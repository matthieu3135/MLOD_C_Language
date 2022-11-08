/*******************************************************************************************
*
*   raylib - classic game: arkanoid
*
*   Sample game developed by Marc Palau and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
//#include "FenetreAide.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define PLAYER_MAX_LIFE         5
#define LINES_OF_BRICKS         5
#define BRICKS_PER_LINE        20

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct Player {
    Vector2 position;
    Vector2 size;
    int life;
    //int score;  //score of the player
} Player;

typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    int radius;
    bool active;
} Ball;

typedef struct Brick {
    Vector2 position;
    bool active;
} Brick;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 1280; 
static const int screenHeight = 720; 

//static const int screenWidth2 = 720; 
//static const int screenHeight2 = 480;

static bool gameOver = false;
static bool pause = false;

static Player player = { 0 };
static Ball ball = { 0 };
static Brick brick[LINES_OF_BRICKS][BRICKS_PER_LINE] = { 0 };
static Vector2 brickSize = { 0 };
static int score = 0;
static int hiScore = 0;
static int tab[] = {1, 32, 6, 43, 12, 15, 21, 14, 26, 38};

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)
//static void InitWindow2(void);      // Second Window


//------------------------------------------------------------------------------------
// Additional functions
//------------------------------------------------------------------------------------

// Search if the element is present in the array (called tab)
bool IsInside(int element, int tab[], int tabTaille){
    for(int j = 0; j < tabTaille; j++){
        if(element == tab[j]) return true;
    }
    return false;
}

// Fill with random integer a new array
int FillArrayRandomly(size){
    int* bonus = malloc(size*sizeof(int));
    for(int i = 0; i<size; i++ ){
        bonus[i] = rand() % 59;                         // We create a random integer between 1 and 59 (max(10*numberOfLine + numberOfBricks) = 59)
        while(IsInside(bonus[i], bonus, size)){         // We check that the number is not already present
            bonus[i] = rand() % 59;
        }
    }
}



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    //int tab[10] = {1, 32, 6, 43, 12, 15, 21, 14, 26, 38}; //we will use 10*numberOfLine + numberOfBricks
    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    const int screenWidth2 = 800;
    const int screenHeight2 = 450;

    InitWindow(screenWidth2, screenHeight2, "raylib [core] example - basic window");

    SetTargetFPS(60);  
      // Main game loop
    /*while (!WindowShouldClose())    // Detect window close button or ESC key
    {*/// Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
    BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
        //----------------------------------------------------------------------------------
    //}
    // De-Initialization
    //--------------------------------------------------------------------------------------
    //CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    //InitWindow(screenWidth2, screenHeight2, "test");
    int bonus[] = FillArrayRandomly(5);
    InitWindow(screenWidth, screenHeight, "classic game: arkanoid");


    InitGame();
    

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //CloseWindow2();
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    brickSize = (Vector2){ GetScreenWidth()/BRICKS_PER_LINE, 40 };

    // Initialize player
    player.position = (Vector2){ screenWidth/2, screenHeight*7/8 };
    player.size = (Vector2){ screenWidth/10, 20 };
    player.life = PLAYER_MAX_LIFE;
    //player.score = 0;

    // Initialize ball
    ball.position = (Vector2){ screenWidth/2, screenHeight*7/8 - 30 };
    ball.speed = (Vector2){ 0, 0 };
    ball.radius = 7;
    ball.active = false;

    // Initialize bricks
    int initialDownPosition = 50;

    for (int i = 0; i < LINES_OF_BRICKS; i++)
    {
        for (int j = 0; j < BRICKS_PER_LINE; j++)
        {
            brick[i][j].position = (Vector2){ j*brickSize.x + brickSize.x/2, i*brickSize.y + initialDownPosition };
            brick[i][j].active = true;
        }
    }
    score = 0;
    //tab = {1, 32, 6, 43, 12, 15, 21, 14, 26, 38}; //we will use 10*numberOfLine + numberOfBricks

}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            // Player movement logic
            if (IsKeyDown(KEY_LEFT)) player.position.x -= 10;
            if ((player.position.x - player.size.x/2) <= 0) player.position.x = player.size.x/2;
            if (IsKeyDown(KEY_RIGHT)) player.position.x += 10;
            if ((player.position.x + player.size.x/2) >= screenWidth) player.position.x = screenWidth - player.size.x/2;

            // Ball launching logic
            if (!ball.active)
            {
                if (IsKeyPressed(KEY_SPACE))
                {
                    ball.active = true;
                    ball.speed = (Vector2){ 0, -10 };
                }
            }

            // Ball movement logic
            if (ball.active)
            {
                ball.position.x += ball.speed.x;
                ball.position.y += ball.speed.y;
            }
            else
            {
                ball.position = (Vector2){ player.position.x, screenHeight*7/8 - 30 };
            }

            // Collision logic: ball vs walls
            if (((ball.position.x + ball.radius) >= screenWidth) || ((ball.position.x - ball.radius) <= 0)) ball.speed.x *= -1;
            if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;
            if ((ball.position.y + ball.radius) >= screenHeight)
            {
                ball.speed = (Vector2){ 0, 0 };
                ball.active = false;

                player.life--;
            }

            // Collision logic: ball vs player
            if (CheckCollisionCircleRec(ball.position, ball.radius,
                (Rectangle){ player.position.x - player.size.x/2, player.position.y - player.size.y/2, player.size.x, player.size.y}))
            {
                if (ball.speed.y > 0)
                {
                    ball.speed.y *= -1;
                    ball.speed.x = ((ball.position.x - player.position.x)/(player.size.x/2)*5);
                }
            }

            // Collision logic: ball vs bricks
            for (int i = 0; i < LINES_OF_BRICKS; i++)
            {
                for (int j = 0; j < BRICKS_PER_LINE; j++)
                {
                    if (brick[i][j].active)
                    {
                        // Hit below
                        if (((ball.position.y - ball.radius) <= (brick[i][j].position.y + brickSize.y/2)) &&
                            ((ball.position.y - ball.radius) > (brick[i][j].position.y + brickSize.y/2 + ball.speed.y)) &&
                            ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x/2 + ball.radius*2/3)) && (ball.speed.y < 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.y *= -1;
                            //player.score = player.score + 10;
                            score = score + 10;
                        }
                        // Hit above
                        else if (((ball.position.y + ball.radius) >= (brick[i][j].position.y - brickSize.y/2)) &&
                                ((ball.position.y + ball.radius) < (brick[i][j].position.y - brickSize.y/2 + ball.speed.y)) &&
                                ((fabs(ball.position.x - brick[i][j].position.x)) < (brickSize.x/2 + ball.radius*2/3)) && (ball.speed.y > 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.y *= -1;
                            //player.score = player.score + 10;
                            score = score + 10;
                        }
                        // Hit left
                        else if (((ball.position.x + ball.radius) >= (brick[i][j].position.x - brickSize.x/2)) &&
                                ((ball.position.x + ball.radius) < (brick[i][j].position.x - brickSize.x/2 + ball.speed.x)) &&
                                ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y/2 + ball.radius*2/3)) && (ball.speed.x > 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.x *= -1;
                            //player.score = player.score + 10;
                            score = score + 10;
                        }
                        // Hit right
                        else if (((ball.position.x - ball.radius) <= (brick[i][j].position.x + brickSize.x/2)) &&
                                ((ball.position.x - ball.radius) > (brick[i][j].position.x + brickSize.x/2 + ball.speed.x)) &&
                                ((fabs(ball.position.y - brick[i][j].position.y)) < (brickSize.y/2 + ball.radius*2/3)) && (ball.speed.x < 0))
                        {
                            brick[i][j].active = false;
                            ball.speed.x *= -1;
                            //player.score = player.score + 10;
                            score = score + 10;
                        }
                    }
                }
            }

            // Game over logic
            if (player.life <= 0) {
                gameOver = true;
                if (score > hiScore) hiScore = score;
            }
            else
            {
                gameOver = true;

                for (int i = 0; i < LINES_OF_BRICKS; i++)
                {
                    for (int j = 0; j < BRICKS_PER_LINE; j++)
                    {
                        if (brick[i][j].active) gameOver = false;
                    }
                }
                if (score > hiScore) hiScore = score;
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

//int public nbrAleatoire = rand() % 3;

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

        ClearBackground(RAYWHITE);
        if(player.life == 1) ClearBackground(CLITERAL(Color){ 230, 41, 55, 255 });

        if (!gameOver)
        {
            // Draw player bar
            DrawRectangle(player.position.x - player.size.x/2, player.position.y - player.size.y/2, player.size.x, player.size.y, BLACK);

            // Draw player lives
            for (int i = 0; i < player.life; i++) DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, GREEN);
            if(player.life == 3) {for (int i = 0; i < player.life; i++) DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, ORANGE);} 
            if(player.life <=2) {for (int i = 0; i < player.life; i++) DrawRectangle(20 + 40*i, screenHeight - 30, 35, 10, RED);} 
            // Draw ball
            DrawCircleV(ball.position, ball.radius, MAROON);

            //Write Score
            DrawText(TextFormat("SCORE: %04i", score), 1000, 500, 40, GRAY);
            DrawText(TextFormat("HIGHEST SCORE: %04i", hiScore), 1000, 550, 20, LIGHTGRAY);


            // Draw bricks           
            for (int i = 0; i < LINES_OF_BRICKS; i++)
            {
                for (int j = 0; j < BRICKS_PER_LINE; j++)
                {
                    if (brick[i][j].active)
                    {
                        if(IsInside((i*10 + j), tab, 10)){DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GREEN); 
                        }
                        else if ((i * j) == 20 || (i * j + j) == 15) {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, MAROON);
                        //if((j*nbrAleatoire) % (i+2) == 0 ){DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GREEN); 
                        }else if (IsInside((i * 10 + j), bonus, 5)) {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, YELLOW);
                        }else if ((i + j) % 2 == 0) {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GRAY);
                        }else {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, DARKGRAY);
                        }
                    }
                }
            }

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        else {
            if (!gameOver){
                DrawText("NEARLY !!! NEXT TIME WILL BE THE ONE", GetScreenWidth()/2 - MeasureText("NEARLY !!! NEXT TIME WILL BE THE ONE", 70)/2, GetScreenHeight()/2 - 100, 70, GRAY);
                DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 50)/2, GetScreenHeight()/2 - 40, 50, GRAY);
                DrawText(TextFormat("YOUR SCORE: %04i", score), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR SCORE: %04i", score), 30)/2, GetScreenHeight()/2 + 70, 30, GRAY);
                DrawText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), 20)/2, GetScreenHeight()/2 + 140, 20, GRAY);
            }
            else {
                DrawText("WHAT A GAMER !!! THAT'S A WIN !!!", GetScreenWidth()/2 - MeasureText("WHAT A GAMER !!! THAT'S A WIN !!!", 70)/2, GetScreenHeight()/2 - 100, 70, GRAY);
                DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 50)/2, GetScreenHeight()/2 - 40, 50, GRAY);
                DrawText(TextFormat("YOUR SCORE: %04i", score), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR SCORE: %04i", score), 30)/2, GetScreenHeight()/2 + 70, 30, GRAY);
                DrawText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), 20)/2, GetScreenHeight()/2 + 140, 20, GRAY);
            }
        }

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}

