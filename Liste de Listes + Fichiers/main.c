#include <stdio.h>
#include <stdlib.h>

//Reconstruire la structure en mémoire.
//declaration avec typedef
typedef    struct    ListeH    *pListH; //on definie une liste H normale.
typedef   struct  ListeH
{
    char     val;
    pListH   svt;
} ListeH;

typedef    struct    ListeV    *pListV; // on definie une liste V qui contient pour elements les tetes des listes H.
typedef   struct  ListeV
{
    pListH   teteH ;
    pListV   svt;
} ListeV;


// ajoute Element en Tete de listeH

pListH    ajoutEnTeteH(pListH L, char V) // on cree une fonction qui ajoute en tete de la liste H le premier element.
{
    pListH    p;

    p = malloc(sizeof(ListeH));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->val = V;
    p->svt = L;

    return p;
}


// Ajoute Element apres prcd listeH

pListH    ajoutApresH(pListH prcd, char V) // on cree une fonction qui ajoute apres l'element precedent un nouvel element.
{
    pListH    p;

    p = malloc(sizeof(ListeH));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->val = V;
    p->svt = prcd->svt;
    prcd->svt = p;

    return p;
}

//creation de la liste fifo horizontale de caracteres 

pListH     CreerListH(int iL) // on cree les listes H sous forme fifo car on veut que les elements soit dans le meme ordre etabli par l'utilisateur.
{
    pListH    tete, prcd;

    int   i, M;
	char val;

     do
    {
        printf("Donner M nombre d'elements de la %d eme liste...\n", iL);
        scanf("%d", &M);
    } while (M <= 0);

    tete = NULL;
    printf("Donner 1er Charactere ...\n");
    scanf(" %c", &val);
    tete = ajoutEnTeteH(tete, val) ; // on appelle donc la fct ajoutEnTeteH pour ajouter le premier element a la liste H.

    prcd = tete;

    for (i = 2; i <= M; i++)
    {
        printf("Donner %d eme caractere ...\n", i);
        scanf(" %c", &val);
        prcd = ajoutApresH(prcd, val); // puis on appelle la fct ajoutApresH pour ajouter le reste des elements (M-1) fois.
    }

    return tete;
}


void  afficherListeH(pListH L) // on cree une procedure pour afficher la liste H.
{
    printf("Liste de Caracteres:     ");
    while (L != NULL)
    {
        printf("%c->", L->val);
        L = L->svt;
    }
    printf("Null\n");
}



// ajoute Element en Tete de listeV 

pListV    ajoutEnTeteV( pListV L) // de meme que pour la liste H on cree une fct pour ajouter en tete la tete de la premiere liste H.
{
    pListV    p;
    pListH    p1;

    p = malloc(sizeof(ListeV));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->teteH = CreerListH(1);
    p->svt = L;

    return p;
}



// Ajoute Element apres prcd de la listeV

pListV    ajoutApresV( pListV prcd, int i) // on cree une fct pour ajouter apres la tete de la liste H precedente la tete de la liste H suivante.
{
    pListV    p;

    p = malloc(sizeof(ListeV));

    if (p == NULL)
    {
        printf("Erreur Probleme d'allocation Memoire malloc ...\n");
        exit(0);
    }

    p->teteH = CreerListH(i);
    p->svt = prcd->svt;
    prcd->svt = p;

    return p;
}


//creation de la liste fifo verticale

/* (ou N represente le nombre de listes horizontales que l'utilisateur veut creer.)*/

pListV     CreerListV()
{
    pListV    teteV, prcd;
    int   i, N;

    do
    {
    	printf("Donner N nombre de listes horizontales...\n");
        scanf("%d", &N);
    }while (N <= 0);

    teteV = NULL;;

    teteV = ajoutEnTeteV(teteV) ; //on appelle donc la fct ajoutEnTeteV pour ajouter la tete de la premiere liste H a la liste V.

    prcd = teteV;

    for (i = 2; i <= N; i++)
    {
        prcd = ajoutApresV(prcd, i); // puis on appelle la fct ajoutApresV pour ajouter les tetes des listes H restantes (N-1) fois.
    }

    return teteV;
}



void  afficherListeV(pListV L) // on cree une procedure pour afficher la liste V.
{
    printf("Liste Verticale: \n");
    while (L != NULL)
    {
        afficherListeH(L->teteH); // on appelle a chaque fois la procedure afficherListeH pour afficher les listes H comme sur le schema.
        L = L->svt;
    }
    printf("\n\n");
}



//Soient deux listes L1 et L2 de caractères. (deux listes horizontales du schéma)
//écrire une fonction qui vérifie si L1 est une sous liste de L2.

int   listeL1souslisteL2(pListH L1, pListH L2) //on cree une fct booleenne qui va verifier elmt par elmt si tout les elements d'une liste L1 donnee sont presents dans une liste L2 donnee.
{

    pListH     p1, p2;

    int    incluse;
    

    incluse = 1;

    p1 = L1;

   while ((p1 != NULL) && incluse)

   {

      p2 = L2;

      incluse = 0;

      while ((p2 != NULL) && !(incluse))

      {

        if (p2->val == p1->val)

           incluse = 1;

        else

           p2 = p2->svt;

      }

      p1 = p1->svt;

   }

 

   return    incluse;

}

//Ecrire une procédure qui supprime les éléments d’une liste de caractères.

