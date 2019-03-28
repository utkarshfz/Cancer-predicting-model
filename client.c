#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "header.h"

int main()
{
FILE *my_file;
my_file=fopen("breast-cancer-wisconsin.data.csv","r");
long int maxln=0;
while(fgetc(my_file)!=EOF)
++maxln;
fseek(my_file,0,0);
char data[maxln];
int ch;
for(int i=0;(ch=fgetc(my_file))!=EOF;i++)
data[i]=ch;
//printf("%s\n",data);
int dataset[maxln][10];
dataextr(data,dataset);
int rows=0,columns=0;
for(int i=0;data[i]!='\n';i++)
if(data[i]==',')
++columns;
++columns;

for(int i=0;data[i]!=EOF;i++)
if(data[i]=='\n')
++rows;
--rows;
//printf("%d\n",rows);


/*for(int i=0;i<rows;i++)
{
for(int j=0;j<columns;j++)
printf("%6d",dataset[i][j]);
printf("\n");
}*/
int test[1000][10];
int train[1000][10];
float split=0.2;
int r=699;
int test_size=test_train_split(dataset,test,train,split,r);

struct features sample;

printf("clump_thickness:");
scanf("%d",&sample.clump_thickness);
printf("unif_cell_size:");
scanf("%d",&sample.unif_cell_size);
printf("unif_cell_shape:");
scanf("%d",&sample.unif_cell_shape);
printf("marg_adhesion:");
scanf("%d",&sample.marg_adhesion);
printf("single_epith_size:");
scanf("%d",&sample.single_epith_size);
printf("bare_nuclei:");
scanf("%d",&sample.bare_nuclei);
printf("bland_chrom:");
scanf("%d",&sample.bland_chrom);
printf("norm_nucleoli:");
scanf("%d",&sample.norm_nucleoli);
printf("mitoses:");
scanf("%d",&sample.mitoses);



//printf("%d\n",r-test_size);


struct classified_dist * clf;
clf=(struct classified_dist *)malloc(1000);
clf=classifier(train,sample,r-test_size-1);
int prediction=predict(clf,r-test_size-1,3);

float confidence=accuracy(test,train,test_size,r);
printf("The current accuracy is-->%f %% \n",confidence);
printf("The Class of Cancer is:   %d\n",prediction);




return 0;
}







