/*Список необходимых функций.
Работа с файлами:
● Загрузка большого числа из файла в бинарном формате.				+
● Загрузка большого числа из файла в текстовом десятичном формате. +
● Сохранение большого числа в файл в бинарном формате.				+
● Сохранение большого числа в файл в текстовом десятичном формате.	+
Арифметические операции:												  =
● Сложение двух больших чисел										 +
● Вычитание двух больших чисел										  +
● Умножение двух больших чисел										   +
● Деление двух больших чисел											+
● Вычисление остатка от деления одного большого числа на другое			 +
● Возведение большого числа в степень большого числа.						 -
Для данных функция необходимо разработать консольный интерфейс:			 +
<название_программы> <файл_с_первым_большим_числом> <операция> <файл_со_вторым_большим_числом> <результирующий_файл> [­b] [файл_содержащий_большое_число_модуль] -
Если передан ключ ­b то, что работа идет с бинарными файлами (порядок бит little­endian). -
Если передан файл содержащий большое число модуль, то все операции вычисляются по модулю этого числа*/	//-+

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
//#include "conio.h"
//#include <windows.h>
#pragma warning(disable: 4996)


//Проверка знака
bool minus(int sign)
{
	if(sign==0)
		return false;

	return true;
}
void PrintStart()
{
	printf("Program TCHMK.\n");
	printf("Enter the input parameters:\n");
	printf("\n<name of program> <filename A> <operation>\n<filename B> <result filename C> [b] [filename with module]\n\n");
	printf("Parametr: \n");
	printf("\"-b\" - binfile\n");
	printf("Operations: \n");
	printf("\"+\" - addition\n");
	printf("\"-\" - subtraction\n");
	printf("\"*\" - multiplication\n");
	printf("\"/\" - division\n");
	printf("\"%\" - taking the remainder\n");
	printf("\"^\" - involution (pow)\n");
}
//Проверка
bool checkParam(int argc, char* argv[])
{
	if (argc < 2)
		return false;

	if (argc > 8)
	{
		printf("\nToo many parameters.\n");
		PrintStart();
		return false;
	}

	if ((argc > 1) && (argc < 7))
	{
		printf("\nIntroduced not all parameters.\n");
		PrintStart();
		return false;
	}

	if (strlen(argv[2]) > 1)
	{
		printf("Invalid input operation.\n");
		PrintStart();
		return false;
	}

	return true;
}
//Функция узнает длины файлов 
//----------------------------------------------------
void Sizeoff(char* bin,char* fname1,char* fname2,char* fmodule, long &size1,long &size2,long &sizem)
{
	char *flag=0;
	if(strcmp(bin,"-b")==0)
		flag = "rb";
	else
		flag = "r";
	FILE *fp1 = fopen(fname1, flag);
	if(NULL==fp1)
		return;
	FILE *fp2 = fopen(fname2, flag);
	if(NULL==fp2)
		return;
	FILE *fp3 = fopen(fmodule, flag);
	if(NULL==fp3)
		return;
	fseek(fp1,0,SEEK_END);
	size1 = ftell(fp1);
	fseek(fp1,0,SEEK_SET);
	fseek(fp2,0,SEEK_END);
	size2 = ftell(fp2);
	fseek(fp2,0,SEEK_SET);
	fseek(fp3,0,SEEK_END);
	sizem = ftell(fp3);
	fseek(fp3,0,SEEK_SET);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}
