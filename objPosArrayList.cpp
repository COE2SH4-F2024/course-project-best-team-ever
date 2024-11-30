#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

#include "objPosArrayList.h" 
#include <iostream>

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
    if(sizeList >= sizeArray){ 
        throw std::overflow_error("[ERROR]: list is full, cannot insert"); 
        
    } 

    for(int i = sizeList; i > 0; i--){
        aList[i] = aList[i - 1]; 
    } 

    aList[0] = thisPos; 
    sizeList++; 

    
}

void objPosArrayList::insertTail(objPos thisPos)
{ 
    if(sizeList >= sizeArray){
        throw std::overflow_error("[ERROR]: list is full, cannot insert");  
        
    }  
    aList[sizeList++] = thisPos; 
    
}

void objPosArrayList::removeHead()
{ 
    if(sizeList == 0){
        throw std::underflow_error("[ERROR]: list is empty, no removal allowed"); 
        
    } 

    for(int i = 0; i < sizeList - 1; i++){
        aList[i] = aList[i + 1]; 
    } 

    sizeList--; 
    
}

void objPosArrayList::removeTail()
{ 
    if(sizeList == 0){
        throw std::underflow_error("[ERROR]: list is empty, no removal allowed"); 
        
    } 

    sizeList--; 
    
}

objPos objPosArrayList::getHeadElement() const
{ 
    if(sizeList == 0){
        throw std::out_of_range("[ERROR]: list is empty, no head element available"); 
    }
    return aList[0]; 
    
}

objPos objPosArrayList::getTailElement() const
{ 
    if(sizeList == 0){
        throw std::out_of_range("[ERROR]: list is empty, no tail element available"); 
    }
    return aList[sizeList - 1]; 
}

objPos objPosArrayList::getElement(int index) const
{ 
    // if(index < 0 || index >= sizeList){
    //     throw std::out_of_range("[ERROR]: index is out of range"); 
        
    // }
    return aList[index]; 
}