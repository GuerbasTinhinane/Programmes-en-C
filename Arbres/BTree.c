#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"


void errorB(char *s){
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}

/*****************************************************************************/
/**************************** fonctions de base ******************************/
/*****************************************************************************/


BTree makeEmptyBTree(void){
	return (BTree)NULL;
}

BTree makeNode(Element e, BTree l,  BTree r){
	BTree new;
	if ((new=(BTree)malloc(sizeof(Node)))==NULL) errorB("Allocation rat�e!");
	new->elem=e;
	new->left=l;
	new->right=r;
	return new;
}

BTree makeLeaf(Element e){
	return makeNode(e,makeEmptyBTree(),makeEmptyBTree());
}


int isEmptyBTree(BTree bt){
	return (bt==NULL);
}

Element root(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de noeud � la racine d'un arbre vide!!!");
	return bt->elem;
}


BTree leftChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils gauche dans un arbre vide!!!");
	return bt->left;
}

BTree rightChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils droit dans un arbre vide!!!");
	return bt->right;
}

int isLeaf(BTree bt){
	return !isEmptyBTree(bt) && isEmptyBTree(leftChild(bt)) && isEmptyBTree(rightChild(bt));
}

void freeNode(Node *c){
	free(c);
}

/*****************************************************************************/
/*************************** fonctions bas niveau ****************************/
/*****************************************************************************/

void insertRight(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(rightChild(n)))
		n->right=makeLeaf(e);
	else errorB("insertRight impossible!");
}

void insertLeft(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(leftChild(n)))
		n->left=makeLeaf(e);
	else errorB("insertLeft impossible!");
}

Element deleteRight(Node *n){
	if(isEmptyBTree(n) || !isLeaf(rightChild(n)))
		errorB("deleteRight imossible!");

	Element res=root(n->right);
	n->right=makeEmptyBTree();
	return res;
}

Element deleteLeft(Node *n){
	if(isEmptyBTree(n)  || !isLeaf(leftChild(n)))
		errorB("deleteLeft imossible!");

	Element res=root(n->left);
	n->left=makeEmptyBTree();
	return res;
}

void insertRightmostNode(BTree *bt, Element e){
	if(isEmptyBTree(*bt))
		*bt=makeLeaf(e);
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(rightChild(tmp)))
			tmp=rightChild(tmp);
		insertRight(tmp,e);
	}
}

Element deleteLeftmostNode(BTree *bt){
	Element res;
	if(isEmptyBTree(*bt))
		errorB("deleteLeftmostNode imossible!");
	if(isEmptyBTree(leftChild(*bt))){
		res=root(*bt);
		*bt=rightChild(*bt);
	}
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(leftChild(leftChild(tmp))))
			tmp=leftChild(tmp);
		res=root(leftChild(tmp));
		tmp->left=(tmp->left)->right;
	}
	return res;
}

//__________________________________________________________________________

// renvoie le min
int min(int a, int b){
	return (a > b)? b : a;
}


// la creation d un arbre
void addNode(Node **tree, unsigned int key)
{
    Node *tmpNode;
    Node *tmpTree = *tree;

    Node *elem = malloc(sizeof(Node));
    elem->elem = key;
    elem->left = NULL;
    elem->right = NULL;

    if(tmpTree)
    do
    {
        tmpNode = tmpTree;
        if(key > tmpTree->elem )
        {
            tmpTree = tmpTree->right;
            if(!tmpTree) tmpNode->right = elem;
        }
        else
        {
            tmpTree = tmpTree->left;
            if(!tmpTree) tmpNode->left = elem;
        }
    }
    while(tmpTree);
    else  *tree = elem;
}


//l affichage d un arbre
void printTree(Node *tree)
{
    if(!tree) return;

    if(tree->left)  printTree(tree->left);

    printf("%d ", tree->elem);

    if(tree->right) printTree(tree->right);
}


//le nettoyage de l arbre
void clearTree(Node **tree)
{
    Node *tmpTree = *tree;

    if(!tree) return;

    if(tmpTree->left)  clearTree(&tmpTree->left);

    if(tmpTree->right) clearTree(&tmpTree->right);

    free(tmpTree);      

    *tree = NULL;
}

