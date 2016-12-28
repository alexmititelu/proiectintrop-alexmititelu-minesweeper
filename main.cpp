#include <iostream>

using namespace std;
void creareTablou(int A[100][100],int n)
{
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            A[i][j]=0;
    for(j=0;j<=n+1;j++)
    {
        A[0][j]=-1;
        A[n+1][j]=-1;
    }
    for(i=1;i<=n;i++)
    {
        A[i][0]=-1;
        A[i][n+1]=-1;
    }
}
int main()
{
    int tablou[100][100],n,i,j;
    n=9;
    creareTablou(tablou,n);
    for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            cout<<tablou[i][j]<<" ";
            cout<<endl;
        }
}
