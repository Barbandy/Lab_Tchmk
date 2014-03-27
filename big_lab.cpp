
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "conio.h"
#include <windows.h>
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>
#pragma warning(disable: 4996)


//������� ������ ����� ������ 
//----------------------------------------------------
void Sizeoff(char* bin,char* fname1,char* fname2, long &size1,long &size2)
{
	 char *flag=0;
	if(strcmp(bin,"-b")==NULL)
	flag = "rb";
	else
		flag = "r";
	FILE *fp1 = fopen(fname1, flag);
	if(NULL==fp1)
		exit(1);
	FILE *fp2 = fopen(fname2, flag);
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
//������� ������ � txt 
//----------------------------------------------------
void WriteFt(char* bin,int* c,long &sizen, char *fname )
{
	 char *flag=0;
	if(strcmp(bin,"-b")==NULL)
	flag = "wb";
	else
		flag = "wt";
	printf("������� � ���� %s.",fname);
	FILE *fp = fopen(fname, flag);
	if(NULL==fp)
	{
		printf("\n�� ������� ������� ���� \n");
		return;
	}
	for(int i=sizen; i>0; i--)
	{
		// fwrite(&c[i], sizeof(int), 1, fp);
		fprintf(fp,"%d",c[i]); 
	}
	fclose(fp);

}
//������� ���������
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
	for(i=len_m;i>=0;i--)	//����������� �� ���������� �����
		if(c[i]==0)
			len_m--;
		else break;

		return len_m;
}
//������� �����
//----------------------------------------------------
int Compare(int *a,int *b,long &size1, long &size2, long &len_)
{
	int k = 3; //  ����� ���������� ������
	len_ = size1;
	if (size1 > size2)
	{
		len_ = size1;
		k = 1; // ������ ����� ������� �������
	}
	else
		if (size2 > size1)
		{
			len_ = size2;
			k = 2; //  ������ ����� ������� �������
		}
		else // ���� ����� ���������� ������, �� ���������� �������� �� ����
			for (int i = 0; i < len_;i++) // ����������� ��������� ����� �����
			{
				if (a[i] > b[i]) // ���� ������ ������� ����� ������
				{
					k = 1; //  ������ ����� ������� �������
					break; 
				}

				if(b[i] > a[i]) // ���� ������ ������� ����� ������
				{
					k = 2; //  ������ ����� ������� �������
					break; 
				}
			} 
			return k;
}
//���������
//----------------------------------------------------
int Submit(int *a,int *b, int *c,long &len_)
{
	int i,loan=0,t=0;

	for(i=0;i<=len_;i++)
	{
		t=a[i]-b[i]-loan;
		if(t>=0)	//���� ��� �����, �� ��
		{
			c[i]=t;	//���������
			loan=0;
		}
		else		 //���� ���� ����, �������� �������� ���������
		{
			c[i]=10+t;	 
			loan=1;	//������ ����, �� ��������� ���� ������
		}            
	}
	return 0;
}
// ��������
//----------------------------------------------------
int Summ(int *a, int *b, long lent)
{
	int i;
	for ( i = 0; i < lent; i++)
	{
		b[i] += a[i]; // ��������� ��������� ������� �����
		b[i + 1] += (b[i] / 10); // ���� ���� ������ ��� ��������, ��������� ��� � ��������� ������
		b[i] %= 10; // ���� ���� ������ ��� �������� �� ����������
	}
	//����������� �� ����� ����� ������
	for( i=lent;i>=0;i--)
	{
		if(b[i] == 0)
			lent--;
		else break;
	}
	return lent;
}
void ReadFt(char *bin,char*fname1,char*fname2,int*a,int*b,long &size1,long &size2)
{
	int i;
	char *flag=0;
	if(strcmp(bin,"-b")==NULL)
	flag = "rb";
	else
		flag = "rt";
	FILE *fp1,*fp2;
	fp1=fopen(fname1,flag);
	if(fp1==NULL)
	{
		printf("\n ���� ������ ����� �� ������...");
		return;
	}
	fp2=fopen(fname2,flag);
	if(fp2==NULL)
	{
		printf("\n ���� ������ ����� �� ������...");
		return;
	}
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);
	
	for(i = size1; i>0; i--) {
		//fread(&a[i], sizeof(int), 1, fp1);
		//a[i] -=  48;
		a[i] = fgetc(fp1) - 48;
	}
	for(i = size2; i>0; i--) {
		//fread(&b[i], sizeof(int), 1, fp2);
		//b[i] -=  - 48;
		b[i] = fgetc(fp2) - 48;
	}

	fclose(fp1);
	fclose(fp2);
	printf("\n������ ������� �������.");
}
//----------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("\n\t���������.\n\n");

	//���������� ����������
	//---------------------------------------------------
	char act[2],bin[4];
	char fname_in1 [15] ,fname_in2 [15],fname_out [15];
	long size1 =0,size2=0,lent=0,len_=0;
	int i=0,*a,*b;
	printf("������� ������� ���������:");
	printf("\n<�������_���������> <����_�_������ ������� ������> <��������> <���� �� ������������� ������> <�������������� ����> [b]\n\n");
	scanf("%s %s %s %s %s",fname_in1,act,fname_in2,fname_out,bin);

	Sizeoff(bin,fname_in1,fname_in2,size1,size2);
	if(size1>size2)
		lent = size1+1;
	else lent = size2+1;
	//�������� ������ ��� �����
	//---------------------------------------------------
	a = (int *) malloc((lent+2)*sizeof(int));
	b = (int *) malloc((lent+2)*sizeof(int));
	//----------------------------------------------------
	for(i = 0; i <= lent; i++)
	{
		a[i] = 0;
		b[i] = 0;
	}
	ReadFt(bin,fname_in1,fname_in2,a,b,size1,size2);

	//------------------------------------------------------
	system("pause");
	// �������� 
	//----------------------------------------------------
	if(act[0] == '+')		
	{	
		printf("\n\tSUM\n");
		lent = Summ(a,b,lent);
		printf("\nResults: ");
		WriteFt(bin,b,lent,fname_out);
		printf("\n\n");
		system("pause");
	}

	// ��������� 
	//---------------------------------------------------
	else if(act[0] == '-')
	{
		printf("\n\tSUB\n");
		int k=0;
		int *c = (int*)malloc((lent+2)*sizeof(int));
		for(i = 0; i <= lent; i++)
			c[i] = 0;
		k = Compare(a,b,size1,size2,len_);
		if(k==1)  Submit(a,b,c,len_);	 //1>2
		if(k==2)  Submit(b,a,c,len_);	 //2>1
		WriteFt(bin,c,len_,fname_out);
		free(c);
		system("pause");
	}
	//���������
	//----------------------------------------------------
	else if(act[0] =='*')
	{
		printf("\n\tMUL\n");
		long len_m=0;
		len_m = size1+size2;
		int *c =(int*)malloc((len_m+2)*sizeof(int));
		for(i=0;i<=len_m;i++)
			c[i]=0;
		len_m = Multiplication(a,b,c,size1,size2);
		WriteFt(bin,c,len_m,fname_out);
		free(c);
		system("pause");
	}

	free(b);
	free(a);				

	_CrtDumpMemoryLeaks();
	return 0;
}



