#include <stdio.h>
#include <stdlib.h>

int writeToTXT(FILE *fPointer,int x1, int x2, int N, int step)
{
    int i,y,n = 0;
    for(i=0; i<=N;i++)
    {
        n++;
        y=x1*2;
        fprintf(fPointer,"%d %d\n", x1, y);

    if(x1>=x2)
    {
        return n;
    }
    x1+=step;
    }
    return n;
}
int writeToBIN(FILE *fPointer,int x1, int x2, int N, int step)
{
    int i,y,n = 0;
    for(i=0; i<=N;i++)
    {
        n++;
        y=x1*2;
        fwrite(&x1,sizeof(int),1,fPointer);
        fwrite(&y,sizeof(int),1,fPointer);
        //fwrite (адрес переменных, размер переменной, указатель на файл)

    if(x1>=x2)
    {
        return n;
    }
    x1+=step;
    }
    return n;
}

void readFromTxt(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("TXT FILE (result.txt) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    //
    for(i = 1; i < n+1;i++)
    {
        fscanf(fPointer,"%d",&x);
        fscanf(fPointer,"%d",&y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
}

void readFromBIN(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("BIN FILE (result.bin) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    for(i = 1; i < n+1;i++)
    {
        fread(&x,sizeof(int),1,fPointer);
        fread(&y,sizeof(int),1,fPointer);
        // fread(адрес переменной, размер, количество, указатель на файл)
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
}

void saveResultToArray(FILE *fPointer,int n)
{
   int i,j,k;
   int **arr = (int **)malloc(n*sizeof(int*)); //n - рядки
   for( i = 0; i < n; i++)
   {
      arr[i] = (int *)malloc(2*sizeof(int));// выделяем память под столбцы
   }
   printf("Array content :\n");
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<2;j++)
       {
           fscanf(fPointer,"%d",&k);
           arr[i][j] = k;
       }
   }
   for(i = 0;i<n;i++)
   {
       for(j = 0;j<1;j++)
       {
            printf("x: %d \ty: %d\n",arr[i][j],arr[i][j+1]);
       }
   }
   for(i = 0; i < n; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

int main()
{
    int N,step,n;
    int x1,x2;
    char group[50];
    FILE *fInput;
    FILE *fReadTxt, *fWriteTxt;
    FILE *fReadBin, *fWriteBin;

    fInput = fopen("input.dat","r");
    fscanf(fInput,"%s%d%d%d%d",&group,&x1,&x2,&N,&step);// & - адреса
    //fscanf (указатель, типы переменных,адреса переменных)
    fclose(fInput);

    printf("group = %s\n",group);
    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %d\n",N);
    printf("x2 = %d\n",x2);
    printf("step = %d\n",step);

    fWriteTxt = fopen("result.txt","w");
    n = writeToTXT(fWriteTxt,x1,x2,N,step);
    fclose (fWriteTxt);

    fReadTxt = fopen("result.txt","r");
    readFromTxt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("result.bin","wb");
    n = writeToBIN(fWriteBin,x1,x2,N,step);
    fclose (fWriteBin);

    fReadBin = fopen("result.bin","rb");
    readFromBIN(fReadBin,n,x1,x2);
    fclose(fReadBin);

    fReadTxt = fopen("result.txt","r");
    saveResultToArray(fReadTxt,n);
    fclose(fReadTxt);
    return 0;
}
