# Relational_Algebra_Database
CSC 173 PROJECT 4 WRITE-UP
Author: BOYU ZHANG (bzhang25)
Collaborators: SHURAN ZHANG (szhang73), ZIYI YOU (zyou5)

To Build and Run:
   make clean
   make
   ./main

Part 1


1. We implemented the relations (tables) shown in FOCS Figure 8.1 and 8.2 by a hashtable for CSG, SNAP, CP, CDH, and CR datasets in HashTable.c and HashTable.h. Tuple implementations are in Tuple.c and Tuple.h. Primary Storage Structures for Relations are keys, i.e., hashing attributes, for the tables. CSG has the key attribute of "COURSE" + "STUDENT_ID". SNAP has the key attribute of "STUDENT_ID". CP has the key attribute of "COURSE" + "PREREQUISITE". CDH has the key attribute of "COURSE" + "DAY". CR has the key attribute of "COURSE". Extra Credit: our data structures are generalized to represent arbitrary databases consisting of arbitrary relations.


1. We implemented the basic single-relation insert (insertTuple), delete, and lookup operations as functions. For delete and lookup operation, we provided two implementations for each: lookup_byKey, lookup_byData, delete_byKey, and delete_byData. They are in HashTable.c. Our functions support leaving some attributes unspecified for delete and lookup (denoted with “*”). Extra Credit: our functions are generalized and support operations on all datasets aforementioned. One function for all.


1. Our main method in main.c populates all the datasets aforementioned by the insert method in the order: SNAP, CSG, CP, CDH, CR. Along with other function demos and informative output. (For demo screenshots, please see README.pdf).


1. We implemented functions for saving your database to one or more files, and loading
from the same. They are called readFromFile and writeToFile in HashTable.c. Demos are included in main.c. The first row in each output text file prints the number of attributes, the second prints  all the attributes names in order, and the following rows print the tuples line by line followed by their keys (the relational table’s last column in each output text file are the keys for the corresponding tuple not the part of the actual data).


Part 2


   1. We implemented a function called P2Q1 to answer the query “What grade did StudentName get in Course-Name?” as described in Section 8.6 “Navigation Among Relations.” We provided REPL for the users to test this function in the last part of the demos in main.c. The users need to enter student name first and course name second.


   1. We implemented a function called P2Q2 to answer the query “Where is StudentName at Time on Day?” (assuming they are in some course). We provided REPL for the users to test this function in the last part of the demos main.c. The users need to enter student name first, time second, and day third.


Part 3


   1. We implemented the Relational Algebra operations as described in Section 8.8 as necessary to do the operations on the “registrar” database described in Examples
8.12 (Selection), 8.13 (Projection), 8.14 (Join), and 8.15 (all three). They are called selection, projection, and join, respectively, in HashTable.c. Demos on Examples
8.12 (Selection), 8.13 (Projection), 8.14 (Join), and 8.15 (all three) are all included in the main method, and it will run automatically. We also provided extra examples to demo these functions: SNAP selection test on <P. Patty, 22222>, SNAP projection test on <STUDENT_ID, NAME>, CSG projection test on <STUDENT_ID> after selection of <CS101>, join test on table from SNAP and CSG, etc. Extra Credit: our functions are generalized and support operations on all datasets aforementioned. One function for all.
