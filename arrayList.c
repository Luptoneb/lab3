#include <stdlib.h>
#include <stdio.h>
#include "arrayList.h"

//getSize not accessed outside of this file so declare it to be static
//static essentially makes it private to this file 
static int getSize(primitiveType type);
/*
 * @author Erik Lupton
 * @version 2.2
 *
 * arrayList is a series of function designed to make a polymorphous array easier to use
 * it has 5 variables in a struct called arrayList that is designated by arrayList.h
 */
arrayList * initialize(primitiveType type)
{
   //set variables and designate memory for struct
   arrayList * a = (arrayList*)malloc(sizeof(arrayList));
   (*a).array = malloc(getSize(type)*4);
   (*a).elementSize = getSize(type);
   (*a).numElements = 0;
   (*a).arraySize = 4;
   (*a).type = type;
   return a;
}

/*
 * simple function that returns the size of the elements in the array specified by the type variable
 */
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

/*
 * adds an element to the arrayList.  If the arrayList needs more room, it doubles the current size of the array
 */
void addElement(arrayList * arylstP, void * element)
{
   int i;
   //if there is not enough room in the array
   if((*arylstP).arraySize == (*arylstP).numElements){
       void * newArr;  //make a new array
       newArr = malloc((*arylstP).elementSize * (((*arylstP).arraySize)*2)); //allocate memory
       //move all elements in old array into new array byte by byte
       for(i = 0; i < (((*arylstP).arraySize)*((*arylstP).elementSize)); i++){
         ((char*)newArr)[i] = ((char*)(*arylstP).array)[i];
       }
       free((*arylstP).array);//free old array allocation to prevent memory leakage
       (*arylstP).array = newArr;//set pointer in arrayList to new array
       (*arylstP).arraySize = ((*arylstP).arraySize)*2;//double size variable
   }
   //add new element to array casting according to type
   if((*arylstP).type == charType){
       ((char*)(*arylstP).array)[(*arylstP).numElements] = (*(char*)element);
   }
   else if((*arylstP).type == shortType){
       ((short*)(*arylstP).array)[(*arylstP).numElements] = (*(short*)element);
   }
   else if((*arylstP).type == intType){
       ((int*)(*arylstP).array)[(*arylstP).numElements] = (*(int*)element);
   }
   (*arylstP).numElements++;//increment number of elements
}

/*
 * remove a singe element from the internal array designated by the index
 */
void removeElement(arrayList * arylstP, int index)
{
    int i;
    //move all elements from index to end left, casting according to type
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
    (*arylstP).numElements--; //decrement count of elements
}
      
/*
 * prints the array out according to type
 */
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

