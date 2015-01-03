#include <iostream>

#define N 4
#define M 3
#define A 2
using namespace std;

class MessageCell{

public:
  int red,blue;
public:
    MessageCell()
    {
        red=-99;
        blue=-99;
    }

 /*
 void putvalue(int c,int d)
{
   red=c;
   blue=d;

}
*/

};



int main()
{
    int i,j,p,q,u1,u2,v1,v2,chk,total;
    int tempFV[A][A],tempUtility[A][A];
int tempVF[A][A]={{0,0},{0,0}};
    int globalutility[N][M]= {                  // Global Utility Function generated corresponding to the Factor Graph
                            {1,0,0},
                            {0,1,0},
                            {1,1,1},
                            {0,0,1}
                             };
    int utilityCheck[M][N]= {
                            {1,0,1,0},
                            {0,1,1,0},
                            {0,0,1,1}
                             };

    int factor[A][6]={
                         {1,3,1,5,3,4},
                         {2,1,4,2,10,1},

                       };



     MessageCell variabletoFunction[N][M],functiontoVariable[M][N];



//variable to function message

for(total=0;total<12;total++)
{



    for(i=0;i<N;i++)
        {
           for(j=0;j<M;j++)
            {
              if(globalutility[i][j]==1){

                  if(variabletoFunction[i][j].red < 0) //functtovar  j i
                  {
                     variabletoFunction[i][j].red=0;  //functtovar  j i
                     variabletoFunction[i][j].blue=0;
                  }

                  for (p=0;p<M;p++)
                    {
                        if(functiontoVariable[p][i].red>=0 && p!=j)
                        {

                            //put the calculation here
                          variabletoFunction[i][j].red = variabletoFunction[i][j].red +functiontoVariable[p][i].red;
                          variabletoFunction[i][j].blue = variabletoFunction[i][j].blue + functiontoVariable[p][i].blue;
                        }

                    }

              }
            }

       }

//Function to Variable Message:

for(i=0;i<N;i++)
        {
           for(j=0;j<M;j++)
            {
              if(globalutility[i][j]==1){

                  if(functiontoVariable[j][i].red<0) //functtovar  j i
                  {
                     functiontoVariable[j][i].red=0;  //functtovar  j i
                     functiontoVariable[j][i].blue=0;
                  }

                  for (q=0;q<N;q++)
                    {
                        if( variabletoFunction[q][j].red>=0 && q!=i)
                        {

                            //the calculation here
                            //


                            if(i+j==2)
                            {
                                for(u1=0;u1<A;u1++)
                                {
                                    for(u2=0;u2<=1;u2++)
                                    {
                                        tempUtility[u1][u2] = factor[u1][u2];
                                    }
                                }
                            }
                              else if(i+j==3)
                            {
                                for(u1=0;u1<A;u1++)
                                {
                                    for(u2=2;u2<=3;u2++)
                                    {
                                        tempUtility[u1][u2] = factor[u1][u2];
                                    }
                                }
                            }

                             else if(i+j==5)
                            {
                                for(u1=0;u1<A;u1++)
                                {
                                    for(u2=4;u2<=5;u2++)
                                    {
                                        tempUtility[u1][u2] = factor[u1][u2];
                                    }
                                }
                            }



               // the tempVF matrix



                          if (i+q>j+q)
                          {
                            tempVF[0][0] =  tempVF[0][0]+ variabletoFunction[q][j].red;
                            tempVF[0][1] =  tempVF[0][1]+ variabletoFunction[q][j].red;
                            tempVF[1][0] =  tempVF[1][0]+ variabletoFunction[q][j].blue;
                            tempVF[1][1] =  tempVF[1][1]+ variabletoFunction[q][j].blue;
                          }

                         else
                          {
                            tempVF[0][0] =  tempVF[0][0]+ variabletoFunction[q][j].red;
                            tempVF[0][1] =  tempVF[0][1]+ variabletoFunction[q][j].blue;
                            tempVF[1][0] =  tempVF[1][0]+ variabletoFunction[q][j].red;
                            tempVF[1][1] =  tempVF[1][1]+ variabletoFunction[q][j].blue;
                          }



for(v1=0;v1<A;v1++)
{
    for (v2=0;v2<A;v2++)
    {
      tempFV[v1][v2] =  tempUtility[v1][v2] +tempVF[v1][v2];
    }
}

    int tmp=0,k1,k2,tmpred=0,tmpblue=0;;
    for (chk=0;chk<N;chk++)
      {

    if(utilityCheck[j][chk] ==1)
       {
        tmp = chk;
       }
      }

    if (tmp==i)
    {
      for(k1=1;k1<A;k1++)
      {
        if(tempFV[0][k1]>tmpred)
            {
            tmpred =tempFV[0][k1];
            }
        if(tempFV[1][k1]>tmpblue)
            {
            tmpblue =tempFV[0][k1];
            }

      }

      functiontoVariable[j][i].red=tmpred;
      functiontoVariable[j][i].blue=tmpblue;
    }
    else{
      for(k1=1;k1<A;k1++)
      {
        if(tempFV[k1][0]>tmpred)
            {
            tmpred =tempFV[k1][0];
            }
        if(tempFV[k1][1]>tmpblue)
            {
            tmpblue =tempFV[k1][1];
            }

      }

      functiontoVariable[j][i].red=tmpred;
      functiontoVariable[j][i].blue=tmpblue;


    }

}

}




              }
            }

       }


}


//Print the Current Status of Variable to Function Message:
cout << "The Variable to Function Message Status: \n\n";for(i=0;i<N;i++)
        {
            for (j=0;j<M;j++)
            {
                cout<<"{"<<variabletoFunction[i][j].red<<" , "<<variabletoFunction[i][j].blue<<"}"<<"   " ;
            }
              cout<<"\n";
        }

//Print the Current Status of Variable to Function Message:
cout << "\n\n\nThe Function to Variable Message Status: \n\n\n";for(i=0;i<M;i++)
        {
            for (j=0;j<N;j++)
            {
                cout<<"{"<<functiontoVariable[i][j].red<<" , "<<functiontoVariable[i][j].blue<<"}"<<"   " ;
            }
              cout<<"\n";
        }



    return 0;
}
