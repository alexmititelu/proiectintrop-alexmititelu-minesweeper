#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <cstring>
#include <ctype.h>
#include <fstream>
#include <mmsystem.h>
using namespace std;
int mesaj,gameOver=0,win=0,languageNr=0;
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
    int x[1000],y[1000];
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
                if(solutie.valoare[i][j]=='0')
                    solutie.valoare[i][j]='-';
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
            AUX.valoare[i][j]=219;

}
void afisareMesajLiveRo(int &mesaj)
{
    if(mesaj==1)
        cout<<'\a'<<"Coordonatele date de dvs. sunt incorecte. Incercati din nou."<<endl;
    if(mesaj==2)
        cout<<'\a'<<"Celula a fost deja deschisa!"<<endl;
    if(mesaj==3)
        cout<<'\a'<<"Celula a fost deja deschisa si nu poate fi marcata cu un Flag!"<<endl;
    if(mesaj==4)
        cout<<'\a'<<"A fost atins numarul maxim de Flaguri!"<<endl;
    cout<<endl;
    mesaj=0;
}
void afisareMesajLiveEn(int &mesaj)
{
    if(mesaj==1)
        cout<<'\a'<<"The coordinates you provided were incorrect. Try again."<<endl;
    if(mesaj==2)
        cout<<'\a'<<"That cell has already been opened!"<<endl;
    if(mesaj==3)
        cout<<'\a'<<"That cell has already been opened and you can't place a Flag here!"<<endl;
    if(mesaj==4)
        cout<<'\a'<<"You reached the maximum number of Flags!"<<endl;
    cout<<endl;
    mesaj=0;
}

