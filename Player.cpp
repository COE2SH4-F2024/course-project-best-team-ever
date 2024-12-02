#include "Player.h"
#include "GameMechs.h"
#include "objPos.h"


Player::Player(GameMechs* thisGMRef)

{
    //Store the reference to the GameMechs object
    mainGameMechsRef = thisGMRef;
    myDir = STOP; //initialize players direction to stop

    //new object position array list to hold the player segments
    playerPosList = new objPosArrayList(); 
   
    //initialize player's starting postion to middle of the board
    int headX = mainGameMechsRef ->getBoardSizeX()/2;
    int headY = mainGameMechsRef ->getBoardSizeY()/2;
    int initialength = 1; //initial length of the snake

    //Creating initial segments of the snake
    for(int i = 0; i < initialength; i++){ 
        objPos segment; 
        segment.pos = new Pos; 
        segment.pos->x = headX - i; 
        segment.pos->y = headY; 
        segment.symbol = '@'; 

        //insert the new segment at the head of the list
        playerPosList-> insertHead(segment);  

    }
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
               mainGameMechsRef->setInput(0); //reset input after processing
                }       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    int boardSizeX  = mainGameMechsRef ->getBoardSizeX(); //Get the board's width
    int boardSizeY = mainGameMechsRef ->getBoardSizeY(); //Get the board's height

    objPos head = playerPosList->getHeadElement(); //Get the current head positon
    objPos newHead = head; //Creating a new head position to update
 
    //Update the new head position based on direction
        switch(myDir){
            case UP:
                if(newHead.pos->y  > 1){
                   newHead.pos->y--; //Move up if not at top border
                }
                else{
                   newHead.pos->y = boardSizeY - 2; //Wrap around to the bottom
                }
                break;

            case DOWN:
                if(newHead.pos->y < boardSizeY -2){
                   newHead.pos->y++; //Move down if not at the bottom border
                }
                else{
                    newHead.pos->y = 1; //Wrap around
                }
                break;

            case LEFT:
                if(newHead.pos->x > 1){
                    newHead.pos->x--; //Move left if not at the left border
                }
                else{
                    newHead.pos->x = boardSizeX-2; //Wrap around
                }
                break;

            case RIGHT:
                if(newHead.pos->x < boardSizeX -2){
                    newHead.pos->x++; //Move right if not at right border
                }
                else{
                    newHead.pos->x = 1; //Wrap around
                }
                break;

         case STOP:

        default:
            break;
    }   

    //Check for collisions with the snake's body
    int snakeLength = playerPosList->getSize(); //Get length of snake
    for (int i=1; i<snakeLength; i++){
        objPos segment = playerPosList->getElement(i);
        //Check if new head position collides with any segment
        if (segment.pos->x  == newHead.pos->x && segment.pos->y  == newHead.pos->y){
            mainGameMechsRef->setLoseFlag(); //Set lose condition if collision occurs
            
        }
    }

    //Get position of the food
    objPos foodPos = mainGameMechsRef->getFoodpos(); 

    //Check if new head position collides with food position
    if(newHead.pos->x == foodPos.pos->x && newHead.pos->y == foodPos.pos->y){ 
        playerPosList->insertHead(newHead); 
        mainGameMechsRef->generateFood(*playerPosList); //Generate new food
        mainGameMechsRef->incrementScore(); //increment the score

    } 
    else{
        //if no food was eaten move the snake normally
        playerPosList->insertHead(newHead); //insert new head
        playerPosList->removeTail(); //remove tail
    }
}


// More methods to be added