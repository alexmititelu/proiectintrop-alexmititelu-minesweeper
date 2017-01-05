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
    int v[]= {-1,-1,0,1,1,1,0,-1},t[]= {0,1,1,1,0,-1,-1,-1};
    for(int i=0; i<=7; i++)
        if(A.valoare[x+v[i]][y+t[i]]=='*')
            nr++;
    return nr;

}
tablou solutie;
void completareTablou(tablou &A,tablou &solutie)
{
    for(int i=1; i<=A.nrLinii; i++)
        for(int j=1; j<=A.nrColoane; j++)
            if(A.valoare[i][j]!='*')
                A.valoare[i][j]=nrMineVecine(i,j,A)+'0';
    solutie=A;
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
int gameOver=0;
void deschideCelula(int x,int y,tablou &A,tablouLive &AUX)
{
    if(A.valoare[x][y]=='*')
        gameOver=1;
    else if(A.valoare[x][y]=='0')
    {
        A.valoare[x][y]='M';
        AUX.valoare[x][y]='0';
        int v[]= {-1,-1,0,1,1,1,0,-1};
        int t[]= {0,1,1,1,0,-1,-1,-1};
        for(int i=0; i<=7; i++)
            deschideCelula(x+v[i],y+t[i],A,AUX);
    }
    else if(A.valoare[x][y]!='*'&&A.valoare[x][y]!='M')
    {
        AUX.valoare[x][y]=A.valoare[x][y];
        A.valoare[x][y]='M';
    }
}
int verificare(tablou A)
{
    for(int i=1; i<=A.nrLinii; i++)
        for(int j=1; j<=A.nrColoane; j++)
            if(A.valoare[i][j]>='0'&&A.valoare[i][j]<='8')
                return 1;
    return 0;
}

void adaugareFlag(int x,int y,tablou &A,tablouLive &AUX)
{
    if(A.valoare[x][y]>='M'&&A.valoare[x][y]<='W')
        {
            if(AUX.valoare[x][y]!='P')
             cout<<'\a'<<"Celula a fost deja deschisa si nu poate fi marcata cu un Flag!"<<endl;
            else
            {
            A.valoare[x][y]=A.valoare[x][y]-'P'+'0';
            AUX.valoare[x][y]='-';
            AUX.nrFlaguri--;
            }

        }
    else if(AUX.nrFlaguri<AUX.nrMine)
    {
        A.valoare[x][y]='P'+A.valoare[x][y]-'0';
        AUX.valoare[x][y]='P';
        AUX.nrFlaguri++;
    }
    else
        cout<<'\a'<<"A fost atins numarul maxim de Flaguri!"<<endl;
}

void gameStart(tablou &A, tablouLive &AUX)
{
    int x,y;
    char raspuns;
    while(gameOver!=1&&verificare(A)!=0)
    {
        cout<<"Daca doriti sa deschideti o celula, apasati tasta 'D'"<<endl<<"Daca doriti sa marcati o celula cu un Flag, apasati tasta 'F'"<<endl;
        cin>>raspuns;
        if(raspuns=='D')
        {
        cout<<"Ce celula doriti sa deschideti?"<<endl;
        cout<<"x:";
        cin>>x;
        cout<<"y:";
        cin>>y;
        cout<<endl;
        if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
            cout<<'\a'<<"Pozitii incorecte!";
        else
            deschideCelula(x,y,A,AUX);
        }
        else
            if(raspuns=='F')
        {
             cout<<"Ce celula vreti sa fie marcata cu un Flag?"<<endl;
        cout<<"x:";
        cin>>x;
        cout<<endl<<"y:";
        cin>>y;
        if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
            cout<<'\a'<<"Pozitii incorecte!";
            else
                adaugareFlag(x,y,A,AUX);
        }
            cout<<endl;
            for(int i=1; i<=A.nrLinii; i++)
            {
                for(int j=1; j<=A.nrColoane; j++)
                    cout<<A.valoare[i][j]<<" ";
                cout<<endl;
            }
            cout<<"Am afisat tabloul solutie"<<endl;
            afisareTablouLive(AUX);
            cout<<"Am afisat tabloul auxiliar!"<<endl;
    }
}

int main()
{
    tablou test,solutie;
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
    completareTablou(test,solutie);
    for(int i=1; i<=test.nrLinii; i++)
    {
        for(int j=1; j<=test.nrColoane; j++)
            cout<<test.valoare[i][j]<<" ";
        cout<<endl;
    }
    //cout<<endl<<endl<<endl<<"PPPPPPPPPPPPPP"<<endl;
    gameStart(test,Aux);



}
