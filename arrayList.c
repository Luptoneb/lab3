#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);

arrayList * initialize(primitiveType type)
{
   arrayList * a = (arrayList*)malloc(sizeof(arrayList));
   (*a).array = malloc(getSize(type)*4);
   (*a).elementSize = getSize(type);
   (*a).numElements = 0;
   (*a).arraySize = 4;
   (*a).type = type;
   return a;
}

int getSize(primitiveType type)
{
   if(type == charType){
       return sizeof(char);
   }
   else if(type == shortType){
       return sizeof(short);
   }
   return sizeof(int);
}

void addElement(arrayList * arylstP, void * element)
{
   int i;
   if((*arylstP).arraySize == (*arylstP).numElements){
       void * newArr;
       newArr = malloc((*arylstP).elementSize * (((*arylstP).arraySize)*2));
       for(i = 0; i < (((*arylstP).arraySize)*((*arylstP).elementSize)); i++){
         ((char*)newArr)[i] = ((char*)(*arylstP).array)[i];
       }
       free((*arylstP).array);
       (*arylstP).array = newArr;
       (*arylstP).arraySize = ((*arylstP).arraySize)*2;
   }
   if((*arylstP).type == charType){
       ((char*)(*arylstP).array)[(*arylstP).numElements] = (*(char*)element);
   }
   else if((*arylstP).type == shortType){
       ((short*)(*arylstP).array)[(*arylstP).numElements] = (*(short*)element);
   }
   else if((*arylstP).type == intType){
       ((int*)(*arylstP).array)[(*arylstP).numElements] = (*(int*)element);
   }
   (*arylstP).numElements++;
}


void removeElement(arrayList * arylstP, int index)
{
    int i;
    for(i = index; i < (*arylstP).numElements; i++){
        if((*arylstP).type == charType){
            ((char*)(*arylstP).array)[i] = ((char*)(*arylstP).array)[i+1];
        }
        else if((*arylstP).type == shortType){
            ((short*)(*arylstP).array)[i] = ((short*)(*arylstP).array)[i+1];
        }
        else if((*arylstP).type == intType){
            ((int*)(*arylstP).array)[i] = ((int*)(*arylstP).array)[i+1];
        }
    }
    (*arylstP).numElements--;
}
      

void printArray(arrayList * arylstP)
{
   int i;
   printf("array size: %d, num elements: %d contents: ", 
          arylstP->arraySize, arylstP->numElements);
   for (i = 0; i < arylstP->numElements; i++)
   {
      if (arylstP->type == charType)
         //fill in the missing code that gets the element and &s it with 0xff
         printf("%02x ",((char*)(*arylstP).array)[i] & 0xff);
      else if (arylstP->type == shortType)
         //fill in the missing code that gets the element and &s it with 0xffff
         printf("%04x ",(unsigned short)((short*)(*arylstP).array)[i] & 0xffff);
      else if (arylstP->type == intType)
         //fill in the missing code that gets the element and &s it with 0xffffffff
         printf("%08x ",(unsigned int)((int*)(*arylstP).array)[i] & 0xffffffff);
   }
   printf("\n");
}

