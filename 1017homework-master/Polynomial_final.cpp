#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct polynomial{
	int coef;                       //多項式的係數
	int expon;                      //多項式的指數
};

struct MyPoly{
	polynomial terms[MAX];          //多項式陣列
	int size;                       //多項式大小
	MyPoly();                       //建構子 初始化 size = 0
	MyPoly(const char*);            //建構子 讀入檔案
	
	void ShowPoly();                //印出多項式內容
	MyPoly Add(MyPoly);             //多項式相加
	MyPoly SingleMult(polynomial);           //將多項式乘上一多項式的一個項次 
	int Lead_Exp();                 //回傳多項式中最大指數的次方
	void Attach(int, int);          //新增 1 個項式到多項式中
	void Remove(int);               //刪除多項式中的某一指數
	MyPoly Mult(MyPoly); 
  	void read(const char*);
};

int main(){
	MyPoly poly1;
	MyPoly poly2;
	MyPoly tempoly;
	int select=1,tem;
	polynomial singleterm;
	while(select!=0){
		printf("===========================\n");
		printf("1. read poly\n2. print poly\n3. poly add\n4. poly mult a term\n5. print the biggest coef in poly\n6. new a term\n7. delete a term in poly\n8. poly mult\noption: ");
		scanf("%d",&select);
		switch(select){
			case 1:
				poly1.read("B1.txt");
				poly2.read("B2.txt");

				break;
			case 2:
				printf("which poly do you want to print?(1or2)\n");
				scanf("%d",&tem);
				if(tem==1){
					poly1.ShowPoly();
				}
				else if(tem==2){
					poly2.ShowPoly();
				}
				break;
			case 3:
				poly1.ShowPoly();
				printf("+\n");
				poly2.ShowPoly();
				printf("=\n");
				tempoly=poly1.Add(poly2);
				tempoly.ShowPoly();
				break;
			case 4:
				printf("which poly do you want to mult a term?(1or2)\n");
				scanf("%d",&tem);
				printf("pls enter the term you want to mult.(coef expon)\n");
				if(tem==1){
					
					scanf("%d %d",&singleterm.coef,&singleterm.expon);
					tempoly=poly1.SingleMult(singleterm);
					tempoly.ShowPoly();
				}
				else if(tem==2){
					
					scanf("%d %d",&singleterm.coef,&singleterm.expon);
					tempoly=poly2.SingleMult(singleterm);					
					tempoly.ShowPoly();
				}				
				break;
			case 5:
				printf("which poly do you want to print the biggest coef in poly?(1or2)\n");
				scanf("%d",&tem);
				if(tem==1){
					printf("the lead exp= %d\n",poly1.Lead_Exp());
				}
				else if(tem==2){
					printf("the lead exp= %d\n",poly2.Lead_Exp());
				}				
				break;	
			case 6:
				printf("which poly do you want to attach a term?(1or2)\n");
				scanf("%d",&tem);
				printf("pls enter the term you want to attach.(coef expon)\n");
				if(tem==1){
					
					scanf("%d %d",&singleterm.coef,&singleterm.expon);
					poly1.Attach(singleterm.coef,singleterm.expon);
					poly1.ShowPoly();
				}
				else if(tem==2){
					
					scanf("%d %d",&singleterm.coef,&singleterm.expon);
					poly2.Attach(singleterm.coef,singleterm.expon);
					poly2.ShowPoly();
				}				
				
				break;
			case 7:
				printf("which poly do you want to delete a term?(1or2)\n");
				scanf("%d",&tem);
				printf("pls enter the term you want to delete.(expon)\n");
				if(tem==1){
					
					scanf("%d",&singleterm.expon);
					poly1.Remove(singleterm.expon);
					poly1.ShowPoly();
				}
				else if(tem==2){
					
					scanf("%d",&singleterm.expon);
					poly2.Remove(singleterm.expon);
					poly2.ShowPoly();
				}				
				break;
			case 8:
				poly1.ShowPoly();
				printf("*\n");
				poly2.ShowPoly();
				printf("=\n");
				tempoly=poly1.Mult(poly2);
				tempoly.ShowPoly();
				break;											
		}
		
	}
	

	
	
	return 0;
} 

