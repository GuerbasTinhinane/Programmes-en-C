#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.c"
#include "file.c"


int main(){
     //Declaration des deux arbres
     BTree A1 = NULL, A2 = NULL;
     Element s;

     //Creation de l'arbre A1
     addNode(&A1, 3);
     addNode(&A1, 5);
     addNode(&A1, 7);
     addNode(&A1, 89);
     addNode(&A1, 23);
     addNode(&A1, 2);
     addNode(&A1, 32);
     addNode(&A1, 65);
     addNode(&A1, 50);
     addNode(&A1, 10);
     addNode(&A1, 70);
     

     //Creation de l'arbre A2
     addNode(&A2, 3);
     addNode(&A2, 5);
     addNode(&A2, 7);
     addNode(&A2, 89);
     addNode(&A2, 23);
     addNode(&A2, 2);
     addNode(&A2, 32);
     addNode(&A2, 65);
     addNode(&A2, 50);
     addNode(&A2, 10);
     addNode(&A2, 70);
     //addNode(&A2, 80);

     puts("********VERSION RECURSIVE*********");
     puts("-------------------------------");
     printf("Affichage de l'arbre A1:\n");
     printTree(A1);puts("");
     puts("");
     printf("Affichage de l'arbre A2:\n");
     printTree(A2);puts("");
     puts("-------------------------------");

     // le test de la qst 1
     int result1 = equalBTreesRecu(A1, A2);
     if(result1>0){
          printf("**Les deux arbres sont egaux.\n");
     }else{
          printf("**Les deux arbres sont differents.\n");
     }
     puts("-------------------------------");

     // le test de la qst 2
     int result2 = isSubBTreeRecu(A1, A2);
     if(result2>0){
          printf("**A1 est un sous-arbre de A2.\n");
     }else{
          printf("**A1 n'est pas un sous-arbre de A2.\n");
     }
     puts("-------------------------------");

     // le test de la qst 3
     int result3 = findElemRec(A1, 25);
     if(result3>0){
          printf("**25 appartient a l'arbre A1.\n");
     }else{
          printf("**25 n'appartient pas a l'arbre A1.\n");
     }
     puts("-------------------------------");

     // le test de la qst 4
     s = findMinRec(A2);
     printf("**La valeur minimum de l'arbre A2 est: %d\n",s);
     puts("-------------------------------");

      // le test de la qst 5
       puts("Le parcours en largeur recursif:");
     printLevelOrder(A1);
     puts("\n-------------------------------");

     
     
     
     
    
     puts("\n\n********VERSION ITERATIVE*********");
     puts("-------------------------------");
     // le test de la qst 1
     subBTreesIter(A1,A2);
     puts("-------------------------------");
     // le test de la qst 2
     equalBTreesIter(A1,A2);
     puts("-------------------------------");
     // le test de la qst 3
     findElemIter(A1,25);
     puts("-------------------------------");
     // le test de la qst 4
     findMinIter(A2);
     puts("-------------------------------");
     // le test de la qst 5
     puts("Le parcours en largeur iteratif:");
     ParcoursLargeurIter(A1);
     puts("-------------------------------");
     
   
     
     
  
    
 

     //Vider l'espace memoire occupé par les deux arbres.
     clearTree(&A1);
     clearTree(&A2);
    
	
	
	
	


	return 0;
}
