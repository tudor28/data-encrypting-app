//Nitescu Tudor-Alin, 312AB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct baza {
	int nr;
	char cuv[20];
	struct baza *urm;
}BAZA;

BAZA* creare_baza(BAZA* cap_lista, int *n)
{
	FILE *f;
	BAZA *p, *q;
	int i,j=0;
	if((f=fopen("baza.txt","rt"))==NULL) {
		printf("Fisierul baza.txt nu a putut fi deschis.");
		exit(1);
	}
	fscanf(f,"%d",n);
	p=(BAZA*)malloc(sizeof(BAZA));
	if(p==NULL) {
		printf("Alocare dinamica esuata.");
		exit(1);
	}
	p->nr=j;
	fscanf(f,"%s",p->cuv);
	p->urm=NULL;
	cap_lista=p;
	for(i=2;i<=*n;i++) {
		q=(BAZA*)malloc(sizeof(BAZA));
		if(p==NULL) {
			printf("Alocare dinamica esuata.");
			exit(1);
		}
		j++;
		q->nr=j;
		fscanf(f,"%s",q->cuv);
		q->urm=NULL;
		p->urm=q;
		p=q;
	}
	fclose(f);
	return cap_lista;
}

int creare_nr(FILE *f, BAZA *cap_lista)
{
	BAZA *p;
	char c[20];
	int n=0,k=1;
	while(!feof(f)) {
		fscanf(f,"%s",c);
		for(p=cap_lista;p!=NULL&&k==1;p=p->urm)
			if(!strcmp(p->cuv,c)) {
				n=n*10+p->nr;
				k=0;
			}
		k=1;
	}
	return n;
}

BAZA* eliminare(BAZA *cap_lista, BAZA *p)
{
	BAZA *q;
	if(p==cap_lista) {
		q=cap_lista;
		cap_lista=q->urm;
		free(q);
	}
	else
	for(q=cap_lista;q!=NULL;q=q->urm)
		if( q->urm==p && q->urm->urm==NULL ) {
			q->urm=NULL;
			free(p);
		}
		else if(q->urm==p) {
			q->urm=q->urm->urm;
			free(p);
		}
	return cap_lista;
}

int indice(int n, BAZA *cap_lista)
{
	int	i=0;
	BAZA *p;
	for(p=cap_lista;p!=NULL;p=p->urm) {
		if(n==p->nr)
			return i;
		i++;
	}
	n++;
	while(1) {
		i=0;
		for(p=cap_lista;p!=NULL;p=p->urm) {
			if(n==p->nr)
				return i;
		i++;
	    }
		n++;
	}
}
int main()
{
	BAZA *p,*q,*cap_lista;
	int m1, m2, i, t=0, m[16], dim, k=0, s;
	FILE *f;
	
	cap_lista=creare_baza(cap_lista,&dim);
	
	if((f=fopen("mesaj1.txt","rt"))==NULL) {
		printf("Fisierul mesaj1.txt nu a putut fi deschis.");
		exit(1);
	}
	m1=creare_nr(f,cap_lista);
	fclose(f);
	
	if((f=fopen("mesaj2.txt","rt"))==NULL) {
		printf("Fisierul mesaj2.txt nu a putut fi deschis.");
		exit(1);
	}
	m2=creare_nr(f,cap_lista);
	fclose(f);
	
	while(m1!=0||m2!=0) {
		
	s=indice(m1%10,cap_lista)+indice(m2%10,cap_lista)+indice(t,cap_lista);
	m1/=10;
	m2/=10;
	i=1;
	
	if(s<dim) {

	p=cap_lista;
	
	while(i<=s) {
		p=p->urm;
		i++;
	}	
	
	m[k]=p->nr;
	k++;
	cap_lista=eliminare(cap_lista,p);
	t=cap_lista->nr;
	}
	if(s>=dim) {
	
	s=s%dim;
	p=cap_lista;
	
	while(i<=s)	{
		p=p->urm;
		i++;
	}	
	
	m[k]=p->nr;
	k++;
	cap_lista=eliminare(cap_lista,p);
	t=cap_lista->urm->nr;
	}
	dim--;
}

	if(t!=0) {
		m[k]=t;
		k++;
	}
	
	cap_lista=creare_baza(cap_lista,&dim);
	
	if((f=fopen("rezultat.txt","wt"))==NULL) {
		printf("Fisierul rezultat.txt nu a putut fi deschis.");
		exit(1);
	}
	for(i=k-1;i>=0;i--)
		for(p=cap_lista;p!=NULL;p=p->urm)
			if(m[i]==p->nr) 
				fprintf(f,"%s ",p->cuv);
	fclose(f);
	for(i=k-1;i>=0;i--)
	printf("%d ",m[i]);
	
	for(p=cap_lista;p!=NULL;p=p->urm) {
		q=p;
		p=q->urm;
		free(q);
	}
	
	return 0;
}

