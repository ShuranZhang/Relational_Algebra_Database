//
//  main.c
//  Project4
//
//  Edited by Boyu Zhang on 2018/11/24.
//  Copyright © 2018 BOYU ZHANG. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h

#include <stdio.h>
typedef struct Tuple *Tuple;
struct Tuple {
    char** data;
    int num_attribute;
    char* key;
    Tuple next;
    char** attributes;
};
extern Tuple new_Tuple(char** data, char*key, int num_attribute, char** attributes);
extern void free_Tuple(Tuple tuple);
extern int isEqual(Tuple tuple1,Tuple tuple2);
extern void printTuple(Tuple tuple);
extern void tuplePrinttofile(Tuple tuple,FILE* pFile);
extern int isEmpty(Tuple tuple);
extern int strEqual(char* s1,char* s2);
extern Tuple addAtEnd(Tuple tuple1, Tuple tuple2);
extern Tuple copyTuple(Tuple tuple1);
#endif /* Tuple_h */
