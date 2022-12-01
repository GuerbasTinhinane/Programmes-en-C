#include <stdio.h>
#include <stdlib.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int PGCDiterative(int a, int b){
	int  t,q,r;
	if (b > a){
		t = b; 
		b = a; 
		a = t;
	}  
	if ((a!=b) && (b==0)) return a;
	while (b != 0){
		a = b;
		b = r;
		q = a/b;
        r = a - q*b;
	}
	return b;
}

int PGCDrecursive(int a, int b){
	if (a == b){
		return 0;
	}
	else{
		if (a>b)
		  return PGCDrecursive(a-b, b);
	    else
	      return PGCDrecursive(a, b-a);
	}
}


int main() {
	
	int choix, n1, n2, pgcd;
    printf("\n Donner deux nombres a et b dont vous voulez calculer le pgcd:");
    printf("\n a =\t");
    scanf("%d",&n1);
    printf("\n b =\t");
    scanf("%d",&n2);
    printf("\n Choisissez votre chiffre:\n1 -> Pour executer lalgorithme iteratif.\n2 2-> Pour executer lalgorithme recursif.\n");
    printf("\nMon choix est:\t");
    scanf("%d",&choix);
    switch(choix){
    case 1:
    	 pgcd = PGCDiterative(n1, n2); 
        break;
    case 2:
    	 pgcd = PGCDrecursive(n1, n2);
    	break;
    }
    printf (" ************* Le PGCD est: %d", pgcd);
	return 0;
}
