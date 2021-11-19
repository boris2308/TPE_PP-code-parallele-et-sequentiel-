#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int serial();
void difusion(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator);


int main (int argc, char** argv){
    MPI_Init(NULL, NULL);

    double start, end, tt_time;
    int n_count = 5;
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    start = MPI_Wtime();
    int data;
    if (world_rank == 0){
        data = serial();
        difusion(&data, world_size, MPI_INT, 1, MPI_COMM_WORLD);

    }
    else{
        difusion(&data, world_size, MPI_INT, 0, MPI_COMM_WORLD);

    }
    end = MPI_Wtime();

    tt_time = (end-start);

    printf("le temps parallele: %lf", tt_time);

    MPI_Finalize();

}

int serial(){
    int taille = 0;
    clock_t start = clock();
    printf("entrez la taille du tab  ");
    scanf("%d", &taille);
        int tab[taille];
    for (int i = 0; i < taille; i++)
        {
            printf("entrez la donnée numero %d : ", i);
            scanf("%d", &tab[i]);

        }
        int dmin = tab[0]-tab[1];
    for (int i = 0; i < taille; i++)
        {
            for (int j = i+1; i < taille; i++)
            {
                if ((tab[i] - tab[j]) < dmin)
                {
                    dmin = tab[i] - tab [j];
                }
            }
        }
    printf("%d", dmin);
    clock_t stop = clock();
    double temp_ecoulez = ((stop-start));
    printf("temps_ecoulez : %lf", temp_ecoulez);

}

void difusion (void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
    {
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);

        if(world_rank == root){
            for(int i=0; i < world_size; i++)
            {
                if (world_rank != i)
                {
                    MPI_Send(data, count, datatype, i, 0, communicator);
                }
            }
        }

        else 
        {
            MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
        }
    }