#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int cte_difference_valide(contrainte cteActive, int index_cte_active){
	printf("Vérification contrainte différence %d portant sur les variables ", index_cte_active);
	for(int i=0;i<=cteActive.IndexMax_varInCte;i++){
		printf("V%d->%d ",cteActive.varInCte[i],variables[cteActive.varInCte[i]].val);
	}
	if(variables[cteActive.varInCte[0]].val==variables[cteActive.varInCte[1]].val)
	{
		printf(" violé\n");
		return 0;
	}
	else
	{
		printf(" OK\n");
		return 1;
	}
	
}
int cte_somme_valide(contrainte cteActive, int index_cte_active){
	int somme=0,allVarAffected=1;
	printf("Vérification contrainte %d somme=%d portant sur les variables ", index_cte_active,cteActive.somme);
	for(int i=0;i<=cteActive.IndexMax_varInCte;i++){
		printf("V%d-->%d ",cteActive.varInCte[i],variables[cteActive.varInCte[i]].val);
	}
	for(int i=0;i<=cteActive.IndexMax_varInCte;i++)
	{
		if(variables[cteActive.varInCte[i]].val==0) allVarAffected=0;
		somme = somme + variables[cteActive.varInCte[i]].val;
	}
	if(allVarAffected)
	{
		if(somme==cteActive.somme)
		{ 
			printf(" OK\n ");
			return 1;
		}
		else
		{
			printf(" violé\n");
			return 0;
		}
			
	}
	else
	{
		if(somme<cteActive.somme)
		{
			printf(" OK\n ");
			return 1;
		}
		else 
		{
			printf("violé\n");
			return 0;
		}
	}
	
}

int main (int argc, char * argv[])
{
  
  if (argc != 2)
  {
    fprintf (stderr,"Utilisation: %s fichier\n",argv[0]);
    exit (-1);
  }
  contraintes = malloc(sizeof(contrainte));
  verif_allocation_memoire(contraintes);
  variables = malloc(sizeof(variable));
  verif_allocation_memoire(variables);
  nb_contraintes=0;
  nb_variables=0;
  parse (argv[1]);

  int num_var=0;
  int indexCteActive;
  contrainte cteActive;
  //Boucle sur le tableau des contraintes
  while(num_var<=nb_variables-1){
	int index_domaine=0, affectation_valide=0;
	printf("var %d Taille tab contrainte=%d\n",num_var,variables[num_var].IndexMax_cteInVar+1);
	//dans le cas d'un retour en arrière sur les variables
	if(variables[num_var].val!=0) index_domaine=variables[num_var].val;
	//Boucle sur le domaine de la variable active
	while(index_domaine<taille_domaine && affectation_valide==0)
	{
		int index_cteInVar=0;
		variables[num_var].val=variables[num_var].domaine[index_domaine];
		printf("Var%d=%d\n",num_var,variables[num_var].val);
		index_domaine ++;
		
		//Boucle sur le tableau des contraintes de la variables active
		while(index_cteInVar<=variables[num_var].IndexMax_cteInVar)
		{
			indexCteActive=variables[num_var].cteInVar[index_cteInVar];
			cteActive = contraintes[indexCteActive];
			if(cteActive.somme==-1)
			{
				if(!cte_difference_valide(cteActive, indexCteActive)) break;
			}
			else 
			{
				if(!cte_somme_valide(cteActive,indexCteActive))break; 
			}
			if(index_cteInVar==variables[num_var].IndexMax_cteInVar)
			{
					affectation_valide = 1;
					printf("Affectation var%d = %d ok\n",num_var,variables[num_var].val);
			}	
			index_cteInVar++;	
		}	
	}
	//printf("\n index_domaine=%d affectation_valide=%d",index_domaine,affectation_valide);
	
	if(index_domaine==taille_domaine&&affectation_valide==0)
	{
		printf("RETOUR ARRIERE\n");
		variables[num_var].val=0;
		num_var --;	
	}
	else num_var++;	
	
  }
  printf("Solution:\n");
  for(int i=0;i<nb_variables;i++){
	printf("%d ",variables[i].val);
  }
  
  
  free(contraintes);
  free(variables);
  return 0;
}
