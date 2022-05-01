#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

//exposant modulaire
void square_and_multiply(mpz_t y,mpz_t a, mpz_t H, mpz_t n){
    mpz_t buffer;
    mpz_init_set(buffer,a);
    int longueurH = mpz_sizeinbase(H, 2);
   
    

    for (int y = longueurH-2; y >= 0; y--){

        mpz_mul(buffer,buffer,buffer);

        mpz_mod(buffer,buffer,n);

        if (mpz_tstbit(H,y) == 1){

            mpz_mul(buffer,buffer,a);
			
            mpz_mod(buffer,buffer,n);
        }
    }
    mpz_set(y,buffer);
    mpz_clear(buffer);
}

///////////////*LE TEST DE FERMAT*///////////////

/*Fonction qui renvoie un nombre aleatoire a tel que 1<a<n-1*/
void AL(mpz_t a, mpz_t n)
{
	clock_t time = clock();

    gmp_randstate_t etat;
    gmp_randinit_default(etat);
    gmp_randseed_ui(etat, time);

    mpz_urandomm(a, etat, n);
    if(mpz_cmp_si(a, 0)==0)//Si le nombre aleatoire vaux 0 on lui ajoute 2
	{mpz_add_ui(a, a, 2);}
	if(mpz_cmp_si(a, 1)==0)//Si le nombre aleatoire vaux 1 on lui ajoute 1
	{mpz_add_ui(a, a, 1);}
}

/*Test de Fermat*/
int Fermat(mpz_t n, mpz_t k) 
{
	mpz_t a;
    mpz_init(a);
    
    mpz_t r;
    mpz_init(r);
    
    mpz_t n1;
    mpz_init(n1);
    
   	int i=1;

/*les nombres premiers ne peuvent être negatif,egual à 0 ou 1*/	
	if (mpz_cmp_si(n,0)<0) 
	{
		mpz_clear(a);
		mpz_clear(r);
		mpz_clear(n1);
		printf("Un nombre negatif ne peut être premier !\n");
		exit(0);
	}
	
	if (mpz_cmp_si(n,0)==0) 
	{
		mpz_clear(a);
		mpz_clear(r);
		mpz_clear(n1);
		printf("0 n'est ni premier ni composé !\n");
		exit(0);
	}
	
	if (mpz_cmp_si(n,1)==0) 
	{
		mpz_clear(a);
		mpz_clear(r);
		mpz_clear(n1);
		printf("1 n'est ni premier ni composé !\n");
		exit(0);
	}

/*2 et 3 sont premiers*/	
	if(mpz_cmp_ui(n, 4) < 0)
	{
		mpz_clear(a);
		mpz_clear(r);
		mpz_clear(n1);

		return(0);
	}


/*Le test de Fermat*/	
	while(mpz_cmp_si(k,i)>=0)
	{
		mpz_sub_ui(n1, n, 1);//n1 = n-1
		AL(a, n);//choisit aleatoirement a tel que 1<a<n-1
		
		square_and_multiply(r, a, n1, n);
		if (mpz_cmp_si(r,1)==0) //Si a^n-1 = 1 mod n 
		{
			gmp_printf("VOICI a: %Zd\n", a);
			mpz_clear(a);
			mpz_clear(r);
			mpz_clear(n1);
			return 0;
		}
		i++;
	}
	gmp_printf("VOICI a: %Zd\n", a);
	
	mpz_clear(a);
	mpz_clear(r);
	mpz_clear(n1);
	return 1;
}

///////////////*LE TEST DE MILLER-RABIN*///////////////

//cela permet de decomposer n en s et d de la façon suivante : (n-1) = (2**s)*d
int Decomposition(unsigned long int* s, mpz_t d, mpz_t n)
{
	mpz_t reponse;
	mpz_init(reponse);

	
	unsigned long int modulo;
	

	//On teste si le nombre choisi est un nombre valide en allouant de la mémoire.
	if(mpz_cdiv_q_ui(reponse, n, 2) == 0)
	{
		mpz_clear(reponse);

		fprintf(stderr, "Erreur : n n'est pas un nombre valide.\n");
		exit(1);
	}
	//On verifie que n doit être superieur a 2
	else if(mpz_cmp_ui(n, 3) < 0)
	{
		
		mpz_clear(reponse);

		fprintf(stderr, "Erreur : n doit être plus grand 2\n");
		exit(2);
	}
	
	mpz_t numérateur;
	mpz_init(numérateur);
	*s = 1;

	//numérateur = n-1
	mpz_sub_ui(numérateur, n, 1);

	do
	{
		*s = *s + 1;

		//d = numérateur / (2**s)
		modulo = mpz_cdiv_q_ui(d, numérateur, 1 << *s);

	//la boucle est appliqué tant que d est un nombre entier
	}while(modulo == 0);
	
	
	*s = *s -1; //s prend alors le précédent exposant valide

	
	mpz_cdiv_q_ui(d, numérateur, 1 << *s);

	
	mpz_clear(numérateur);
	mpz_clear(reponse);

	return(0);
}

