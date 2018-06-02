#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>




void parse (char * nom_fichier)
{
  FILE * f;         /* le descripteur du fichier à lire */
  int c;            /* le caractère courant */
  
  int num_ligne;    /* le numero de la ligne courante */
  int num_colonne;  /* le numero de la colonne courante */
  int nb_variables; /* le nombre de variables déjà trouvées */
  int somme;        /* une somme */
  
  
  int * portee;     /* la portee d'une contrainte */
  int arite;        /* l'arité d'une contrainte */
  int i,j;          /* des compteurs de boucle */
  
  f = fopen (nom_fichier,"r");
  
  if (f == NULL)
  {
    fprintf (stderr,"Fichier %s non trouve\n",nom_fichier);
    exit (-1);
  }

  /* on calcule la taille de la grille */
  
  nb_lignes = 0;
  nb_colonnes = 0;
  
  c = fgetc(f);
  
  while (! feof (f))
  {
    if (c == '\n')
      nb_lignes++;
    else      
      if ((nb_lignes == 0) && ((c == '.') || (c == '\\')))
        nb_colonnes++;

    c = fgetc(f);
  }
  fclose (f);

  printf ("Taille : %d x %d\n",nb_lignes,nb_colonnes);


  /* remplissage de la grille */

  grille = (Case **) malloc (sizeof(Case *) * nb_lignes);
  for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
    grille[num_ligne] = (Case *) malloc (sizeof(Case) * nb_colonnes);

  f = fopen (nom_fichier,"r");
  
  if (f == NULL)
  {
    fprintf (stderr,"Fichier %s non trouve\n",nom_fichier);
    exit (-1);
  }  
  
  num_ligne = 0;
  num_colonne = 0;
  nb_variables = 0;
  
  c = fgetc(f);
 
  while (! feof (f))
  {
    if (c == '\n')
    {
      num_ligne++;
      num_colonne = 0;
    }
    else
      if (c == ' ')
        num_colonne++;
      else
        if (c == '.')     /* case blanche */
        {
          grille[num_ligne][num_colonne].coul = BLANCHE;
          grille[num_ligne][num_colonne].num = nb_variables;
          grille[num_ligne][num_colonne].somme_horizontale = -1;
          grille[num_ligne][num_colonne].somme_verticale = -1;
          Variable(nb_variables);
          
          nb_variables++;
        }
        else
          if (c == '\\')    /* case noire de la forme \y ou \ */
          {
            grille[num_ligne][num_colonne].coul = NOIRE;
            grille[num_ligne][num_colonne].num = -1;
            grille[num_ligne][num_colonne].somme_verticale = -1;

            c = fgetc(f);
            
            if (isdigit(c))    /* case noire de la forme \y */
            {
              ungetc (c,f);
              fscanf (f,"%d",&somme);
              grille[num_ligne][num_colonne].somme_horizontale = somme;
            }
            else  /* case noire de la forme \ */
            {
              grille[num_ligne][num_colonne].somme_horizontale = -1;
              
              ungetc (c,f);
            }
          }
          else
            if (isdigit(c))    /* case noire de la forme x\ ou x\y */
            {
              grille[num_ligne][num_colonne].coul = NOIRE;
              grille[num_ligne][num_colonne].num = -1;
              
              ungetc (c,f);
              fscanf (f,"%d",&somme);
              grille[num_ligne][num_colonne].somme_verticale = somme;
              
              c = fgetc(f);   /* on lit le caractère \ */
              
              c = fgetc(f);
              
              if (isdigit(c))  /* case noire de la forme x\y */
              {
                ungetc (c,f);
                fscanf (f,"%d",&somme);
                grille[num_ligne][num_colonne].somme_horizontale = somme;
              }
              else   /* case noire de la forme x\ */
              {
                grille[num_ligne][num_colonne].somme_horizontale = -1;
                
                ungetc (c,f);
              }
            }
    
    c = fgetc(f);
  }
  fclose (f);  
  
  printf ("Nombre de variables trouvées : %d\n",nb_variables);
  
  
  /* on crée les contraintes */
  
  if (nb_lignes < nb_colonnes)
    portee = (int *) malloc (sizeof(int) * nb_colonnes);
  else portee = (int *) malloc (sizeof(int) * nb_lignes);
  
  for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
    for (num_colonne = 0; num_colonne < nb_colonnes; num_colonne++)
      if (grille[num_ligne][num_colonne].coul == NOIRE)
      {
        if (grille[num_ligne][num_colonne].somme_horizontale != -1)
        {
          arite = 0;
          i = num_colonne+1;
          while ((i < nb_colonnes) && (grille[num_ligne][i].coul == BLANCHE))
          {
            portee[arite] = grille[num_ligne][i].num;
            arite++;
            
            j = i+1;
            while ((j < nb_colonnes) && (grille[num_ligne][j].coul == BLANCHE))
            {
              Contrainte_Difference (grille[num_ligne][i].num,grille[num_ligne][j].num);
              j++;
            }
            i++;
          }
          
          Contrainte_Somme (portee,arite,grille[num_ligne][num_colonne].somme_horizontale);
        }
        
        if (grille[num_ligne][num_colonne].somme_verticale != -1)
        {
          arite = 0;
          i = num_ligne+1;
          while ((i < nb_lignes) && (grille[i][num_colonne].coul == BLANCHE))
          {
            portee[arite] = grille[i][num_colonne].num;
            arite++;
            
            j = i+1;
            while ((j < nb_lignes) && (grille[j][num_colonne].coul == BLANCHE))
            {
              Contrainte_Difference (grille[i][num_colonne].num,grille[j][num_colonne].num);
              j++;
            }
            i++;
          }
          
          Contrainte_Somme (portee,arite,grille[num_ligne][num_colonne].somme_verticale);          
        }
      }
      
      
  /* liberation de la mémoire allouée pour la grille et la portée des contraintes */
  free (portee);
  
  for (num_ligne = 0; num_ligne < nb_lignes; num_ligne++)
    free (grille[num_ligne]);
  free (grille);
}