MyPoly::MyPoly()
{
	size=0;
	int i;
	for(i=0;i<MAX;i++){
		terms[i].expon=0;
		terms[i].coef=0;
	}
	//printf("No arg\n");
}

MyPoly::MyPoly(const char* filename)
{
	FILE *fptr=NULL;
	fptr=fopen(filename, "r");
	size=0;
	while(!feof(fptr)) 
	{
		fscanf(fptr,"%d %d", &terms[size].coef, &terms[size].expon);
		size++;
	}
	fclose(fptr);
	
}
void MyPoly::read(const char* filename)
{
	FILE *fptr=NULL;
	fptr=fopen(filename, "r");
	size=0;
	while(!feof(fptr)) 
	{
		fscanf(fptr,"%d %d", &terms[size].coef, &terms[size].expon);
		size++;
	}
	fclose(fptr);
	
}

void MyPoly::ShowPoly()
{
	for(int i=0;i<size;i++)
	{
		printf("%dx^%d+", terms[i].coef, terms[i].expon);
	}
	printf("\b \n");
}

MyPoly MyPoly::SingleMult(polynomial p)
{
	MyPoly result;
	//result.size=0;
	//printf("%d %d\n",p.coef, p.expon);
	for(int i=0;i<size;i++)
	{
		result.terms[i].coef=terms[i].coef*p.coef;
		result.terms[i].expon=terms[i].expon+p.expon;
		result.size++;
	}
	//printf("%d\n", result.size);
	return result;
	
	
}

MyPoly MyPoly::Add(MyPoly B)
{
	MyPoly result;
	int a_index=0, b_index=0;
	if(size==0){
		return B;
	}
	while(a_index<size&&b_index<B.size)
	{
		if(terms[a_index].expon<B.terms[b_index].expon)
		{
			result.terms[result.size]=B.terms[b_index];
			result.size++;
			b_index++;
		}
		else if(terms[a_index].expon==B.terms[b_index].expon)
		{
			int result_coef=terms[a_index].coef + B.terms[b_index].coef;
			if(result_coef!=0)
			{
				result.terms[result.size].coef=result_coef;
				result.terms[result.size].expon=B.terms[b_index].expon;
			}
			result.size++;
			a_index++;
			b_index++;
		}
		else
		{
			result.terms[result.size]=terms[a_index];
			result.size++;
			a_index++;
		}
	}
	for(;a_index<size;a_index++)
	{
		result.terms[result.size]=terms[a_index];
		result.size++;
	}
	for(;b_index<size;b_index++)
	{
		result.terms[result.size]=B.terms[b_index];
		result.size++;
	}
	return result;
	
}

int MyPoly::Lead_Exp()
{
	return terms[0].expon;
	
}

void MyPoly::Attach(int coef, int expon)	
{

	for(int i=0;i<size;i++)
	{
		if(expon>terms[i].expon)
		{
			for(int j=size;j>i;j--)
			{
				terms[j]=terms[j-1];
			}
			terms[i].coef=coef;
			terms[i].expon=expon;
			size++;
			break;
		}
		else if(expon==terms[i].expon)
		{
			terms[i].coef+=coef;
			break;
		}
	}

	
}
void MyPoly::Remove(int num)
{
	int index=0;
	for(int i=0;i<size;i++)
	{
		if(terms[i].expon==num)
		{
			index=i;
			break;
		}
	}
	for(int i=index;i<size;i++)
	{
		terms[i]=terms[i+1];
	}
	size--;
	
}

MyPoly MyPoly::Mult(MyPoly B)
{
     MyPoly result;
     polynomial resplus;
     int a_index=0;
     while(a_index<size){
     	resplus.coef=terms[a_index].coef;
     	resplus.expon=terms[a_index].expon;
     	result=result.Add(B.SingleMult(resplus));
     	a_index++;
	 }
	result.size=result.size-B.size;	
	 
	 return result;
}

