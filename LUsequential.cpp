#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

void printMatrix(double* matrix, int dim, string msg);

int main(int argc, char *argv[]) 
{
	
	string n_str(argv[1]);
	int n = stoi(n_str);
	
	double* a;
	a = (double*)malloc(sizeof(double)*(n*n));
    	double* l;
    	l = (double*)malloc(sizeof(double)*(n*n));
    	double* u;
    	u = (double*)malloc(sizeof(double)*(n*n));
	int* p;
    	p = (int*)malloc(sizeof(int)*(n));
	
	// Initialize arrays
	
	for(int i=0; i<n; i++) 
	{
		p[i] = i;
		for(int j=0; j<n; j++)
		{
			a[i*n + j] = ((double)(rand()%1000))/100.0;
	//		scanf("%lf", &a[i*n + j]); 
			if(j>i) 
			{
				u[i*n + j] = a[i*n + j];
				l[i*n + j] = 0.0;
			} 
			else if(j == i)
			{
				u[i*n + j] = a[i*n + j];
				l[i*n + j] = 1.0;
			}
			else 
			{
				u[i*n + j] = 0.0;
				l[i*n + j] = a[i*n + j];
			}
		}	
	}
	
	auto start = chrono::high_resolution_clock::now();
	
	for(int k=0; k<n; k++)
	{
		double max = 0.0;
		int kd = -1;
		for(int i=k; i<n; i++)
		{
			if(max < abs(a[i*n + k]))
			{
				max = abs(a[i*n + k]);
				kd = i;
			}
		}
		
		if( max == 0.0)
		{
			printf("Singular matrix error\n\n");
			return 1;
		}
		
		int temp;
		temp = p[k];
		p[k] = p[kd];
		p[kd] = temp;
		
		double temp2;
		for(int i=0; i<n; i++)
		{
			temp2 = a[k*n + i];
			a[k*n + i] = a[kd*n + i];
			a[kd*n + i] = temp2;
		}
		for(int i=0; i<k; i++)
		{
			temp2 = l[k*n + i];
			l[k*n + i] = l[kd*n + i];
			l[kd*n + i] = temp2;
		}
		u[k*n + k] = a[k*n + k];
		
		for(int i=k+1; i<n; i++)
		{
			l[i*n + k] = a[i*n + k]/u[k*n + k];
			u[k*n + i] = a[k*n + i];
		}
		for(int i=k; i<n; i++)
		{
			for(int j=k; j<n; j++)
			{
				a[i*n + j] = a[i*n + j] - l[i*n + k]*u[k*n + j];
			}
		}
		
	} 
	
	auto end = chrono::high_resolution_clock::now();
	auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start);

	printf("%d %.02f %d\n", n, (float)time_taken.count()/1000, 1);	
	
//	printMatrix((double*)a, n, "Residual Matrix");
//	printMatrix((double*)u, n, "Upper Matrix");
//	printMatrix((double*)l, n, "Lower Matrix");	
	
	return 0;
	
}	

void printMatrix(double* matrix, int dim, string msg)
{
    cout << '\n' << msg << '\n';
    for(int i=0 ; i<dim ; i++)
    {
        for(int j=0 ; j<dim ; j++)
        {
            printf("%.02lf ", matrix[i*dim + j]);
        }
        printf("\n");
    }
}
	
	