void actualizareMesaj(int &mesaj,int mesajNou)
{
    mesaj=mesajNou;
}
void afisareTablouLiveRo(tablouLive AUX)
{
    if(system("CLS"))
        system("clear");
    Sleep(0);

    afisareMesajLiveRo(mesaj);
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
    cout<<endl<<" Flags:"<<AUX.nrFlaguri<<"/"<<AUX.nrMine<<endl<<endl;
}
void afisareTablouLiveEn(tablouLive AUX)
{
    if(system("CLS"))
        system("clear");
    Sleep(0);

    afisareMesajLiveEn(mesaj);
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
    cout<<endl<<" Flags:"<<AUX.nrFlaguri<<"/"<<AUX.nrMine<<endl<<endl;
}
void deschideCelula(int x,int y,tablou &A,tablouLive &AUX)
{
    if(A.valoare[x][y]=='*')
        gameOver=1;
    else if(A.valoare[x][y]=='0')
    {
        A.valoare[x][y]='M';
        AUX.valoare[x][y]='-';
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
            AUX.valoare[x][y]=219;
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
    for(int i=1; i<=AUX.nrMine; i++)
        if(AUX.valoare[mine.x[i]][mine.y[i]]==219)
            AUX.valoare[mine.x[i]][mine.y[i]]='*';
        else
            AUX.valoare[mine.x[i]][mine.y[i]]='X';


}
void gameStartRo(tablou &A, tablouLive &AUX)
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
        afisareTablouLiveRo(AUX);
    }
}
void gameStartEn(tablou &A, tablouLive &AUX)
{
    int x,y,valid;
    char raspuns[20],coordX[20],coordY[20];
    while(gameOver!=1&&verificare(A)!=0)
    {
        valid=1;
        cout<<"If you want to open a cell, type 'O'."<<endl<<"If you want to mark the cell with a Flag, type 'F'."<<endl;
        cin>>raspuns;
        if((raspuns[0]=='O' || raspuns[0]=='o')&&raspuns[1]==NULL)
        {
            cout<<"Which cell would you like to open?"<<endl;
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
            cout<<"Which cell would you like to mark with a Flag?"<<endl;
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
        afisareTablouLiveEn(AUX);
    }
}
void sfarsitJocRo(tablou A,tablouLive AUX,tablou solutie,int &win)
{
    char raspuns;
    if(gameOver==1)
    {
        if(system("CLS"))
            system("clear");
        afisareMine(AUX);
        afisareTablouLiveRo(AUX);
        cout<<"Ati pierdut! "<<endl;
    }
    if(victorie(A,AUX)==1)
    {
        cout<<"Felicitari!"<<endl<<"Ati castigat jocul!";
        win=1;
    }
}
void sfarsitJocEn(tablou A,tablouLive AUX,tablou solutie,int &win)
{
    char raspuns;
    if(gameOver==1)
    {
        if(system("CLS"))
            system("clear");
        afisareMine(AUX);
        afisareTablouLiveEn(AUX);
        cout<<"You lost! "<<endl;
    }
    if(victorie(A,AUX)==1)
    {
        cout<<"Congratulations!"<<endl<<"You won the game!";
        win=1;
    }
}
void alegeDificultateRo(tablou &A,int &record)
{
    int numar=10;
    char raspuns[20];
    char nivel[20];
    cout<<"Pentru a juca pe nivelul 'BEGINNER', apasa tasta '1'"<<endl;
    cout<<"Pentru a juca pe nivelul 'INTERMEDIATE', apasa tasta '2'"<<endl;
    cout<<"Pentru a juca pe nivelul 'EXPERT', apasa tasta '3'"<<endl;
    cout<<"Pentru a juca pe nivelul 'CUSTOM', apasa tasta '4'"<<endl;
    cin>>nivel;
    if(nivel[1]!=NULL || nivel[0]>'4' || nivel[0]<'1')
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
    else if(nivel[0]=='4')
    {
        cout<<endl;
        cout<<"Ce marime doriti sa aiba tabla de joc?";
        cout<<endl<<endl<<"<alegeti un numar intre 2 si 26>";
        cout<<endl<<"Numar linii: ";
        cin>>raspuns;
        int ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);

        while(numar<2||numar>26||ok==0)
        {
            cout<<endl<<'\a'<<"Eroare!";
            cout<<endl<<"<alegeti un numar intre 2 si 26>";
            cout<<endl<<"Numar linii: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrLinii=numar;
        cout<<endl<<"<alegeti un numar intre 2 si 26>";
        cout<<endl<<"Numar coloane: ";
        cin.get();
        cin>>raspuns;
        ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);

        while(numar<2||numar>26||ok==0)
        {
            cout<<endl<<'\a'<<"Eroare!";
            cout<<endl<<"<alegeti un numar intre 2 si 26>";
            cout<<endl<<"Numar coloane: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrColoane=numar;

        cout<<endl<<endl<<"Cate mine doriti sa aiba harta?";
        cout<<endl<<endl<<"<alegeti un numar intre 1 si "<<(A.nrLinii-1)*(A.nrColoane-1)<<">";
        cout<<endl<<"Numar mine: ";
        cin.get();
        cin>>raspuns;
        ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);
        while(numar<1||numar>(A.nrLinii-1)*(A.nrColoane-1)||ok==0)
        {
            cout<<endl<<'\a'<<"Eroare!";
            cout<<endl<<"<alegeti un numar intre 1 si "<<(A.nrLinii-1)*(A.nrColoane-1)<<">";
            cout<<endl<<"Numar mine: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrMine=numar;
    }
    record=nivel[0]-'0';
}

void alegeDificultateEn(tablou &A,int &record)
{
    int numar=10;
    char raspuns[20];
    char nivel[20];
    cout<<"To play the game on 'BEGINNER' difficulty, press '1'"<<endl;
    cout<<"To play the game on 'INTERMEDIATE' difficulty, press '2'"<<endl;
    cout<<"To play the game on 'EXPERT' difficulty, press '3'"<<endl;
    cout<<"To play the game on 'CUSTOM' difficulty, press '4'"<<endl;
    cin>>nivel;
    if(nivel[1]!=NULL || nivel[0]>'4' || nivel[0]<'1')
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
    else if(nivel[0]=='4')
    {
        cout<<endl;
        cout<<"Choose your table size (number of rows & columns) ";
        cout<<endl<<endl<<"<pick a number between 2 and 26>";
        cout<<endl<<"Number of rows: ";
        cin>>raspuns;
        int ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);

        while(numar<2||numar>26||ok==0)
        {
            cout<<endl<<'\a'<<"Error!";
            cout<<endl<<endl<<"<pick a number between 2 and 26>";
            cout<<endl<<"Number of rows: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrLinii=numar;
        cout<<endl<<"<pick a number between 2 and 26>";
        cout<<endl<<"Number of columns: ";
        cin.get();
        cin>>raspuns;
        ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);

        while(numar<2||numar>26||ok==0)
        {
            cout<<endl<<'\a'<<"Error!";
            cout<<endl<<"<pick a number between 2 and 26>";
            cout<<endl<<"Number of columns: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrColoane=numar;

        cout<<endl<<endl<<"Choose the number of mines for your map";
        cout<<endl<<endl<<"<pick a number between 1 and "<<(A.nrLinii-1)*(A.nrColoane-1)<<">";
        cout<<endl<<"Number of mines: ";
        cin.get();
        cin>>raspuns;
        ok=1;
        for(int i=0; i<strlen(raspuns); i++)
            if(raspuns[i]>'9'||raspuns[i]<'0')
                ok=0;
        if(ok==1)
            numar=atoi(raspuns);
        while(numar<1||numar>(A.nrLinii-1)*(A.nrColoane-1)||ok==0)
        {
            cout<<endl<<'\a'<<"Error!";
            cout<<endl<<"<pick a number between 1 and "<<(A.nrLinii-1)*(A.nrColoane-1)<<">";
            cout<<endl<<"Number of mines: ";
            cin.get();
            cin>>raspuns;
            ok=1;
            for(int i=0; i<strlen(raspuns); i++)
                if(raspuns[i]>'9'||raspuns[i]<'0')
                    ok=0;
            if(ok==1)
                numar=atoi(raspuns);
        }
        A.nrMine=numar;
    }
    record=nivel[0]-'0';
}

void newRecordRo(int nrSecunde,int fisier)
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
            cout<<"Felicitari!!";
            PlaySound(TEXT("record.wav"),NULL,SND_SYNC);
            cout<<"Ati stabilit un nou record pentru acest nivel!"<<endl;
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
void newRecordEn(int nrSecunde,int fisier)
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
            cout<<"Congratulations!! You broke the record for this level!"<<endl;
            cout<<endl<<"What's your name?"<<endl;
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
            cout<<"Congratulations!! You broke the record for this level!"<<endl;
            cout<<endl<<"What's your name?"<<endl;
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
            cout<<"Congratulations!! You broke the record for this level!"<<endl;
            cout<<endl<<"What's your name?"<<endl;
            char numeNou[100];
            cin.get();
            cin.getline(numeNou,100);
            fout<<numeNou;
            fout.close();
        }
    }
}

