#include <math.h>
#include <stdio.h>  
#include <stdlib.h>   
#include <string.h>
#include <ctype.h>

int hextodec(char c[])
{
    int b = 1;
    int val = 0;
    int i;
    for(i = strlen(c) - 1; i >= 0; i--) 
    {
        c[i] = toupper(c[i]);
        if(c[i] >= '0' && c[i] <= '9')
        {
            val += (c[i] - 48) * b;
            b = b * 16;
        }
        else if(c[i] >= 'A' && c[i] <= 'F') 
        {
            val += (c[i] - 55) * b;
            b = b * 16;
        }
    }
    return val;
}

int bintodec(int bhr[])
{
    int bhrvalue = 0;
    int base = 1;
    int i;
    for(i = 7; i >= 0; i--) 
    {
        if(bhr[i] == 1)
        {
            bhrvalue += base;
        }
        base = base * 2;
    }
    return bhrvalue;
}

int main(int argc, char *argv[]) 
{
	int n=12, k=8,i,j;
   int z = pow(2,n);
   int bhrnum = pow(2,k);
   int pht[bhrnum][z];
   int bhr[z][k];
   int temp[k];
   int hex;
   int prediction,correctpred=0,totalpred=0;
   int bhrvalue;
   
   unsigned decadr;
   char address[8],outcome,bin;
   unsigned  mask;
   float x =0.0,hwcost;
   FILE *fp1,*fp2;
   
   // initialize bhr to 11...1
   for(i=0;i<z;i++)
   {
      for(j=0;j<k;j++)
      {
        bhr[i][j] = 1;
      }
   }
   
   // initialize everything pht to 11
   for(i=0;i<bhrnum;i++)
   {
      for(j=0;j<z;j++)
      {
         pht[i][j] = 11;
      }
   }
   
   fp1 = fopen(argv[1],"r");
   fp2 = fopen("oppap.txt","w");
   if(fp1 == NULL)  
   {
     printf("Error! File cannot be opened");
     exit(1);
   }
   if(fp2 == NULL)  
   {
     printf("Error! File cannot be opened");
     exit(1);
   }
   
  
	while(fscanf(fp1,"%s %c %c",address,&outcome,&bin)!=EOF) 
   {
        hex = hextodec(address);  //hex branch addr to decimal
        mask = (1 << n) - 1;
        decadr = hex & mask;    // decimal value of last n bits of the addr
        
        memcpy(temp,bhr[decadr],sizeof(bhr[decadr]));
        bhrvalue = bintodec(temp);            //bhr value in decimal
        
        //Prediction
        if(pht[bhrvalue][decadr]== 11 || pht[bhrvalue][decadr]== 10)
        {
           prediction = 1;
        }
        else
        {
           prediction = 0;
        }
        
        if((outcome== '+' && prediction== 1 )||(outcome== '-' && prediction== 0))
        {
          correctpred += 1;
        }
        totalpred += 1;
        fprintf(fp2,"%d\n",prediction); 
        
        // updating pht
        if(outcome == '+')
        {
            if(pht[bhrvalue][decadr]== 10){
                pht[bhrvalue][decadr]= 11;
            }
            else if(pht[bhrvalue][decadr]== 01){
                pht[bhrvalue][decadr]= 10;
            }
            else if(pht[bhrvalue][decadr]== 00){
                pht[bhrvalue][decadr]= 01;
            }
        }
        else {
            if(pht[bhrvalue][decadr]== 11){
                pht[bhrvalue][decadr]= 10;
            }
            else if(pht[bhrvalue][decadr]== 10){
                pht[bhrvalue][decadr]= 01;
            }
            else if(pht[bhrvalue][decadr]== 01){
                pht[bhrvalue][decadr]= 00;
            }
        }
        
        // updating bhr        
        for(j=0;j<k-1;j++){              
            bhr[decadr][j]=bhr[decadr][j+1];
        }
        if(outcome == '+')
        {
          bhr[decadr][k-1] = 1; 
        }
        else 
        {
          bhr[decadr][k-1] = 0;
        } 
	}

   x = (float)(correctpred*100)/totalpred;
   printf("No. of correct predictions is %d\n",correctpred);
   printf("Total no. of predictions is %d\n",totalpred);
   printf("Accuarcy is %f\n",x);
   hwcost = (float)(z*k+z*bhrnum*2)/8192;
   printf("Hardware cost for Branch Prediction with PAp is %f KB",hwcost);
   fclose(fp1);
   fclose(fp2);
   return 0; 
}