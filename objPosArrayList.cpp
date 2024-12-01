#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.



// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{ 
    arrayCapacity = ARRAY_MAX_CAP; 
    //Dynamically allocate array for objPos
    aList = new objPos[arrayCapacity]; 
    sizeList = 0; 
    //max allocated size for the array
    sizeArray = arrayCapacity;  
    
} 

objPosArrayList::objPosArrayList(const objPosArrayList &other){ 
    arrayCapacity = other.arrayCapacity; //Copy capacity
    sizeArray = other.sizeArray; //Copy allocated size
    sizeList = other.sizeList; //Copy current size

    aList = new objPos[arrayCapacity]; //Allocate new array
    for(int i = 0; i < sizeList; i++){ //Copy elements from the source array
        aList[i] = other.aList[i]; 
    }

} 
//Overloads the assignment operator to support deep copy 
objPosArrayList& objPosArrayList::operator=(const objPosArrayList& other){
    if(this != &other){ //Avoid self-assignment
        delete[] aList; //Free exisitng memory 

        arrayCapacity = other.arrayCapacity; 
        sizeArray = other.sizeArray; 

        aList = new objPos[arrayCapacity]; 
        for(int i = 0; i < sizeList; i++){
            aList[i] = other.aList[i]; 
        }
    }  

    return *this; //Return reference to the current object


}

//Frees the dynamically allocated memory for the array 
objPosArrayList::~objPosArrayList()
{ 
    delete[] aList; 

}

int objPosArrayList::getSize() const
{ 
    return sizeList; 

}

void objPosArrayList::insertHead(objPos thisPos)
{ 
    

    for(int i = sizeList; i > 0; i--){
        aList[i] = aList[i - 1]; //Shift the elements to the right
    } 

    aList[0] = thisPos; //Insert a new element at the head
    sizeList++; //Increase the size of the list 

    
}

void objPosArrayList::insertTail(objPos thisPos)
{ 
    aList[sizeList++] = thisPos; //End element at the end of the list and increase the size
    
}

void objPosArrayList::removeHead()
{ 

    for(int i = 0; i < sizeList - 1; i++){
        aList[i] = aList[i + 1]; //Shift elements to the left
    } 

    sizeList--; 
    
}

void objPosArrayList::removeTail()
{ 
    

    sizeList--; //Simply decrease the size of the list, no shifting 
    
}

objPos objPosArrayList::getHeadElement() const
{ 
    //Return the first element 
    return aList[0]; 
    
}

objPos objPosArrayList::getTailElement() const
{ 
   //Return the last element 
    return aList[sizeList - 1]; 
}

objPos objPosArrayList::getElement(int index) const
{ 
    //Return the element at the specified index 
    return aList[index]; 
}