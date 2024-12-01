#include "GameMechs.h"
#include "MacUILib.h" 
#include "Player.h"



GameMechs::GameMechs() 
{
    input = 0;
    exitFlag=0;
    loseFlag=0;
    score=0;
    //Default board width
    boardSizeX=30; 
    //Default board height 
    boardSizeY=15; 
    //seed randmon number generator to ensure same number isn't produced twice
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
    return score;
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
    bool validPos = false; //Flag used to check if position is valid
    int x,y;

    while(!validPos){ 
        //Randomly generating coordinates within the boarder 
        x=1+rand()%(boardSizeX-2);
        y=1+rand()%(boardSizeY-2);

        validPos=true;  //Assume generated position is valid

        for(int i = 0; i < playerPosList.getSize(); i++){ 

            objPos snakeSegment = playerPosList.getElement(i);
            if (snakeSegment.pos->x == x && snakeSegment.pos->y == y){
                //If player's position is already at the generated coordinates,
                //then invalid coordinates
                validPos = false; 
                break; 
            }
        } 

        if(validPos){ 
            //If coordinates remain valid assigned food position to those coordinates
            foodPos = objPos(x,y,'*'); 
        }
    }
}

objPos GameMechs::getFoodpos() const{
    return foodPos;
}