// QST 1---------------------------------------------------------
int equalBTreesRecu(BTree t1, BTree t2){ 
	if(isEmptyBTree(t1))
		return (isEmptyBTree(t2));
	else
		if(isEmptyBTree(t2))
			return 0;
		else return root(t1)==root(t2) && equalBTreesRecu(leftChild(t1),leftChild(t2)) && equalBTreesRecu(rightChild(t1),rightChild(t2));
}


// QST 2---------------------------------------------------------
int isSubBTreeRecu(BTree subt, BTree t){ 
	if(isEmptyBTree(t))
		return isEmptyBTree(subt);
	else 
		if(equalBTreesRecu(subt,t))
			return 1;
		else return isSubBTreeRecu(subt,leftChild(t)) || isSubBTreeRecu(subt,rightChild(t));
}


// QST 3---------------------------------------------------------
int findElemRec(BTree bt,Element e){
	if(isEmptyBTree(bt))
		return 0;
	else {
		if(root(bt)==e)
			return 1;
		else
			return findElemRec(leftChild(bt),e) ||  findElemRec(rightChild(bt),e);
	}
}


// QST 4---------------------------------------------------------
Element findMinRec(BTree bt){
	if(isEmptyBTree(bt))
		printf("finfMin impossible!");
	if(isLeaf(bt))
	 	return root(bt);
	else {
		Element m=root(bt);
		if(!isEmptyBTree(leftChild(bt)))
			m=min(m,findMinRec(leftChild(bt)));
		if(!isEmptyBTree(rightChild(bt)))
			m=min(m,findMinRec(rightChild(bt)));
		
		return m;
	}
}

// QST 5---------------------------------------------------------
/*print par niveau en traversant l'arbre*/
void printLevelOrder(Node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}
 
/* Print nodes du niveau actuel */
void printCurrentLevel(Node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->elem);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
 
