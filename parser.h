#ifndef PARSER_H
#define PARSER_H

typedef struct variable variable;
typedef struct contrainte contrainte;

struct variable{
  char name[6];
  int val;
  int * domaine;
  contrainte *concernedContraintes;
};

struct contrainte{
  char name[15];
  variable *concernedVariables;
  int somme;				//-1 si contrainte de différence
};


variable * variables;
contrainte * contraintes;

void parse (char * nom_fichier);

/* fonctions à compléter pour remplir vos structures de données */

void Variable (int num);      /* fonction permettant la création d'une nouvelle variable ayant pour numéro num */
void Contrainte_Difference (int var1, int var2);  /* fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2*/
void Contrainte_Somme (int portee[], int arite, int val);  /* fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenant 
                                                              dans le tableau portee de taille arite et dont la valeur est val */


#endif