void verif_allocation_memoire(void *pointeur)
{
	if(pointeur==NULL){
		printf("Erreur allocation mémoire\n");
		exit(-1);
	}
}

/* fonctions à compléter pour remplir vos structures de données */


void Variable (int num)
/* fonction permettant la création d'une nouvelle variable ayant pour numéro num */
{
  variables = realloc(variables, sizeof(variable)*(num+1));
  verif_allocation_memoire(variables);
  nb_variables += 1;
  variables[num].val = 0;
  for(int i=0;i<=8;i++){
	variables[num].domaine[i]=i+1;
  }
  variables[num].IndexMax_cteInVar = -1;
  variables[num].cteInVar = malloc(sizeof(int));
  //printf ("Variable %d\n",num);
}


void Contrainte_Difference (int var1, int var2)
/* fonction permettant la création d'une nouvelle contrainte binaire de différence entre les variables var1 et var2*/
{
  contraintes = realloc(contraintes, sizeof(contrainte)*(nb_contraintes+1));
  verif_allocation_memoire(contraintes);
  nb_contraintes += 1;
  printf ("Contrainte n°%d binaire de difference entre %d et %d\n",nb_contraintes-1,var1,var2);
  if(contraintes == NULL) printf("Erreur mémoire");
  //affectation des variables à la contrainte
  contraintes[nb_contraintes-1].varInCte=malloc(sizeof(int)*2);
  contraintes[nb_contraintes-1].IndexMax_varInCte=1;
  contraintes[nb_contraintes-1].varInCte[0]=var1;
  contraintes[nb_contraintes-1].varInCte[1]=var2;

  //Affectation de la contraintes aux variables concernées
  variables[var1].IndexMax_cteInVar += 1;
  variables[var2].IndexMax_cteInVar += 1;
  variables[var1].cteInVar=realloc(variables[var1].cteInVar, sizeof(int)*(variables[var1].IndexMax_cteInVar+1));
  variables[var2].cteInVar=realloc(variables[var2].cteInVar, sizeof(int)*(variables[var2].IndexMax_cteInVar+1));
  variables[var1].cteInVar[variables[var1].IndexMax_cteInVar]=nb_contraintes-1;
  variables[var2].cteInVar[variables[var2].IndexMax_cteInVar]=nb_contraintes-1;
  contraintes[nb_contraintes-1].somme = -1;
  //printf ("nb_contraintes= %d\n",nb_contraintes);
}


void Contrainte_Somme (int portee [], int arite, int val)
/* fonction permettant la création d'une nouvelle contrainte n-aire de somme portant sur les variables contenues dans le tableau portee de taille arite et dont la valeur est val */
{
  int i;
  contraintes = realloc(contraintes, sizeof(contrainte)*(nb_contraintes+1));
  verif_allocation_memoire(contraintes);
  nb_contraintes += 1;
  contraintes[nb_contraintes-1].somme=val;
  contraintes[nb_contraintes-1].IndexMax_varInCte=arite-1;
  contraintes[nb_contraintes-1].varInCte=malloc(sizeof(int)*arite);
  verif_allocation_memoire(contraintes[nb_contraintes-1].varInCte);
  printf ("Contrainte n°%d n-aire de somme portant sur",nb_contraintes-1);
  for (int i = 0; i < arite; i++){
	contraintes[nb_contraintes-1].varInCte[i]=portee[i];
	variables[portee[i]].IndexMax_cteInVar += 1;
	variables[portee[i]].cteInVar=realloc(variables[portee[i]].cteInVar, sizeof(int)*(variables[portee[i]].IndexMax_cteInVar+1));
  	verif_allocation_memoire(variables[portee[i]].cteInVar);
	variables[portee[i]].cteInVar[variables[portee[i]].IndexMax_cteInVar]=nb_contraintes-1;
        
    	printf (" %d",portee[i]);
  }
  printf (" et de valeur %d\n",val);
  //printf ("nb_contraintes= %d\n",nb_contraintes);
}
