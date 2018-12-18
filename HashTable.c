//
//  main.c
//  Project4
//
//  Edited by Boyu Zhang on 2018/11/24.
//  Copyright © 2018 BOYU ZHANG. All rights reserved.
//

#include "HashTable.h"
#include "Tuple.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

// create new hash table
HashTable new_HashTable(int length, int num_attribute){
    HashTable table = (HashTable) malloc(sizeof(HashTable));
    table->table=(Tuple*)calloc(length, sizeof(Tuple));
    table->length=length;
    table->num_attribute=num_attribute;
    for(int i=0; i<length; i++){
        table->table[i] = NULL;
    }
    return table;
}
//connect two string into one
char* concat(const char *s1, const char *s2){

    // +1 for the null-terminator
    char *result = calloc((strlen(s1) + strlen(s2) + 1),sizeof(char));

    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    strcat(result, "\0");
    return result;
}
// copy a new hash table: for memory managment
HashTable HashTable_copyTable(HashTable table1){
    HashTable table2 = new_HashTable(table1->length, table1->num_attribute);
    for(int i=0; i<table1->length; i++){
        if(!isEmpty(table1->table[i])){
            table2->table[i]=copyTuple(table1->table[i]);
            Tuple pointer=table1->table[i];
            while (!isEmpty(pointer->next)) {
                pointer=pointer->next;
                addAtEnd(table2->table[i],pointer);
            }
            
        }
        
    }
    return table2;
}

// IO method to write to file
void writeToFile(HashTable table, char* filename){
    FILE* pFile;
    pFile = fopen(filename, "w");
    fprintf(pFile, "%d\n", table->num_attribute);
    //print attributes
    for(int k = 0; k < table->length; k ++){
        if(!isEmpty(table->table[k])){
            for(int j = 0; j < table->table[k]->num_attribute; j ++){
                fprintf(pFile,"%s ", table->table[k]->attributes[j]);
            }
            break;
        }
    }
    fprintf(pFile,"\n");
    //print tuple
    for(int i=0; i<table->length; i++){
        if(!isEmpty(table->table[i])){
            tuplePrinttofile(table->table[i],pFile);
            Tuple pointer=table->table[i];
            while (!isEmpty(pointer->next)) {
                pointer=pointer->next;
                tuplePrinttofile(pointer,pFile);
            }
            
        }
        
    }
    fclose(pFile);
}

// print the hash table
void printTable(HashTable table){

	for(int k = 0; k < table->length; k ++){
		if(!isEmpty(table->table[k])){
			for(int j = 0; j < table->table[k]->num_attribute; j ++){
				printf("%s ", table->table[k]->attributes[j]);
			}
			break;
		}
	}
	
	printf("\n");

    for(int i=0; i<table->length; i++){
        if(!isEmpty(table->table[i])){
            printTuple(table->table[i]);
            Tuple pointer=table->table[i];
            while (!isEmpty(pointer->next)) {
                pointer = pointer->next;
                printTuple(pointer);
            } 
        }
    }
    printf("\n");
}

// free the hash table
void free_HashTable(HashTable table){
    free(table->table);
    free(table);
}

// the hashing function: hash the key of the tuple and return the index
int hash(HashTable table, char* key){
    int x=0;
    while(*key != '\0'){
        x+=(*key-'0');
        key++;
    }
    return x%table->length;   
}

// Part 1: insert a tuple at the hash table
// if collision happens, chain at the end of the linked list
void insertTuple(Tuple tuple, HashTable table){

    if(contains(tuple, table) == 1){
        return;
    }else{

        int index = hash(table, tuple->key);
        Tuple list = table->table[index];

        // if this position is not occupied
        if (isEmpty(list)) {
            table->table[index] = tuple;

        }else{

            // chaining to the list at bucket
            Tuple pointer = table->table[index];
            while (!isEmpty(pointer->next)) {
                pointer = pointer->next;
            }
            pointer->next = tuple;
        }
    }
}

