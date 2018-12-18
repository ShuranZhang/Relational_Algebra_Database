//
//  main.c
//  Project4
//
//  Edited by Boyu Zhang on 2018/11/24.
//  Copyright © 2018 BOYU ZHANG. All rights reserved.
//
#include "stdlib.h"
#include "Tuple.h"
#include "string.h"

// tuple struct: <data, key, number of attributes, attributes>
Tuple new_Tuple(char** data, char* key, int num_attribute, char** attributes){
    Tuple this = (Tuple)malloc(sizeof(struct Tuple));
    this->data = data;
    this->key = key;
    this->next = (Tuple)malloc(sizeof(struct Tuple));
    this->num_attribute = num_attribute;
    this->attributes = attributes;
    return this;
    
}

// for memory management: copy a tuple
Tuple copyTuple(Tuple tuple1){
    
    char* temp_key = (char*)malloc(100 * sizeof(char));
    strcpy(temp_key, tuple1->key);
    
    int temp_att = tuple1->num_attribute;

    char** new_data = (char**)malloc(tuple1->num_attribute * sizeof(char*));
    
    for(int i = 0; i < tuple1->num_attribute; i ++){
        new_data[i] = (char*)malloc(100 * sizeof(char));
        strcpy(new_data[i], tuple1->data[i]);
    }

    char** new_att = (char**)malloc(tuple1->num_attribute * sizeof(char*));
    
    for(int i = 0; i < tuple1->num_attribute; i ++){
        new_att[i] = (char*)malloc(100 * sizeof(char));
        strcpy(new_att[i], tuple1->attributes[i]);
    }

    Tuple tuple2 = new_Tuple(new_data, temp_key, temp_att, new_att);
    return tuple2;
}

void tuplePrinttofile(Tuple tuple,FILE* pFile){

    for (int i=0; i<tuple->num_attribute; i++){
        fprintf(pFile, "%s,",tuple->data[i]);
    }
    fprintf(pFile, "%s,",tuple->key);
    fprintf(pFile,"\n");
}

void printTuple(Tuple tuple){
    for (int i=0; i<tuple->num_attribute; i++){
        printf("%s\t",tuple->data[i]);
    }
    printf("\n");
}

void free_Tuple(Tuple tuple){
    // free(tuple->data);
    free(tuple);
}

// test if a tuple is empty
int isEmpty(Tuple tuple){
    if(tuple == NULL){
        return 1;
    }else if(tuple->data==NULL){
        return 1;
    }else{

        if(*(tuple->data)==NULL){
            return 1;
        }

        for(int i = 0; i < tuple -> num_attribute; i++){
            if(strcmp(tuple->data[i], "") != 0){
                return 0;
            }
        }
    }
    return 1;
}

int strEqual(char* s1, char*s2){
    if(strlen(s1)!=strlen(s2)){
        return 0;
    }else{
        while(*s1!='\0'){
            if(*s1!=*s2){
                return 0;
            }
            s1++;
            s2++;
        }
    }
    return 1;
}
int isEqual(Tuple tuple1, Tuple tuple2){
    if(tuple1->num_attribute!=tuple2->num_attribute){
        return 0;
    }else{
        for(int i=0;i<(tuple1->num_attribute);i++){
            if((strcmp(tuple1->data[i], "*")!=0&&strcmp(tuple2->data[i], "*")!=0&&strcmp(tuple1->data[i], tuple2->data[i])!=0)){
                
                return 0;
            }
        }
    }
    return 1;
}

Tuple addAtEnd(Tuple tuple1,Tuple tuple2){
    if(isEmpty(tuple1)){
        tuple1=copyTuple(tuple2);
    }else{
        if(isEmpty(tuple1->next)){
            tuple1->next=copyTuple(tuple2);
        }else{
        Tuple pointer=tuple1;
        while(!isEmpty(pointer->next)){
            pointer=pointer->next;
        }
            pointer->next=copyTuple(tuple2);
        }
    }
    return tuple1;
}

