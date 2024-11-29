#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)

{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    

    playerPosList = new objPosArrayList(); 
   
    int headX = mainGameMechsRef ->getBoardSizeX()/2;
    int headY = mainGameMechsRef ->getBoardSizeY()/2;
    // playerPos.symbol = '*'; 

    int initialength = 7; 

    for(int i = 0; i < initialength; i++){ 
        objPos segment; 
        segment.pos = new Pos; 
        segment.pos->x = headX - i; 
        segment.pos->y = headY; 
        segment.symbol = '*'; 

        
        playerPosList-> insertHead(segment);  

    }

    //playerPosList-> insertHead(objPos(headX, headY, '*')); 
    

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}


objPos Player::getPlayerHeadPos() const
{
    // return the reference to the playerPos array list
    return playerPosList->getHeadElement();
} 

objPosArrayList* Player::getPlayerPos() const{
    return playerPosList; 
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

    objPos head = playerPosList->getHeadElement(); 
    objPos newHead = head; 

    // int newX = currHead.pos->x; 
    // int newY = currHead.pos ->y; 

    
        switch(myDir){
            case UP:
                if(newHead.pos->y  > 1){
                   newHead.pos->y--;
                }
                else{
                   newHead.pos->y = boardSizeY - 2;
                }
                break;

            case DOWN:
                if(newHead.pos->y < boardSizeY -2){
                   newHead.pos->y++;
                }
                else{
                    newHead.pos->y = 1;
                }
                break;

            case LEFT:
                if(newHead.pos->x > 1){
                    newHead.pos->x--;
                }
                else{
                    newHead.pos->x = boardSizeX-2;
                }
                break;

            case RIGHT:
                if(newHead.pos->x < boardSizeX -2){
                    newHead.pos->x++;
                }
                else{
                    newHead.pos->x = 1;
                }
                break;

         case STOP:

        default:
            break;
    } 

    playerPosList->insertHead(newHead); 
    playerPosList->removeTail(); 

    // currHead.pos->x = newX; 
    // currHead.pos->y = newY; 
}

// More methods to be added