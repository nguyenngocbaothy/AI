//Trieu phu va ke cuop - Depth Deepening Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
const int MAX=20;
struct node{
	int T,C;//so trieu phu va so ke cuop o ben trai	
	int f;		
	node* father;
	node* next;	
};
typedef node* nodeptr;
#include<e:/baigiang/ttnt/baitap/list.cpp>
int n;//so T/C ban dau
nodeptr s, t;
//khoi tao 
void Init(){
	//tao node bat dau va ket thuc 
    s=new node;
	s->T=s->C = n;	
	s->father=NULL;s->next=NULL; s->f=0;
	t=new node;
	t->T=t->C=0;	
	t->father=NULL;t->next=NULL;t->f=0;
}
//tim trang thai cua node p trong list l
//tra ve true hoac false
bool IsStateInList(nodeptr p, list l){
	nodeptr q=l.head;
	while(q!=NULL){
		if (p->T==q->T&&p->C==q->C) return true;
		q=q->next;
	}
	return false;
}
//in trang thai cua node p 
void PrintState(nodeptr p){	
	printf("%2d: Left(%2d,%2d)-Right(%2d,%2d)\n",p->f,p->T,p->C,n-p->T,n-p->C);
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
        q->father=p;q->next=NULL;q->f=p->f+1;		
       	InsertLastList(q,l);   	
    }
    //cho 1 Cuop:(2,2)-(1,1)->(2,1)-(1,2);(3,1)-(0,2)->(3,0)-(0,3);
	if(p->C>0&&(T1==0||T1>=C1+1)){	
		nodeptr q=new node;  
        q->T=p->T;q->C=p->C-1;        
        q->father=p;q->next=NULL;q->f=p->f+1;		
       	InsertLastList(q,l);   			
	}		 
    //cho 1 Trieu phu va 1 Cuop (3,2)-(0,1)->(2,1)-(1,2)
	if(p->T>0&&p->C>0&&T1+1>=C1+1){
		nodeptr q=new node;  
        q->T=p->T-1;q->C=p->C-1;        
        q->father=p;q->next=NULL;q->f=p->f+1;		
       	InsertLastList(q,l);   	
	}	
    //cho 2 Trieu phu (3,3)(0,0)->(1,3)(2,0);(3,0)(0,3)->(1,0)(2,3)
	if(p->T>=2&&p->T-2>=p->C&&T1+2>=C1){
		nodeptr q=new node;  
        q->T=p->T-2;q->C=p->C;	        
        q->father=p;q->next=NULL;q->f=p->f+1;		
       	InsertLastList(q,l);   	
    }
    //cho 2 Cuop (3,3)(0,0)->(3,1)(0,2)
	if(p->C>=2&&(T1==0||T1>=C1+2)){		
		nodeptr q=new node;  
        q->T=p->T;q->C=p->C-2;	        
        q->father=p;q->next=NULL;q->f=p->f+1;		
       	InsertLastList(q,l);   			
    }
    return l;
}
//node chua trang thai ban dau la s, node chua trang thai ket thuc la t
//tim kiem toi do sau toi da la d, tra ve true/false
bool Depth_Limited_Search (nodeptr s, nodeptr t, int d){
	bool found=false;
	list open,close,childs;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);
	while(!found){
		nodeptr u=open.head;
		if(u==NULL) {found=false;break;}
		MoveFirstToFirst(open,close);
		if(u->f<d){
			childs=ChildNodes(u);		
			nodeptr p=childs.head;
			while(p!=NULL){
				nodeptr q=p->next;p->next=NULL;		
				if (!IsStateInList(p,open)&&!IsStateInList(p,close)){	
					if(p->T==t->T&&p->C==t->C) {
						t->father=p->father; t->f=p->f;
						found=true; break;
					} 				
					InsertFirstList(p,open);
				}else delete p;	
				p=q;		
			}
		}
	}
	return found;
}
void Depth_Deepening_Search (nodeptr s, nodeptr t, int max_d){	
	bool found=false;
	for (int d =0;d<= max_d;d++){
		found= Depth_Limited_Search (s,t,d);
		if (found) break;
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
	int max_d;	
	printf("*Nhap do sau toi da:");scanf("%d",&max_d);
	Depth_Deepening_Search(s,t,max_d);
	printf("\n");
	return 0;
}
