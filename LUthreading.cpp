#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

double* a;
double* l;
double* u;
int n;
int t;
int t_num = 0;
void printMatrix(double* matrix, int dim, string msg);
void* make_thread(void* arg);

struct threadArg
{
    int minm;
    int maxm;
    int k;
    int kd;
};

void* make_thread(void* arg)
{
    threadArg* thread_arg = (threadArg*)arg;
    int k = thread_arg->k;
    int minm = thread_arg->minm;
    int maxm = thread_arg->maxm;

    for(int i = minm; i < min(maxm, n); i++)
    {
        for(int j=k ; j<n ; j++)
        {
            a[i*n + j] -= l[i*n + k] * u[k*n + j];
        }
    }
    pthread_exit(NULL);
}

//void* swap1(void* arg)
//{
//    threadArg* thread_arg = (threadArg*)arg;
//    int k = thread_arg->k;
//    int kd = thread_arg->kd;
//    int minm = thread_arg->minm;
//    int maxm = thread_arg->maxm;
//    double temp2;
//
//    for(int i=minm; i< min(maxm, n); i++)
//	{
//		temp2 = a[k*n + i];
//		a[k*n + i] = a[kd*n + i];
//		a[kd*n + i] = temp2;
//	}
//    pthread_exit(NULL);
//}

//void* swap2(void* arg)
//{
//    threadArg* thread_arg = (threadArg*)arg;
//    int k = thread_arg->k;
//    int kd = thread_arg->kd;
//    int minm = thread_arg->minm;
//   int maxm = thread_arg->maxm;
//    double temp3;
//
//   for(int i=minm; i< min(maxm, n); i++)
//	{
//		temp3 = l[k*n + i];
//		l[k*n + i] = l[kd*n + i];
//		l[kd*n + i] = temp3;
//	}
//    pthread_exit(NULL);
//}


int main(int argc, char *argv[]) 
{
	
	string n_str(argv[1]);
	n = stoi(n_str);
	
	string t_str(argv[2]);
    	t = stoi(t_str);
	
	a = (double*)malloc(sizeof(double)*(n*n));
    	l = (double*)malloc(sizeof(double)*(n*n));
    	u = (double*)malloc(sizeof(double)*(n*n));
	int* p;
    	p = (int*)malloc(sizeof(int)*(n));
	
//	srand(time(0));
	// Initialize arrays
	
	for(int i=0; i<n; i++) 
	{
		p[i] = i;
		for(int j=0; j<n; j++)
		{
			a[i*n + j] = ((double)(rand()%1000))/100.0;
	//		scanf("%lf", &(a[i*n + j])); 
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
		
//		t_num = 0;
//       	pthread_t threads[t];
//        	void* status[t];
        	
//        	for(int i = 0; i < t; i++)
//        	{
//         	   threadArg *thread_arg;
//         	   thread_arg = (threadArg*)malloc(sizeof(threadArg));
//         	   thread_arg->minm = t_num*(n-k)/t;
//         	   thread_arg->maxm = (t_num + 1)*(n-k)/t;
//         	   thread_arg->k = k;
//         	   thread_arg->kd = kd;
//
//         	   pthread_create(&threads[i], NULL, swap1, (void*)thread_arg);
//         	   t_num++;
//        	}
//

//        	for(int i = 0; i < t; i++)
//        	{
//        	    pthread_join(threads[i],&status[i]);
//        	}
        	
//        	t_num = 0;
//        	for(int i = 0; i < t; i++)
//        	{
//         	   threadArg *thread_arg;
//         	   thread_arg = (threadArg*)malloc(sizeof(threadArg));
//         	   thread_arg->minm = t_num*(n-k)/t;
//         	   thread_arg->maxm = (t_num + 1)*(n-k)/t;
//         	   thread_arg->k = k;
//        	   thread_arg->kd = kd;
//
//         	   pthread_create(&threads[i], NULL, swap2, (void*)thread_arg);
//         	   t_num++;
//        	}

//        	for(int i = 0; i < t; i++)
//        	{
//        	    pthread_join(threads[i],&status[i]);
//        	}
		
		double temp2;
		for(int i=0; i<n; i++)
		{
			temp2 = a[k*n + i];
			a[k*n + i] = a[kd*n + i];
			a[kd*n + i] = temp2;
		}
		double temp3;
		for(int i=0; i<k; i++)
		{
			temp3 = l[k*n + i];
			l[k*n + i] = l[kd*n + i];
			l[kd*n + i] = temp3;
		}
		u[k*n + k] = a[k*n + k];
		
		for(int i=k+1; i<n; i++)
		{
			l[i*n + k] = a[i*n + k]/u[k*n + k];
			u[k*n + i] = a[k*n + i];
		}
		
		t_num = 0;
        	pthread_t threads[t];
        	for(int i = 0; i < t; i++)
        	{
         	   threadArg *thread_arg;
         	   thread_arg = (threadArg*)malloc(sizeof(threadArg));
         	   thread_arg->minm = k + t_num*(n-k)/t;
         	   thread_arg->maxm = k + (t_num + 1)*(n-k)/t;
         	   thread_arg->k = k;

         	   pthread_create(&threads[i], NULL, make_thread, (void*)thread_arg);
         	   t_num++;
        	}

        	void* status[t];
        	for(int i = 0; i < t; i++)
        	{
        	    pthread_join(threads[i],&status[i]);
        	}
		
	} 
	
	auto end = chrono::high_resolution_clock::now();
	auto time_taken = chrono::duration_cast<chrono::milliseconds>(end - start);

	printf("%d %.02f %d", n, (float)time_taken.count()/1000, t);
	
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
	
	