void afisareRecordRo(int record)
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
            cout<<endl<<"Pentru acest nivel (Beginner) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<" secunde"<<endl<<"Puzzle-ul a fost rezolvat de";
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
            cout<<endl<<"Pentru acest nivel (Intermediate) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<endl<<"de secunde. Puzzle-ul a fost rezolvat de";
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
            cout<<endl<<"Pentru acest nivel (Expert) recordul rezolvarii puzzle-ului este de "<<nrSecunde<<" secunde."<<endl<<"Puzzle-ul a fost rezolvat de";
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
void afisareRecordEn(int record)
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
            cout<<endl<<"For this level (Beginner) the record of solving the puzzle is "<<nrSecunde<<" seconds. The puzzle was solved by";
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
            cout<<endl<<"For this level (Beginner) the record of solving the puzzle is "<<nrSecunde<<" seconds. The puzzle was solved by";
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
            cout<<endl<<"For this level (Beginner) the record of solving the puzzle is "<<nrSecunde<<" seconds. The puzzle was solved by";
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
void regulament()
{
    if(languageNr==1)
    {
        cout<<"Minesweeper este un test simplu (dar inselator) de memorie si de rationament."<<endl;
        cout<<"Scopul: de a gasi patrate goale si de a evita minele, marcandu-le cu un steag."<<endl;
        cout<<"Cand toate minele au fost marcate (corect) si toate celelalte celule au fost"<<endl<<"deschise in siguranta, atunci ai castigat jocul."<<endl;

        cout<<endl;
        cout<<"Cand vei deschide o celula, aceasta poate avea diferite valori:"<<endl;
        cout<<"- '*', reprezinta o mina, ai pierdut"<<endl;
        cout<<"- '-', dintre celulele adiacente cu aceasta, niciuna nu reprezinta mina"<<endl;
        cout<<"	! daca deschizi o celula cu valoare nula ('-') atunci se vor deschide"<<endl<<"automat celulele adiacente ei"<<endl;
        cout<<"- 'n', pentru orice n din multimea {1,2,3,4,5,6,7,8}, atunci n dintre celulele"<<endl<<"adiacente cu celula deschisa reprezinta mine"<<endl;
    }
    else if(languageNr==2)
    {

        cout<<"Minesweeper is a deceptively simple test of memory and reasoning."<<endl;
        cout<<"The goal: find the empty squares and avoid the mines. Mark all the mines."<<endl;
        cout<<"When all the mines were marked (correctly) and all the others cells were opened"<<endl<<"then you won the game."<<endl;
        cout<<endl;
        cout<<"When you open a cell, it may have different values:"<<endl;
        cout<<"- '*', represents a mine so you lost"<<endl;
        cout<<"- '-', none of the adjacent cells represents a mine"<<endl;
        cout<<" ! if you open a cell with value '-' (NULL) then the adjacent cells will "<<endl<<"automatcly be opened"<<endl;
        cout<<"- 'n', for any n from M={1,2,3,4,5,6,7,8}, then n adjacent cells with"<<endl<<" the opened cell represents mines"<<endl;
    }
    cout<<endl;
}
void language()
{
    cout<<endl;

    cout<<"   _   _   _   _   _   _   _   _   _   _   _  "<<endl;
    cout<<"  / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ "<<endl;
    cout<<" ( M | I | N | E | S | W | E | E | P | E | R )"<<endl;
    cout<<"  \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/"<<endl;
    cout<<endl<<endl;


    cout<<"Alegeti limba  / Choose your language"<<endl;
    cout<<"         < RO  /  EN >"<<endl;
    char raspuns[4];
    cin>>raspuns;
    strupr(raspuns);
    while(strcmp(raspuns,"RO")!=0&&strcmp(raspuns,"EN"))
    {
        cout<<"Alegeti limba  / Choose your language"<<endl;
        cout<<"         < RO  /  EN >"<<endl;
        cin>>raspuns;
        strupr(raspuns);
    }
    cout<<endl;
    if(strcmp(raspuns,"RO")==0)
        {
            languageNr=1;
            cout<<"Doriti sa cititi regulamentul?"<<endl;
            cout<<"       < DA / NU >"<<endl;
            cin>>raspuns;
            strupr(raspuns);
            while(strcmp(raspuns,"DA")!=0&&strcmp(raspuns,"NU")!=0)
            {
                cout<<endl;
                cout<<"Doriti sa cititi regulamentul?"<<endl;
                cout<<"       < DA / NU >"<<endl;
            cin>>raspuns;
            strupr(raspuns);
            }
            if(strcmp(raspuns,"DA")==0)
                regulament();
        }
    if(strcmp(raspuns,"EN")==0)
        {
            languageNr=2;
            cout<<"Would you like to read the rules?"<<endl;
            cout<<"       < YES / NO >"<<endl;
            cin>>raspuns;
            strupr(raspuns);
            while(strcmp(raspuns,"YES")!=0&&strcmp(raspuns,"NO")!=0)
            {
                cout<<endl;
                cout<<"Would you like to read the rules?"<<endl;
                cout<<"       < YES / NO >"<<endl;
            cin>>raspuns;
            strupr(raspuns);
            }
            if(strcmp(raspuns,"YES")==0)
                regulament();
        }

}

