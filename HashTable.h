//
//  main.c
//  Project4
//
//  Edited by Boyu Zhang on 2018/11/24.
//  Copyright © 2018 BOYU ZHANG. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h
#include "Tuple.h"

typedef struct HashTable* HashTable;
struct HashTable{
    Tuple* table;
    int length;
    int num_attribute;
};
extern HashTable new_HashTable(int length,int num_attribute);
extern HashTable HashTable_copyTable(HashTable table1);
extern void free_HashTable(HashTable table);
extern int hash(HashTable table, char* key);
extern void insertTuple(Tuple tuple, HashTable table);
extern Tuple lookup_byKey(char* key, HashTable table );
extern HashTable delete_byData(Tuple tuple, HashTable table);
extern HashTable delete_byKey(char* key, HashTable table);
extern int contains(Tuple tuple, HashTable table);
extern void printTable(HashTable table);
extern void writeToFile(HashTable table, char* Filename);
extern Tuple lookup_byData(Tuple tuple, HashTable table);
extern HashTable selection(char** key, HashTable table);
extern int tuple_contains(char* key, Tuple tuple);
extern HashTable projection(char** target_attributes, HashTable hashtable);
extern HashTable HashTable_copyTable(HashTable table1);
extern HashTable join(HashTable table1, HashTable table2, char* attri1, char* attri2);
extern Tuple join_new_Tuple(char** data, int num_attribute);
extern char** getAtt_HashTable(HashTable table1);
extern char* concat(const char *s1, const char *s2);
extern void P2Q1(char* StudentName, char* CourseName, HashTable SNAP, HashTable CSG);
extern void P2Q2(char* StudentName, char* Time, char* Day, HashTable SNAP, HashTable CSG, HashTable CDH, HashTable CR);
#endif /* HashTable_h */
