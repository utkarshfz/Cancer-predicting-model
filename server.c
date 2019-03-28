#include"header.h"
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
int dataextr(char data[],int dataset[][10])//converts char data to int format
{
int len=strlen(data);
int temp=0;
for(int i=0,j=0,k=0;i<len;i++)
{
if(data[i]!=',' && data[i]!='\n')
{
if(isdigit(data[i]))
temp=temp*10+(data[i]-'0');
else
temp=-9999;
}
if(data[i]==',')
{
dataset[j][k++]=temp;
temp=0;
}
if(data[i]=='\n')
{
dataset[j][k]=temp;
++j;
k=0;
temp=0;
}
}
return 0;
}

struct classified_dist * classifier(int data[][10],struct features sample,int rows)//creates the classifer.
{
struct labels label[rows];

for(int i=0;i<rows;i++)//converts int data to structure format
{
label[i].clump_thickness=data[i][0];
label[i].unif_cell_size=data[i][1];
label[i].unif_cell_shape=data[i][2];
label[i].marg_adhesion=data[i][3];
label[i].single_epith_size=data[i][4];
label[i].bare_nuclei=data[i][5];
label[i].bland_chrom=data[i][6];
label[i].norm_nucleoli=data[i][7];
label[i].mitoses=data[i][8];
label[i].Class=data[i][9];
}

struct classified_dist *classifier;
classifier=(struct classified_dist *)malloc(5000);
for(int i=0;i<rows;i++)
{
classifier[i].dist=sqrt(pow(sample.clump_thickness-label[i].clump_thickness,2)+pow(sample.unif_cell_size-label[i].unif_cell_size,2)+pow(sample.unif_cell_shape-label[i].unif_cell_shape,2)+pow(sample.marg_adhesion-label[i].marg_adhesion,2)+pow(sample.single_epith_size-label[i].single_epith_size,2)+pow(sample.bare_nuclei-label[i].bare_nuclei,2)+pow(sample.norm_nucleoli-label[i].norm_nucleoli,2)+pow(sample.mitoses-label[i].mitoses,2));
classifier[i].Class=label[i].Class;
}


return classifier;
}


int predict(struct classified_dist * classifier,int rows,int k)
{
for(int i=0;i<rows-1;i++)
for(int j=i;j<rows;j++)
if(classifier[j].dist<classifier[i].dist)
{
float temp;
temp=classifier[i].dist;
classifier[i].dist=classifier[j].dist;
classifier[j].dist=temp;

int tempx;
tempx=classifier[i].Class;
classifier[i].Class=classifier[j].Class;
classifier[j].Class=tempx;
}

/*for(int i=0;i<rows;i++)
printf("%f	%d\n",classifier[i].dist,classifier[i].Class);*/

int count_2=0,count_4=0;
for(int i=0;i<k;i++)
{
if(classifier[i].Class==2)
count_2+=1;
if(classifier[i].Class==4)
count_4+=1;
}

return count_2>count_4?2:4;
}


int test_train_split(int dataset[][10],int test[][10],int train[][10],float split,int row)
{
int seed=floor(random()*row);
for(int i=1;i<row-1;i++)
if(seed%i==0)
for(int j=i+1;j<row;j++)
if(seed%j==0)
for(int k=0;k<9;k++)
{
dataset[i][k]^=dataset[j][k];
dataset[j][k]^=dataset[i][k];
dataset[i][k]^=dataset[j][k];
}

for(int i=0;i<(int)ceil(split*row);i++)
for(int j=0;j<10;j++)
test[i][j]=dataset[i][j];

for(int i=(int)ceil(split*row);i<row;i++)
for(int j=0;j<10;j++)
train[i-(int)(split*row)][j]=dataset[i][j];


return (int)ceil(split*row);

}


float accuracy(int test[][10],int train[][10],int test_size,int r)
{
float score=0;
struct labels test_sample[test_size];
for(int i=0;i<test_size;i++)
{
test_sample[i].clump_thickness=test[i][0];
test_sample[i].unif_cell_size=test[i][1];
test_sample[i].unif_cell_shape=test[i][2];
test_sample[i].marg_adhesion=test[i][3];
test_sample[i].single_epith_size=test[i][4];
test_sample[i].bare_nuclei=test[i][5];
test_sample[i].bland_chrom=test[i][6];
test_sample[i].norm_nucleoli=test[i][7];
test_sample[i].mitoses=test[i][8];
test_sample[i].Class=test[i][9];
}

struct features test_feature;
for(int i=0;i<test_size;i++)
{
test_feature.clump_thickness=test_sample[i].clump_thickness;
test_feature.unif_cell_size=test_sample[i].unif_cell_size;
test_feature.unif_cell_shape=test_sample[i].unif_cell_shape;
test_feature.marg_adhesion=test_sample[i].marg_adhesion;
test_feature.single_epith_size=test_sample[i].single_epith_size;
test_feature.bare_nuclei=test_sample[i].bare_nuclei;
test_feature.bland_chrom=test_sample[i].bland_chrom;
test_feature.norm_nucleoli=test_sample[i].norm_nucleoli;
test_feature.mitoses=test_sample[i].mitoses;
//--------**********-------------------

struct classified_dist * clf;
clf=(struct classified_dist *)malloc(1000);
clf=classifier(train,test_feature,r-test_size-1);
int prediction=predict(clf,r-test_size-1,3);
if(prediction==test_sample[i].Class)
++score;

}


return score/test_size*100;
}












