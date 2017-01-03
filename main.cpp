#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct tablou
{
    int nrLinii,nrColoane,nrMine;
    int valoare[100][100];
};
void creareTablou(tablou &A)
{
    int i,j;
    for(i=1;i<=A.nrLinii;i++)
        for(j=1;j<=A.nrColoane;j++)
            A.valoare[i][j]=0;
    for(j=0;j<=A.nrColoane+1;j++)
    {
        A.valoare[0][j]=-1;
        A.valoare[A.nrLinii+1][j]=-1;
    }
    for(i=1;i<=A.nrLinii;i++)
    {
        A.valoare[i][0]=-1;
        A.valoare[i][A.nrColoane+1]=-1;
    }
}

void generareHarta(tablou &A)
{
     srand(time(NULL));
        for(int i=1;i<=A.nrMine;)
        {
            int x=rand()%A.nrLinii+1;
            int y=rand()%A.nrColoane+1;
            if(A.valoare[x][y]==0)
            {
                A.valoare[x][y]=9;
                i++;
            }
        }
}
int main()
{
    tablou test;
    test.nrLinii=9;
    test.nrColoane=9;
    test.nrMine=9;
    creareTablou(test);
    generareHarta(test);
    for(int i=1;i<=test.nrLinii;i++)
        {
            for(int j=1;j<=test.nrColoane;j++)
            cout<<test.valoare[i][j]<<" ";
            cout<<endl;
        }


}
