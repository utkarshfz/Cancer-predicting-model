struct labels
{
int clump_thickness,unif_cell_size,unif_cell_shape,marg_adhesion,single_epith_size,bare_nuclei,bland_chrom,norm_nucleoli,mitoses,Class;
};


struct features
{
int clump_thickness,unif_cell_size,unif_cell_shape,marg_adhesion,single_epith_size,bare_nuclei,bland_chrom,norm_nucleoli,mitoses;
};


struct classified_dist
{
float dist;
int Class;
};

int dataextr(char data[],int dataset[][10]);

struct classified_dist * classifier(int data[][10],struct features sample,int rows);

int predict(struct classified_dist * classifier,int rows,int k);


int test_train_split(int dataset[][10],int test[][10],int train[][10],float split,int row);


float accuracy(int test[][10],int train[][10],int test_size,int r);


