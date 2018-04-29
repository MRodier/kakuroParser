# kakuroParser
A practice on Kakuro game parsing

petit test de création d'un dossier ou je puisse t'envoyer mes propositions, dis moi s'il y'a une meilleur manière de faire.
J'ai rajouté dans parser.h deux structures de données: "variable" et "contrainte" qui s'utilisent mutuellement, ainsi:
*une variable possède un pointeur vers un ensemble de contrainte (un tableau regroupant les contraintes qui la concerne afin de 
vérifier qu'elles sont bien respectées lors de l'affectation d'une valeur à cette variable)
Une contrainte possède un pointeur vers une variable de type "variable": un tableau regroupant les variables concernées par cette
contrainte, afin d'accéder à leurs valeurs lorsques l'on souhaitera valider le respect de cette contrainte par la valuation en
cours).
Problème évident de ce modèle simpliste:  on crée une contrainte autant de fois que le nombre de variable qu'elle concerne...idem pour les variables dans la structure contrainte. pas terrible pour la mémoire.
->il faudrait stocker uniquement des noms de variable ou des pointeurs, une référence permettant d'y accéder.
C'est loin d'être une solution complète au problème, dis moi ce que cela t'inspire ;).

Je suis en train de réfléchir à comment sauvegarder l'état d'avancement de l'algorithme (variable en cours, variable déjà valuées, état des domaines des variables....). C'est sans doute sur ce sujet que tu pensais à un arbre n-aire? 


2 ème édition:

J'ai gardé l'idée originelle des structures mais il y'a quelques différences:
->Je déclare uniquement un tableau contenant des structures de type "variable", les tableaux de type "contraintes" sont déclarés directement dans les variables.
C'est inspiré de l'ennoncé qui nous conseil de nous inspirer des listes d'adjacences, ainsi chaque variables a accès via ce tableau de contraintes (ou liste de contraintes!) aux contraintes qui la concernent et donc aux variables qui lui sont voisine (c'est à dire avec qui elle a une contrainte en commun). Je ne sais pas si c'est pas bien celà que le prof entendait mais cela me paraît pas mal...

J'ai joint un document texte avec du pseudo code correspondant à Backtrack, je pense que c'est fonctionnel, donne moi ton avis :). Je fais une pause et je m'y remet ce soir!
