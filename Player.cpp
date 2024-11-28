#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)

{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    

    playerPos.pos = new Pos;
   
    playerPos.pos ->x = mainGameMechsRef ->getBoardSizeX()/2;
    playerPos.pos ->y = mainGameMechsRef ->getBoardSizeY()/2;
    playerPos.symbol = '*';
    

}


Player::~Player()
{
    // delete any heap members here
    delete playerPos.pos;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic   
    
   
     if(input !=0)  // if not null character
    {
        switch(input)
        {                     
            case 'w':
                if (myDir == STOP ||myDir == LEFT || myDir == RIGHT) {
                    myDir = UP;
                }
                break;
            
            case 'a':
                 if (myDir == STOP ||myDir == UP || myDir == DOWN) {
                    myDir = LEFT;
                }
                break;

            case 's':
                if (myDir == STOP ||myDir == LEFT || myDir == RIGHT) {
                    myDir = DOWN;
                }
                break;
            case 'd':
                if (myDir == STOP ||myDir == UP || myDir == DOWN) {
                    myDir = RIGHT;
                }
                break;
            default:
                break;
                }
               mainGameMechsRef->setInput(0);
                }       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    int boardSizeX  = mainGameMechsRef ->getBoardSizeX();
    int boardSizeY = mainGameMechsRef ->getBoardSizeY();

    
        switch(myDir){
            case UP:
                if(playerPos.pos->y>1){
                    playerPos.pos->y--;
                }
                else{
                    playerPos.pos->y=boardSizeY -2;
                }
                break;

            case DOWN:
                if(playerPos.pos->y<boardSizeY -2){
                    playerPos.pos->y++;
                }
                else{
                    playerPos.pos->y=1;
                }
                break;

            case LEFT:
                if(playerPos.pos->x>1){
                    playerPos.pos->x--;
                }
                else{
                    playerPos.pos->x=boardSizeX-2;
                }
                break;

            case RIGHT:
                if(playerPos.pos->x<boardSizeX -2){
                    playerPos.pos->x++;
                }
                else{
                    playerPos.pos->x=1;
                }
                break;

         case STOP:

            default:
            break;
    }
}

// More methods to be added