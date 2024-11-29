#include "GameMechs.h"
#include "MacUILib.h" 
#include "Player.h"



GameMechs::GameMechs() 
{
    input = 0;
    exitFlag=0;
    loseFlag=0;
    score=0;
    boardSizeX=30;
    boardSizeY=15;
    srand(time(0));
}

GameMechs::GameMechs(int boardX, int boardY) 
{
    input = 0;
    exitFlag=0;
    loseFlag=0;
    score=0;
    boardSizeX = boardX;
    boardSizeY=boardY;
    srand(time(0));

}

// do you need a destructor?
GameMechs::~GameMechs()
//at this moment NO
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{

    return loseFlag;

}
    

char GameMechs::getInput() const
{
   return input;      
}

int GameMechs::getScore() const
{
    


    return playerPosList->getSize() - 1;

    
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag =true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
 input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}


// More methods should be added here

void GameMechs::generateFood(const objPosArrayList& playerPosList){
    bool validPos = false;
    int x,y;

    while(!validPos){
        x=1+rand()%(boardSizeX-2);
        y=1+rand()%(boardSizeY-2);

        validPos=true; 

        for(int i = 0; i < playerPosList.getSize(); i++){ 

            objPos snakeSegment = playerPosList.getElement(i);
            if (snakeSegment.pos->x == x && snakeSegment.pos->y == y){
                validPos = false; 
                break; 
            }
        } 

        if(validPos){
            foodPos = objPos(x,y,'*'); 
        }
    

    // if( x!=blockOff.pos->x||y!=blockOff.pos->y){
    //     validPos=true;
    // }
    }

    // foodPos = objPos(x,y,'*');

    // MacUILib_printf("Generated Food Position: (%d, %d)\n", foodPos.pos->x, foodPos.pos->y);
}

objPos GameMechs::getFoodpos() const{
    return foodPos;
}