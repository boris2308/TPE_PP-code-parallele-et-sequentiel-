
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(int argc, char** argv) 
    {
        int taille = 0;
        clock_t start = clock();
        printf("entrez la taille du tab  ");
        scanf("%d",&taille);
           int tab[taille];
        for (int i = 0; i < taille; i++)
            { 
                printf("entrez la donnée numero %d : ",i);
                scanf("%d",&tab[i]);
            }
             int dmin = tab[0]- tab[1];
        for(int i = 0; i < taille; i++)
            {
                for(int j = i+1; i < taille; i++)
                {
                    if((tab[i] -tab[j]) < dmin)
                    {
                        dmin = tab[i]-tab[j];
                    }
                }
            } 

        printf("%d",dmin);
        clock_t stop = clock();
        double temp_ecoulez = ((stop-start));
        printf(" temp_ecoulez : %f",temp_ecoulez);
    }