// Part 1: helper mathod for Insert function
int contains(Tuple tuple, HashTable table){

    int index = hash(table, tuple->key);
    Tuple list = table->table[index];

    if (isEmpty(list)) {
        return 0;
    }else{

        Tuple pointer = table->table[index];
        if(strcmp(pointer->key, tuple->key) == 0){
            return 1;
        }

        while (!isEmpty(pointer->next)) {
            if(strcmp(pointer->key, tuple->key) == 0){
                return 1;
            }
            pointer = pointer->next;
        }
    }
    return 0;
}

// Part1: Lookup by given key function
Tuple lookup_byKey(char* key, HashTable table){
    int index = hash(table, key);
    Tuple list = table->table[index];
    if (isEmpty(list)) {

    	printf("Empty Set!\n");
        return NULL;
        
    }else{

        Tuple pointer = table->table[index];
        if(strcmp(pointer->key, key) == 0){
            return pointer;
        }
        while (!isEmpty(pointer->next)) {
            if(strcmp(pointer->key, key) == 0){
                return pointer;
            }
            pointer = pointer->next;
        }
        return NULL;
    }
}

// Part1: Delete by given key function
HashTable delete_byKey(char* key, HashTable table){
    int index = hash(table, key);
    Tuple list = table->table[index];
    if (list == NULL) {
        return table;

    }else if(isEmpty(list->next)){

        if(strcmp(list->key, key) == 0){
            table->table[index] = NULL;
            free_Tuple(table->table[index]);
            return table;
        }
        return table;

    }else{

        Tuple pointer = table->table[index];
        while (!isEmpty(pointer->next)) {
            if(strcmp(pointer->next->key, key) == 0){
                Tuple temp = pointer->next;
                pointer->next = pointer->next->next;
                free_Tuple(temp);
                return table;
            }
            pointer = pointer->next;
        }
        return table;
    }    
}

// Part1: Delete by given data function
HashTable delete_byData(Tuple tuple, HashTable table){

    for(int i=0; i<table->length; i++){

        Tuple temp = table->table[i];

        if(!isEmpty(table->table[i])){

            Tuple pointer=table->table[i];

            if(isEqual(tuple, temp)){

                delete_byKey(temp->key, table);
                // printf("add\n");
            }
            while (!isEmpty(pointer->next)) {

                pointer = pointer->next;

                if(isEqual(tuple, pointer)){
                    delete_byKey(pointer->key, table);
                }
            }
        } 
    }
    return table;
}

// Part1: Lookup by given data function
Tuple lookup_byData(Tuple tuple, HashTable table){

    Tuple result = NULL;
    for(int i = 0; i < table->length; i++){
        Tuple temp = table->table[i];
        if(!isEmpty(table->table[i])){
            Tuple pointer=table->table[i];
            if(isEqual(tuple, temp)){
                // printf("add\n");
                result = addAtEnd(result, temp);
            }
            while (!isEmpty(pointer->next)) {
                pointer=pointer->next;
                if(isEqual(tuple, pointer)){
                    result=addAtEnd(result, pointer);
                }
            }
            
        }
        
    }
    return result;
}

// Part 2 Question 1
void P2Q1(char* StudentName, char* CourseName, HashTable SNAP, HashTable CSG){

	char** student = (char**)malloc(1 * sizeof(char*));
	student[0] = StudentName;

	// find all the SNAP tuple containing student name
	HashTable t1 = selection(student, SNAP);
	free(student);

	// only need the IDs
	char** ID = (char**)malloc(1 * sizeof(char*));
	ID[0] = "STUDENT_ID";

	// find all the IDs tuple for all the tuples
	HashTable t2 = projection(ID, t1);
	free(ID);

	// for each ID find its grade
	for(int i=0; i < t2->length; i++){

        Tuple temp = t2->table[i];

        // for non-empty tuple in IDs
        if(!isEmpty(t2->table[i])){

            Tuple pointer = t2->table[i];

            // the id string
            char* id = temp->data[0];

            // form a CSG key
            char* CSG_key = concat(CourseName, id);

            // print the result
            printf("Grade: %s\n",lookup_byKey(CSG_key, CSG)->data[2]);

            // for same-name students
            while (!isEmpty(pointer->next)) {
            	pointer = pointer->next;
            	id = pointer->data[0];
            	CSG_key = concat(CourseName, id);
                printf("Grade: %s\n",lookup_byKey(CSG_key, CSG)->data[2]);
            }
        } 
    }
}

