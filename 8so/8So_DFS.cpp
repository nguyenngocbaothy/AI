		//8 so - Depth First Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
struct node{
	int state[3][3];
	int row,col;//hang, cot chua so 0
	int f;
	node* father;
	node* next;		
};
typedef node* nodeptr;
#include<e:/baigiang/ttnt/baitap/list.cpp>
//chep trang thai cua node p sang trang thai cua node q
void CopyState(nodeptr p, nodeptr q){
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++) 
			q->state[i][j]=p->state[i][j];
}
//xet trang thai cua hai node p&q co giong nhau kg
bool IsEqualState(nodeptr p,nodeptr q){
	for(int i=0;i<3;i++)	
		for(int j=0;j<3;j++)	
			if(p->state[i][j]!=q->state[i][j]) 
				return false;
	return true;
}
//tim trang thai cua node p trong list l,tra ve true hoac false
bool IsStateInList(nodeptr p, list l){
	nodeptr q=l.head;
	while(q!=NULL){
		if (IsEqualState(p,q)) return true;
		q=q->next;
	}
	return false;
}
//in trang thai cua node p 
void PrintState(nodeptr p){	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%2d",p->state[i][j]);
		}
		printf("\n");
	}
	printf("depth=%d\n",p->f);
	printf("-------\n");
}
//in cac trang thai trong list 
void PrintStatesInList(list l){
	nodeptr p=l.head;
	while(p!=NULL){
		PrintState(p);
		p=p->next;
	}
}
//khoi tao node s va t voi trang thai da biet
void InitNode(nodeptr &s,nodeptr &t){
	s=new node;
	s->state[0][0]=2;s->state[0][1]=8;s->state[0][2]=3;
	s->state[1][0]=1;s->state[1][1]=6;s->state[1][2]=4;
	s->state[2][0]=7;s->state[2][1]=0;s->state[2][2]=5;
	s->row=2;s->col=1;s->father=NULL;s->next=NULL;s->f=0;
	t=new node;
	t->state[0][0]=1;t->state[0][1]=2;t->state[0][2]=3;
	t->state[1][0]=8;t->state[1][1]=0;t->state[1][2]=4;
	t->state[2][0]=7;t->state[2][1]=6;t->state[2][2]=5;
	t->row=1;t->col=1;t->father=NULL;t->next=NULL;t->f=0;
}
//tao node p voi trang thai ngau nhien
void InitRandomNode(nodeptr &p){
    bool used[9];
	int i,j,k;
    for (i = 0; i <= 8; i++) used[i] = false;
    srand(time(NULL)*rand());
    p=new node; 
    for (i = 0; i < 3; i++) {
		  for (j = 0; j < 3; j++) {
            int k;
            do {
                k = rand()*8/RAND_MAX;//so ngau nhien tu 0 den 8
            } while (used[k]);
            p->state[i][j] = k; used[k] = true;
            if (k == 0) {//ghi nhan vi tri o trong
               p->row = i;
               p->col = j;
            }            
        }
    }      
	p->f=0;  
    p->father = NULL;    
    p->next=NULL;
}  
//ds cac node con cua node p
list ChildNodes(nodeptr p){
	list l;  	
	InitList(l);
    if (p->row>0){//doi o ben tren xuong o trong
    	nodeptr q=new node;  
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row-1][p->col];
        q->state[p->row-1][p->col] = 0;
        q->row=p->row-1;q->col=p->col;
        q->father=p;q->next=NULL;q->f=p->f+1;
        InsertLastList(q,l);
    }
    if (p->row<2) {//doi o ben duoi len o trong
    	nodeptr q=new node;
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row + 1][p->col];
        q->state[p->row + 1][p->col] = 0;
        q->row=p->row+1;q->col=p->col;
        q->father=p;q->next=NULL;q->f=p->f+1;
    	InsertLastList(q,l);    
    }
    if (p->col>0) {//doi o ben trai qua o trong
    	nodeptr q=new node; 
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row][p->col-1];
        q->state[p->row][p->col-1] = 0;
        q->row=p->row;q->col=p->col-1;
        q->father=p; q->next=NULL;q->f=p->f+1;
	    InsertLastList(q,l);
    }
    if (p->col<2) {//doi o ben phai qua o trong
    	nodeptr q=new node;  
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row][p->col+1];
        q->state[p->row][p->col+1] = 0;
        q->row=p->row;q->col=p->col+1;
        q->father=p;q->next=NULL;q->f=p->f+1;
        InsertLastList(q,l);
    }
    return l;
}
//node chua trang thai ban dau la s, node chua trang thai ket thuc la t
void Depth_First_Search(nodeptr s,nodeptr t) {
	if(IsEqualState(s,t)){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	bool found=false;
	list open,close,child;
	nodeptr p,q,u;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);
	while(!found){
		u=open.head;
		if(u==NULL) {found=false;break;}	
		MoveFirstToFirst(open,close);
		child=ChildNodes(u);		
		p=child.head;				
		while(p!=NULL){
			q=p->next;p->next=NULL;
			if (!IsStateInList(p,open)&&!IsStateInList(p,close)){
				if(IsEqualState(p,t)) {
					t->father=p->father;t->f=p->f;
					found=true; break;
				}
				InsertFirstList(p,open);
			}else delete p;	
			p=q;		
		}
	}
	if(!found){
		printf("Khong tim thay TT KT\n");
	}else{
		printf("\n*Chuoi Bien Doi:\n");
		list l=Path(s,t);		
		PrintStatesInList(l);
	}
}
int main(){	
	nodeptr s,t;
	//InitRandomNode(s);//khoi tao node bat dau
	//InitRandomNode(t);//khoi tao node ket thuc
	InitNode(s,t);
	printf("*TT Ban dau:\n");	
	PrintState(s);
	printf("\n*TT Ket thuc:\n");
	PrintState(t);
	Depth_First_Search(s,t);
	printf("\n");
	return 0;
}