void intrebareJucatorRo()
{
    char raspuns[100];
    cout<<endl<<"Doriti sa incepeti jocul?"<<endl<<"D / N"<<endl;
    cin>>raspuns;
    if((raspuns[0]=='D' || raspuns[0]=='d')&&raspuns[1]==NULL)
    {
        int nrSecunde=0,record;
        clock_t this_time=clock();
        clock_t last_time=this_time;
        tablou A;
        tablouLive AUX;
        alegeDificultateRo(A,record);
        while(A.nrMine==0)
            alegeDificultateRo(A,record);
        afisareRecordRo(record);
        creareTablou(A);
        generareHarta(A);
        construireTablouLive(A,AUX);
        // de sters
        /*
        cout<<endl<<"Jocul va incepe in 7 secunde..."<<endl<<endl;
        Sleep(2000);
        cout<<endl<<"Jocul va incepe in 5 secunde..."<<endl<<endl;
        Sleep(2000);
        */
        cout<<endl<<'\a'<<"Jocul va incepe in 3 secunde..."<<endl;
        Sleep(1000);
        cout<<endl<<'\a'<<"Jocul va incepe in 2 secunde..."<<endl;
        Sleep(1000);
        char smiley=1;
        cout<<endl<<'\a'<<"Start joc! Mult succes!  "<<smiley<<endl<<endl;
        Sleep(1000);
        afisareTablouLiveRo(AUX);
        completareTablou(A,solutie);
        gameStartRo(A,AUX);
        sfarsitJocRo(A,AUX,solutie,win);
        if(win==1)
        {
            this_time=clock();
            nrSecunde=(nrSecunde+(this_time-last_time))/1000;
            cout<<endl<<"Ai rezolvat puzzle-ul in "<<nrSecunde<<" secunde.";

            if(A.nrMine==10)
                newRecordRo(nrSecunde,1);
            else if(A.nrMine==40)
                newRecordRo(nrSecunde,2);
            else if(A.nrMine==99)
                newRecordRo(nrSecunde,3);
            win=0;
            gameOver=1;
        }
    }
    else if((raspuns[0]=='N'||raspuns[0]=='n')&&raspuns[1]==NULL)
        return;
    else
        intrebareJucatorRo();

    while(gameOver==1)
    {
        cout<<endl<<endl;
        cout<<"Doriti sa jucati din nou?"<<endl;
        cout<<"Daca da, apasati tasta 'D', altfel, apasati tasta 'N'."<<endl;
        cin>>raspuns;
        if((raspuns[0]=='D'||raspuns[0]=='d') && raspuns[1]==NULL)
        {
            gameOver=0;
            intrebareJucatorRo();
        }
    }
}

