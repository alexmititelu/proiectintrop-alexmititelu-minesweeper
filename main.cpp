#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;
int mesaj;
struct tablou
{
    int nrLinii,nrColoane,nrMine;
    char valoare[100][100];
} solutie;
struct tablouLive
{
    int nrLinii,nrColoane,nrMine,nrFlaguri;
    char valoare[100][100];
};
struct coordonate
{
    int x[100],y[100];
} mine;
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
            mine.x[i]=x;
            mine.y[i]=y;
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
void completareTablou(tablou &A,tablou &solutie)
{
    solutie.nrLinii=A.nrLinii;
    solutie.nrColoane=A.nrColoane;
    solutie.nrMine=A.nrMine;
    for(int i=1; i<=A.nrLinii; i++)
        for(int j=1; j<=A.nrColoane; j++)
            if(A.valoare[i][j]!='*')
            {
                A.valoare[i][j]=nrMineVecine(i,j,A)+'0';
                solutie.valoare[i][j]=A.valoare[i][j];
            }
            else
                solutie.valoare[i][j]='P';
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
void afisareMesajLive(int &mesaj)
{
    if(mesaj==1)
        cout<<'\a'<<"Pozitii incorecte!"<<endl;
    if(mesaj==2)
        cout<<'\a'<<"Celula a fost deja deschisa!"<<endl;
    if(mesaj==3)
        cout<<'\a'<<"Celula a fost deja deschisa si nu poate fi marcata cu un Flag!"<<endl;
    if(mesaj==4)
        cout<<'\a'<<"A fost atins numarul maxim de Flaguri!"<<endl;
    cout<<endl;
    mesaj=0;
}
void actualizareMesaj(int &mesaj,int mesajNou)
{
    mesaj=mesajNou;
}
void afisareTablouLive(tablouLive AUX)
{
    if(system("CLS"))
        system("clear");
    Sleep(0);

    afisareMesajLive(mesaj);
    for(int i=0; i<=AUX.nrLinii; i++)
    {
        for(int j=0; j<=AUX.nrColoane; j++)
            if(i>0&&j>0)
                cout<<AUX.valoare[i][j]<<" ";
            else if(i==0&&j>0)
                cout<<j<<" ";
            else if(i==0&&j==0)
                cout<<"  ";
            else
                cout<<i<<" ";
        cout<<endl<<endl;
    }
    cout<<endl<<"Flags:"<<AUX.nrFlaguri<<"/"<<AUX.nrMine<<endl<<endl;
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
            if((A.valoare[i][j]>='0'&&A.valoare[i][j]<='8') ||A.valoare[i][j]=='*')
                return 1;
    return 0;
}

void adaugareFlag(int x,int y,tablou &A,tablouLive &AUX)
{
    if(A.valoare[x][y]>='M'&& A.valoare[x][y]<='X')
    {
        if(AUX.valoare[x][y]!='P')
            actualizareMesaj(mesaj,3);
        if(AUX.valoare[x][y]=='P')
        {
            if(A.valoare[x][y]!='X')
                A.valoare[x][y]=A.valoare[x][y]-'P'+'0';
            else
                A.valoare[x][y]='*';
            AUX.valoare[x][y]='-';
            AUX.nrFlaguri--;
        }
    }
    else if(AUX.nrFlaguri<AUX.nrMine)
    {
        if(A.valoare[x][y]!='*')
            A.valoare[x][y]='P'+A.valoare[x][y]-'0';
        else
            A.valoare[x][y]='X';
        AUX.valoare[x][y]='P';
        AUX.nrFlaguri++;
    }
    else
        actualizareMesaj(mesaj,4);
}
int victorie(tablou A,tablouLive &AUX)
{
    if(AUX.nrFlaguri<AUX.nrMine)
        return 0;
    for(int i=1; i<=AUX.nrLinii; i++)
        for(int j=1; j<=AUX.nrColoane; j++)
            if(AUX.valoare[i][j]!=solutie.valoare[i][j])
                return 0;
    return 1;
}
void afisareMine(tablouLive &AUX)
{
    /*for(int i=1; i<=AUX.nrLinii; i++)
        for(int j=1; j<=AUX.nrColoane; j++)
            if(solutie.valoare[i][j]=='*' && AUX.valoare[i][j]=='P')
                    AUX.valoare[i][j]='X';
                else
                    if(solutie.valoare[i][j]=='*')
                    AUX.valoare[i][j]='*';
                    */
    /*for(int i=1; i<=AUX.nrLinii; i++)
        cout<<mine.x[i]<<" "<<mine.y[i]<<endl;*/
    for(int i=1; i<=AUX.nrLinii; i++)
        if(AUX.valoare[mine.x[i]][mine.y[i]]=='-')
            AUX.valoare[mine.x[i]][mine.y[i]]='*';
        else
            AUX.valoare[mine.x[i]][mine.y[i]]='X';


}
void gameStart(tablou &A, tablouLive &AUX)
{
    int x,y;
    char raspuns;
    while(gameOver!=1&&verificare(A)!=0)
    {
        cout<<"Daca doriti sa deschideti o celula, apasati tasta 'D'"<<endl<<"Daca doriti sa marcati o celula cu un Flag, apasati tasta 'F'"<<endl;
        cin>>raspuns;
        if(raspuns=='D' || raspuns=='d')
        {
            cout<<"Ce celula doriti sa deschideti?"<<endl;
            cout<<"x:";
            cin>>x;
            cout<<"y:";
            cin>>y;
            cout<<endl;
            if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
                actualizareMesaj(mesaj,1);
            else if(A.valoare[x][y]=='*'||(A.valoare[x][y]>='0'&&A.valoare[x][y]<'9'))
                deschideCelula(x,y,A,AUX);
            else
                actualizareMesaj(mesaj,2);
        }
        else if(raspuns=='F'||raspuns=='f')
        {
            cout<<"Ce celula vreti sa fie marcata cu un Flag?"<<endl;
            cout<<"x:";
            cin>>x;
            cout<<endl<<"y:";
            cin>>y;
            if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
                actualizareMesaj(mesaj,1);
            else
                adaugareFlag(x,y,A,AUX);

        }
        cout<<endl;
        /* for(int i=1; i<=A.nrLinii; i++)
         {
             for(int j=1; j<=A.nrColoane; j++)
                 cout<<A.valoare[i][j]<<" ";
             cout<<endl;
         }
         */
        afisareTablouLive(AUX);
    }
}
void sfarsitJoc(tablou A,tablouLive AUX,tablou solutie)
{
    char raspuns;
    if(gameOver==1)
    {
        if(system("CLS"))
            system("clear");
        afisareMine(AUX);
        afisareTablouLive(AUX);
        cout<<"Ati pierdut!"<<endl;
    }
    if(victorie(A,AUX)==1)
        cout<<"Felicitari!"<<endl<<"Ati castigat jocul!";

   /* cout<<endl<<endl;
    cout<<"Doriti sa jucati din nou?"<<endl;
    cout<<"Daca da, apasati tasta 'D', altfel, apasati tasta 'N'."<<endl;
    cin>>raspuns;
    if(raspuns=='D')
    {
        gameOver=0;
        creareTablou(A);
        generareHarta(A);
        construireTablouLive(A,AUX);
        completareTablou(A,solutie);
        afisareTablouLive(AUX);
        gameStart(A,AUX);

    }
*/
    /*       for(int i=1; i<=solutie.nrLinii; i++)
      {
          for(int j=1; j<=solutie.nrColoane; j++)
              cout<<solutie.valoare[i][j]<<" ";
          cout<<endl;
      }
      */

}
void intrebareJucator()
{
    char raspuns;
    cout<<"Doriti sa incepeti jocul?"<<endl<<"D / N"<<endl;
    cin>>raspuns;
    if(raspuns=='D' || raspuns=='d')
    {
        tablou A;
        tablouLive AUX;
        A.nrLinii=9;
        A.nrColoane=9;
        A.nrMine=9;
        creareTablou(A);
        generareHarta(A);

        construireTablouLive(A,AUX);
        afisareTablouLive(AUX);
        completareTablou(A,solutie);
        gameStart(A,AUX);
        sfarsitJoc(A,AUX,solutie);
        /* cout<<"Solutia este............."<<endl;
         for(int i=1; i<=solutie.nrLinii; i++)
             {
                 for(int j=1; j<=solutie.nrColoane; j++)
                     cout<<solutie.valoare[i][j]<<" ";
                 cout<<endl;
             }
             */

    }
    else
        if(raspuns=='N'||raspuns=='n')
            return;
    cout<<endl<<endl;
    cout<<"Doriti sa jucati din nou?"<<endl;
    cout<<"Daca da, apasati tasta 'D', altfel, apasati tasta 'N'."<<endl;
    cin>>raspuns;
    if(raspuns=='D')
    {
       /* gameOver=0;
        creareTablou(A);
        generareHarta(A);
        construireTablouLive(A,AUX);
        completareTablou(A,solutie);
        afisareTablouLive(AUX);
        gameStart(A,AUX);
        */
        gameOver=0;
        intrebareJucator();
    }



}

int main()
{
    //  intrebareJucator();
    // tablou test;
    // tablouLive Aux;
    /* tablou test,solutie;
     tablouLive Aux;
     test.nrLinii=9;
     test.nrColoane=9;
     test.nrMine=9;*/
    //  creareTablou(test);
    //  generareHarta(test);
    /*solutie.nrLinii=test.nrLinii;
    solutie.nrColoane=test.nrColoane;
    for(int i=1;i<=solutie.nrLinii;i++)
        for(int j=1;j<=solutie.nrColoane;j++)
            solutie.valoare[i][j]=test.valoare[i][j];

    */

    /* for(int i=1; i<=test.nrLinii; i++)
     {
         for(int j=1; j<=test.nrColoane; j++)
             cout<<test.valoare[i][j]<<" ";
         cout<<endl;
     }
     cout<<"!!!!!!!!!!"<<endl;*/
    // construireTablouLive(test,Aux);
    // afisareTablouLive(Aux);
    // completareTablou(test,solutie);
    // gameStart(test,Aux);
    /*for(int i=1; i<=9; i++)
        cout<<mine.x[i]<<" "<<mine.y[i]<<endl;*/
    /*    for(int i=1; i<=solutie.nrLinii; i++)
       {
           for(int j=1; j<=solutie.nrColoane; j++)
               cout<<solutie.valoare[i][j]<<" ";
           cout<<endl;
       }
       */
    intrebareJucator();

}
