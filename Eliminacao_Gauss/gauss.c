/*Método de eliminação de Gauss*/
#include <stdio.h>
#include <stdlib.h>

double** ler(const char *nomeArq, int *d) {
	int i, j, dim;
	double **L, a;
	FILE *arq;
    
    arq = fopen(nomeArq, "r");
	i = fscanf(arq,"%d",&dim);
	L = malloc( dim*sizeof(double *));
	for( i = 0 ; i < dim ; i++ )
		L[i] = (double *) malloc((dim+1)*sizeof(double));
	i=j=0;
	while (fscanf(arq,"%lf",&a) != EOF) {
		L[i][j] = a;
		j++;
		if (j == dim+1) {
			j = 0;
			i++;
		}
	}
	*d=dim;
	return L;
}

void imprime(double **N, int var){
	int i, j;
	for(i=0;i<var;i++) {
		for(j=0;j<var+1;j++) { 
			printf("%5.2lf\t",N[i][j]);
		}	  
		puts("");
	}
}

void triangsup(double **M, int dim) {
	int i, j, r;
	double lamb;
	i=j=0;
	puts("\nMatriz triangularizada:");
	for(j=0; j<dim-1; j++) {
		for(i=j+1; i<=dim-1; i++) {
			lamb=M[i][j]/M[j][j];
			for(r=j; r<=dim; r++)
				M[i][r] = M[i][r] - (lamb)*M[j][r];
		}
	}
}

void subsreversa(double **M,double *raizes, int dim, int *n) {
	int i, j;
	double a;
	for(i=dim-1; i>=0; i--) {
		a=0;
		for(j=i+1; j<dim; j++)
			a += M[i][j]*raizes[j];
		raizes[i] = (M[i][dim]-a)/(M[i][i]);
		*n=*n+1;
	}
}

int main(int argc, char **argv) {
	double **M;
	double *raizes;
	int dim, i, ntrocas, noperacoes=0;
	M=ler(argv[1], &dim);
	imprime(M,dim);
	triangsup(M,dim);
	puts("\nMatriz Solução:");
	imprime(M,dim);
	raizes = malloc(dim*sizeof(double));
	subsreversa(M,raizes,dim, &noperacoes);
	puts("");
	for (i=0;i<dim;i++) printf ("x%1d = %5.2lf\n",i+1,raizes[i]);
	printf("%d operações\n",noperacoes);
	return 0;
}
