#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <cstring>
#include <ctype.h>
#include <fstream>
using namespace std;
int mesaj,gameOver=0,win=0;
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
    int x[101],y[101];
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
                cout<<char('A'+j-1)<<" ";
            else if(i==0&&j==0)
                cout<<"  ";
            else
                cout<<char('A'+i-1)<<" ";
        cout<<endl<<endl;
    }
    cout<<endl<<"Flags:"<<AUX.nrFlaguri<<"/"<<AUX.nrMine<<endl<<endl;
}
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
    for(int i=1; i<=AUX.nrMine; i++)
        if(AUX.valoare[mine.x[i]][mine.y[i]]=='-')
            AUX.valoare[mine.x[i]][mine.y[i]]='*';
        else
            AUX.valoare[mine.x[i]][mine.y[i]]='X';


}
void gameStart(tablou &A, tablouLive &AUX)
{
    int x,y,valid;
    char raspuns[20],coordX[20],coordY[20];
    while(gameOver!=1&&verificare(A)!=0)
    {
        valid=1;
        cout<<"Daca doriti sa deschideti o celula, apasati tasta 'D'"<<endl<<"Daca doriti sa marcati o celula cu un Flag, apasati tasta 'F'"<<endl;
        cin>>raspuns;
        if((raspuns[0]=='D' || raspuns[0]=='d')&&raspuns[1]==NULL)
        {
            cout<<"Ce celula doriti sa deschideti?"<<endl;
            cout<<"x:";
            cin.get();
            cin>>coordX;
            cout<<"y:";
            cin.get();
            cin>>coordY;
            cout<<endl;
            if(coordX[1]!=NULL || coordY[1]!=NULL)
            {
                valid=0;
                actualizareMesaj(mesaj,1);
            }
            if(valid==1)
            {
                strupr(coordX);
                strupr(coordY);
                x=coordX[0]-'A'+1;
                y=coordY[0]-'A'+1;
                if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
                    actualizareMesaj(mesaj,1);
                else if(A.valoare[x][y]=='*'||(A.valoare[x][y]>='0'&&A.valoare[x][y]<'9'))
                    deschideCelula(x,y,A,AUX);
                else
                    actualizareMesaj(mesaj,2);
            }
        }
        else if((raspuns[0]=='F'||raspuns[0]=='f')&&raspuns[1]==NULL)
        {
            cout<<"Ce celula vreti sa fie marcata cu un Flag?"<<endl;
            cout<<"x:";
            cin.get();
            cin>>coordX;
            cout<<"y:";
            cin.get();
            cin>>coordY;
            cout<<endl;
            if(coordX[1]!=NULL || coordY[1]!=NULL)
            {
                valid=0;
                actualizareMesaj(mesaj,1);
            }
            if(valid==1)
            {
                strupr(coordX);
                strupr(coordY);
                x=coordX[0]-'A'+1;
                y=coordY[0]-'A'+1;
                if(!(x>=1&&x<=A.nrLinii&&y>=1&&y<=A.nrColoane))
                    actualizareMesaj(mesaj,1);
                else
                    adaugareFlag(x,y,A,AUX);
            }
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
void sfarsitJoc(tablou A,tablouLive AUX,tablou solutie,int &win)
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
    {
        cout<<"Felicitari!"<<endl<<"Ati castigat jocul!";
        win=1;
    }

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
void alegeDificultate(tablou &A,int &record)
{
    char nivel[20];
    cout<<"Pentru a juca pe nivelul 'BEGINNER', apasa tasta '1'"<<endl;
    cout<<"Pentru a juca pe nivelul 'INTERMEDIATE', apasa tasta '2'"<<endl;
    cout<<"Pentru a juca pe nivelul 'EXPERT', apasa tasta '3'"<<endl;
    cin>>nivel;
    if(nivel[1]!=NULL || nivel[0]>'3' || nivel[0]<'1')
        A.nrMine=0;
    else if(nivel[0]=='1')
    {
        A.nrLinii=9;
        A.nrColoane=9;
        A.nrMine=10;
    }
    else if(nivel[0]=='2')
    {
        A.nrLinii=16;
        A.nrColoane=16;
        A.nrMine=40;
    }
    else if(nivel[0]=='3')
    {
        A.nrLinii=20;
        A.nrColoane=24;
        A.nrMine=99;
    }
    record=nivel[0]-'0';
}
/*
void afisareTimp(int nrSecunde)
{
    nrSecunde=nrSecunde/1000;
    int nrOre=0;
    int nrMinute=0;
    if(nrSecunde>=60)
    {
        nrMinute=nrSecunde/60;
        nrSecunde=nrSecunde%60;
    }
    if(nrMinute>=60)
    {
        nrOre=nrMinute/60;
        nrMinute=nrMinute%60;
    }
    cout<<endl<<"Ai rezolvat puzzle-ul in ";
    if(nrOre>0)
    {
        cout<<nrOre<<" ore";
        if(nrMinute>0||nrSecunde>0)
            cout<<", ";
        else
            cout<<".";
    }
    if(nrMinute>0)
    {
        cout<<nrMinute<<" minute";
        if(nrSecunde>0)
            cout<<", ";
        else
            cout<<".";
    }
    if(nrSecunde>0)
        cout<<nrSecunde<<".";
}
*/
void newRecord(int nrSecunde,int fisier)
{
    if(fisier==1)
    {
        ifstream fin("beginner.txt");
        int secundeRecord;
        fin>>secundeRecord;
        if(nrSecunde<secundeRecord || secundeRecord==0)
        {
            fin.close();
            ofstream fout("beginner.txt");
            fout<<nrSecunde<<endl;
            Sleep(500);
            cout<<endl;
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<"."<<endl;
            cout<<"Felicitari!! Ati stabilit un nou record pentru acest nivel!"<<endl;
            cout<<endl<<"Care este numele dumneavoastra?"<<endl;
            char numeNou[100];
            cin.get();
            cin.getline(numeNou,100);
            fout<<numeNou;
            fout.close();
        }
    }
    else if(fisier==2)
    {
        ifstream fin("intermediate.txt");
        int secundeRecord;
        fin>>secundeRecord;
        if(nrSecunde<secundeRecord || secundeRecord==0)
        {
            fin.close();
            ofstream fout("intermediate.txt");
            fout<<nrSecunde<<endl;
            Sleep(500);
            cout<<endl;
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<"."<<endl;
            cout<<"Felicitari!! Ati stabilit un nou record pentru acest nivel!"<<endl;
            cout<<endl<<"Care este numele dumneavoastra?"<<endl;
            char numeNou[100];
            cin.get();
            cin.getline(numeNou,100);
            fout<<numeNou;
            fout.close();
        }
    }
    else if(fisier==3)
    {
        ifstream fin("expert.txt");
        int secundeRecord;
        fin>>secundeRecord;
        if(nrSecunde<secundeRecord || secundeRecord==0)
        {
            fin.close();
            ofstream fout("expert.txt");
            fout<<nrSecunde<<endl;
            Sleep(500);
            cout<<endl;
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<"."<<endl;
            cout<<"Felicitari!! Ati stabilit un nou record pentru acest nivel!"<<endl;
            cout<<endl<<"Care este numele dumneavoastra?"<<endl;
            char numeNou[100];
            cin.get();
            cin.getline(numeNou,100);
            fout<<numeNou;
            fout.close();
        }
    }
}
void afisareRecord(int record)
{
    int nrSecunde;
    char nume[100];
    if(record==1)
    {
        ifstream fin("beginner.txt");
        fin>>nrSecunde;
        if(nrSecunde!=0)
        {
            fin.get();
            fin.getline(nume,100);
            cout<<endl<<"Pentru acest nivel (Beginner) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<". Puzzle-ul a fost rezolvat de";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(1000);
            cout<<" "<<nume<<"."<<endl;
            Sleep(2000);
            fin.close();
        }
    }
    else if(record==2)
    {
        ifstream fin("intermediate.txt");
        fin>>nrSecunde;
        if(nrSecunde!=0)
        {
            fin.get();
            fin.getline(nume,100);
            cout<<endl<<"Pentru acest nivel (Intermediate) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<". Puzzle-ul a fost rezolvat de";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(1000);
            cout<<" "<<nume<<"."<<endl;
            Sleep(2000);
            fin.close();
        }
    }
    else if(record==3)
    {
        ifstream fin("expert.txt");
        fin>>nrSecunde;
        if(nrSecunde!=0)
        {
            fin.get();
            fin.getline(nume,100);
            cout<<endl<<"Pentru acest nivel (Expert) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<". Puzzle-ul a fost rezolvat de";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(500);
            cout<<".";
            Sleep(1000);
            cout<<" "<<nume<<"."<<endl;
            Sleep(2000);
            fin.close();
        }
    }
}
void intrebareJucator()
{
    char raspuns[100];
    cout<<"Doriti sa incepeti jocul?"<<endl<<"D / N"<<endl;
    cin>>raspuns;
    if((raspuns[0]=='D' || raspuns[0]=='d')&&raspuns[1]==NULL)
    {
        int nrSecunde=0,record;
        clock_t this_time=clock();
        clock_t last_time=this_time;
        tablou A;
        tablouLive AUX;
        alegeDificultate(A,record);
        while(A.nrMine==0)
            alegeDificultate(A,record);
        afisareRecord(record);
        creareTablou(A);
        generareHarta(A);
        construireTablouLive(A,AUX);
        cout<<endl<<"Jocul va incepe in 7 secunde..."<<endl<<endl;
        Sleep(2000);
        cout<<endl<<"Jocul va incepe in 5 secunde..."<<endl<<endl;
        Sleep(2000);
        cout<<endl<<'\a'<<"Jocul va incepe in 3 secunde..."<<endl;
        Sleep(1000);
        cout<<endl<<'\a'<<"Jocul va incepe in 2 secunde..."<<endl;
        Sleep(1000);
        char smiley=1;
        cout<<endl<<'\a'<<"Start joc! Mult succes!  "<<smiley<<endl<<endl;
        Sleep(1000);
        afisareTablouLive(AUX);
        completareTablou(A,solutie);
        gameStart(A,AUX);
        sfarsitJoc(A,AUX,solutie,win);
        if(win==1)
        {
            this_time=clock();
            nrSecunde=(nrSecunde+(this_time-last_time))/1000;
            //afisareTimp(nrSecunde);
            cout<<endl<<"Ai rezolvat puzzle-ul in "<<nrSecunde<<" secunde.";

            if(A.nrMine==10)
                newRecord(nrSecunde,1);
            else if(A.nrMine==40)
                newRecord(nrSecunde,2);
            else if(A.nrMine==99)
                newRecord(nrSecunde,3);
            win=0;
        }

        /* cout<<"Solutia este............."<<endl;
         for(int i=1; i<=solutie.nrLinii; i++)
             {
                 for(int j=1; j<=solutie.nrColoane; j++)
                     cout<<solutie.valoare[i][j]<<" ";
                 cout<<endl;
             }
             */

    }
    else if((raspuns[0]=='N'||raspuns[0]=='n')&&raspuns[1]==NULL)
        return;
    else
        intrebareJucator();
    if(gameOver==1)
    {
        cout<<endl<<endl;
        cout<<"Doriti sa jucati din nou?"<<endl;
        cout<<"Daca da, apasati tasta 'D', altfel, apasati tasta 'N'."<<endl;
        cin>>raspuns;
        if((raspuns[0]=='D'||raspuns[0]=='d') && raspuns[1]==NULL)
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
