#include "parser.h"
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char * argv[])
{
  
  if (argc != 2)
  {
    fprintf (stderr,"Utilisation: %s fichier\n",argv[0]);
    exit (-1);
  }
  parse (argv[1]);
  printf("VALEUR = %d",variables[1].val);
  return 0;
}
