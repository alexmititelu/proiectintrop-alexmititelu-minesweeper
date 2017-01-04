#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
struct tablou
{
    int nrLinii,nrColoane,nrMine;
    char valoare[100][100];
};
struct tablouLive
{
    int nrLinii,nrColoane,nrMine,nrFlaguri;
    char valoare[100][100];
};
void creareTablou(tablou &A)
{
    int i,j;
    for(i=1; i<=A.nrLinii; i++)
        for(j=1; j<=A.nrColoane; j++)
            A.valoare[i][j]='0';
    for(j=0; j<=A.nrColoane+1; j++)
    {
        A.valoare[0][j]='!';
        A.valoare[A.nrLinii+1][j]='!';
    }
    for(i=1; i<=A.nrLinii; i++)
    {
        A.valoare[i][0]='!';
        A.valoare[i][A.nrColoane+1]='!';
    }
}

void generareHarta(tablou &A)
{
    srand(time(NULL));
    for(int i=1; i<=A.nrMine;)
    {
        int x=rand()%A.nrLinii+1;
        int y=rand()%A.nrColoane+1;
        if(A.valoare[x][y]=='0')
        {
            A.valoare[x][y]='*';
            i++;
        }
    }
}
int nrMineVecine(int x,int y, tablou A)
{
    int nr=0;
    int v[]={-1,-1,0,1,1,1,0,-1},t[]={0,1,1,1,0,-1,-1,-1};
    for(int i=0;i<=7;i++)
        if(A.valoare[x+v[i]][y+t[i]]=='*')
            nr++;
    return nr;

}
void completareTablou(tablou &A)
{
    for(int i=1;i<=A.nrLinii;i++)
        for(int j=1;j<=A.nrColoane;j++)
            if(A.valoare[i][j]!='*')
                A.valoare[i][j]=nrMineVecine(i,j,A)+'0';
}
void construireTablouLive(tablou A,tablouLive &AUX)
{
    AUX.nrLinii=A.nrLinii;
    AUX.nrColoane=A.nrColoane;
    AUX.nrMine=A.nrMine;
    AUX.nrFlaguri=0;
    for(int i=1; i<=AUX.nrLinii; i++)
        for(int j=1; j<=AUX.nrColoane; j++)
            AUX.valoare[i][j]='-';

}
void afisareTablouLive(tablouLive AUX)
{
    cout<<"====================="<<endl<<endl;
    for(int i=1; i<=AUX.nrLinii; i++)
    {
        for(int j=1; j<=AUX.nrColoane; j++)
            cout<<AUX.valoare[i][j];
        cout<<endl;
    }
    cout<<endl<<"~~~~~~"<<"Flags:"<<AUX.nrFlaguri<<"/"<<AUX.nrMine<<endl;
}


int main()
{
    tablou test;
    tablouLive Aux;
    test.nrLinii=9;
    test.nrColoane=9;
    test.nrMine=9;
    creareTablou(test);
    generareHarta(test);
    for(int i=1; i<=test.nrLinii; i++)
    {
        for(int j=1; j<=test.nrColoane; j++)
            cout<<test.valoare[i][j]<<" ";
        cout<<endl;
    }
    cout<<"!!!!!!!!!!"<<endl;
    construireTablouLive(test,Aux);
    afisareTablouLive(Aux);
    completareTablou(test);
     for(int i=1; i<=test.nrLinii; i++)
    {
        for(int j=1; j<=test.nrColoane; j++)
            cout<<test.valoare[i][j]<<" ";
        cout<<endl;
    }



}
