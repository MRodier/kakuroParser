#ifndef PARSER_H
#define PARSER_H
#define taille_domaine 9
typedef struct variable variable;
typedef struct contrainte contrainte;

struct variable{
  int val;
  int domaine[taille_domaine][2];
  int *cteInVar;		//contraintes concernant la variable
  int IndexMax_cteInVar;
};

struct contrainte{
  int *varInCte;		//Index dans le tableau "variables" des Variables concernées par la contrainte
  int somme;				//-1 si contrainte de différence
  int IndexMax_varInCte;			
};

enum couleur {BLANCHE,NOIRE};   /* les deux couleurs possibles pour les cases */ 

typedef struct
{
  enum couleur coul;      /* la nature de la case */
  int num;                /* le numero de la case s'il s'agit d'une case blanche */
  int somme_horizontale;  /* la valeur de la somme horizontale le cas écheant, -1 sinon */
  int somme_verticale;    /* la valeur de la somme verticale le cas écheant, -1 sinon */
} Case;

variable * variables;
contrainte * contraintes;		//tableau de l'ensemble des variables
int nb_contraintes;
int nb_variables;
Case ** grille;   /* la grille de jeu */
int nb_colonnes;  /* le nombre de colonnes de la grille */
int nb_lignes;    /* le nombre de lignes de la grille */


void parse (char * nom_fichier);
void verif_allocation_memoire(void *pointeur);
void Variable (int num);
void Contrainte_Difference (int var1, int var2);
void Contrainte_Somme (int portee[], int arite, int val); 



#endif