void SupprimeLH(pListV LV, pListH LH) 
{
	pListV TV,TS;
	pListH dup;
	
	if(LV != NULL)
	{
		if(LV->teteH = LH) // si le premier element de LV est la tete de la liste H qu'on veut supprimer.
		{
			while(LH != NULL)
			{
				dup = LH;
				LH  = LH->svt; // on met (le suivant de LH) dans LH pour la suite avant de liberer dup.
				free(dup);
			}
			//on supprime la tete de la liste H de la liste V.
			TV = LV;
			LV = LV->svt;
			free(TV);
			
		}
	   else /* sinon on cherche l'element de la liste V qui contient la tete de la liste H qu'on veut supprimer.*/
	    {
	    	TV = LV;
	    	TS = TV->svt;
	    	
	    	while(TS != NULL)
	    	{
	    		if (TS->teteH = LH) // si l'element de la liste V correspond a LH alors on procede a la supression element par element.
	    		{
	    			while(LH != NULL)
	    			{
	    				dup = LH;
	    				LH  = LH->svt;
	    				free(dup);
					}
					//puis on supprime la tete de la liste H de la liste V.
					TV->svt = TS->svt; 
					free(TS);
					
				}
				else //sinon on passe a l'element de la liste V suivant.
				{
					TV->svt = TS;
					TS     = TS->svt;
				}
			}
	    	
	}	 } 
}



//Copier les informations des listes de caractères restantes, dans un fichier d’enregistrements.

#include <error.h>
#define    FichierIn    "Infos.dat"
#define   Taille    100

typedef struct //on definie un enregistrement "Informations" avec 2 champs la postion et le Nombre d'Elements.

{

    int    position;

    int    NE;

} Informations;




int RTab( Informations T[], pListV LV, pListH LH) // fonction qui 'R'emplie le 'Tab' d'Informations avec la position et le nbr d'Elmts de chaque liste H et qui retoune i(le nombre d'elements du tableau).
{
  pListV TV,TS;
  int nbr, i, pos;
    
   pos = 0;
   i = 0;
   if(LV != NULL)
	{
		if(LV->teteH = LH)
		{
			while(LH != NULL)
			{
				nbr = nbr + 1;
				LH  = LH->svt;
			}
			
			T[i].NE       = nbr;
			pos           = pos + 1;
			T[i].position = pos; //on mets d'abords pos dans le champ postion du tableau avant d'incrementer le i.
			i             = i + 1;
			
			//on passe a la liste H suivante.
			TV->svt = TS; 
			TS      = TS->svt;
        }
    }  
	

	
	return i;
}
	    




int creerFichierBinInfos( Informations T[], char nomFichier[], pListV LV, pListH LH) //on cree une fct qui cree le fichier binaire qui va contenir le tableau d'Informations.

{

     FILE *pFile;

     int j, i;


     pFile = fopen(nomFichier, "wb");
     

     if (pFile == NULL)

     {	
        return  -1;
     }
     
      i = RTab( T, LV, LH);
   
     for (j = 0; j < i; j++) // i est initialise a 0 dans la fct RTab mais il est incremente de 1 avant de verifier la condition LV->teteH = LH donc on a pas besoin de lui rajouter + 1.
     {
     	
        fwrite(&T[j], sizeof(Informations), 1, pFile); //on remplie le fichier. 

     }

 

     fclose(pFile);

 

     return  1;

}



int lireFichierBinInfos(char nomFichier[]) // on cree une fct qui lie le fichier binaire.
{

     FILE *pFile;

     Informations infos;

 

     pFile = fopen(nomFichier, "rb");

 

     if (pFile == NULL)

     {

                return  -1;

      }

 

     printf("Voici la position et le nombre delements de chaque liste: \n");

     while (fread(&infos, sizeof(infos), 1, pFile) != 0)

     {

       printf("%d %d\n", infos.position, infos.NE);

     }

 

     printf("\n");

     fclose(pFile);

     return  1;

}








//écrire l’algorithme qui supprime toutes les sous chaines de la première puis de la deuxième … etc

int main()
{
    pListV LV;
    pListH L1, L2, LH;
	pListV TV, TS, TP;
	Informations T[100]; // ca cest pour la creation du fichier
    
    LV = CreerListV();

    afficherListeV(LV);
    
    //suppression de toutes les sous chaines presentes dans la structure.
    TV = LV;
	if(TV != NULL)
	{
		L2 = TV->teteH;
		TP = TV;
		TS = TV->svt; /*TP est le précédent de TS*/
		while(TS != NULL)
		{
			L1 = TS->teteH;
			if(listeL1souslisteL2(L1, L2) == 1)
			{
				//avant de libérer TS on sauvegarde son svt pour la suite de la procédure.
				TS = TS->svt;
				SupprimeLH(LV, L1);
			}
			else
			{
				TP =TS;
				TS = TS->svt;
			}
		}
		
		TV = TV->svt;
	}
	
	printf("Voici la structure apres supression des sous listes: \n");
	afficherListeV(LV);

    
    //on recopie les informations des listes restantes dans un fichier.
    
    if (creerFichierBinInfos( T, "Infos.dat", LV, LH) == -1)

    {
        printf("Problems creating file Infos.dat ...\n");
        printf("Value of errno: %d\n", errno);
        perror("Error printed by perror");
        return  0;

    }

    // on lit le fichier cree.

    if (lireFichierBinEtudAdmis("Infos.dat") == -1)

    {
        printf("Problems reading file Infos.dat ...\n");
        printf("Value of errno: %d\n", errno);
        perror("Error printed by perror");
        return  0;

    }

 


    return 0;
}









