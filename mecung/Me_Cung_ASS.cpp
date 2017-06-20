 //Me cung - A* Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
const int MAX=20;
struct node{
	int x,y;//vi tri trang thai 
	int g,h,f;		
	node* father;
	node* next;	
};
typedef node* nodeptr;
#include<e:/baigiang/ttnt/baitap/list.cpp>
int row,col;//so hang, so cot cua me cung
int maze[MAX][MAX];
nodeptr s,t;

//khoi tao ngau nhien cac bien row,col,maze
void Init(){
	srand(time(NULL)*rand());
	//so hang, so cot ngau nhien
	//row = rand()*5/RAND_MAX+5;
    //col = rand()*5/RAND_MAX+5;    
	row=col=8;  
    //gan 4 duong vien =-1 de kg can kiem tra vien
    //-1 la chuong ngai vat, 0 khong la chuong ngai vat
    for (int j = 0; j <= col + 1; j++) {
        maze[0][j] = -1;
        maze[row + 1][j] = -1;
    }
    for (int i = 0; i <= row + 1; i++) {
        maze[i][0] = -1;
        maze[i][col + 1] = -1;
    }
    //dat chuong ngai vat ngau nhien
    //0 la trong, -1 la chuong ngai vat
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            maze[i][j] = (rand()*1.0/RAND_MAX)> 0.3 ? 0 : -1;
        }
    }    
	//tao node bat dau va ket thuc co dinh
	s=new node;
	s->x =s->y=1;
	s->father=NULL;s->next=NULL;
	s->g=0;s->h=0;s->f=0;
	t=new node;	
	t->x =row;t->y =col;
	t->father=NULL;t->next=NULL;
	t->g=0;t->h=0;t->f=0;
	//danh dau vi tri bat dau va ket thuc
	maze[s->x][s->y] = -2;
    maze[t->x][t->y] = -3;
}
//tim trang thai cua node p trong list l
//tra ve dia chi tim thay hoac tra ve NULL
nodeptr IsStateInList(nodeptr p, list l,nodeptr &pre){
	nodeptr q=l.head;pre=NULL;
	while(q!=NULL){
		if (p->x==q->x&&p->y==q->y) return q;
		pre=q;
		q=q->next;
	}
	return NULL;
}
//h(p)= tong binh phuong khoang cach cua p den t
//g=tong so buoc doi, f=h+g 
//f cang nho cang tot, open can sx tang theo f. 
int h(nodeptr p){
	return ((p->x-t->x)*(p->x-t->x)+(p->y-t->y)*(p->y-t->y));
}
//ds cac node con cua node p
list ChildNodes(nodeptr p){
	list l;  	
	InitList(l);
    if (maze[p->x][p->y-1] != -1) {//neu ben trai kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x; q->y =p->y-1;
        q->father=p;q->next=NULL;	
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x][p->y+1] !=-1) {//neu ben phai kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y] != -1) {//neu ben tren kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y] != -1) {//neu ben duoi kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y-1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y-1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y+1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y+1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y-1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y-1;
        q->father=p;q->next=NULL;
		q->g=p->g+1;q->h=h(q);q->f=q->g+q->h;
       	InsertLastList(q,l);    
    }
    return l;
}
//in me cung
void Printmaze(){	
	for(int i=1;i<=row;i++){
		for(int j=1;j<=col;j++){
			switch(maze[i][j]){
				case 0:printf("%3s",".");break;//in o trong bang dau "."
				case -1:printf("%3s","*");break;//in vat can bang dau "*"
				case -2:printf("%3s","S");break;//in vt bat dau bang "S"
				case -3:printf("%3s","T");break;//in vt ket thuc bang "T"
				default: printf("%3d",maze[i][j]);break; //in thu tu cac buoc di
			}
		}	
		printf("\n\n");
	}
}
//node chua trang thai ban dau la s, node chua trang thai ket thuc la t
void A_Star_Search(nodeptr s, nodeptr &t) {	
	bool found=false;
	list open,close,childs;
	nodeptr p,q,u,p1,p2,pre1,pre2;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);	
	while(!found){
		u=open.head;
		if(u==NULL) {found=false;break;}
		if(u->x==t->x&&u->y==t->y) {
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
				if(p1!=NULL&&p->f<p1->f){					
					if(p1==open.head) DelFirstList(open);
					else DelAfterList(pre1,open);						
					InsertSortAscList(p,open);					
				}
			}			
			p=q;		
		}
	}	
	printf("\n+TT Bat dau:(%d,%d)\n",s->x,s->y);
	printf("+TT Ket thuc:(%d,%d)\n\n",t->x,t->y);
	Printmaze();		
	if(!found){
		printf("\n\n+Khong tim thay TTKT\n\n");
	}else{
		printf("\n\n+Chuoi bien doi:\n\n");
		maze[t->x][t->y]=t->g+1;	
		nodeptr p=t;
		do{
			p=p->father;	
			maze[p->x][p->y]=p->g+1;			
		}while(p->father!=NULL);
	}
	Printmaze();		
}
int main(){	
	Init();	
	A_Star_Search(s,t);
	printf("\n");
}
