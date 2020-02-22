#include <stdio.h>
#include "dictionary.h"

void showDictionary(Dictionary* dictionary) {
    printf("Size: %d\nDictionary: ", sizeOfDictionary(dictionary));
    printDictionary(dictionary);
    printf("\n");
}

void main() {
   /* Dictionary* dictionary = initDictionary();
    showDictionary(dictionary);

    putInDictionary(dictionary, 1, 10);
    showDictionary(dictionary);

    putInDictionary(dictionary, 1, 2);
    showDictionary(dictionary);

    removeFromDictionary(dictionary, 1);
    showDictionary(dictionary);

    removeFromDictionary(dictionary, 1);
    showDictionary(dictionary);

    printf("43: %d\n", getFromDictionary(dictionary, 43));
    showDictionary(dictionary);

    destroyDictionary(dictionary);*/

    int keys[] =   {7,-61,43,-12,14,97,0,12};
    int values[] = {10,2,-5,7,-9,10,10,10};
    int size = sizeof(keys) / sizeof(int);

    Dictionary* dictionary = createDictionaryFromArrays(keys, values, size);
    showDictionary(dictionary);

    int value = getFromDictionary(dictionary, 43);
    printf("43: %d\n", value);
    showDictionary(dictionary);

    removeFromDictionary(dictionary, -12);
    removeFromDictionary(dictionary, 43);
    showDictionary(dictionary);

    destroyDictionary(dictionary);
}




//#include <stdio.h>
//#include <assert.h>
//#include "dictionary.h"
//
//void showDictionary(Dictionary* dictionary) {
//    printf("Size: %d\nDictionary: ", sizeOfDictionary(dictionary));
//    printDictionary(dictionary);
//    printf("\n");
//}
//
//void main() {
//    Dictionary* dictionary = initDictionary();
//    showDictionary(dictionary);
//
//    //putInDictionary(dictionary, 0, 0);   EDGE CASE********
//    //putInDictionary(dictionary, 5, 1);
//    ////showDictionary(dictionary);
//    //putInDictionary(dictionary, 8, 1);
//    //putInDictionary(dictionary, 9, 1);
//    //putInDictionary(dictionary, 4, 1);
//    //putInDictionary(dictionary, 3, 1);
//    ////putInDictionary(dictionary, 0, 0);
//    //putInDictionary(dictionary, 7, 1);
//    //putInDictionary(dictionary, 6, 1);
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 0);
//    //showDictionary(dictionary);
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 0);
//    //showDictionary(dictionary);
//    //putInDictionary(dictionary, 11, 5);
//    //putInDictionary(dictionary, 26, 5);
//    //putInDictionary(dictionary, 88, 5);
//    //putInDictionary(dictionary, 18, 5);
//    //putInDictionary(dictionary, 86, 5);
//    //putInDictionary(dictionary, 96, 5);
//    //putInDictionary(dictionary, 79, 5);
//    //putInDictionary(dictionary, 10, 5);
//    //putInDictionary(dictionary, 3, 5);
//    //putInDictionary(dictionary, 5, 5);
//    //putInDictionary(dictionary, 2, 5);
//    //putInDictionary(dictionary, 7, 5);
//    //putInDictionary(dictionary, 19, 5);
//    ////printf("43: %d\n", getFromDictionary(dictionary, 43));
//    ////printf("%d\n", sizeOfDictionary(dictionary));
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 86);
//    //showDictionary(dictionary);
//    //putInDictionary(dictionary, 6, 5);
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 3);
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 4);
//    //showDictionary(dictionary);
//    //removeFromDictionary(dictionary, 5);
//    //showDictionary(dictionary);
//    //
//    //putInDictionary(dictionary, 1, 2);
//    //showDictionary(dictionary);
//
//    //removeFromDictionary(dictionary, 1);
//    //showDictionary(dictionary);
//
//    //removeFromDictionary(dictionary, 1);
//    //showDictionary(dictionary);
//
//    //printf("43: %d\n", getFromDictionary(dictionary, 43));
//    //showDictionary(dictionary);
//
////   destroyDictionary(dictionary);
//   
//    int keys[] = { 7,-61,43,-12,14,97,0,12 };
//    int values[] = { 10,2,-5,7,-9,10,10,12 };
//    int size = sizeof(keys) / sizeof(int);
//
//    dictionary = createDictionaryFromArrays(keys, values, size);
//    showDictionary(dictionary);
//
//    int value = getFromDictionary(dictionary, 43);
//    printf("43: %d\n", value);
//    showDictionary(dictionary);
//
//    removeFromDictionary(dictionary, -12);
//    removeFromDictionary(dictionary, 43);
//    showDictionary(dictionary);
//
//    destroyDictionary(dictionary);
//}


