Mohamed-Redha LACHOUB
Habib BEN ABDALLAH

# Tests de primalité de Fermat et de Miller-Rabin
## Exponentiation modulaire

`void square_and_multiply(mpz_t y, mpz_t a, mpz_t H, mpz_t n);`

La fonction square_and_multiply permet de calculer l'exponentiation modulaire
`(a^H) % n`


## Test de Fermat


`void AL(mpz_t a, mpz_t n);`

Simple fonction qui permet de générer un nombre aleatoire a compris entre 1 et n-1

`int Fermat(mpz_t n, mpz_t k);`

La fonction Fermat prend en paramètres deux entiers n et k de type mpz_t de la bibliothèque GMP et exécute k fois le test de Fermat sur l'entier n.
Renvoie 0 si l'entier à de forte chance d'être premier (plus k est grand plus les chances sont élever)
Et renvoie 1 si l'entier est composé.


## Test de Miller-Rabin


`int Decomposition(unsigned long int* s, mpz_t d, mpz_t n);`

La fonction Decomposition  permet de decomposer n en s et d de la façon suivante :
`(n-1) = (2**s)*d ` 

`int estTemoin(mpz_t a, mpz_t n, unsigned long int *s , mpz_t d);`

Cette fonction permet de renvoyer 1 si un entier a de type mpz_t est un témoin de Miller et retourne 0 si il ne l'est pas

`int miller(mpz_t n, mpz_t k);`

La fonction Fermat prend en paramètres deux entiers n et k de type mpz_t et exécute k fois le test de Fermat sur l'entier n.
Renvoie 1 si l'entier est premier, 0 sinon.

Commandes d'utilisation
===================================
Pour compiler ce programme vous pouvez utiliser le Makefile avec la commande make dans un terminal

Voici comment l'utiliser :
Après avoir entrer make, il vous sera demander un entier (Un "passage" dans le main permet d'en simplifier la saisie): 

Cette entier peut être entrer sous forme d'un nombre (ex : 2), on peut egualement lui adjoindre une puissance (ex : 2^23) et on peut ensuite lui soustraire un nombre (ex:2^23-1)
Attention on ne peut entrer un entier sous cette forme "13-6" ou alors il faudrait ecrire "13^1-6"

Ensuite Il vous sera demander un nombre de repetition (entier) 

Enfin s'affichera les résultats pour les deux algorithmes.


