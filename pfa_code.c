#include<stdio.h>
#include<math.h>
#include <time.h>
#include<string.h>
#include<stdlib.h>
#define NRAND(min, max)     ((rand() % (max - min + 1)) + min)


void saisir_ville(int v[30],int n)
{int i;
 char ch[10];

    for(i=0;i<n;i++)
{
  printf("\nentrer une ville  ");
  scanf("%s", ch);
  printf("\nla ville numero %d est %s",i,ch);
  v[i]=i;
}
}

/////////////////////////////////////// Remplir la matrice des distances entre les villes ///////////////////////////////////////////////////////////

void remp_dist(int M[30][30],int n,int v[30])
{int i,j;
int x;

  for(i=0;i<n;i++)
   {
       for(j=0;j<=i;j++)
            {if (i==j)
              M[i][i]=0;
              else
             {printf("\nentrer la distance entre %d et %d  ",v[i],v[j]);
             scanf("%d",&x);
             M[i][j]=x;
             M[j][i]=M[i][j];
             }
             }
    }
}

void affichage_mat(int M[30][30],int n)
{int i,j;
    for(i=0;i<n;i++)
       {
       {for(j=0;j<n;j++)
        printf("%d ",M[i][j]);
       }
        printf("\n");
      }
}

void generer_ind(int ind[30],int n)
{int i,j;
 for(i=0;i<n;i++)
    {
        ind[i]=rand()%n;
          for(j=0;j<i;j++)
             if(ind[j]==ind[i])
              i--;
    }
}
/*
void generer_ind(int ind[30],int n)
{int i,j,k,l;
 k=0;
 int t[30];
for(i=0;i<n;i++)
    t[i]=i;

    for(j=n-1;j>=0;j--)
       {
        l=rand()%j+1;
          ind[k]=t[l];
           t[l]=t[j];
           k++;
             printf("** ");
      }
}

*/
void generer_gen(int gen[30][30],int nb,int n,int tab_dist[30],int M[30][30])
{int i,j;
  for(i=0;i<=nb;i++)
    {generer_ind(gen[i],n);
    tab_dist[i]=distance(gen[i],n,M);
    printf("\n");
    for(j=0;j<n;j++)
    printf("%d ",gen[i][j]);
    printf("  distance de l'individu= %d \n",tab_dist[i]);
    }
}


int distance(int ind[],int n,int M[30][30])
{int i;
int Dist=0;
for(i=0;i<n;i++)
    Dist+=M[ind[i]][ind[i+1]];
Dist+=M[ind[0]][ind[n]];
return Dist;
}


int selection_tournois(int gen[30][30],int nb,int n,int M[30][30])
{
int i1,i2,i3,imax;
i1=rand()%nb+1;
i2=rand()%nb+1;
imax=i1;
if(fitness(gen[i2],n,M)>fitness(gen[imax],n,M))
    imax=i2;
return(imax);
}


int fitness(int ind[30],int n,int M[30][30])
{
return 1./distance(ind,n,M);
}


void selection_generation(int gen_select[30][30],int gen[30][30],int nb,int n,int M[30][30])
{int i,pos,j,k,h;
    for(i=0;i<nb+2;i++)
      {
       pos=selection_tournois(gen,nb,n,M);
       for(j=0;j<n;j++)
       gen_select[pos][j]=gen[pos][j];
       pos++;
       for(j=0;j<n;j++)
       gen_select[pos][j]=gen[pos][j];
       pos++;
      }
    for(k=0;k<nb;k++)
       {for(h=0;h<n;h++)
        printf("%d ",gen_select[k][h]);
        printf("\n");
        }
}