// Part 2: Question 2
void P2Q2(char* StudentName, char* Time, char* Day, HashTable SNAP, HashTable CSG, HashTable CDH, HashTable CR){

	char** student = (char**)malloc(1 * sizeof(char*));
	student[0] = StudentName;

	// find all the SNAP tuple containing student name
	HashTable t1 = selection(student, SNAP);
	free(student);

	// only need the IDs
	char** ID = (char**)malloc(1 * sizeof(char*));
	ID[0] = "STUDENT_ID";

	// find all the IDs tuple for all the tuples
	HashTable t2 = projection(ID, t1);
	free(ID);

	// for each ID find all courses taken
	for(int i=0; i < t2->length; i++){

        Tuple temp = t2->table[i];

        // for non-empty ID
        if(!isEmpty(t2->table[i])){

			char** id = (char**)malloc(1 * sizeof(char*));
			id[0] = temp->data[0];

            // find all courses for that that one ID
            HashTable t3 = selection(id, CSG);
            free(id);

            // all courses registered by that one ID
            char** COURSES = (char**)malloc(1 * sizeof(char*));
			COURSES[0] = "COURSE";
            HashTable t4 = projection(COURSES, t3);

            // selection all courses at give D and H
            char** CDH_conditions = (char**)malloc(2 * sizeof(char*));
            CDH_conditions[0] = Time;
            CDH_conditions[1] = Day;

            // all courses in given day and hour
            HashTable t5 = selection(CDH_conditions, CDH);
            free(CDH_conditions);
            // trim to left only courses
            HashTable t6 = projection(COURSES, t5);
            free(COURSES);

            // double loop to match the courses
            for(int m = 0; m < t4->length; m ++){

            	Tuple c4 = t4->table[m];

            	if(!isEmpty(c4)){

            		for(int n = 0; n < t6->length; n ++){

            			Tuple c6 = t6->table[n];

            			if(!isEmpty(c6)){

            				if(strcmp(c6->data[0], c4->data[0]) == 0){
                                 printf("Location: %s\n",lookup_byKey(c6->data[0], CR)->data[1]);
            					break;
            				}

            			}
            		}

            	}
            }
        } 
    }
}

// helper method: another contains method (idk why)
int tuple_contains(char* key, Tuple tuple){
    for(int i = 0; i < tuple->num_attribute; i++){
        if(strcmp(key, tuple->data[i]) == 0){
            return 1;
        }
    }
    return 0;
}

// Part 3: Selection 
// Our method is generic, so for this one function works for all datasets
HashTable selection(char** key, HashTable table){

	// find how many target attributes are there
	int key_len = 0;
	char** temp_key = key;
	for (char* k = *temp_key; k; k = *++temp_key) {
   		key_len ++;
	}

    // the result hash table with selected query conditions 
    HashTable result = new_HashTable(table->length, table->num_attribute);

    // iterate through all buckets
    // match by the first condition
    for(int i = 0; i < table->length; i++){

        // current tuple
        Tuple temp = table->table[i];

        // if the bucket is not empty, see if it contains the first query condition
        if(!isEmpty(temp)){

            // for chainning tuples
            Tuple pointer = table->table[i];

            if(tuple_contains(*key, temp)){
                insertTuple(new_Tuple(temp->data, temp->key, temp->num_attribute, temp->attributes), result);
            }
            
            // move all collision tuples to the new table 
            while (!isEmpty(pointer->next)) {
                pointer = pointer->next;
                if(tuple_contains(*key, pointer)){
                    insertTuple(new_Tuple(pointer->data, pointer->key, pointer->num_attribute, pointer->attributes), result);
                }
            }
        }
    }

    // process to the next condition
    key++;

    // i should have put these into one loop --shuran zhang
    // iterate through all conditions
    while(*key != NULL){

        HashTable tempTable = new_HashTable(result->length, result->num_attribute);

        // iterate new table and match the second condition
        for(int i = 0;i < result->length; i++){

            Tuple temp2 = result->table[i];

            if(!isEmpty(temp2)){

                // for chainning tuples
                Tuple pointer2 = result->table[i];

                if(tuple_contains(*key, temp2)){
                    insertTuple(new_Tuple(temp2->data, temp2->key, temp2->num_attribute, temp2->attributes), tempTable);
                }

                while (!isEmpty(pointer2->next)) {

                    pointer2 = pointer2->next;
                    if(tuple_contains(*key, pointer2)){
                        insertTuple(new_Tuple(pointer2->data, pointer2->key, pointer2->num_attribute, pointer2->attributes), tempTable);
                    }
                }
            }
        }

        // next condition
        key++;

        // TODO: memory management
        result = tempTable;
    }

    return result;
}

