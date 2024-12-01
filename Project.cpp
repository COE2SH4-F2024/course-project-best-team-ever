#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"

#include "GameMechs.h"


#define WIDTH 20  // x-axis from 0 to 19
#define HEIGHT 10 // y-axis from 0 to 10

//GameMechs* gamemechs = new GameMechs;
Player *myPlayer;

//Declare a global pointer to the GameMechs class
GameMechs* gamemechs;

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!gamemechs->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();

    }
    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //Create the GameMechs object on the heap
    gamemechs = new GameMechs(WIDTH, HEIGHT); 

    myPlayer = new Player(gamemechs);

    objPos playerPos = myPlayer -> getPlayerPos() -> getElement(0);
    gamemechs->generateFood(*(myPlayer->getPlayerPos()));

}

void GetInput(void)
{

if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        gamemechs->setInput(input);

        // Debug key to regenerate food
        if (input == 'F') { 
            objPosArrayList* playerPosList = myPlayer->getPlayerPos(); 

            if(playerPosList->sizeList> 0){
                objPos playerPos = playerPosList->getElement(0); 
                gamemechs->generateFood(*(myPlayer->getPlayerPos()));
            }
            

        }
    }
}

void RunLogic(void)
{
  
   if (gamemechs->getInput()!=0){
        if(gamemechs->getInput()== ' ')
            gamemechs->setExitTrue();
        myPlayer->updatePlayerDir();
   }
    
    myPlayer->movePlayer();
    gamemechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    char board[HEIGHT][WIDTH]={0};

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Set borders to '#', fill the inside with spaces
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                board[y][x] = '#';
            } else {
                board[y][x] = ' ';
            }
        }
    }


    objPos foodPos = gamemechs ->getFoodpos();
    board[foodPos.pos->y][foodPos.pos->x]=foodPos.symbol;

    objPosArrayList* playerPositions = myPlayer->getPlayerPos();  

    for(int i = 0; i < playerPositions->getSize(); i++){
        objPos segment = playerPositions->getElement(i);
        board[segment.pos->y][segment.pos->x] = segment.symbol; 
    }
    

    // Print game board
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            MacUILib_printf("%c", board[y][x]);
        }
        MacUILib_printf("\n");
        
    }
    int score = gamemechs->getScore();
    MacUILib_printf("Score: %d\n", score);
    if (gamemechs->getLoseFlagStatus()){
       MacUILib_printf("GAME OVER.\nYou Lost!");
       gamemechs->setExitTrue();
   }

    else if (gamemechs->getExitFlagStatus()) {
     MacUILib_printf("GAME OVER.\nYou ended the game!");
   }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    

    delete gamemechs;
    delete myPlayer;
    MacUILib_uninit();
}
