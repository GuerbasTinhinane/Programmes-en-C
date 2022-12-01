#include <stdio.h>
#include <stdlib.h>

typedef int TypeElement;

typedef struct Element* Pile;
typedef struct Element{ 
    int info;
    Pile suiv;
}CelluleP;


void InitPile (Pile *p)
{
	*p==NULL;
} 


int PileVide (Pile *p)
{
	if (*p == NULL) return 1;
	else return 0;
}

void Empiler (Pile *p, TypeElement x)
{
	Pile nouv;
	nouv = malloc(sizeof(CelluleP));
	nouv->info = x;
	nouv->suiv = *p;
	*p = nouv;
}

void Depiler (Pile *p, TypeElement *x)
{
	Pile temp;
	
	if(PileVide(p) == 0)
	{
	    *x = (*p)->info;
	    temp = *p;
	    *p = temp->suiv;
	    free(temp);
	
	}
	else
	{
		printf("La pile est vide");
	}
}



void AffichePile (Pile *p, int taille)
{  
    int i;
    TypeElement x;  
	Pile p2;
	InitPile (&p2);
	printf("Voici la pile \n");
	for(i=0; i<taille; i++)
	{
		Depiler (&(*p), &x);
		printf("X = %d\n", x);
		Empiler (&p2, x);
	    
	}

	
}


int main() 
{
	Pile p; TypeElement x; int i, N;
	InitPile(&p);
	
	printf("Donner le nombre d'elements de la pile \n");
	scanf("%d", &N);
	for (i=0; i<N; i++)
	{
		printf("Donner %deme element \t", i);
		scanf("%d", &x);
		Empiler (&p, x);
	}
	
	printf("\n");
    AffichePile (&p, N);
	
	
	return 0;
}











