//Trieu phu va ke cuop - A star Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>

struct node{
	int T,C;//so trieu phu va so ke cuop o ben trai	
	int g,h,f;		
	node* father;
	node* next;	
};
typedef node* nodeptr;
#include<e:/baigiang/ttnt/baitap/list.cpp>

int n;//so T/C ban dau
nodeptr s, t;
//tao node bat dau va ket thuc 
void Init(){	
    s=new node;
	s->T=s->C = n;	
	s->g=0;s->h=0;s->f=0;
	s->father=NULL;s->next=NULL;
	t=new node;
	t->T=t->C=0;
	t->g=0;t->h=0;t->f=0;	
	t->father=NULL;t->next=NULL;
}
//tim trang thai cua node p trong list l
//tra ve dia chi tim thay hoac tra ve NULL
nodeptr IsStateInList(nodeptr p, list l,nodeptr &pre){
	nodeptr q=l.head;pre=NULL;
	while(q!=NULL){
		if (p->T==q->T&&p->C==q->C) return q;
		pre=q;
		q=q->next;
	}
	return NULL;
}
//in trang thai cua node p 
void PrintState(nodeptr p){	
	printf("%2d: Left(%2d,%2d)-Right(%2d,%2d)\n",p->g,p->T,p->C,n-p->T,n-p->C);
}
//in chuoi trang thai trong list 
void PrintStateList(list l){
	nodeptr p=l.head;
	while(p!=NULL){
		PrintState(p);
		p=p->next;
	}
}
//ds cac node con cua node p
list ChildNodes(nodeptr p){
	list l;  	
	int T1,C1;//so trieu phu, cuop o bo phai
	InitList(l);
	T1=n-p->T; C1=n-p->C;
	//cho 1 Trieu phu; (3,0)-(0,3)->(2,0)-(1,3)	
	if(p->T>0&&p->T>p->C&&T1+1>=C1){
		nodeptr q=new node;  
        q->T=p->T-1;q->C=p->C;	        
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=1;q->f=q->h-q->g;		
       	InsertLastList(q,l);   	
    }
    //cho 1 Cuop:(2,2)-(1,1)->(2,1)-(1,2);(3,1)-(0,2)->(3,0)-(0,3);
	if(p->C>0&&(T1==0||T1>=C1+1)){	
		nodeptr q=new node;  
        q->T=p->T;q->C=p->C-1;        
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=1;q->f=q->h-q->g;		
       	InsertLastList(q,l);   			
	}		 
    //cho 1 Trieu phu va 1 Cuop (3,2)-(0,1)->(2,1)-(1,2)
	if(p->T>0&&p->C>0&&T1+1>=C1+1){
		nodeptr q=new node;  
        q->T=p->T-1;q->C=p->C-1;        
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=2;q->f=q->h-q->g;		
       	InsertLastList(q,l);   	
	}	
    //cho 2 Trieu phu (3,3)(0,0)->(1,3)(2,0);(3,0)(0,3)->(1,0)(2,3)
	if(p->T>=2&&p->T-2>=p->C&&T1+2>=C1){
		nodeptr q=new node;  
        q->T=p->T-2;q->C=p->C;	        
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=2;q->f=q->h-q->g;		
       	InsertLastList(q,l);   	
    }
    //cho 2 Cuop (3,3)(0,0)->(3,1)(0,2)
	if(p->C>=2&&(T1==0||T1>=C1+2)){		
		nodeptr q=new node;  
        q->T=p->T;q->C=p->C-2;	        
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=2;q->f=q->h-q->g;		
       	InsertLastList(q,l);   			
    }
    return l;
}
//node chua trang thai ban dau la s, node chua trang thai ket thuc la t
void A_Star_Search(nodeptr s, nodeptr &t) {
	bool found=false;
	list open,close,childs;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);
	while(!found){
		nodeptr u=open.head;
		if(u==NULL) break;	
		if(u->T==t->T&&u->C==t->C) {
			t->g=u->g;t->h=u->h;t->f=u->f;
			t->father=u->father;
			found=true; break;
		} 	
		MoveFirstToFirst(open,close);
		childs=ChildNodes(u);		
		nodeptr p=childs.head;
		nodeptr pre1,pre2;				
		while(p!=NULL){
			nodeptr q=p->next;p->next=NULL;
			nodeptr p1=IsStateInList(p,open,pre1);
			nodeptr p2=IsStateInList(p,close,pre2);
			if (p1==NULL&&p2==NULL){				
				InsertSortDecList(p,open);
			}else{
				if(p1!=NULL&&p1->f<p->f){					
					if(p1==open.head) DelFirstList(open);
					else DelAfterList(pre1,open);
					InsertSortDecList(p,open);					
				}
			}	
			p=q;		
		}
	}
	if(!found){
		printf("Khong tim thay TT KT\n");
	}else{
		printf("\n*Chuoi Bien Doi:\n");
		list l=Path(s,t);		
		PrintStateList(l);
	}
}
int main(){	
	printf("So trieu phu va so ke cuop ban dau:");
	scanf("%d",&n);	
	Init();	
	printf("*TT Ban dau:\n");	
	PrintState(s);
	printf("\n*TT Ket thuc:\n");
	PrintState(t);
	A_Star_Search(s,t);
	printf("\n\n");
}
