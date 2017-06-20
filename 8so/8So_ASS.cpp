//8 so - A* Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
struct node{
	int state[3][3];
	int row,col;//hang, cot chua so 0
	int g,h,f;
	node* father;
	node* next;		
};
typedef node* nodeptr;
nodeptr s,t;
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
//tim trang thai cua node p trong list l
//tra ve dia chi tim thay hoac tra ve NULL
nodeptr IsStateInList(nodeptr p, list l,nodeptr &pre){
	nodeptr q=l.head;pre=NULL;
	while(q!=NULL){
		if (IsEqualState(p,q)) return q;
		pre=q;
		q=q->next;
	}
	return NULL;
}
//in trang thai cua node p 
void PrintState(nodeptr p){	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%2d",p->state[i][j]);
		}
		printf("\n");
	}
	printf("g=%d,h=%d,f=%d\n",p->g,p->h,p->f);
	printf("--------------\n");
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
	s->row=2;s->col=1;
	s->g=0;s->h=0;s->f=0;
	s->father=NULL;s->next=NULL;
	t=new node;
	t->state[0][0]=1;t->state[0][1]=2;t->state[0][2]=3;
	t->state[1][0]=8;t->state[1][1]=0;t->state[1][2]=4;
	t->state[2][0]=7;t->state[2][1]=6;t->state[2][2]=5;
	t->row=1;t->col=1;
	t->g=0;t->h=0;t->f=0;
	t->father=NULL;t->next=NULL;
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
 	p->g=0;p->h=0;p->f=0;
    p->father = NULL;    
    p->next=NULL;
}  
/*
//h=tong so vi tri sai,g=tong so buoc doi, f=h+g 
// f cang nho cang tot, open can sx tang theo f. 
int h(nodeptr p){
	int s=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(p->state[i][j]!=t->state[i][j]) s++;		
		}	
	}
	return s;
}
*/
int Distance(int x1, int y1,int x2, int y2){
	return ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
void FindPosition(int val, int &x, int &y){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(t->state[i][j]==val){
				x=i;y=j;		
				return;
			} 
		}	
	}	
}
//h= tong binh phuong khoang cach cua moi vt den vt dich
//g=tong so buoc doi, f=h+g 
//f cang nho cang tot, open can sx tang theo f. 
int h(nodeptr p){
	int x,y,val=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(p->state[i][j]>0){
				FindPosition(p->state[i][j],x,y);
				val+=Distance(i,j,x,y);	
			}
		}	
	}
	return val;
}
//ds cac node con cua node p
list ChildNodes(nodeptr p){
	list l;  	
	InitList(l);
    if (p->row>0){//doi o ben tren xuong o trong
    	nodeptr q=new node; q->next=NULL;
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row-1][p->col];
        q->state[p->row-1][p->col] = 0;
        q->row=p->row-1;q->col=p->col;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
        InsertLastList(q,l);
    }
    if (p->row<2) {//doi o ben duoi len o trong
    	nodeptr q=new node;  q->next=NULL;
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row + 1][p->col];
        q->state[p->row + 1][p->col] = 0;
        q->row=p->row+1;q->col=p->col;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
    	InsertLastList(q,l);    
    }
    if (p->col>0) {//doi o ben trai qua o trong
    	nodeptr q=new node;  q->next=NULL;
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row][p->col-1];
        q->state[p->row][p->col-1] = 0;
        q->row=p->row;q->col=p->col-1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
	    InsertLastList(q,l);
    }
    if (p->col<2) {//doi o ben phai qua o trong
    	nodeptr q=new node;  q->next=NULL;
		CopyState(p,q);    
        q->state[p->row][p->col] = q->state[p->row][p->col+1];
        q->state[p->row][p->col+1] = 0;
        q->row=p->row;q->col=p->col+1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
        InsertLastList(q,l);
    }
    return l;
}
//node chua trang thai ban dau la s, node chua trang thai ket thuc la t
void A_Star_Search(nodeptr s, nodeptr &t) {
	if(IsEqualState(s,t)){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	bool found=false;
	list open,close,childs;
	nodeptr p,q,u,p1,p2,pre1,pre2;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);
	while(!found){
		u=open.head;
		if(u==NULL) {found=false;break;	}
		if(IsEqualState(u,t)) {
			t->g=u->g;t->h=u->h;t->f=u->f;
			t->father=u->father;
			found=true; break;
		} 	
		MoveFirstToFirst(open,close);
		childs=ChildNodes(u);		
		p=childs.head;					
		while(p!=NULL){
			q=p->next;p->next=NULL;
			p1=IsStateInList(p,open,pre1);
			p2=IsStateInList(p,close,pre2);
			if (p1==NULL&&p2==NULL){								
				InsertSortAscList(p,open);
			}else{
				if(p1!=NULL){
					if(p->f<p1->f){
						if(p1==open.head) DelFirstList(open);
						else DelAfterList(pre1,open);						
						InsertSortAscList(p,open);
					}
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
		PrintStatesInList(l);
	}
}
int main(){		
	//InitRandomNode(s);//khoi tao node bat dau
	//InitRandomNode(t);//khoi tao node ket thuc
	InitNode(s,t);
	printf("*TT Ban dau:\n");	
	PrintState(s);
	printf("\n*TT Ket thuc:\n");
	PrintState(t);
	A_Star_Search(s,t);
	printf("\n");
	return 0;
}
