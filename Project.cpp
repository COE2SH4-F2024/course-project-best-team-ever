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

// Global variables
objPos itemBin[3];      // Array to hold items
const char excludedChars[] = {'#'}; // Excluded characters for random generation

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


    objPos playerPos = myPlayer -> getPlayerPos();
    gamemechs->generateFood(playerPos);



     // Generate random items with unique positions
    // for (int i = 0; i < 3; i++) {
    //     char randomChar;
    //     int valid = 0;

    //     // Generate a valid random character
    //     while (!valid) {
    //         randomChar = static_cast<char>(33 + rand() % (126 - 33 + 1));
    //         bool excluded = false;
    //         for (char ch : excludedChars) {
    //             if (randomChar == ch) {
    //                 excluded = true;
    //                 break;
    //             }
    //         }
    //         if (!excluded) {
    //             valid = 1;
    //         }
    //     }

    //     int x, y;
    //     bool uniquePos = false;

    //     // Generate a unique position for each item
    //     while (!uniquePos) {
    //         x = 1 + rand() % (WIDTH - 2);  // Avoid borders
    //         y = 1 + rand() % (HEIGHT - 2);

    //         uniquePos = true;

    //         // Check for overlap with other items
    //         for (int j = 0; j < i; j++) {
    //             if (itemBin[j].pos->x == x && itemBin[j].pos->y == y) {
    //                 uniquePos = false;
    //                 break;
    //             }
    //         }
    //     }

    //     // Assign the item to the bin
    //     itemBin[i] = objPos(x, y, randomChar);
    // }

}

void GetInput(void)
{
  //if (MacUILib_hasChar())
    //gamemechs->setInput(MacUILib_getChar());
if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        gamemechs->setInput(input);

        // Debug key to regenerate food
        if (input == 'F') { 
            objPos playerPos = myPlayer->getPlayerPos();
            gamemechs->generateFood(playerPos);

}}}

void RunLogic(void)
{
  
    // if (input!=0){
    //     switch(input)
    //     {
    //         case ' ':
    //             gamemechs->setExitTrue();
    //             break;

         
    //         case 'l': // Debug key to trigger lose flag
    //             gamemechs->setLoseFlag();
    //             cout << "[DEBUG] Lose flag triggered!" << endl;
    //             break;

    //         default:
    //             myPlayer->updatePlayerDir();
    //            break;

        //}
    //}
   if (gamemechs->getInput()!=0){
        if(gamemechs->getInput()== ' ')
            gamemechs->setExitTrue();
        myPlayer->updatePlayerDir();
   }
    
    //myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    gamemechs->incrementScore();
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

 // Place items on the board
    // for (int i = 0; i < 3; i++) {
    //     board[itemBin[i].pos->y][itemBin[i].pos->x] = itemBin[i].getSymbol();
    // }

    objPos playerPos = myPlayer->getPlayerPos(); 
    board[playerPos.pos->y][playerPos.pos->x] = playerPos.symbol;

    // Print game board
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            MacUILib_printf("%c", board[y][x]);
        }
        MacUILib_printf("\n");
        
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