void croisement(int ind1[30],int ind2[30],int n)
{
    int a,b,i,j,x,aux,h;

    b=rand()%n+1;
     a=rand()%b;
     for(i=a;i<=b;i++)
        {
         aux=ind1[i];
         ind1[i]=ind2[i];
         ind2[i]=aux;
        }
  for(i=a;i<=b;i++)
    if(doublement(ind1,ind1[i],n,a,b)!=0);
     {h=doublement(ind1,ind1[i],n,a,b);
      j=a;
      x=0;
      do
      {
       if (exist(ind1,ind2[j],0,a-1)==-1)
               {ind1[h]=ind2[j];
                x=1;}
      else if (exist(ind1,ind2[j],b+1,n-1)==-1)
               {ind1[h]=ind2[j];
                x=1;}
           else j++;
      }
      while(j<=b && x==0);
     }
  for(i=a;i<=b;i++)
    if(doublement(ind1,ind2[i],n,a,b)!=0);
     {h=doublement(ind1,ind2[i],n,a,b);
      j=a;
      x=0;
      do
      {
       if (exist(ind2,ind1[j],0,a-1)==-1)
               {ind2[h]=ind1[j];
                x=1;}
      else if (exist(ind2,ind1[j],b+1,n-1)==-1)
               {ind2[h]=ind1[j];
                x=1;}
           else j++;
      }
      while(j<=b && x==0);
     }
}

int exist(int t[30],int x,int d,int f)
{int i;
    for(i=d;i<=f;i++)
        if(t[i]==x)
        return i;
    return -1;
}


int doublement(int t[30],int x,int n,int d,int f)
{int i,e;
        if (exist(t,x,0,d-1)!=-1)
         {e=exist(t,x,0,d-1);
          return e;}
        else if (exist(t,x,f+1,n-1)!=-1)
            {e=exist(t,x,f+1,n-1);
             return e;}
    return 0;
}


/*
int meilleur_ind(int pop[nb][10])
{int i;
int id=0;
for(i=1;i<nb;i++)
if(fitness(pop[i])>fitness(pop[id]))
    id=i;
return id;
}



void selection_gen(int nb_gen,Individu gen[],Individu gen_select[],float d_tot[])
{int i,k,j;
    for(i=1;i<m/2;i++)
       {
        k=max_fct(d_tot,m);
        d_tot[k]=0;
       }
       for(i=1;i<=m;i++)
        if(gen[i]!=0)
           {gen_select[j]=gen[i];
            j++;}


}


/////////////////////////////////////mutation///////////////////////////////////////////////////////////////////////////////////////


void mutation(int t[30],int n)
{int i,j,aux;
 i=(rand()%n+1);
 i=(rand()%n+1);

 aux=i;
 i=j;
 j=aux;

}

*/

/////////////////////////////////////////PROGRAMME PRINCIPALE//////////////////////////////////////////////////////////////////////

int main()

{int n,i,nb,nb_gen;
 int S;
 int M[30][30];
 int gen[30][30];
 int gen1[30][30];
 int gen2[30][30];
 int gen3[30][30];
 int gen_select[30][30];
 int v[30];
 int ind[30];
 int tab_dist[30];
  printf("combien de ville  ");
    scanf("%d",&n);
saisir_ville(v,n);
remp_dist(M,n,v);
affichage_mat(M,n);
  printf("\ncombien d'individu par generation  ");
  scanf("%d",&nb);
 generer_gen(gen,nb,n,tab_dist,M);
printf("\n");
 selection_generation(gen_select,gen,nb,n,M);
 printf("**");
 /*
 i=0;
do
{
    croisement(gen_select[i],gen_select[i+1],n);
    i=i+2;
}
while(i<n-1);

 for(i=0;i<nb-2;i=i+2)
 croisement(gen0[i],gen0[i+1],n);
 generer_gen(gen1,nb,n,tab_dist,M);
 generer_gen(gen2,nb,n,tab_dist,M);
 generer_gen(gen3,nb,n,tab_dist,M);


S=selection_tournois(gen0,nb,n,M);
printf(" %d ",S);

selection_gen(m,gen,gen_select,d_tot)
*/
getch();
}
