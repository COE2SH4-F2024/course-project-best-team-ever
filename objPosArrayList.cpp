#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.



// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{ 
    arrayCapacity = ARRAY_MAX_CAP; 
    aList = new objPos[arrayCapacity]; 
    sizeList = 0; 
    sizeArray = arrayCapacity;  
    
} 

objPosArrayList::objPosArrayList(const objPosArrayList &other){ 
    arrayCapacity = other.arrayCapacity; 
    sizeArray = other.sizeArray; 
    sizeList = other.sizeList; 

    aList = new objPos[arrayCapacity]; 
    for(int i = 0; i < sizeList; i++){
        aList[i] = other.aList[i]; 
    }

} 

objPosArrayList& objPosArrayList::operator=(const objPosArrayList& other){
    if(this != &other){
        delete[] aList; 

        arrayCapacity = other.arrayCapacity; 
        sizeArray = other.sizeArray; 

        aList = new objPos[arrayCapacity]; 
        for(int i = 0; i < sizeList; i++){
            aList[i] = other.aList[i]; 
        }
    }  

    return *this; 


}

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
        aList[i] = aList[i - 1]; 
    } 

    aList[0] = thisPos; 
    sizeList++; 

    
}

void objPosArrayList::insertTail(objPos thisPos)
{ 
    aList[sizeList++] = thisPos; 
    
}

void objPosArrayList::removeHead()
{ 

    for(int i = 0; i < sizeList - 1; i++){
        aList[i] = aList[i + 1]; 
    } 

    sizeList--; 
    
}

void objPosArrayList::removeTail()
{ 
    

    sizeList--; 
    
}

objPos objPosArrayList::getHeadElement() const
{ 
    
    return aList[0]; 
    
}

objPos objPosArrayList::getTailElement() const
{ 
   
    return aList[sizeList - 1]; 
}

objPos objPosArrayList::getElement(int index) const
{ 
    
    return aList[index]; 
}