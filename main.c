//
//  main.c
//  Project4
//
//  Edited by Boyu Zhang on 2018/11/24.
//  Copyright © 2018 BOYU ZHANG. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.c"
#include "Tuple.c"

// Test main method
int main(int argc, const char * argv[]) {
    
    printf("\n");
    HashTable SNAP = new_HashTable(109, 4);

    // SNAP tuple attributes
    char* SNAP_att[4] = {"STUDENT_ID", "NAME", "ADDRESS", "PHONE"};

    // SNAP dataset: StudentId-Name-Address-Phone
    char* SNAP1[4]={"12345","C. Brown","12 Apple St.","555-1234"};
    char* SNAP2[4]={"67890","L. Van Pelt","34 Pear Ave.","555-5678"};
    char* SNAP3[4]={"22222","P. Patty","56 Grape Blvd.","555-9999"};

    // SNAP tuples <data, key, number of attributes, attributes>
    Tuple snap1 = new_Tuple(SNAP1, SNAP1[0], 4, SNAP_att);
    Tuple snap2 = new_Tuple(SNAP2, SNAP2[0], 4, SNAP_att);
    Tuple snap3 = new_Tuple(SNAP3, SNAP3[0], 4, SNAP_att);

    // insert to relation
    insertTuple(snap1, SNAP);
    insertTuple(snap2, SNAP);
    insertTuple(snap3, SNAP);  

    // test result of SNAP selection
    printf("SNAP selection test on <P. Patty, 22222>: \n");

    // must be 5 becuase there are total 4 attributes
    char** NAME = (char**)malloc(5 * sizeof(char*));
    NAME[0] = "P. Patty";
    NAME[1] = "22222";
    HashTable CBROWN = selection(NAME,SNAP);
    printTable(CBROWN);
    
    // projection test
    printf("SNAP projection test on <STUDENT_ID, NAME>:\n");

    // must be 5 becuase there are total 4 attributes
    char** projection_SNAP = (char**)malloc(5 * sizeof(char*));
    projection_SNAP[0] = "STUDENT_ID";
    projection_SNAP[1] = "NAME";
    // projection_SNAP[2] = "PHONE";
    // projection_SNAP[3] = "ADDRESS";

    HashTable project_test_SNAP = projection(projection_SNAP, SNAP);
    printTable(project_test_SNAP);

    // write the SNAP to file
    writeToFile(SNAP, "output2");
	
    // ------------------------------------------------------------------------------------------------------
    // CSG test
    HashTable CSG = new_HashTable(1009,3);

    // CSG dataset
    char* CSG1[3] = {"CS101","12345","A"};
    char* CSG2[3] = {"CS101","67890","B"};
    char* CSG3[3] = {"EE200","12345","C"};
    char* CSG4[3] = {"EE200","22222","B+"};
    char* CSG5[3] = {"CS101","33333","A-"};
    char* CSG6[3] = {"PH100","67890","C+"};
    char* CSG7[3] = {"CS101","12345","*"};

    // CSG tuple attributes
    char* CSG_att[3] = {"COURSE","STUDENT_ID","GRADE"};

    // CSG tuples <data, key, number of attributes>
    Tuple csg1 = new_Tuple(CSG1, concat(CSG1[0], CSG1[1]), 3, CSG_att);
    Tuple csg2 = new_Tuple(CSG2, concat(CSG2[0], CSG2[1]), 3, CSG_att);
    Tuple csg3 = new_Tuple(CSG3, concat(CSG3[0], CSG3[1]), 3, CSG_att);
    Tuple csg4 = new_Tuple(CSG4, concat(CSG4[0], CSG4[1]), 3, CSG_att);
    Tuple csg5 = new_Tuple(CSG5, concat(CSG5[0], CSG5[1]), 3, CSG_att);
    Tuple csg6 = new_Tuple(CSG6, concat(CSG6[0], CSG6[1]), 3, CSG_att);
    Tuple csg7 = new_Tuple(CSG7, concat(CSG7[0], CSG7[1]), 3, CSG_att);

    // insert to the relation
    insertTuple(csg1, CSG);
    insertTuple(csg2, CSG);
    insertTuple(csg3, CSG);
    insertTuple(csg4, CSG);
    insertTuple(csg5, CSG);
    insertTuple(csg6, CSG);

    // test lookup function
    printf("%s\n", "Lookup by Data test for CSG on <CS101, 12345, *> from Example 8.2 on FOCS:");
    Tuple lookup_test = lookup_byData(csg7, CSG);
    while(!isEmpty(lookup_test)){
    	printf("%s\n",lookup_test->data[2]);
        lookup_test = lookup_test->next;
    }
    printf("\n");

    // test result of CSG selection
    printf("CSG selection test on <CS101> from Example 8.12 in FOCS:\n");

    // must be 4 becuase there are total 3 attributes
    char** CSG_selection = (char**)malloc(4 * sizeof(char*));
    CSG_selection[0] = "CS101";

    HashTable CSG_selection_test = selection(CSG_selection, CSG);
    printTable(CSG_selection_test);
    free(CSG_selection);

    // projection test
    printf("CSG projection test on <STUDENT_ID> after selection of <CS101>\n");
    printf("From Example 8.13 in FOCS:\n");

    // must be 4 becuase there are total 3 attributes
    char** projection_CSG = (char**)malloc(4 * sizeof(char*));
    projection_CSG[0] = "STUDENT_ID";

    HashTable project_test_CSG = projection(projection_CSG, CSG_selection_test);
    printTable(project_test_CSG);
    free(projection_CSG);

    // Join CSG SNAP test
    printf("Join test: joined table from SNAP and CSG: \n");
	HashTable CSG_JOIN_SNAP = join(CSG, SNAP, "STUDENT_ID", "STUDENT_ID");
    printTable(CSG_JOIN_SNAP);

    // write the CSG relation to file
    writeToFile(CSG, "output");
	
	// ------------------------------------------------------------------------------------------------------
    // CP tuple attributes
    char* CP_att[2] = {"COURSE","PREREQUISITE"};

    //table for CP
    HashTable CP = new_HashTable(109, 2);
    char* CP1[2]={"CS101","CS100"};
    char* CP2[2]={"EE200","EE005"};
    char* CP3[2]={"EE200","CS100"};
    char* CP4[2]={"CS120","CS101"};
    char* CP5[2]={"CS121","CS120"};
    char* CP6[2]={"CS205","CS101"};
    char* CP7[2]={"CS206","CS121"};
    char* CP8[2]={"CS206","CS205"};
    
    Tuple cp1 = new_Tuple(CP1,concat(CP1[0], CP1[1]),2, CP_att);
    Tuple cp2 = new_Tuple(CP2,concat(CP2[0], CP2[1]),2, CP_att);
    Tuple cp3 = new_Tuple(CP3,concat(CP3[0], CP3[1]),2, CP_att);
    Tuple cp4 = new_Tuple(CP4,concat(CP4[0], CP4[1]),2, CP_att);
    Tuple cp5 = new_Tuple(CP5,concat(CP5[0], CP5[1]),2, CP_att);
    Tuple cp6 = new_Tuple(CP6,concat(CP6[0], CP6[1]),2, CP_att);
    Tuple cp7 = new_Tuple(CP7,concat(CP7[0], CP7[1]),2, CP_att);
    Tuple cp8 = new_Tuple(CP8,concat(CP8[0], CP8[1]),2, CP_att);

    insertTuple(cp1,CP);
    insertTuple(cp2,CP);
    insertTuple(cp3,CP);
    insertTuple(cp4,CP);
    insertTuple(cp5,CP);
    insertTuple(cp6,CP);
    insertTuple(cp7,CP);
    insertTuple(cp8,CP);

    printf("%s\n", "Original Table: ");
    printTable(CP);

    // Lookup by key test from Example 8.2
    char* CP_test_key = "CS205CS120";
    printf("%s\n", "Lookup by key test on CP key of <CS206, CS205> from Example 8.2 on FOCS: ");
    Tuple pre_CSC206 = lookup_byKey(CP_test_key, CP);
    while(!isEmpty(pre_CSC206)){
      	printf("The prerequisite of %s is %s\n", pre_CSC206->data[0], pre_CSC206->data[1]);
        pre_CSC206 = pre_CSC206->next;
    }
    printf("\n");

    // insert<(“CS205”, “CS120”), Course-Prerequisite> makes CS120 a prerequisite of CS205.
    char* CP9[2]={"CS205","CS120"};
    Tuple cp9 = new_Tuple(CP9,concat(CP9[0], CP9[1]), 2, CP_att);
    insertTuple(cp9, CP);
    printf("%s\n", "Insert(“CS205”, “CS120”) in CP dataset from Example 8.2 on FOCS: ");
    printTable(CP);

    // insert<(“CS205”, “CS101”), Course-Prerequisite> has no effect on the relation.
    char* CP10[2]={"CS205","CS101"};
    Tuple cp10 = new_Tuple(CP10, concat(CP10[0], CP10[1]), 2, CP_att);
    insertTuple(cp10,CP);
    printf("%s\n", "Insert(“CS205”, “CS101”) in CP dataset from Example 8.2 on FOCS: ");
    printTable(CP);

    // selection test
    printf("CP selection test on <CS206>:\n");
    char** CP_selection = (char**)malloc(3 * sizeof(char*));
    CP_selection[0] = "CS206";

    HashTable CP_selection_test = selection(CP_selection, CP);
    printTable(CP_selection_test);
    free(CP_selection);

    // back to original dataset
    delete_byKey("CS205CS120", CP);
    writeToFile(CP, "output3");

    // ------------------------------------------------------------------------------------------------------
    // CDH tuple attributes
    char* CDH_att[3] = {"COURSE", "DAY", "HOUR"};

    //table for CDH
    HashTable CDH=new_HashTable(109, 3);
    char* CDH1[3]={"CS101","M","9AM"};
    char* CDH2[3]={"CS101","W","9AM"};
    char* CDH3[3]={"CS101","F","9AM"};
    char* CDH4[3]={"EE200","Tu","10AM"};
    char* CDH5[3]={"EE200","W","1PM"};
    char* CDH6[3]={"EE200","Th","10AM"};
    
    Tuple cdh1 = new_Tuple(CDH1,concat(CDH1[0], CDH1[1]), 3, CDH_att);
    Tuple cdh2 = new_Tuple(CDH2,concat(CDH2[0], CDH2[1]), 3, CDH_att);
    Tuple cdh3 = new_Tuple(CDH3,concat(CDH3[0], CDH3[1]), 3, CDH_att);
    Tuple cdh4 = new_Tuple(CDH4,concat(CDH4[0], CDH4[1]), 3, CDH_att);
    Tuple cdh5 = new_Tuple(CDH5,concat(CDH5[0], CDH5[1]), 3, CDH_att);
    Tuple cdh6 = new_Tuple(CDH6,concat(CDH6[0], CDH6[1]), 3, CDH_att);
    
    insertTuple(cdh1,CDH);
    insertTuple(cdh2,CDH);
    insertTuple(cdh3,CDH);
    insertTuple(cdh4,CDH);
    insertTuple(cdh5,CDH);
    insertTuple(cdh6,CDH);

    // original table
    printf("Original CDH Table: \n");
    printTable(CDH);

    // Lookup by key test
    char* CDH_test_key = "CS101M";
    printf("%s\n", "Lookup by key test on CDH key of <CS101, M>: ");
    Tuple key_test_CDH = lookup_byKey(CDH_test_key, CDH);
    while(!isEmpty(key_test_CDH)){
      	printf("Course: %s, Day: %s, Hour: %s\n", key_test_CDH->data[0], key_test_CDH->data[1], key_test_CDH->data[2]);
        key_test_CDH = key_test_CDH->next;
    }
    printf("\n");

    // delete by key test
    printf("%s\n", "Delete by key test on CDH key of <CS101, M, 9AM>: ");
    HashTable delete_test_CDH = delete_byKey(CDH_test_key, CDH);
    printTable(delete_test_CDH);
	
	// back to the original table    
    insertTuple(cdh1,CDH);

    // original table
    printf("Original CDH Table: \n");
    printTable(CDH);

    // delete by data test
    printf("%s\n", "Delete by data test on CDH data of <EE200, *, *>: ");
    char* CDH_delete_data[] = {"EE200","*","*"};
    Tuple CDH_delete_data_tuple = new_Tuple(CDH_delete_data, concat(CDH_delete_data[0], CDH_delete_data[1]), 3, CDH_att);

    HashTable delete_by_data_CDH = delete_byData(CDH_delete_data_tuple, CDH);
    printTable(delete_by_data_CDH);

	// back to the original table    
    insertTuple(cdh4,CDH);
    insertTuple(cdh5,CDH);
    insertTuple(cdh6,CDH);
    writeToFile(CDH, "output4");

    // ------------------------------------------------------------------------------------------------------
    // CR tuple attributes
    char* CR_att[2] = {"COURSE", "ROOM"};

    //table for CR
    HashTable CR = new_HashTable(109, 2);
    char* CR1[2]={"CS101","Turing Aud"};
    char* CR2[2]={"EE200","25 Ohm Hall"};
    char* CR3[2]={"PH100","Newton Lab"};
    
    Tuple cr1 = new_Tuple(CR1, CR1[0], 2, CR_att);
    Tuple cr2 = new_Tuple(CR2, CR2[0], 2, CR_att);
    Tuple cr3 = new_Tuple(CR3, CR3[0], 2, CR_att);

    insertTuple(cr1,CR);
    insertTuple(cr2,CR);
    insertTuple(cr3,CR);

    printf("Original Table: \n");
    printTable(CR);

    // delete<(“CS101”, *), Course-Room> from Example 8.2 on FOCS
    printf("Delete by data test on CR data of <CS101, *> from Example 8.2 on FOCS: \n");
    char* CR4[3]={"CS101","*"};
    Tuple cr4 = new_Tuple(CR4, CR4[0], 2, CR_att);
    delete_byData(cr4,CR);
    printTable(CR);

    // back to original table
    insertTuple(cr1,CR);
    writeToFile(CR, "output5");

    // join test for CDH and CR
    printf("Join test: joined table from CDH and CR\n");
    printf("From FOCS Example 8.14: \n");
	HashTable joinTable = join(CDH, CR, "COURSE", "COURSE");
    printTable(joinTable);

    // FOCS Example 8.15
    printf("Complex Example from FOCS Example 8.15\n");
    printf("Join(CDR, CR) on COURSE then Selection(Turing Aud) then Projection(Day, Hour): \n");

    char** projection_day_hour = (char**)malloc(2 * sizeof(char));
    projection_day_hour[0] = "DAY";
    projection_day_hour[1] = "HOUR";

	char** selection_turing = (char**)malloc(1 * sizeof(char));
    selection_turing[0] = "Turing Aud";

    HashTable final_table = projection(projection_day_hour, selection(selection_turing, joinTable));
    printTable(final_table);
    free(projection_day_hour);
    free(selection_turing);
    // ------------------------------------------------------------------------------------------------------

    // recover all relations
 
    // SNAP = readFromFile("output2");
    // CSG = readFromFile("output");
    // CP = readFromFile("output3");
    // CDH = readFromFile("output4");
    // CR = readFromFile("output5");
    HashTable SNAP_new = readFromFile("output2");
    HashTable CSG_new = readFromFile("output");
    HashTable CDH_new = readFromFile("output4");
    HashTable CR_new = readFromFile("output5");
    

    // Part 2: Question 1 RELP
    printf("Part 2 Question 1 RELP: “What grade did StudentName get in CourseName?”\n");
    while(1){

    	printf("Please enter Student Name first (enter 'QUIT' to quit): ");
    	char StudentName[50];
    	scanf("%[^\n]%*c", StudentName);
    	if(strcmp("QUIT", StudentName) == 0){
    		break;
    	}

    	printf("Please enter Course Name: ");
    	char CourseName[50];
    	scanf("%[^\n]%*c", CourseName);

    	P2Q1(StudentName, CourseName, SNAP_new, CSG_new);
    }
    printf("\n");

    // Part 2: Question 1 RELP
    printf("Part 2 Question 2 RELP: “Where is StudentName at Time on Day?”\n");
    while(1){

    	printf("Please enter Student Name first (enter 'QUIT' to quit): ");
    	char StudentName[50];
    	scanf("%[^\n]%*c", StudentName);
    	if(strcmp("QUIT", StudentName) == 0){
    		break;
    	}

    	printf("Please enter Time: ");
    	char Time[50];
    	scanf("%[^\n]%*c", Time);

    	printf("Please enter Day: ");
    	char Day[50];
    	scanf("%[^\n]%*c", Day);

    	P2Q2(StudentName, Time, Day, SNAP_new, CSG_new, CDH_new, CR_new);
    }
    
}