//Функции записи в txt и bin
//----------------------------------------------------
void WriteFt(char* bin,int* c,long &sizen, char *fname,int znak)
{
	int i=0;

	char *flag=0;
	char sign=0;
	if(strcmp(bin,"-b")==0)
		flag = "wb";
	else
		flag = "w";
	FILE *fp = fopen(fname, flag);
	if(NULL==fp)
	{
		printf("\nCan't open this file \n");
		return;
	}
	printf("\n");
	if(znak==1 &&(strcmp(bin,"-b")==0))
		fwrite(&"-", sizeof(char), 1, fp);
	else if(znak==1)	
		fprintf(fp,"%c",'-');



	if(strcmp(bin,"-b")==0)
	{
		for(i=sizen; i>0; i--)
		{
			fwrite(&c[i], sizeof(int), 1, fp); 
		}
	}
	else
	{
		for(i=sizen; i>0; i--)
		{
			fprintf(fp,"%d",c[i]); 
		}
	}


	printf("Result written to the file %s.\n",fname);
	fclose(fp);

}
//----------------------------------------------------
void WriteFtR(char* bin,int &R,long sizen, char *fname )
{
	char *flag=0;
	char sign=0;
	if(strcmp(bin,"-b")==0)
		flag = "bw";
	else
		flag = "w";

	FILE *fp = fopen(fname, flag);
	if(NULL==fp)
	{
		printf("\nCan't open this file \n");
		return;
	}
	if(strcmp(bin,"-b")==0)
	{
		fwrite(&R, sizeof(int), 1, fp);
	}
	else
		fprintf(fp,"%d",R); 

	printf("\nResult written to the file %s.\n",fname);
	fclose(fp);

}
//Функции умножения	 
//----------------------------------------------------
int SMul(int *a,int *b,int *c,long &size1,long &size2)
{
	int i=0;
	long sizec=size1+size2;

	for (i = 0; i<= size1; i++)
		c[i ] += a[i] * b[size2];

	for (i = 0; i < sizec; i++)
	{
		c[i + 1] +=  c[i] / 10;
		c[i] %= 10;
	}
	for(i=sizec;i>=0;i--)	//избавляемся от лидирующих нулей
		if(c[i]==0)
			sizec--;
		else break;
		return sizec;
}
//----------------------------------------------------
int Multiplication(int *a,int *b,int *c,long &size1,long &size2)
{
	int i=0,j=0;
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
int Multiplication_m(int *a,int *b,int *c,long &size1,long &size2)
{
	int j=0;
	long len_m=0;
	//len_m = size1*size2;
	for( int i=b[j]; i>0; i--)
	{
		len_m=Multiplication(a,a,c,size1,size1);
	}
	///

	return len_m;
}

//Функции сравния
//----------------------------------------------------
// Больше
bool bolshe_d(int * a, long size1, int * b, long size2)
{
	int i=0;

	if (size1>size2)
		return true;
	else if (size2>size1) 
		return false;
	else
		for (i=0;i<size1;i++)
		{
			if (a[i]>b[i]) 
				return true;
			else if (b[i]>a[i]) 
				return false;
		}

		return false;
}
// Равно
bool ravno_d(int * a, long size1, int * b, long size2)
{
	int i=0;

	if (size1!=size2) 
		return false;
	else
		for (i=0;i<size1;i++)
		{
			if (a[i]!=b[i])
				return false;
		}

		return true;
}
// Больше
bool bolshe(int * a, long size1, int * b, long size2)
{
	int i=0;

	if (size1>size2)
		return true;
	else if (size2>size1) 
		return false;
	else
		for (i=size1; i>=0; i--)
		{
			if (a[i]>b[i]) 
				return true;
			else if (b[i]>a[i]) 
				return false;
		}

		return false;
}
// Равно
bool ravno(int * a, long size1, int * b, long size2)
{
	int i=0;

	if (size1!=size2) 
		return false;
	else
		for (i=size1; i>=0; i--)
		{
			if (a[i]!=b[i])
				return false;
		}

		return true;
}
//Функция вычитания
//----------------------------------------------------
void Submit(int *a,int *b, int *c,long &len_)
{
	int i=0,loan=0,t=0;

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
	for(i=len_;i>=0;i--)	//избавляемся от лидирующих нулей
		if(c[i]==0)
			len_--;
		else break;

}
// Функция сложения
//----------------------------------------------------
int Summ(int *a, int *b, long lent)
{
	int i=0;
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
//Функции деления
// Первое вычитаемое
void ForDiv(int * a, long size1, int * b, long size2, int * l, long &nl)
{
	int i=0;

	for (i=0; i<size2; i++) 
		l[i] = a[i];
	nl = size2;

}
// Дополняем нулями
void Nol(int *ar, long &m, long n)
{
	int i=0,j=0;

	for(i=0; i<n-m; i++)
		for(j=n-1; j>0; j--)
			ar[j]=ar[j-1];

	for(i=0; i<n-m; i++)
		ar[i]=0;

	m=n;	
}
// Вычитание
void Sub(int * a, long &n, int * b, long &m,int *c)
{
	int i=0,j=0,o=0;

	//Дополняем нулями
	if(n>m) Nol(b,m,n);
	else if(n<m) Nol(a,n,m);
	//Обнуляем резултат
	for(i=0; i<n; i++)
		c[i]=0;
	//Вычитание
	o=0;
	for(j=n-1; j>=0; j--) 
	{
		c[j] += a[j] - b[j] + o;
		o=0;
		if(c[j]<0)
		{
			o=-1;
			c[j]=10 + c[j];
		}
	}
	//Избавляемся от ведущих нулей
	while(c[0]==0) {
		for(j=0; j<n-1; j++)
			c[j]=c[j+1];
		if(n!=1) n--; else break;
	}
	while(b[0]==0) {
		for(j=0; j<m-1; j++)
			b[j]=b[j+1];
		if(m!=1) m--; else break;
	}
	//Вывод результата
	for(i=0; i<n; i++)
		a[i] = c[i];
}
//---------------------------------------------------
void RereverseMass(int *R, long size)
{
	int i = 0,j=0;
	int *k;
	k=(int*)malloc((size)*sizeof(int));
	for (i = 0; i<size; i++)
	{
		k[j]=R[i];
		j++;
	}
	printf("\n");
	j=0;
	for(i=size;i>0;i--)	{
		R[i]=k[j];
		j++;
	}
	free(k);
}		   
void reverseMass(int *R, long size)
{
	int i = 0,j=0, temp=0;
	int *k;
	k=(int*)malloc((size)*sizeof(int));
	for (i = size; i>0; i--)
	{
		k[j]=R[i];
		j++;
	}
	for(i=0;i<size;i++)
		R[i]=k[i];
	free(k);
}		   

//Деление
void Div(int *a,int *b,int *q,int *r,int *c,int *m,long &size1,long &size2)
{
	int i=0,j=0;
	long nq=0,nm=0,nr=0,start=0;
	reverseMass(a,size1);
	reverseMass(b,size2);

	ForDiv(a,size1,b,size2,r,nr);
	for (i=0; i<size2; i++)
		m[i] = b[i];
	nm = size2;
	start = nr;
	if (!(ravno_d(r,nr,a,size1) && bolshe_d(b,size2,a,size1)))
	{
		for (i=0; bolshe_d(r,nr,m,nm) || ravno_d(r,nr,m,nm); i++){
			Sub(r,nr,m,nm,c);
		}
		q[nq] = i;
	}
	nq++;

	for (i=start; i<size1; i++)
	{
		r[nr] = a[i]; nr++;

		for (j=0; bolshe_d(r,nr,m,nm) || ravno_d(r,nr,m,nm); j++){
			Sub(r,nr,m,nm,c);
		}

		q[nq] = j; nq++;
	}
	while(q[0]==0) {
		for(j=0; j<nq-1; j++)
			q[j]=q[j+1];
		if(nq!=1) nq--; else break;
	}

	RereverseMass(q,nq);
	RereverseMass(r,nr);

	size1=nq;
	size2=nr;
}
//----------------------------------------------------
void SDiv(int *a,int *b,int *q,int &R ,long &size1)
{
	int i=0,temp=0;

	for(i=size1;i>0;i--)
	{
		temp = R*10 +a[i];
		q[i] = temp/b[1];
		R = temp -q[i]*b[1];
	}

}
//Функция чтения
void ReadFt(char *bin,char*fname1,char*fname2,char*fmodule,int*a,int*b,int *mod,long &size1,long &size2,long &sizem,int &sign1,int&sign2)
{	
	int i=0;
	char *flag=0;
	if(strcmp(bin,"-b")==0)
		flag = "rb";
	else
		flag = "r";
	FILE *fp1,*fp2,*fp3;
	fp1=fopen(fname1,flag);
	if(fp1==NULL)
	{
		printf("\nCan't open this file ");
		return;
	}
	fp2=fopen(fname2,flag);
	if(fp2==NULL)
	{
		printf("\nCan't open this file ");
		return;
	}
	fp3=fopen(fmodule,flag);
	if(fp3==NULL)
	{
		printf("\nCan't open this file ");
		return;
	}
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);
	fseek(fp3, 0, SEEK_SET);

	char sign[2];

	sign[0] = fgetc(fp1);
	if(sign[0]=='-'){
		sign1=1;
		size1-=1;
	}
	else
		fseek(fp1, 0, SEEK_SET);

	if(strcmp(bin,"-b")==0)
	{  
		for (i=size1; i>0; i--)
		{
			a[i] = fgetc(fp1);
		}
		// size1=nSize1;
	}
	else
		for(i = size1; i>0; i--){ 
			a[i] = fgetc(fp1)- 48;
		}

		printf("\n");
		//Избавляемся от нулей перед числом
		for( i=size1;i>=0;i--)
		{	
			if(a[i] == 0)	{
				size1--;}
			else break;
		}
		sign[0] = fgetc(fp2);
		if(sign[0]=='-')
		{
			sign2=1;
			size2-=1;
		}
		else
			fseek(fp2, 0, SEEK_SET);
		if(strcmp(bin,"-b")==0)
		{ 
			for (i=size2; i>0; i--)
			{
				b[i] = fgetc(fp2);
			}
		}
		else
			for(i = size2; i>0; i--)
			{
				b[i] = fgetc(fp2) - 48;
			}

			//Избавляемся от нулей перед числом
			for( i=size2;i>=0;i--)
			{
				if(b[i] == 0 )	{
					size2--;}
				else break;
			}
			//--------------------------------------->
			for(i = sizem; i>0; i--)
			{
				mod[i] = fgetc(fp3) - 48;
			}

			fclose(fp1);
			fclose(fp2);
			fclose(fp3);
			printf("\nData read successfully.");
}
//----------------------------------------------------

//----------------------------------------------------

int main(int argc, char* argv[])
{	
	/*PrintStart();

	char *fname_in1 = argv[1];
	char *act = argv[2];
	char *fname_in2 =argv[3];
	char *fname_out = argv[4];
	char *bin = argv[5];
	char *fmodule = argv[6];
	if(!checkParam(argc,argv))
		return 0;*/
	//Объявление переменных
	//---------------------------------------------------
	char act[2],bin[4];
	char fname_in1 [15] ,fname_in2 [15],fname_out [15], fmodule[15];
	printf("Program TCHMK.\n");
	printf("Enter the input parameters:\n");
	printf("\n<name of program> <filename A> <operation>\n<filename B> <result filename C> [b] [filename with module]\n\n");
	scanf("%s %s %s %s %s %s",fname_in1,act,fname_in2,fname_out,bin, fmodule);
	long size1 =0,size2=0,sizem=0,lent=0,len_=0;
	int i=0,*a,*b,sign1=0,sign2=0,*mod;

	Sizeoff(bin,fname_in1,fname_in2,fmodule,size1,size2,sizem);
	if(size1>size2)
		lent = size1+1;
	else lent = size2+1;
	//Выделяем память под числа
	//---------------------------------------------------
	a = (int *) malloc((lent+2)*sizeof(int));
	b = (int *) malloc((lent+2)*sizeof(int));
	mod = (int *) malloc((sizem+2)*sizeof(int));
	//---------------------------------------------------
	for(i = 0; i <= lent; i++)
	{
		a[i] = 0;
		b[i] = 0;
	}
		for(i = 0; i <= sizem; i++)
			mod[i] = 0;
	

	ReadFt(bin,fname_in1,fname_in2,fmodule,a,b,mod,size1,size2,sizem,sign1,sign2);

	//------------------------------------------------------
	// Сложение 
	//----------------------------------------------------
	if(act[0] == '+')
	{	
		int sign=0;
		if(minus(sign1) & minus(sign2)){
			sign =1;
			//goto summ;
			printf("\n\tSUM\n");
			lent = Summ(a,b,lent);
			WriteFt(bin,b,lent,fname_out,sign);
			printf("\n\n");
			free(a);
			free(b);
			free(mod);
			return 0;
		}
		if(minus(sign1) || minus(sign2))
		{
			//goto dif;
			printf("\n\tSUB\n");
			int k=0;
			int *c = (int*)malloc((lent+2)*sizeof(int));
			for(i = 0; i <= lent; i++)
				c[i] = 0;
			if(bolshe(a,size1,b,size2))
			{
				if(minus(sign1))
					sign=1;
				len_=size1;
				Submit(a,b,c,len_);	 
			}
			else if(bolshe(b,size2,a,size1)) 
			{	if(minus(sign2) && !minus(sign1))
			sign=1;
			else
				sign=0;
			len_=size2;
			Submit(b,a,c,len_);
			}
			else if(ravno(a,size1,b,size2))
				len_=1;

			WriteFt(bin,c,len_,fname_out,sign);
			free(c);
			free(a);
			free(b);
			free(mod);
			return 0;
		}

		//summ:;
		printf("\n\tSUM\n");
		lent = Summ(a,b,lent);
		WriteFt(bin,b,lent,fname_out,sign);
		printf("\n\n");
	}

	// Вычитание 
	//---------------------------------------------------
	else if(act[0] == '-')
	{	int sign=0;
	if(!minus(sign1) && minus(sign2))
	{
		//goto summ;
		printf("\n\tSUM\n");
		lent = Summ(a,b,lent);
		WriteFt(bin,b,lent,fname_out,sign);
		printf("\n\n");
		free(a);
		free(b);
		free(mod);
		return 0;
	}

	//dif:
	printf("\n\tSUB\n");
	int k=0;
	int *c = (int*)malloc((lent+2)*sizeof(int));
	for(i = 0; i <= lent; i++)
		c[i] = 0;
	if(bolshe(a,size1,b,size2))
	{
		if(minus(sign1))
			sign=1;
		len_=size1;
		Submit(a,b,c,len_);	 
	}
	else if(bolshe(b,size2,a,size1)) 
	{	if(minus(sign2) && !minus(sign1))
	sign=1;
	else
		sign=0;
	len_=size2;
	Submit(b,a,c,len_);
	}
	else if(ravno(a,size1,b,size2))
		len_=1;

	WriteFt(bin,c,len_,fname_out,sign);
	free(c);
	}
	//Умножение
	//----------------------------------------------------
	else if(act[0] =='*')
	{
		int sign=1;
		if(minus(sign1) && minus(sign2))
			sign=0;
		if(!minus(sign1) && !minus(sign2))
			sign =0;

		printf("\n\tMUL\n");
		long len_m=0;
		len_m = size1+size2;
		int *c =(int*)malloc((len_m+2)*sizeof(int));
		for(i=0;i<=len_m;i++)
			c[i]=0;
		len_m = Multiplication(a,b,c,size1,size2);
		WriteFt(bin,c,len_m,fname_out,sign);
		free(c);
	}
	//Деление
	//----------------------------------------------------
	else if(act[0] =='/' || act[0]=='%')	
	{	
		int sign=1;
		if(minus(sign1) && minus(sign2))
			sign=0;
		if(!minus(sign1) && !minus(sign2))
			sign =0;

		printf("\n\tDIV\n '/' and % \n");
		int *c = (int*)malloc((lent+2)*sizeof(int)); //для подсчетов
		int *q = (int*)malloc((lent+2)*sizeof(int)); //частное
		int *r = (int*)malloc((lent+2)*sizeof(int)); //остаток
		int *m = (int*)malloc((lent+2)*sizeof(int)); //вычетаемое
		for(i = 0; i <= lent; i++)
		{
			q[i] = 0;
			r[i] = 0;
			m[i] = 0;
			c[i] = 0;
		}

		int R=0 ,j=0;
		if(size1<=size2 ||b[size2]<0)
		{
			printf("\nIncorrect input data\n");
			free(q),free(r),free(m),free(c),free(b),free(a),free(mod);
			return 0;
		}
		if(size2==1)
		{
			SDiv(a,b,q,R,size1);
			if(act[0] =='/')
				WriteFt(bin,q,size1,fname_out,sign);
			if(act[0]=='%')
				WriteFtR(bin,R,1,fname_out);
			free(q),free(r),free(m),free(c),free(b),free(a),free(mod);
			return 0;
		}
		Div(a,b,q,r,c,m,size1,size2);

		if(act[0] =='/')
			WriteFt(bin,q,size1,fname_out,sign);
		if(act[0]=='%')
			WriteFt(bin,r,size2,fname_out,0);

		free(q);
		free(r);
		free(m);
		free(c);
	}

	else if(act[0] =='^')
	{
		printf("\n\t^MUL^\n");
		long len_m=0;
		len_m = size1*size2;
		int *c =(int*)malloc((len_m+2)*sizeof(int));
		for(i=0;i<=len_m;i++)
			c[i]=0;
		len_m = Multiplication_m(a,b,c,size1,size2);
		WriteFt(bin,c,len_m,fname_out,0);
		free(c);

	}

	free(b);
	free(a);
	free(mod);
	return 0;
}