// Part 3: helper method
Tuple project_new_tuple(Tuple temp, int att_len, char** target_attributes){

	// new number of attributes
    int new_num = att_len;
    // new attributes
    char** new_att = (char**)malloc((att_len + 1) * sizeof(char*));

	for (int e = 0; e < att_len; e ++) {
		new_att[e] = (char*)malloc(strlen(target_attributes[e]) * sizeof(char));
   		new_att[e] = strcpy(new_att[e], target_attributes[e]);
	}

	// new key
	char* new_key = (char*)malloc(strlen(temp->key) * sizeof(char));
	strcpy(new_key, temp->key);

    // new data
    char** new_data = (char**)malloc(att_len * sizeof(char*));

    // length of original attributes
    int old_att_len = temp->num_attribute;
    // printf("old: %d\n", old_att_len);

	// only copy required attributes
	for(int k = 0; k < old_att_len; k ++){
		for(int n = 0; n < att_len; n ++){

			// found the required attributes
			if(strcmp(temp->attributes[k], target_attributes[n]) == 0){
				new_data[n] = (char*)malloc(strlen(temp->data[k]) * sizeof(char));
				strcpy(new_data[n], temp->data[k]);
			}
		}
	}

	return new_Tuple(new_data, new_key, new_num, new_att);
}

// Part 3: Projection 
// Our method is generic, so for this one function works for all datasets
HashTable projection(char** target_attributes, HashTable hashtable){

	// find how many target attributes are there
	int att_len = 0;
	char** temp_ta3 = target_attributes;
	while(*temp_ta3 != NULL){
        att_len++;
        (temp_ta3)++;
    }
	// printf("att_len: %d\n", att_len);
	
	// the result projection
	HashTable new_table = new_HashTable(hashtable->length, att_len);

	// iterate through all buckets
    for(int i = 0; i < hashtable->length; i++){

        // current tuple
        Tuple temp = hashtable->table[i];

        // not empty tuple
        if(!isEmpty(temp)){  

        	// new tuple to be inserted
        	Tuple new_tuple = project_new_tuple(temp, att_len, target_attributes);
        	// insert to the projection table
        	insertTuple(new_tuple, new_table);

        	// for chainning tuples
            Tuple pointer = hashtable->table[i];
            while (!isEmpty(pointer->next)) {

                pointer = pointer->next;

                // new tuple to be inserted
        		Tuple new_chain = project_new_tuple(pointer, att_len, target_attributes);

        		// insert to the projection table
        		insertTuple(new_chain, new_table);
            }

        }
    }

    return new_table;
}

//helper function to get the attribute of the hashtable from the first non-empty tuple
char** getAtt_HashTable(HashTable table1){
    for(int i=0; i<table1->length; i++){
        if(!isEmpty(table1->table[i])){
            return table1->table[i]->attributes;
        }
    }
    return NULL;
}

Tuple join_new_Tuple(char** data, int num_attribute){
    Tuple this = (Tuple)malloc(sizeof(Tuple));
    this->num_attribute = num_attribute;
    this->data = data;
    return this;
}