//nous retournerons 1 si a est un témoin de Miller, 0 sinon
int estTemoin(mpz_t a, mpz_t n, unsigned long int *s , mpz_t d)
{
	mpz_t reponse;
	mpz_init(reponse);

	//on teste la validité du nombre choisi 
	if(mpz_cdiv_q_ui(reponse, n, 2) == 0)
	{
		
		mpz_clear(reponse);

		fprintf(stderr, "Erreur : n'est pas un nombre valide.\n");
		exit(-1);
	}
	//On vérifie que n est superieur à 2
	else if(mpz_cmp_ui(n, 3) < 0)
	{
		
		mpz_clear(reponse);

		fprintf(stderr, "Erreur : n doit être plus grand que 2\n");
		exit(-2);
	}
	//On vérifie que a est superieur à 1
	else if(mpz_cmp_ui(a, 1) < 0)
	{
		
		mpz_clear(reponse);

		fprintf(stderr, "Erreur : a doit être plus grand que 1\n");
		exit(-3);
	}	

	//on copie le paramètre
	unsigned long int Sclone = *s;
	mpz_t numérateur;
	mpz_init(numérateur);

	//numérateur = (n-1)
	mpz_sub_ui(numérateur, n, 1);

	// permet de calculer reponse = (a**d) % n
	square_and_multiply(reponse,a,d,n);
   
    //si ce qui en ressort = 1 ou (n-1)
	
	if((mpz_cmp_ui(reponse, 1) == 0) || (mpz_cmp(reponse, numérateur) == 0))
	{
		mpz_clears(numérateur, reponse, NULL);
		
		return(0);    //il n'y a pas de témoin de miller 
	}

	while (Sclone > 1)
	{
		mpz_t deux;
		mpz_init_set_si(deux,2);
		square_and_multiply(reponse,reponse,deux,n);

		//si ce qui en ressort = (n-1), alors de même, il n'y pas de témoin de miller 
		if(mpz_cmp(reponse, numérateur) == 0)
		{
			
			mpz_clears(numérateur, reponse, NULL);

		
			return(0);
		}
		
		Sclone = Sclone - 1;
		
	}

	
	mpz_clears(reponse, numérateur, NULL);

	//Si les conditions ci-dessus ne sont pas remplies, alors on suppose que c'est un témoin de Miller
	return(1);

}

//Retournera 1 si n est premier, 0 sinon
int miller(mpz_t n, mpz_t k)
{
	
	mpz_t reponse;
	mpz_init(reponse);

	if(mpz_cmp_ui(n, 4) < 0)
	{
		
		mpz_clear(reponse);

		return(1);
	}
	//si le nombre choisi n'est pas valide on désalloue la mémoire
	else if(mpz_cdiv_q_ui(reponse, n, 2) == 0)
	{
		
		mpz_clear(reponse);

		return(0);
	}

	
	mpz_clear(reponse);


	mpz_t d, a;
	unsigned long int s = 0;
	mpz_inits(d, a, NULL);
	int i;

	if(Decomposition(&s, d, n) != 0)
	{
		
		mpz_clear(d);

		fprintf(stderr, "Erreur\n");
		return(-1);
	}
	//On teste tout les nombres de 2 à n-2 pour les témoins
	//et si il y a un témoin, alors le nombre choisi n'est pas premier.
	if(mpz_cmp_ui(n, MAX_INPUT) < 0)
	{
		unsigned long int tailleN = mpz_get_ui(n);
	
		i=2;
		while( i<(tailleN-2))
		{
			mpz_set_ui(a, i);
				
			if(estTemoin(a, n, &s, d) == 1)
			{
				
				mpz_clears(d, a, NULL);

				
				return(0);
			}	
			i++;
		}


		
		mpz_clears(d, a, NULL);

		
		return(1); //si il n'y a pas de témoin de Miller, alors n est surement premier.
	}
	return(1);
}

///////////////*MAIN*///////////////

int main() 
{
	mpz_t n, k, p, res, d;
    mpz_init(n);
    mpz_init_set_si(p, 1);
    
    mpz_init(res);
    mpz_init(d);
    
    
	printf("Entrez un entier: ");
	gmp_scanf("%Zd^%Zd-%Zd", n, p, d);

///////////////////Ce passage sert à simplifier la saisie de l'entier///////////////////
		if(mpz_cmp_si(p,0)<0)
		{
            printf("Erreur, la puissance est inférieure à zéro.");
            printf("\n");
            mpz_clear(n);
            mpz_clear(p);
            mpz_clear(res);
            return 0;
		}
	else if(mpz_cmp_si(p,0)==0)
			mpz_set_si(n,1);
			
	else if(mpz_cmp_si(p,1)==0)
			mpz_set(n,n);
	
	else
		{
			int i=1;
			mpz_set(res,n);
			while(mpz_cmp_si(p,i)>0)
			{
				mpz_mul(res, res, n);
				//gmp_printf("%Zd^%Zd = %Zd", &n, &p, &res);
				i++;
			}
			mpz_set(n, res);
		}
		
	mpz_sub(n,n,d);
		
//////////////////////////////////////////////////////////////////////////////////////////

	printf("Combien de fois voulez-vous répéter les tests : ");
    gmp_scanf("%Zd", &k);
    printf("\n");
    
    if(mpz_cmp_si(k,0)<=0)
	{
		gmp_printf("On ne peut pas répéter %Zd fois une opération !", &k);
		printf("\n");
		mpz_clear(n);
		mpz_clear(p);
		mpz_clear(res);
		return 0;
	}
	
	printf("test de Fermat : ");
	if (Fermat(n, k) == 0)
	{
		printf("Le nombre est premier\n");
	}
	
	else
	{
		printf("Le nombre n'est pas premier\n");
	}
	
	printf("\n");
	printf("test de Miller-Rabin : ");
	
	int a = miller(n,k);

	if (a == 1){
		printf("Le nombre est premier\n");
	}else{
		printf("le nombre est composé\n");
	}
	
	printf("\n");
	
	mpz_clear(n);
	mpz_clear(k);
	mpz_clear(p);
	mpz_clear(res);
	mpz_clear(d);
	return 0;

}

