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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define PLAYER_MAX_LIFE         5
#define LINES_OF_BRICKS         5
#define BRICKS_PER_LINE        20
#define CASES_BONUS             5

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
    int bonus; //0: Score+10   1: Ball_Speed*1.5   2: Score*2   3: Score/2
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
static int tableauAleatoire[50];
static int tableauBonus[CASES_BONUS];

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
int IsInside(int element, int tab[], int tabTaille){
    for(int i = 0; i<tabTaille; i++){
        if(element == tab[i]) return 1;
    }
    return 0;
}

// Fill with random integer a new array
void FillArrayRandomly(){
    
    for(int i = 0; i<50; i++ ){
        tableauAleatoire[i] = rand() % 59;     // We create a random integer between 1 and 59 (max(10*numberOfLine + numberOfBricks) = 59)
    }

    for(int j = 0; j<CASES_BONUS; j++){
        int l = tableauAleatoire[rand() % 30];
        int ran = rand() % 30;
        while(IsInside(l, tableauBonus, j) == 1){
            l = tableauAleatoire[ran];
            ran = ran + 1;
        }
        tableauBonus[j] = l;
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
    FillArrayRandomly();
    
    const int screenWidth2 = 800;
    const int screenHeight2 = 450;

    InitWindow(screenWidth2, screenHeight2, "Explanations");

    SetTargetFPS(60);  
      // Main game loop
      
    //while (!WindowShouldClose())    // Detect window close button or ESC key
    //{// Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
    
    BeginDrawing();
        ClearBackground(LIGHTGRAY);

        DrawText("Ceci explique les règles", 190, 200, 20, GRAY);

    EndDrawing();
        //----------------------------------------------------------------------------------
    //}
    // De-Initialization
    //--------------------------------------------------------------------------------------
    //CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    //InitWindow(screenWidth2, screenHeight2, "test");
    //int bonus[] = FillArrayRandomly(5);

    
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
    

    //int tableauBonus1 = tableauBonus;    // array used for bonus
    //tableauBonus = FillArrayRandomly(tableauBonus);
    //int tableauBonus[] = {1, 15, 20, 32, 41}; 
    //FillArrayRandomly();
    //int tableauBonus2 = tableauBonus;    // array used for bonus

    for (int i = 0; i < LINES_OF_BRICKS; i++)
    {
        for (int j = 0; j < BRICKS_PER_LINE; j++)
        {
            brick[i][j].position = (Vector2){ j*brickSize.x + brickSize.x/2, i*brickSize.y + initialDownPosition };
            if(IsInside((i * 10 + j), tableauBonus, 5)){ 
                brick[i][j].bonus = 1;
            }
            brick[i][j].active = true;
        }
    }
    score = 0;
    //int bonus[] = FillArrayRandomly(5);
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
                        if(((i==3) && (j==4)) || ((i==2) && (j==14))){
                            DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, DARKGREEN); 
                        }
                        else if((i==2 && j==6) || (i==3 && j==16)){
                            DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, MAROON); 
                        }
                        else if(IsInside((i*10 + j), tableauBonus, 5)){
                            DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, BEIGE); 
                        }
                        //else if((i * j) == 20 || (i * j + j) == 15) {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, YELLOW);
                        //if((j*nbrAleatoire) % (i+2) == 0 ){DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GREEN); 
                        /*}else if (IsInside((i * 10 + j), bonus, 5)) {DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, YELLOW);
                        */
                        //}
                        else if ((i + j) % 2 == 0) {
                            DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, GRAY);
                        }else {
                            DrawRectangle(brick[i][j].position.x - brickSize.x/2, brick[i][j].position.y - brickSize.y/2, brickSize.x, brickSize.y, DARKGRAY);
                        }
                    }
                }
            }

            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GRAY);
        }
        else {
            if (gameOver){
                DrawText("NEARLY !!! NEXT TIME WILL BE THE ONE", GetScreenWidth()/2 - MeasureText("NEARLY !!! NEXT TIME WILL BE THE ONE", 60)/2, GetScreenHeight()/2 - 200, 60, DARKGRAY);
                DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 50)/2, GetScreenHeight()/2 - 40, 50, GRAY);
                DrawText(TextFormat("YOUR SCORE: %04i", score), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR SCORE: %04i", score), 30)/2, GetScreenHeight()/2 + 70, 30, GRAY);
                DrawText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), GetScreenWidth()/2 - MeasureText(TextFormat("YOUR HIGHEST SCORE: %04i", hiScore), 20)/2, GetScreenHeight()/2 + 140, 20, GRAY);
            }
            else {
                DrawText("WHAT A GAMER !!! THAT'S A WIN !!!", GetScreenWidth()/2 - MeasureText("WHAT A GAMER !!! THAT'S A WIN !!!", 70)/2, GetScreenHeight()/2 - 200, 60, DARKGRAY);
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

