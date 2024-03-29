#include <iostream>
#include <mpi.h>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>
using std::cout;
using std::endl;
using std:: vector;


//la dimensione della matrice deve essere un multiplo del numero di processori; parto con 4 processori e una matrice (8X8)


void Transpose(int** Matrix,int rank,int size,const int N);



int main(int argc, char ** argv)
{ 
    int rank;
    int size;
    const int N = 8;
    int** MatrixGeneration(int N);
    int** Matrix = MatrixGeneration(N);
    

    MPI::Init(argc, argv);
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    
    if (size <= 1)
    {
         cout << "Error!: you are running a serial code" << endl;
         MPI::COMM_WORLD.Abort(1);
    }
    else if ((N % size) != 0)
    {
        if (rank == 0)
        {
            cout << "Error!: Matrix dimension should be a multiple of process number" << endl;
        }
                
        MPI::COMM_WORLD.Abort(1);
    }
    else 
    {
        
        Transpose(Matrix, rank,size,N);   

    }

    MPI::Finalize();
    return 0;
}


int** MatrixGeneration(int N)
{ 
    //Create an array of pointers with size 3.
    int** arr = new int* [N];

    //Each pointer points to an array with size 3.
    for (int i = 0; i < N; i++)
    {
        arr[i] = new int[N];
    }


    cout << "The input matrix is: " << endl;

    // Use current time as seed for random generator
    srand(time(0));
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            arr[i][j] = rand();
            cout << arr[i][j] << " ";
            
        }
        cout << endl;
    }
    
    return arr;
}

void Transpose(int** Matrix,int rank,int size,const int N) 
{    
    int Rapp =  N /size ;

    int** LoMat = new int* [N];

    for (int i = 0; i < N; i++)
    {
        LoMat[i] = new int[N];
    }

    for (int proc=0; proc<size; proc++) 
    {
        if (proc == rank) 
        {
            cout << rank << endl;
           cout << "il rank è: " << rank << endl;
           if (rank == 0)
           {
              for (int i = 0; i <Rapp ; i++)
              {
                for (int j = 0; j < N ; j++)
                {
                 LoMat[i][j] = Matrix[i][j];
                 cout <<  LoMat[i][j] << " ";                       
                }
                cout <<  endl;    
              }
              cout <<  endl;
           }
           else
           {
              for (int i = 0; i <Rapp ; i++)
              {  
                 for (int j = 0; j < N; i++)
                 {
                   LoMat[i][j] = Matrix[i*Rapp][j];
                   cout <<  LoMat[i][j] << " ";                         
                 }
               cout <<  endl;   
              }
             cout <<  endl;
           }
           

        }
        //MPI_Barrier(MPI_COMM_WORLD);
    }

}

