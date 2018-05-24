#include<stdio.h>
#include <string.h>
#include <math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
typedef float probability;
int test_count(int test[],float prob[][192][5], float prob_class[]);
float count_j(int train[][192], int label[], int class, int feature, int value, float prob_class[]);
int main(){
	FILE *f1 = fopen("pp_tra.dat", "r"); 
	int train[6670][192];
	int label[6670];
	float prob_class[10];
	int i,j,k,c;
	for(i=0;i<6670;i++){
		for(j=0;j<192;j++){
			fscanf(f1,"%d",&train[i][j]);
		}
        fscanf(f1,"%d",&label[i]);
	}

	float prob[10][192][5];

	for(i=0;i<10;i++){
		for(j=0;j<192;j++){
			for(k=0;k<5;k++){
				prob[i][j][k]=count_j(train,label,i,j,k,prob_class);
			}
		}
	}

	for(i=0;i<10;i++){
		printf("%d\n\n ",i);
		for(j=0;j<192;j++){
			printf("%d ",j);
			for(k=0;k<5;k++){
				printf("%f ",prob[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	FILE *f2 = fopen("pp_tes.dat", "r"); 
	int test[3333][192];
	int label_pred[3333];
	int label_test[3333];
	for(i=0;i<3333;i++){
		for(j=0;j<192;j++){
			fscanf(f2,"%d",&test[i][j]);
		}
        fscanf(f2,"%d",&label_test[i]);
	}

	for(i=0;i<3333;i++){
		label_pred[i] = test_count(test[i],prob,prob_class);
	}
    int count=0;
	for(i=0;i<3333;i++){
		if(label_test[i]==label_pred[i]){
			count++;
		}
	}

	for(i=0;i<3333;i++){
		printf("testcount:%d ,originallabel:%d ,classifiedlabel:%d\n",i,label_pred[i],label_test[i]);
	}

	printf("accuracy of naive bayes classifier:%lf\n",(count/3333.0)*100);

	
	return 0;
}




float count_j(int train[][192], int label[], int class, int feature, int value, float prob_class[]){
	int i,j;
	float count=0.0,count1=0.0;
	for(i=0;i<6670;i++){
		if(label[i]==class){ 
			if(train[i][feature] == value){
				count++;
			}
			count1++;
		}
	}
	prob_class[class]=count1/6670.0;
	return count/count1;
}
int test_count(int test[],float prob[][192][5], float prob_class[]){
	float max = -9999.0;
	float sum;
	int i,j,ind=-1;
	for(i=0;i<10;i++){
		sum=0.0;
		for(j=0;j<192;j++){
			sum = sum + log(prob[i][j][test[j]]);
		}

		sum = sum + log(prob_class[i]);
		if(sum > max){
			max = sum;
			ind = i;
		}
	}
    return ind;
}
