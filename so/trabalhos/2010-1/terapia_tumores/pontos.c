#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include <Judy.h>

#define JUDYERROR_SAMPLE 1

#define HASHSIZE (1 << 9)

#define MEM 512

int main()
{
	Pvoid_t JArray[HASHSIZE] = { NULL }; // Declare static hash table
	int * PValue;	

	FILE *arq;
	long int count, i, j, k;
	float *x,*y,*z;
	float a,b,c;
	float d; 
	int n_uniq, sum_uniq;
	int sum;

	float *f_dist;
	int   *i_dist;


	//entrada de dados
	arq=fopen("cells","r");


	count=0;

	while(fscanf(arq,"%f %f %f", &a, &b, &c)!=EOF)
		count++;

	// alocando memória
	x=(float *)memalign (16, count*sizeof(float));
	y=(float *)memalign (16, count*sizeof(float));
	z=(float *)memalign (16, count*sizeof(float));

	rewind(arq);
	for(i=0;i<count;i++)
	 	fscanf(arq,"%f %f %f", &x[i], &y[i], &z[i]);
	
	fclose(arq);
	//fim entrada de dados

	for(i = 0; i < HASHSIZE; i++) 
		JArray[i] = NULL;

	for(i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)
		{
			a=x[i]-x[j];
			b=y[i]-y[j];
			c=z[i]-z[j];
			d=sqrt(a*a+b*b+c*c);
			i_dist = (int*) &d;
			JLI(PValue, JArray[(int)d % HASHSIZE], *i_dist);
			*PValue += 1;	
		}
	}

	n_uniq = 0;
	sum_uniq = 0;	

	for(j=0;j<HASHSIZE;j++)
	{
		if (JArray[j] == NULL) continue;
		i = 0;
		JLF(PValue, JArray[j], i);
		while(PValue != NULL){
			n_uniq++;
			f_dist = (float*) &i;
	 		printf("%.14f \t %i\n", *f_dist, *PValue );
			sum_uniq=sum_uniq+*PValue;
			JLN(PValue, JArray[j],i);
		}
	}
	printf("n_uniq %d\n", n_uniq);
	printf("sum_uniq %d\n", sum_uniq);
	
	free(x);
	free(y);
	free(z);
	
	return 0;
}