HashTable join(HashTable table1, HashTable table2, char* attri1, char* attri2){
    int attIndex1 = -1;
    int attIndex2 = -1;
    char** attributes1 = getAtt_HashTable(table1);
    char** attributes2 = getAtt_HashTable(table2);

    //find the index of the common attribute in each table
    for(int i = 0; i < table1->num_attribute; i++){
        if(strcmp(attri1, attributes1[i]) == 0){
            attIndex1 = i;
            break;
        }
    }
    
    for(int i = 0; i < table2->num_attribute; i++){
        if(strcmp(attri2, attributes2[i]) == 0){
            attIndex2 = i;
            break;
        }
    }
    //add to find the new number of attributes and construct the new attributes string array for the new joined table
    int totalnum_Att = table1 -> num_attribute + table2 -> num_attribute -1;
    char** new_Att = calloc(totalnum_Att, sizeof(char*));
    
    
    //contruct new attributes array
    for(int i=0; i<table1->num_attribute; i++){
        new_Att[i]=attributes1[i];
    }
    int x = table1->num_attribute;
    for(int i=0; i<table2->num_attribute; i++){
        if(i==attIndex2){
            
        }else{
            new_Att[x]=attributes2[i];
            x++;
        }
    }
    //hashtable to store the joined table
    HashTable result = new_HashTable(19, totalnum_Att);
    for(int i=0; i<table1->length; i++){
        if(!isEmpty(table1->table[i])){
            Tuple tuple_Table1 = table1->table[i];
            Tuple pointer = tuple_Table1;
            //build a look up tuple fot table2 
            while(!isEmpty(pointer)){
                char ** keyForTable2 = calloc(table2 -> num_attribute, sizeof(char*));
                for(int j=0; j<table2->num_attribute; j++){
                if(j==attIndex2){
                        keyForTable2[j] = tuple_Table1->data[attIndex1];
                    }else{
                        keyForTable2[j]= "*";
                    }
                    
                }
                
                Tuple tuple_Table2 = lookup_byData(join_new_Tuple(keyForTable2,table2->num_attribute),table2);
                Tuple pointer2 = tuple_Table2;
                while(!isEmpty(pointer2)){
                    char** data = calloc(totalnum_Att, sizeof(char*));
                    //add data from table1
                    for(int z=0; z<table1->num_attribute; z++){
                        data[z] = tuple_Table1->data[z];
                    }
                    
                    
                    int r = table1->num_attribute-1;
                    //add data from table2
                    for(int y=0; y<table2->num_attribute; y++){
                        if(y==attIndex2){
                            
                        }else{
                            //printf("data: %s ", pointer2->data[y]);
                            data[r] = pointer2->data[y];
                        }
                        r++;
                        //printf("\n");
                    }
            
                    //char* finalKey = join_getKey(key_Table1, key_Table2);
                    insertTuple(new_Tuple(data,concat(data[0],data[1]),totalnum_Att,new_Att), result);
                    pointer2=pointer2->next;
                }
                pointer=pointer->next;

            }
        }
    }
    return result;
}

///IO method to read from file
HashTable readFromFile(char* filename){
    FILE* pFile;
    pFile = fopen(filename, "r");
    char inStream[512];
    //read number of attributes
    int num_att = 0;
    fgets(inStream, 512, pFile);
    num_att = atoi(inStream);
    //initialize table
    HashTable readTable = new_HashTable(19, num_att);
    //read the file line by line 
    strcpy(inStream, "");
    char** attributes = calloc(num_att, sizeof(char*));
    for(int i=0; i<num_att; i++){
        attributes[i] = calloc(50, sizeof(char));
    }
    fgets(inStream, 512, pFile);
    char* lineBreak;
    if((lineBreak = strchr(inStream, '\n'))!=NULL){
        *lineBreak = '\0';
    }
    //copy attributes
    strcpy(attributes[0], strtok(inStream, " "));
    for(int i=1; i<num_att; i++){
        strcpy(attributes[i], strtok(NULL, " "));
    }
    strcpy(inStream, "");
    //read tuples
    fgets(inStream, 512, pFile);
    while(!feof(pFile)){
        char** data = calloc(num_att, sizeof(char*));
        for(int i=0; i<num_att; i++){
            data[i] = calloc(50, sizeof(char));
        }

        if(strcmp(inStream,"")!=0){
            char* lineBreak;
            if((lineBreak = strchr(inStream, '\n'))!=NULL){
                *lineBreak = '\0';
            }
            strcpy(data[0], strtok(inStream, ","));
            for(int i=1; i<num_att; i++){
                strcpy(data[i], strtok(NULL, ","));
            }
            char* readKey =strtok(NULL, ","); 
            Tuple temp = new_Tuple(data, readKey, num_att, attributes);
            insertTuple(copyTuple(temp), readTable);


        }
        strcpy(inStream, "");
        fgets(inStream, 512, pFile);

    }
    return readTable;
}