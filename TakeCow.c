#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------

#define NUM_MAX_ENEMIES 100

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

typedef struct Player{
    Rectangle rec;
    Vector2 speed;
    Color color;
} Player;

typedef struct Enemy{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

typedef struct Points {
    Vector2 position;
    int radius;
    int value;
    bool active;
} Points;

typedef struct Home {
    Rectangle rec;
    bool active;
    bool save;
    Color color;
} Home;

typedef struct Name{
    char jog1[3];
    char jog2[3];
    char jog3[3];
    char NameVoid[20];
    
    bool active; 
    bool p1;
    bool p12;
    bool p2;
    bool p3;
    bool none;
}Name;

typedef struct Chang{
    char jog1[3];
    char jog2[3];
    char jog3[3];
}Chang;



//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static int screenWidth = 450;
static int screenHeight = 650;

static int framesCounter;
static bool gameOver;
static bool pause;
static int score;
static bool victory;
static int hiScore;
static int hiScore1;
static int hiScore2;
static int hiscore;
static int cont;

static Player player;
static Enemy enemy[NUM_MAX_ENEMIES];
static Points points;
static Home home;
static Name name;
static Chang chang;


static int activeEnemies;


static Texture2D texture2;
static Texture2D texture3;
static Texture2D texture4;
static Texture2D texture5;




//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)
static void PlayerName(void);       // Entra com o nome do jogador
static void ChangeName(void);       // Troca os nomes

//------------------------------------------------------------------------------------
// Program main 
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "TakeCow");
    
    Texture2D texture  = LoadTexture("/jogo/imagenns/fundo.png");
              texture2 = LoadTexture("/jogo/imagenns/ufo-512.png");
              texture3 = LoadTexture("/jogo/imagenns/cow.png");
              texture4 = LoadTexture("/jogo/imagenns/ufo.png");
              texture5 = LoadTexture("/jogo/imagenns/bullet.png");
    Texture2D texture6 = LoadTexture("/jogo/imagenns/cubicmap.png");
                
    InitGame();
  
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateGame();
        //----------------------------------------------------------------------------------

             DrawTexture(texture, 0, 0, LIGHTGRAY);
             DrawTexture(texture6,400,20,WHITE);
             
        // Draw
        //----------------------------------------------------------------------------------
        DrawGame();
        
        
        //----------------------------------------------------------------------------------
    }   


    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------


// Initialize game variables
void InitGame(void)
{
    // Initialize game variables
    
        pause = false;
        gameOver = false;
        victory = false;
        activeEnemies = 10;
        score = 0;
        

    // Initialize player
        player.rec.x =  205;
        player.rec.y = 50;
        player.rec.width = 50;
        player.rec.height = 40;
        player.speed.x = 5;
        player.speed.y = 5;
        player.color = BLANK;

    // Initialize enemies
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rec.width = 5;
        enemy[i].rec.height = 20;
        enemy[i].rec.x = GetRandomValue(0, screenWidth );
        enemy[i].rec.y = GetRandomValue(screenHeight, screenHeight + 1000 );
        enemy[i].speed.x = 3;
        enemy[i].speed.y = 3;
        enemy[i].active = true;
        enemy[i].color = RED;
    }

    
    //Initialize points
        points.radius = 10;
        points.position = (Vector2){GetRandomValue(points.radius, screenWidth - points.radius), 600};
        points.value = 100;
        points.active = true;
        
    
    // Initialize Home
            
        home.rec.width = 450;
        home.rec.height = 100;
        home.rec.x = 0;
        home.rec.y = 0;
        home.active = false;
        home.save = false;
        
    // Player Name Bool
        
        name.p1 = false;
        name.p2 = false;
        name.p2 = false;
        name.p12 = false;
        cont = 0;
        
        
        
}

