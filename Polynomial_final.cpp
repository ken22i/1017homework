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
  
};

int main(){

	MyPoly poly1("B1.txt");
	MyPoly poly2("B2.txt");

	MyPoly poly4;
	MyPoly poly5;
	poly1.ShowPoly(); 
	poly2.ShowPoly();

	printf("=========\n");
	poly4 = poly1.Add(poly2);
	poly4.ShowPoly();
	printf("=========\n");
	poly5=poly1.Mult(poly2);
	
	poly5.ShowPoly();
	printf("%d\n",poly5.size);
	printf("%d\n",poly2.Lead_Exp());
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
     MyPoly resplus;
     int a_index=0, b_index=0,res_index=0,i=0;
     printf("%d",size);
     while(a_index<size){
     	    while(b_index<B.size){
     		resplus.terms[0].coef=terms[a_index].coef*B.terms[b_index].coef;
     		resplus.terms[0].expon=terms[a_index].expon+B.terms[b_index].expon;
     		
     		while(result.terms[i].expon!=0){
     			i++;
			 }
			result.size=i;
     		result=result.Add(resplus);
     		b_index++;
     		printf("%d",a_index);
		 }
		 a_index++;
	 }
	
	 
	 return result;
}