void intrebareJucatorEn()
{
    char raspuns[100];
    cout<<"Would you like to start the game now?"<<endl<<"Y / N"<<endl;
    cin>>raspuns;
    if((raspuns[0]=='Y' || raspuns[0]=='y')&&raspuns[1]==NULL)
    {
        int nrSecunde=0,record;
        clock_t this_time=clock();
        clock_t last_time=this_time;
        tablou A;
        tablouLive AUX;
        alegeDificultateEn(A,record);
        while(A.nrMine==0)
            alegeDificultateEn(A,record);
        afisareRecordEn(record);
        creareTablou(A);
        generareHarta(A);
        construireTablouLive(A,AUX);
        // de sters
        /*
        cout<<endl<<"The game begins in 7 seconds..."<<endl<<endl;
        Sleep(2000);
        cout<<endl<<"The game begins in 5 seconds..."<<endl<<endl;
        Sleep(2000);
        */
        cout<<endl<<'\a'<<"The game begins in 3 seconds..."<<endl;
        Sleep(1000);
        cout<<endl<<'\a'<<"The game begins in 2 seconds..."<<endl;
        Sleep(1000);
        char smiley=1;
        cout<<endl<<'\a'<<"Start game! Good luck!  "<<smiley<<endl<<endl;
        Sleep(1000);
        afisareTablouLiveEn(AUX);
        completareTablou(A,solutie);
        gameStartEn(A,AUX);
        sfarsitJocEn(A,AUX,solutie,win);
        if(win==1)
        {
            this_time=clock();
            nrSecunde=(nrSecunde+(this_time-last_time))/1000;
            cout<<endl<<"You solved the puzzle in "<<nrSecunde<<" seconds.";

            if(A.nrMine==10)
                newRecordEn(nrSecunde,1);
            else if(A.nrMine==40)
                newRecordEn(nrSecunde,2);
            else if(A.nrMine==99)
                newRecordEn(nrSecunde,3);
            win=0;
            gameOver=1;
        }
    }
    else if((raspuns[0]=='N'||raspuns[0]=='n')&&raspuns[1]==NULL)
        return;
    else
        intrebareJucatorEn();

    if(gameOver==1)
    {
        cout<<endl<<endl;
        cout<<"Would you like to play again?"<<endl;
        cout<<"If yes, then type 'Y', else, type 'N'."<<endl;
        cin>>raspuns;
        if((raspuns[0]=='Y'||raspuns[0]=='y') && raspuns[1]==NULL)
        {
            gameOver=0;
            intrebareJucatorEn();
        }
    }
}

int main()
{
    language();
    if(languageNr==1)
        intrebareJucatorRo();
    else if(languageNr==2)
        intrebareJucatorEn();
}