void PlayerName(void){
    
    if(!name.p1 && !name.p2 && !name.p3 )
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
        int j=150;
                for(int i = 0; i < 3; i++){
                    DrawText(FormatText("%c", name.jog1[i]), j, 50 , 20, LIGHTGRAY);
                    DrawText(FormatText("%c", name.jog2[i]), j, 70 , 20, LIGHTGRAY);
                    DrawText(FormatText("%c", name.jog3[i]), j, 90 , 20, LIGHTGRAY);
                    j+=15;
                }
                
            DrawText(FormatText(" %04i", hiscore), 190, 50, 20,  LIGHTGRAY);
            DrawText(FormatText(" %04i", hiScore1), 190, 70, 20, LIGHTGRAY);
            DrawText(FormatText(" %04i", hiScore2), 190, 90, 20, LIGHTGRAY);
            
    }        
    else 
    {
        DrawText("DIGITE 3 LETRAS", 110,180,20, BLUE);
    
        //First place
         if(name.p1){
                if (IsKeyPressed(KEY_A)) name.jog1[cont] = 'A', cont++;
                if (IsKeyPressed(KEY_B)) name.jog1[cont] = 'B', cont++;
                if (IsKeyPressed(KEY_C)) name.jog1[cont] = 'C', cont++;
                if (IsKeyPressed(KEY_D)) name.jog1[cont] = 'D', cont++;
                if (IsKeyPressed(KEY_E)) name.jog1[cont] = 'E', cont++;
                if (IsKeyPressed(KEY_F)) name.jog1[cont] = 'F', cont++;
                if (IsKeyPressed(KEY_G)) name.jog1[cont] = 'G', cont++;
                if (IsKeyPressed(KEY_H)) name.jog1[cont] = 'H', cont++;
                if (IsKeyPressed(KEY_I)) name.jog1[cont] = 'I', cont++;
                if (IsKeyPressed(KEY_J)) name.jog1[cont] = 'J', cont++;
                if (IsKeyPressed(KEY_K)) name.jog1[cont] = 'K', cont++;
                if (IsKeyPressed(KEY_L)) name.jog1[cont] = 'L', cont++;
                if (IsKeyPressed(KEY_M)) name.jog1[cont] = 'M', cont++;
                if (IsKeyPressed(KEY_N)) name.jog1[cont] = 'N', cont++;
                if (IsKeyPressed(KEY_O)) name.jog1[cont] = 'O', cont++;
                if (IsKeyPressed(KEY_P)) name.jog1[cont] = 'P', cont++;
                if (IsKeyPressed(KEY_Q)) name.jog1[cont] = 'Q', cont++;
                if (IsKeyPressed(KEY_R)) name.jog1[cont] = 'R', cont++;
                if (IsKeyPressed(KEY_S)) name.jog1[cont] = 'S', cont++;
                if (IsKeyPressed(KEY_T)) name.jog1[cont] = 'T', cont++;
                if (IsKeyPressed(KEY_U)) name.jog1[cont] = 'U', cont++;
                if (IsKeyPressed(KEY_V)) name.jog2[cont] = 'V', cont++;
                if (IsKeyPressed(KEY_W)) name.jog1[cont] = 'W', cont++;
                if (IsKeyPressed(KEY_X)) name.jog1[cont] = 'X', cont++;
                if (IsKeyPressed(KEY_Y)) name.jog1[cont] = 'Y', cont++;
                if (IsKeyPressed(KEY_Z)) name.jog1[cont] = 'Z', cont++;
         }
         //-------------------------------------------------------------------------
         //Second place
         if(name.p2){
                if (IsKeyPressed(KEY_A)) name.jog2[cont] = 'A', cont++;
                if (IsKeyPressed(KEY_B)) name.jog2[cont] = 'B', cont++;
                if (IsKeyPressed(KEY_C)) name.jog2[cont] = 'C', cont++;
                if (IsKeyPressed(KEY_D)) name.jog2[cont] = 'D', cont++;
                if (IsKeyPressed(KEY_E)) name.jog2[cont] = 'E', cont++;
                if (IsKeyPressed(KEY_F)) name.jog2[cont] = 'F', cont++;
                if (IsKeyPressed(KEY_G)) name.jog2[cont] = 'G', cont++;
                if (IsKeyPressed(KEY_H)) name.jog2[cont] = 'H', cont++;
                if (IsKeyPressed(KEY_I)) name.jog2[cont] = 'I', cont++;
                if (IsKeyPressed(KEY_J)) name.jog2[cont] = 'J', cont++;
                if (IsKeyPressed(KEY_K)) name.jog2[cont] = 'K', cont++;
                if (IsKeyPressed(KEY_L)) name.jog2[cont] = 'L', cont++;
                if (IsKeyPressed(KEY_M)) name.jog2[cont] = 'M', cont++;
                if (IsKeyPressed(KEY_N)) name.jog2[cont] = 'N', cont++;
                if (IsKeyPressed(KEY_O)) name.jog2[cont] = 'O', cont++;
                if (IsKeyPressed(KEY_P)) name.jog2[cont] = 'P', cont++;
                if (IsKeyPressed(KEY_Q)) name.jog2[cont] = 'Q', cont++;
                if (IsKeyPressed(KEY_R)) name.jog2[cont] = 'R', cont++;
                if (IsKeyPressed(KEY_S)) name.jog2[cont] = 'S', cont++;
                if (IsKeyPressed(KEY_T)) name.jog2[cont] = 'T', cont++;
                if (IsKeyPressed(KEY_U)) name.jog2[cont] = 'U', cont++;
                if (IsKeyPressed(KEY_V)) name.jog2[cont] = 'V', cont++;
                if (IsKeyPressed(KEY_W)) name.jog2[cont] = 'W', cont++;
                if (IsKeyPressed(KEY_X)) name.jog2[cont] = 'X', cont++;
                if (IsKeyPressed(KEY_Y)) name.jog2[cont] = 'Y', cont++;
                if (IsKeyPressed(KEY_Z)) name.jog2[cont] = 'Z', cont++;
         }
         //-------------------------------------------------------------------------
         //Third place
         if(name.p3){
                if (IsKeyPressed(KEY_A)) name.jog3[cont] = 'A', cont++;
                if (IsKeyPressed(KEY_B)) name.jog3[cont] = 'B', cont++;
                if (IsKeyPressed(KEY_C)) name.jog3[cont] = 'C', cont++;
                if (IsKeyPressed(KEY_D)) name.jog3[cont] = 'D', cont++;
                if (IsKeyPressed(KEY_E)) name.jog3[cont] = 'E', cont++;
                if (IsKeyPressed(KEY_F)) name.jog3[cont] = 'F', cont++;
                if (IsKeyPressed(KEY_G)) name.jog3[cont] = 'G', cont++;
                if (IsKeyPressed(KEY_H)) name.jog3[cont] = 'H', cont++;
                if (IsKeyPressed(KEY_I)) name.jog3[cont] = 'I', cont++;
                if (IsKeyPressed(KEY_J)) name.jog3[cont] = 'J', cont++;
                if (IsKeyPressed(KEY_K)) name.jog3[cont] = 'K', cont++;
                if (IsKeyPressed(KEY_L)) name.jog3[cont] = 'L', cont++;
                if (IsKeyPressed(KEY_M)) name.jog3[cont] = 'M', cont++;
                if (IsKeyPressed(KEY_N)) name.jog3[cont] = 'N', cont++;
                if (IsKeyPressed(KEY_O)) name.jog3[cont] = 'O', cont++;
                if (IsKeyPressed(KEY_P)) name.jog3[cont] = 'P', cont++;
                if (IsKeyPressed(KEY_Q)) name.jog3[cont] = 'Q', cont++;
                if (IsKeyPressed(KEY_R)) name.jog3[cont] = 'R', cont++;
                if (IsKeyPressed(KEY_S)) name.jog3[cont] = 'S', cont++;
                if (IsKeyPressed(KEY_T)) name.jog3[cont] = 'T', cont++;
                if (IsKeyPressed(KEY_U)) name.jog3[cont] = 'U', cont++;
                if (IsKeyPressed(KEY_V)) name.jog2[cont] = 'V', cont++;
                if (IsKeyPressed(KEY_W)) name.jog3[cont] = 'W', cont++;
                if (IsKeyPressed(KEY_X)) name.jog3[cont] = 'X', cont++;
                if (IsKeyPressed(KEY_Y)) name.jog3[cont] = 'Y', cont++;
                if (IsKeyPressed(KEY_Z)) name.jog3[cont] = 'Z', cont++;
         }
         //--------------------------------------------------------------------------
         //Final position of string
         if (cont == 3) ChangeName(),name.active = true;
         //--------------------------------------------------------------------------
    }
}

