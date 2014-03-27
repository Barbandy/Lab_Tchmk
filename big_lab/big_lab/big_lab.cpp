
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "conio.h"
#include <windows.h>
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#pragma warning(disable: 4996)

//Меню 
//----------------------------------------------------
int printMenu()
{
	char menu;
	printf("\n\n\n\n _________________________\n");
	printf("|_________________________|\n");
	printf("|1.Сумма                  |\n");
	printf("|_________________________|\n");
	printf("|2.Разность               |\n");
	printf("|_________________________|\n");
	printf("|3.Умножение              |\n");
	printf("|_________________________|\n");
	printf("|Esc.Выход                |\n");
	printf("|_________________________|\n\n\n\n\n");
	menu=_getch(); 
	return menu;
}
//Функция узнает длины файлов 
//----------------------------------------------------
void Sizeoff(char* fname1,char* fname2, long &size1,long &size2)
{
	FILE *fp1 = fopen(fname1, "r");
	if(NULL==fp1)
		exit(1);
	FILE *fp2 = fopen(fname2, "r");
	if(NULL==fp2)
		exit(1);
	fseek(fp1,0,SEEK_END);
	size1 = ftell(fp1);
	fseek(fp1,0,SEEK_SET);
	fseek(fp2,0,SEEK_END);
	size2 = ftell(fp2);
	fseek(fp2,0,SEEK_SET);
	fclose(fp1);
	fclose(fp2);
}
//Функция записи в txt 
//----------------------------------------------------
void WriteFt(int* c,long &sizen, char *fname )
{
	printf("записан в файл out_f.txt.\n");
	FILE *fp = fopen(fname, "w");
	if(NULL==fp)
	{
		printf("\nНе удалось открыть файл \n");
		return;
	}
	for(int i=sizen; i>0; i--)
	{
		fprintf(fp,"%d",c[i]); 
	}
	fclose(fp);

}
//Функция умножения
//----------------------------------------------------
int Multiplication(int *a,int *b,int *c,long &size1,long &size2)
{
	int i,j;
	long len_m;
	len_m = size1+size2;
	for (i = 0; i<= size1; i++)
		for (j = 0; j <= size2; j++)
			c[i + j - 1] += a[i] * b[j];

	for (i = 0; i < len_m; i++)
	{
		c[i + 1] +=  c[i] / 10;
		c[i] %= 10;
	}
	for(i=len_m;i>=0;i--)	//избавляемся от лидирующих нулей
		if(c[i]==0)
			len_m--;
		else break;

		return len_m;
}
//Сравним числа
//----------------------------------------------------
int Compare(int *a,int *b,long &size1, long &size2, long &len_)
{
	int k = 3; //  числа одинаковой длинны
	len_ = size1;
	if (size1 > size2)
	{
		len_ = size1;
		k = 1; // первое число длиннее второго
	}
	else
		if (size2 > size1)
		{
			len_ = size2;
			k = 2; //  второе число длиннее первого
		}
		else // если числа одинаковой длинны, то необходимо сравнить их веса
			for (int i = 0; i < len_;i++) // поразрядное сравнение весов чисел
			{
				if (a[i] > b[i]) // если разряд первого числа больше
				{
					k = 1; //  первое число длиннее второго
					break; 
				}

				if(b[i] > a[i]) // если разряд второго числа больше
				{
					k = 2; //  второе число длиннее первого
					break; 
				}
			} 
			return k;
}
//Вычитание
//----------------------------------------------------
int Submit(int *a,int *b, int *c,long &len_)
{
	int i,loan=0,t=0;

	for(i=0;i<=len_;i++)
	{
		t=a[i]-b[i]-loan;
		if(t>=0)	//если нет заема, всё ок
		{
			c[i]=t;	//сохраняем
			loan=0;
		}
		else		 //если есть заем, вычитаем согласно основанию
		{
			c[i]=10+t;	 
			loan=1;	//ставим флаг, на следующем шаге вычтем
		}            
	}
	return 0;
}
// Сложение
//----------------------------------------------------
int Summ(int *a, int *b, long lent)
{
	int i;
	for ( i = 0; i < lent; i++)
	{
		b[i] += a[i]; // суммируем последние разряды чисел
		b[i + 1] += (b[i] / 10); // если есть разряд для переноса, переносим его в следующий разряд
		b[i] %= 10; // если есть разряд для переноса он отсекается
	}
	//Избавляемся от нулей перед числом
	for( i=lent;i>=0;i--)
	{
		if(b[i] == 0)
			lent--;
		else break;
	}
	return lent;
}
void ReadFt(char*fname1,char*fname2,int*a,int*b,long &size1,long &size2)
{
	int i;
	FILE *fp1,*fp2;
	fp1=fopen(fname1,"r");
	if(fp1==NULL)
	{
		printf("\n Файл скорее всего не найден...");
		return;
	}
	fp2=fopen(fname2,"r");
	if(fp2==NULL)
	{
		printf("\n Файл скорее всего не найден...");
		return;
	}
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);

	for(i = size1; i>0; i--)
		a[i] = fgetc(fp1) - 48;
	for(i = size2; i>0; i--)
		b[i] = fgetc(fp2) - 48;

	fclose(fp1);
	fclose(fp2);
	printf("\nДанные успешно считаны.");
}
//----------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	 printf("\n\tПрограмма.\n\n");

	//Объявление переменных
	//---------------------------------------------------
	char menu,key;
	char *fname_in1 = "in_f1.txt",
		*fname_in2	= "in_f2.txt",
		*fname_out	= "out_f.txt";
	long size1 =0,size2=0,lent=0,len_=0;
	int i=0,*a,*b;
	Sizeoff(fname_in1,fname_in2,size1,size2);
					if(size1>size2)
						lent = size1+1;
					else lent = size2+1;
					//Выделяем память под числа
					//---------------------------------------------------
					a = (int *) malloc((lent+2)*sizeof(int));
					b = (int *) malloc((lent+2)*sizeof(int));
					//----------------------------------------------------
					for(i = 0; i <= lent; i++)
					{
						a[i] = 0;
						b[i] = 0;
					}
					ReadFt(fname_in1,fname_in2,a,b,size1,size2);

	//------------------------------------------------------
	system("pause");
	do
	{
		menu = printMenu();
		switch(menu)
		{	
		case '1':// Сложение 
			//----------------------------------------------------
			{	
				printf("\n\tSUM\n");
				lent = Summ(a,b,lent);
				printf("\nResults: ");
				WriteFt(b,lent,fname_out);
				printf("\n\n");
				break;
			}
		case '2': // Вычитание 
			//---------------------------------------------------
			printf("\n\tSUB\n");
			{	int k=0;
			int *c = (int*)malloc((lent+2)*sizeof(int));
			for(i = 0; i <= lent; i++)
				c[i] = 0;
			k = Compare(a,b,size1,size2,len_);
			if(k==1)  Submit(a,b,c,len_);	 //1>2
			if(k==2)  Submit(b,a,c,len_);	 //2>1
			WriteFt(c,len_,fname_out);
			free(c);
			break;
			}
		case '3': //Умножение
			//----------------------------------------------------
			{
				printf("\n\tMUL\n");
				long len_m=0;
				len_m = size1+size2;
				int *c =(int*)malloc((len_m+2)*sizeof(int));
				for(i=0;i<=len_m;i++)
					c[i]=0;
				len_m = Multiplication(a,b,c,size1,size2);
				WriteFt(c,len_m,fname_out);
				free(c);
				break;
			}

		default: if(menu!=27) 
				 { 
					 printf("Неверный пункт меню.\nВведите команду\n\n"); 
				 } 
		}
	}while (menu!=27);;
	free(b);
	free(a);				

	_CrtDumpMemoryLeaks();
	return 0;
}



