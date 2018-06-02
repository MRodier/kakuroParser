#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
int sauveMaj[200];
int sauvMajIndex;

//mode=0 -> mode "affectation", mode=1 -> mode retour sur une variable déjà affectée
int MajDomDifContrainte(int numCte, int numVarAffectee, int valDom, int mode){
	for(int index_var=0;index_var<=contraintes[numCte].IndexMax_varInCte;index_var++){
			int num_var=contraintes[numCte].varInCte[index_var];
			if(num_var!=numVarAffectee){
				if(mode==0){
					SauveMaj(num_var, valDom);
					variables[num_var].domaine[valDom-1][1]=variables[num_var].domaine[valDom-1][1]+1;
					variables[num_var].domaine[valDom-1][1]=-1;
				}
				else if(mode==1){
					variables[num_var].domaine[valDom-1][1]=variables[num_var].domaine[valDom-1][1]-1;
					if(variables[num_var].domaine[valDom-1][1]==0){
						variables[num_var].domaine[valDom-1][1]=valDom;
					}
				
				}
			}
	}
	return (!DomaineVide(numCte));
	
}
int MajDomSomContrainte(int numCte, int numVarAffectee, int valeurVar, int mode) {
	int sommmeVar=0;
	int max=0;
	int nbVarNonAffectees=0;
	int *varNonAffectees=malloc(sizeof(int));
	for(int i=0;i<contraintes[numCte].IndexMax_varInCte;i++){
		int num_var=contraintes[numCte].varInCte[i];
		if(variables[num_var]!=0) sommeVar=sommeVar+varaibles[num_var].val;
		else{
			nbVarNonAffectees=nbVarNonAffectees+1;
			varNonAffectees=realloc(varNonAffectees, sizeof(int)*nbVarNonAffectees);
			varNonAffectees[nbVarNonAffectees-1]=num_var;
		}
	}
	max= contraintes[numCte].somme-sommeVar;
	if(nbVarNonAffectes==0&&mode==0) return(max==0);
	else if (nbVarNonAffectes==1)
	{
		if(max>taille_domaine) return 0;
		else{
			for(int i=0;i<taille_domaine){
				if(i!=max-1){
					if(mode==0){
						variables[varNonAffectes[0]].domaine[i][0]=-1;
						variables[varNonAffectes[0]].domaine[i][1]=variables[varNonAffectes[0]].domaine[i][1]+1;
						SauveMaj(varNonAffectees[0],i+1);
					}
					else{
						variables[varNonAffectes[0]].domaine[i][1]=variables[varNonAffectes[0]].domaine[i][1]-1;
						if(variables[varNonAffectes[0]]domaine[i][1]==0){
							variables[varNonAffectes[0]]domaine[i][1]=i+1;	
						}
					}
				}
			}
		}
	}
	else{
		for(int j=0;j<nbVarNonAffectes;j++){
			for(int k=0;k<taille_domaine;k++){
				if(mode==0){
					variables[varNonAffectes[j]].domaine[k][0]=-1;
					variables[varNonAffectes[j]].domaine[k][1]=variables[varNonAffectes[0]].domaine[i][1]+1;
					SauveMaj(varNonAffectees[j],k+1);
				}
				else{
					variables[varNonAffectes[j]].domaine[i][1]=variables[varNonAffectes[0]].domaine[i][1]-1;
						if(variables[varNonAffectes[j]]domaine[k][1]==0){
						variables[varNonAffectes[j]]domaine[k][1]=k+1;
						}
				}
			}
		}
	}
}

int DomaineVide(int numCte){
	int j;
	for(int i=0;i<=contraintes[numCte].IndexMax_varInCte;i++){
		int num_var=contraintes[numCte].varInCte[i];
		j=0;
		while(j<=taille_domaine){
			if(variables[num_var].domaine[j][0]!=1) break;
			j++;
		}
		if(j==taille_domaine) return 1;
	}
	return 0;
}

void SauveMaj(int num_var, int ValInterdite){
	sauvMaj[sauvMajIndex][0]=num_var;
	sauvMaj[sauvMajIndex][1]=valInterdite;
	sauvMajIndex++;
}

void AnnulMaj(){
	for(int i=0<=sauvMajIndex){
		num_var=sauveMaj[i][0];
		indexDom=sauvMaj[i][1];
		variables[num_var.domaine[indexDom][1]=variables[num_var.domaine[indexDom][1]-1;
		if(variables[num_var.domaine[indexDom][1]==0)variables[num_var.domaine[indexDom][0]=indexDom+1;
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
	if(variables[num_var].val!=0){
		int val_var=variables[num_var].val;
		for(int i=0;i<variables[num_var].IndexMax_cteInVar;i++){
			if(contraintes[cteInVar[i]].somme==-1) MajDomDifContrainte(cteInVar[i], num_var, val_var, 1);
			else MajDomSomContrainte(cteInVar[i]e, num_var, val_var, 1);
		}
	index_domaine=variables[num_var].val;
	}
	//Boucle sur le domaine de la variable active
	while(index_domaine<taille_domaine && affectation_valide==0)
	{
		sauvMajIndex=0
		int index_cteInVar=0;
		variables[num_var].val=variables[num_var].domaine[index_domaine];
		printf("Var%d=%d\n",num_var,variables[num_var].val);
		index_domaine ++;
		//On vérifie si la valeur est valide dans le domaine, sinon on passe à la suivante
		if(variables[num_var].val==-1) continue;
		//Boucle sur le tableau des contraintes de la variables active
		int maj_valide;
		while(index_cteInVar<=variables[num_var].IndexMax_cteInVar)
		{
			indexCteActive=variables[num_var].cteInVar[index_cteInVar];
			cteActive = contraintes[indexCteActive];
			if(cteActive.somme==-1)
			{
				maj_valide=MajDomDifContrainte(indexCteActive, num_var, val_var, 0);
				if(!maj_valide){
					AnnulMaj();
					break;
				}
			}
			else 
			{
				maj_valide=MajDomSomContrainte(indexCteActive, num_var, val_var, 0);
				if(!maj_valide){
					AnnulMaj();
					break;
				}
			}
			if(index_cteInVar==variables[num_var].IndexMax_cteInVar)
			{
					affectation_valide = 1;
					printf("Affectation var%d = %d ok\n",num_var,variables[num_var].val);
			}	
			index_cteInVar++;	
		}	
	}
	
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