void ChangeName(void){
    
        
        strcpy (chang.jog2, name.jog2);
        strcpy (chang.jog3, name.jog3);
    
    if(name.p1){
        if(hiScore2 != 0) strcpy (name.jog3, chang.jog2); 
        if(hiScore1 != 0) strcpy (name.jog2, chang.jog1);
    }
	if(name.p2){
		if(hiScore2 != 0) strcpy (name.jog3, chang.jog2); 
	}
	
    
    
    
}


// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        
        //nome de novo
        name.active = false;
        
        
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            // levels : 
            switch (score)
            {
                case 0:
                {
                    activeEnemies = 5;
                    
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 3;
                        enemy[i].speed.y = 3;
        
                    }
                        
                        
                    
                } break;
                case 200:
                {
                    activeEnemies = 10;
                    
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 4;
                        enemy[i].speed.y = 4;
        
                    }
                        
                } break;
                case 400:
                {
                    activeEnemies = 15;
                    
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 5;
                        enemy[i].speed.y = 5;
        
                    }
                        
                        
                    
                } break;
                case 600:
                {
                    activeEnemies = 20;
                    
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 7;
                        enemy[i].speed.y = 7;
        
                    }
                        
                } break;
                case 800:
                {
                    activeEnemies = 30;

                    player.speed.x = 7;
                    player.speed.y = 7;
                   
                   
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 8;
                        enemy[i].speed.y = 8;
        
                    }
                        
                } break;
                case 1000:
                {
                    activeEnemies = 35;
                    
                    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
                    {
        
                        enemy[i].speed.x = 9;
                        enemy[i].speed.y = 9;
        
                    }
                        
                } break;
                default: break;
            }

            // Player movement
            if (IsKeyDown(KEY_RIGHT)) player.rec.x += player.speed.x; //RIGHT
            if (IsKeyDown(KEY_LEFT)) player.rec.x -= player.speed.x; //LEFT
            if (IsKeyDown(KEY_UP)) player.rec.y -= player.speed.y; //UP
            if (IsKeyDown(KEY_DOWN)) player.rec.y += player.speed.y; // DOWN

            // Player collision with enemy
            for (int i = 0; i < activeEnemies; i++)
            {
                if (CheckCollisionRecs(player.rec, enemy[i].rec) ) gameOver = true;
                 for (int j = 0; j < activeEnemies; j++)
                    {
                        if (enemy[j].active)
                        {
                            if (CheckCollisionRecs(home.rec, enemy[j].rec))
                            {
                               
                                enemy[j].rec.x = GetRandomValue(0, screenWidth + 1000);
                                enemy[j].rec.y = GetRandomValue(screenHeight, screenHeight - enemy[j].rec.height);
                                
                            }
                            
                            
                        }
                    }
            }

             // Enemy behaviour
            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active)
                {
                    enemy[i].rec.y -= enemy[i].speed.y;

                    if (enemy[i].rec.y < 0)
                    {
                        enemy[i].rec.x = GetRandomValue(0, screenWidth - enemy[i].rec.height);
                        enemy[i].rec.y = GetRandomValue(screenHeight, screenHeight + 1000);
                    }
                }
            }

            // Wall behaviour
            if (player.rec.x <= 0) player.rec.x = 0;
            if (player.rec.x + player.rec.width >= screenWidth) player.rec.x = screenWidth - player.rec.width;
            if (player.rec.y <= 0) player.rec.y = 0;
            if (player.rec.y + player.rec.height >= screenHeight) player.rec.y = screenHeight - player.rec.height;
            
            //Home & Points
            
            //points logic
            
            if (CheckCollisionCircleRec(points.position, points.radius, player.rec) && points.active)
            {
                points.active = false;
                home.active = true;
            }
            
            //Home & local do point
            
            if (CheckCollisionRecs(player.rec, home.rec))
            {
               
               if (!points.active)
               {
                    score +=  50 ;
                    points.active = true;
                    points.position = (Vector2){GetRandomValue(points.radius, screenWidth - points.radius), 620};
                    
                    
               }
               
               home.save = true;
            }
            else home.save = false;
            
            // pontos na tela
            if (score > hiScore) hiscore = score;
            
            //if(score >= 200) victory = true;
        }
    }
    else
    {
        
        // Tabela de Hi-Score
        if (score != 0)
		{
            if (score > hiScore)// primeiro lugar
            {
                victory = true; //mensagem de hiscore
                hiScore2 = hiScore1; //terceiro recebe segundo
                hiScore1 = hiScore; //segundo recebe primeiro
                hiScore = score; //primeiro recebe novo valor
                name.p1 = true; //primeiro recebe string
                    strcpy (chang.jog1, name.jog1);
            }
                else if (score == hiScore && score != hiScore1 && !name.p1) // igual ao primeiro lugar
                {
                    hiScore2 = hiScore1; //terceiro recebe segundo
                    hiScore1 = score; //segundo recebe novo valor
                    name.p2 = true;
					if(hiScore2 != 0) strcpy (name.jog3, chang.jog2);
                    
                }
                else if (score == hiScore && score == hiScore1 && score != hiScore2 && !name.p1)
                {
                    hiScore2 = score;
                    name.p3 = true;
                }
                
            if (score < hiScore && score > hiScore1) // segundo lugar
            {
                hiScore2 = hiScore1; //terceiro recebe segundo
                hiScore1 = score; //segundo recebe novo valor
                name.p2 = true; //segundo recebe nova string    
                    if(hiScore2 != 0) strcpy (name.jog3, name.jog2);
            }
				else if (score == hiScore1 && score > hiScore2 && !name.p2 )
				{
					hiScore2 = score;
					name.p3 = true;
				}
				
            if (score < hiScore1 && score > hiScore2) //terceiro lugar
            {
                hiScore2 = score; //terceiro recebe novo valor
                name.p3 = true; //terceiro lugar recebe nova string
            }
            if (score == 0 || score < hiScore2) name.none = true; //nenhuma string recebe novo valor, comeca o jogo novamente
			score = 0; //zera contador de pontos da partida
        }
            
            
        
        if (IsKeyPressed(KEY_ENTER)) //inicia novamente o jogo
        {
            InitGame();
            gameOver = false;
        }
    }
                    
}

