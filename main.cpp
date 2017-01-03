#include <iostream>

using namespace std;
void creareTablou(int A[100][100],int nrLinii,int nrColoane)
{
    int i,j;
    for(i=1;i<=nrLinii;i++)
        for(j=1;j<=nrColoane;j++)
            A[i][j]=0;
    for(j=0;j<=nrColoane+1;j++)
    {
        A[0][j]=-1;
        A[nrLinii+1][j]=-1;
    }
    for(i=1;i<=nrLinii;i++)
    {
        A[i][0]=-1;
        A[i][nrColoane+1]=-1;
    }
}

void generareHarta(int A[100][100],int dificultate)
{

}
int main()
{
    int tablou[100][100],nrLinii,nrColoane,i,j;
    nrLinii=9;
    nrColoane=9;
    creareTablou(tablou,16,9);
    for(i=1;i<=nrLinii;i++)
        {
            for(j=1;j<=nrColoane;j++)
            cout<<tablou[i][j]<<" ";
            cout<<endl;
        }
}
