#include <stdio.h>
#include <stdlib.h>


typedef int TypeElement;

typedef struct Element* File;
typedef struct Element{ 
    int info;
    File suiv;
}CelluleF;


void InitFile (File *f)
{
	*f==NULL;
} 


int FileVide (File *f)
{
	if (*f == NULL) return 1;
	else return 0;
}


File AdrsLastElement(File f)
{
	File p;
	p = f;
	
	if(p == NULL)
	   return NULL;  
	     
	while (p->suiv != NULL)
	{
		p = p->suiv;
	}
	
	return p;
}


void Enfiler (File *f, TypeElement x)
{
	File nouv, queue;
	nouv = malloc(sizeof(CelluleF));
	nouv->info = x;
	nouv->suiv = NULL;
	
	if(FileVide(f))
	{
		*f = nouv;
	}
	else
	{
		queue = AdrsLastElement(*f);
		queue->suiv = nouv;
	}
}

void Desenfiler (File *f, TypeElement *x)
{
	File temp;
      
	if(FileVide(f) == 0)
	{
		*x = (*f)->info;
    	temp = *f;
    	*f = (*f)->suiv;
    	free(temp);
	}
	else
	{
		printf("La file est vide...\n");
	}
	
}


void AfficheFile (File *f, int taille)
{   
    int i;
    TypeElement x;  
	File f2;
	InitFile (&f2);
	printf ("Voici la file: \n");
	for(i=0; i<taille; i++)
	{
		Desenfiler (&(*f), &x);
		printf("X = %d\n", x);
		Enfiler (&f2, x);
	    
	}
	


	
}


int main() 
{
	File f; TypeElement x; int i, N;
	InitFile(&f);
	
	printf ("Donner le nombre d'elements de la file: \n");
	scanf("%d", &N);
	
	for (i=1; i<N+1; i++)
	{
		printf("Donner %deme element \t", i);
		scanf("%d", &x);
		Enfiler (&f, x);
	}
	
	    printf("\n");
		AfficheFile (&f, N);
	
    
	
	
	return 0;

}

