// Draw game (one frame)
void DrawGame(void)
{
     
    BeginDrawing();

        ClearBackground(RAYWHITE);
        
        if (!gameOver)
        {
            //Safe Point && MotherShip
            DrawRectangleLines(home.rec.x, home.rec.y, home.rec.width, home.rec.height, BLACK);
            DrawTexture(texture4,180 ,30,WHITE);
            //------------------------------------------------------------------------------
            //Player UFO
            DrawRectangleRec(player.rec, player.color);
            DrawTexture(texture2,player.rec.x+5,player.rec.y,WHITE);
            //------------------------------------------------------------------------------
            //Draw Enemy
            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active) DrawRectangleRec(enemy[i].rec, enemy[i].color),DrawTexture(texture5,enemy[i].rec.x-5,enemy[i].rec.y-5,WHITE);
            }
            //------------------------------------------------------------------------------
            //Draw PointsUps
            if (points.active) DrawCircleV(points.position, points.radius, GOLD), DrawTexture(texture3,points.position.x-30,points.position.y-30,WHITE);
            //------------------------------------------------------------------------------
            //Score in the corner
            DrawText(FormatText("%04i", score), 20, 20, 40, GRAY);
            //------------------------------------------------------------------------------
            //Pause Game Message
            if (pause) DrawText("GAME PAUSED", screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, screenHeight/2 - 40, 40, GOLD);
            //------------------------------------------------------------------------------
        }
        else{
            //Name of the Player
            if(!name.active){
                PlayerName();
                
            }
            //------------------------------------------------------------------------------
            else {
            //If player loses Message
            DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
            //------------------------------------------------------------------------------    
            //impressao dos nomes na tela de fim do jogo
            int j=150;
            if(name.p1 || name.p2 || name.p3){
                for(int i = 0; i < 3; i++){
                    DrawText(FormatText("%c", name.jog1[i]), j, 50 , 20, LIGHTGRAY);
                    DrawText(FormatText("%c", name.jog2[i]), j, 70 , 20, LIGHTGRAY);
                    DrawText(FormatText("%c", name.jog3[i]), j, 90 , 20, LIGHTGRAY);
                    j+=15;
                }
            }
            //------------------------------------------------------------------------------
            //tabela de pontos final do jogo
            DrawText(FormatText(" %04i", hiscore), 190, 50, 20,  LIGHTGRAY);
            DrawText(FormatText(" %04i", hiScore1), 190, 70, 20, LIGHTGRAY);
            DrawText(FormatText(" %04i", hiScore2), 190, 90, 20, LIGHTGRAY);
            //------------------------------------------------------------------------------
            //Caso pontuacao da partida for maior que o melhor dos 3
            if (victory) DrawText("NEW HI-SCORE", 70 , screenHeight/2, 40, GOLD);
            //------------------------------------------------------------------------------

            cont = 0; //zera o contador dos espacos da string
            }
        }
        
        
            
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame) recursividade
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}