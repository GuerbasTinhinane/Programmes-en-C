#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>

int i,k;
struct
{
       int l;
       int t[10000];
}tab1;
struct
{
       int l;
       int t[10000];
}tab2;
struct
{
       int l;
       int t[10000];
}tab3;

typedef struct Elementt Elementt;
struct Elementt
{
	int valeur;
	Elementt *suivant;
};

typedef struct Liste Liste;
struct Liste
{
	Elementt *tete;
};

Liste *initialisation(int nvvaleur)
{
	Liste *liste = malloc(sizeof(*liste));
	Elementt *Elementt = malloc(sizeof(*Elementt));
	
	if (liste == NULL || Elementt == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	Elementt->valeur = nvvaleur;
	Elementt->suivant = NULL;
	liste->tete = Elementt;
	
	return liste;
}

void sup1(int t[20],int k)
{
    for(i=k;i<tab1.l-1;i++)
    t[i]=t[i+1];
    tab1.l--;
}
void sup2(int t[20],int k)
{
    for(i=k;i<tab2.l-1;i++)
    t[i]=t[i+1];
    tab2.l--;
}

int max(int t[20], Elementt *k)
{
	
	int m = t[0];
	k->valeur = 0;
    for (i=1; i<tab2.l; i++)
    {
        if (m < tab2.t[i]) 
        {
            m = tab2.t[i];
            k->valeur = i;
        }
        
    }
    return m;

}

int min(int t[20], Elementt *k)
{
	
	int m = t[0];
	k->valeur = 0;
    for (i=1; i<tab1.l; i++)
    {
        if (m > tab1.t[i]) 
        {
            m = tab1.t[i];
            k->valeur = i;
        }
        
    }
    return m;

}

void afficherListe(Liste *liste)
{
	if (liste == NULL)
	{
		exit(EXIT_FAILURE);
	}
	
	Elementt *actuel = liste->tete;
	
	while(actuel != NULL)
	{
		printf("%d -> ", actuel->valeur);
		actuel = actuel->suivant;
	}
	printf("NULL\n");
}


void append (Liste *liste, int nvvaleur)
{
	/*Cr�ation du nouvel �l�ment*/
	Elementt *nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	nouveau->valeur = nvvaleur;
	
	/*Insertion de l'�l�ment � la fin de la liste */
	Elementt *dernier = liste->tete;
	while(dernier->suivant != NULL)
	{
		dernier = dernier->suivant;
	}
	dernier->suivant = nouveau;
	nouveau->suivant = NULL;
}

void range_append(Liste *liste, int t[20])
{
	int valeur;
	Elementt *e2 = malloc(sizeof(*e2));
    int cmpt=0;
    while (cmpt<tab1.l)
	{
		valeur = min(tab1.t,e2);
		sup1(tab1.t,e2->valeur);
		append(liste, valeur);
	}
}

void insert (Liste *liste, int nvvaleur)
{
	/*Cr�ation du nouvel �l�ment*/
	Elementt *nouveau = malloc(sizeof(*nouveau));
	if (liste == NULL || nouveau == NULL)
	{
		exit(EXIT_FAILURE);
	}
	nouveau->valeur = nvvaleur;
	
	/*Insertion de l'�l�ment au d�but de la liste */
	nouveau->suivant = liste->tete;
	liste->tete = nouveau;
	
}

void range_insert(Liste *liste, int t[20])
{
    int valeur;
	Elementt *e2 = malloc(sizeof(*e2));
    int cmpt=0;
    while (cmpt<tab2.l)
	{
		valeur = max(tab2.t,e2);
		sup2(tab2.t,e2->valeur);
		insert(liste, valeur);
	}
}




main()
{    
    //Changer la couleur de l'interface en jaune et l'ecriture en noir
    system("color e0");
    srand(time(NULL));
    //********************************************
    
    //DECLARATION DES FICHIERS POUR LES RESULTATS
    FILE* fichier1=NULL;
    FILE* fichier2=NULL;
    
    //CREATION DU FICHIER QUI VA STOCKER LES RESULTATS 
	fichier1 = fopen("C:/Users/DELL/Desktop/RESULTATS_RANGE_APPEND.txt","w");
	fichier2 = fopen("C:/Users/DELL/Desktop/RESULTATS_RANGE_INSERT.txt","w");
	
	//DECLARATION DES VARIABLES DE MESURE DU TEMPS
    clock_t t1,t2,t3,t4;
    double delta1, delta2;
    float reel1, reel2;
    //********************************************
    
    Liste *maListe1;
    Liste *maListe2;
	Elementt *e1 = malloc(sizeof(*e1));
	Elementt *e2 = malloc(sizeof(*e2));
	int j;
	
    int  m=-1, pos, v1, v2;
    int n=10000, y=0;
    
    //********************************************

do {
	y++;
printf(" \n\n//*********************************************************************************\n");
printf("---------->EXECUTION numero %d \n",y );	
printf("\t pour n = %d\n",n );


    tab3.l=n;
    tab1.l=tab3.l;
    tab2.l=tab3.l;
    
    //remplir le tableau avec les valeurs et l'afficher
    //printf("Affichage du tableau \n");
    for(i=0;i<tab3.l;i++)
    {
      
       tab3.t[i] = (rand() % (100 + 1 - 1)) + 1;
       tab1.t[i] = tab3.t[i];
       tab2.t[i] = tab3.t[i];
      
//       printf("\t\tT[%d]=%d\n",i,tab3.t[i]);
	}
	
	
	
	
//    printf("max: %d\n", max(tab.t1,e1));
//    printf("posmax: %d\n\n", e1->valeur);
//    printf("min: %d\n", min(tab.t1,e2));
//    printf("posmin: %d\n\n", e2->valeur);

    //********************************************
    ////////////////////////////RANGE_APPEND/////////////////////////////////
    
    
    
    v1 = min(tab1.t,e1);
	sup1(tab1.t,e1->valeur);
	maListe1 = initialisation(v1);
    
    //1ERE VAR DE TEMPS
    t1 = clock();
    range_append(maListe1,tab1.t);
    //2EME VAR DE TEMPS
    t2 = clock();
    //printf("Affichage du tableau t1 (si bonne execution ne doit rien afficher)\n");
    for(i=0;i<tab1.l;i++)
    {
       printf("\t\tT[%d]=%d\n",i,tab1.t[i]);
	}
	//affichage de la liste fifo
	printf("Affichage de la liste range_append \n");
//    afficherListe(maListe1);
    
    
    //LA MOYENNE DU TEMPS D'EXECUTION
        delta1 = (double)(t2-t1)/CLOCKS_PER_SEC;
        reel1 = (float)delta1;
        
        //AFFICHAGE DU TEMPS D'EXECUTION
        printf("\n Le temps d'execution pour la liste range_append est: ( %lf )\n\n", delta1);
        fprintf(fichier1,"%lf,", delta1);
    
    //********************************************
    ////////////////////////////RANGE_INSERT/////////////////////////////////
    
    
    v2 = max(tab2.t,e2);
	sup2(tab2.t,e2->valeur);
	maListe2 = initialisation(v2);
	
    //1ERE VAR DE TEMPS
    t3 = clock();
    range_insert(maListe2,tab2.t);
    //2EME VAR DE TEMPS
    t4 = clock();
    //printf("Affichage du tableau t2 (si bonne execution ne doit rien afficher)\n");
    for(i=0;i<tab2.l;i++)
    {
       printf("\t\tT[%d]=%d\n",i,tab2.t[i]);
	}
	//affichage de la liste fifo
	printf("Affichage de la liste range_insert \n");
//    afficherListe(maListe2);
   
        
    //LA MOYENNE DU TEMPS D'EXECUTION
        delta2 = (double)(t4-t3)/CLOCKS_PER_SEC;
        reel2 = (float)delta2;
        
        //AFFICHAGE DU TEMPS D'EXECUTION
        printf("\n Le temps d'execution pour la liste range_insert est: ( %lf )\n\n", delta2);
        fprintf(fichier2,"%lf,", delta2);
//        for(i=0;i<tab3.l;i++)
//    {
//       
//       printf("\t\tT[%d]=%d\n",i,tab3.t[i]);
//	}
    
    n=n+10000;
}while (n != 110000);
	fprintf(fichier1,"\n");
	fprintf(fichier2,"\n");
    system("pause");
    return 0;
    

}

