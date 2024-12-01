#include <iostream>
#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"

#include "GameMechs.h"


#define WIDTH 30  // x-axis from 0 to 29
#define HEIGHT 15 // y-axis from 0 to 14

//Declare a pointer to Player class
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

    //Create the Player object on the heap
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

            //if there are positions in the player list, generate food
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
        myPlayer->updatePlayerDir(); //update player direction based on input
   }
    
    myPlayer->movePlayer(); //move the player
    gamemechs->clearInput(); // clear the input after processing
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

    //Get the position of the food and place it on the board
    objPos foodPos = gamemechs ->getFoodpos();
    board[foodPos.pos->y][foodPos.pos->x]=foodPos.symbol;

    //Get the player's position and place on board
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

    //Display current score
    int score = gamemechs->getScore();
    MacUILib_printf("Score: %d\n", score);

    //Check for game over conditions
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
    delete gamemechs;
    delete myPlayer;
    MacUILib_uninit();
}
