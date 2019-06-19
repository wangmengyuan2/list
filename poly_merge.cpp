#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

typedef int ElemType;

typedef struct Lnode {
	ElemType coef;
	int exp;
	struct Lnode *next;
}Lnode;

Lnode* merge(Lnode *polya, Lnode *polyb) //choose tail_insert 
{
	Lnode *p, *q, *tmp, *tail;

	p = polya;
	q = polyb;
	tmp = q;
	tail = p;

	while(p != NULL && q != NULL){
		if(p->exp > q->exp){
			tail->next = q;
			tail = q;
			tmp = q->next;
			q->next = p;	
			q = tmp;
		}
		else if(p->exp == q->exp){
			p->coef = p->coef + q->coef;//p->coef == 0??
			if(p->coef){
				tail = p;
				p = p->next;
				tmp = q;
				q = q->next;
				free(tmp);
			}
			else{
				tail->next = p->next;
				tmp = p;
				p = p->next;
				free(tmp);
				tmp = q->next;
				free(q);
				q = tmp;
			}
		}
		else{
			tail = p;
			p = p->next;
		}
	}
//	printf("p: %p, q: %p, q->next: %p, tail: %p \n", p, q, q->next, tail);
	printf("p: %p, q: %p, tail: %p \n", p, q, tail);

	while(q != NULL){
		tail->next = q;
		tail = q;
		q = q->next;
	}
	return polya;
}

void create_sl(Lnode *H)
{
	Lnode *tail, *s;
	int co, ex;
	scanf("%d", &co);
	scanf("%d", &ex);
	tail = H;

	s = (Lnode *)malloc(sizeof(Lnode));
	s->coef = co;
	s->exp = ex;
	s->next = NULL;

	while(co != -1){
		tail->next = s;
		tail = s;
		scanf("%d", &co);
		scanf("%d", &ex);
		s = (Lnode *)malloc(sizeof(Lnode));
		s->coef = co;
		s->exp = ex;
		s->next = NULL;
	}
}

int main()
{
	Lnode *ha, *hb, *p;

	ha = (Lnode *)malloc(sizeof(Lnode));
	hb = (Lnode *)malloc(sizeof(Lnode));

	ha->exp = -1;
	ha->next = NULL;

	hb->exp = -1;
	hb->next = NULL;

	printf("ha: \n");
	create_sl(ha);
	printf("hb:\n");
	create_sl(hb);
	
	merge(ha, hb);

	p = ha;
	p = p->next;
	while(p){
		printf("coef %d, exp %d\n", p->coef, p->exp);
		p = p->next;
	}
	return 0;
}