/* calculer profondeur*/
int height(Node *node)
{
    if (node == NULL)
        return 0;
    else {
        /* calculer profondeur de chaque subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
 
        /* prendre la plus grande valeur */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Fonctions iteratives
// QST 1---------------------------------------------------------
int egaux(Node *n1, Node *n2)
{
    Node *stack1[100], *stack2[100];
    int stack_size1 = 0, stack_size2 = 0;
    Node *p1, *p2;
    
    for (p1 = n1; p1 != NULL; p1 = p1->left) {
        stack1[stack_size1++] = p1;
    }
    for (p2 = n2; p2 != NULL; p2 = p2->left) {
        stack2[stack_size2++] = p2;
    }
    if (!(stack_size1 == stack_size2)) {
    	printf("**Les deux arbres n'ont pas la meme taille donc ils ne sont pas egaux.\n");
    	return 0;
	}
    
    while (stack_size1 > 0) {
        Node *n1 = stack1[--stack_size1]; // pop
        Node *n2 = stack2[--stack_size2]; // pop
        
        if(n1->elem == n2->elem)
         printf("%d = %d\n", n1->elem, n2->elem);
        else {
        	printf("%d != %d\n", n1->elem, n2->elem);
        	printf("**Les deux arbres ne sont pas egaux.\n");
        	return 0;
		}
        
        for (p1 = n1->right; p1 != NULL; p1 = p1->left) {
            stack1[stack_size1++] = p1;
        }
        for (p2 = n2->right; p2 != NULL; p2 = p2->left) {
            stack2[stack_size2++] = p2;
        }
    }
    printf("**Les deux arbres sont egaux.\n");
    return 1;
}


int equalBTreesIter(Node *t1, Node *t2)
{
    return egaux(t1, t2);
}


// QST 2---------------------------------------------------------
int sub(Node *n1, Node *n2)
{
    Node *stack1[100], *stack2[100];
    int stack_size1 = 0, stack_size2 = 0;
    Node *p1, *p2;
    
    for (p1 = n1; p1 != NULL; p1 = p1->left) {
        stack1[stack_size1++] = p1;
    }
    for (p2 = n2; p2 != NULL; p2 = p2->left) {
        stack2[stack_size2++] = p2;
    }
    
    while (stack_size1 > 0) {
        Node *n1 = stack1[--stack_size1]; // pop
        Node *n2 = stack2[--stack_size2]; // pop
        
        if(n1->elem == n2->elem)
         printf("%d = %d\n", n1->elem, n2->elem);
        else {
        	printf("%d != %d\n", n1->elem, n2->elem);
        	printf("**A1 n'est pas un sous arbre de A2.\n");
        	return 0;
		}
        
        for (p1 = n1->right; p1 != NULL; p1 = p1->left) {
            stack1[stack_size1++] = p1;
        }
        for (p2 = n2->right; p2 != NULL; p2 = p2->left) {
            stack2[stack_size2++] = p2;
        }
    }
    printf("**A1 est un sous arbre de A2.\n");
    return 1;
}

int subBTreesIter(Node *t1, Node *t2)
{
    return sub(t1, t2);
}
// QST 3---------------------------------------------------------
int findElem(Node *n, int e)
{
    Node *stack[100];
    int stack_size = 0;
    Node *p;
    
    for (p = n; p != NULL; p = p->left) {
        stack[stack_size++] = p;
    }
    
    while (stack_size > 0) {
        Node *n = stack[--stack_size]; // pop
        
        if(n->elem == e)
        {
        	printf("**%d appartient a l'arbre A1.\n", e);
            return 1;
		}
         
        
        for (p = n->right; p != NULL; p = p->left) {
            stack[stack_size++] = p;
        }
       
    }
    printf("**%d n'appartient a l'arbre A1.\n", e);
    return 0;
}

int findElemIter(Node *t, int e)
{
    return findElem(t, e);
}

// QST 4---------------------------------------------------------
int findMin(Node *n)
{
    Node *stack[100];
    int stack_size = 0, min;
    Node *p;
    
    for (p = n; p != NULL; p = p->left) {
        stack[stack_size++] = p;
    }
    Node *m = stack[stack_size];
    min = m->elem;
    while (stack_size > 0) {
       Node *n = stack[--stack_size]; // pop
        
        if(n->elem < min)
        {
        	min = n->elem;
		}
         
        for (p = n->right; p != NULL; p = p->left) {
            stack[stack_size++] = p;
        }
       
    }
    printf("**La valeur minimum de l'arbre est: %d\n",min);
    return 1;
}

int findMinIter(Node *t)
{
    return findMin(t);
}

// QST 5---------------------------------------------------------


/*****************************************file*/
typedef struct tmaillon{
	BTree val; struct tmaillon *suiv ;
}tmaillon;
typedef struct file{tmaillon *tete ; tmaillon *queuef;}file;


void initfile(file *f){
	( *f ).tete=NULL;
	}

int filevide(file *f){
	if (( *f ).tete == NULL) return 1;
	else return 0;
}


void enfiler(file *f , BTree x){
	tmaillon *nouv;
	nouv=malloc(sizeof(tmaillon));
	nouv->val =x;
	nouv->suiv=NULL;
	if(filevide(f)==1){
		(*f).tete=nouv;
	}
	else(((*f).queuef)->suiv=nouv); 
    (*f).queuef=nouv;
}


void defiler(file *f ,  BTree *x){
	tmaillon *sauv;
	if(filevide(f)==1){printf("la file est vide \n");}
	else {
	*x =((*f).tete)->val; 
	sauv=(*f).tete; 
	(*f).tete = ((*f).tete)->suiv;
	 free(sauv);}
}

//Fonction principale

void ParcoursLargeurIter(BTree R){
	file *f;
	BTree x;
	
    initfile(&f);
	enfiler(&f,R);
	
	while(filevide(f) == 0)
	{
		defiler(&f,&x);
		printf("%d ", x->elem);
		
		if((x->left) !=NULL)	enfiler(&f,x->left);
		
		if((x->right) !=NULL)	enfiler(&f,x->right);
	}
}



