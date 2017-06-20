 //Me cung - Depth Deepening Search
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
const int MAX=20;
struct node{
	int x,y;//vi tri trang thai 
	int f;		
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
            maze[i][j] = (rand()*1.0/RAND_MAX)> 0.4 ? 0 : -1;
        }
    }    
	//tao node bat dau va ket thuc co dinh
	s=new node;
	s->x =s->y =1;s->father=NULL;s->next=NULL;s->f=0;	
	t=new node;	
	t->x =row;t->y =col;t->father=NULL;t->next=NULL;t->f=0;
	//danh dau vi tri bat dau va ket thuc
	maze[s->x][s->y] = -2;
    maze[t->x][t->y] = -3;
}
//tim trang thai cua node p trong list l
//tra ve true hoac false
bool IsStateInList(nodeptr p, list l){
	nodeptr q=l.head;
	while(q!=NULL){
		if (p->x==q->x&&p->y==q->y) return true;
		q=q->next;
	}
	return false;
}
//ds cac node con cua node p
list ChildNodes(nodeptr p){
	list l;  	
	InitList(l);
    if (maze[p->x][p->y-1] != -1) {//neu ben trai kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x; q->y =p->y-1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x][p->y+1] !=-1) {//neu ben phai kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y] != -1) {//neu ben tren kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y] != -1) {//neu ben duoi kg la chuong ngai vat 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y-1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y-1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y+1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x-1][p->y+1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x-1;q->y =p->y+1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
       	InsertLastList(q,l);    
    }
    if (maze[p->x+1][p->y-1] != -1) { 
		nodeptr q=new node;  
        q->x =p->x+1;q->y =p->y-1;
        q->father=p;q->next=NULL;
		q->f=p->f+1;
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
//tim kiem toi do sau toi da la d, tra ve true/false
bool Depth_Limited_Search (nodeptr s, nodeptr t, int d){
	bool found=false;
	list open,close,childs;
	nodeptr p,q,u;
	InitList(open);	InitList(close);	
	InsertFirstList(s,open);
	while(!found){
		u=open.head;
		if(u==NULL) {found=false;break;}		
		MoveFirstToFirst(open,close);
		if(u->f<d){
			childs=ChildNodes(u);		
			p=childs.head;				
			while(p!=NULL){
				q=p->next;p->next=NULL;
				if (!IsStateInList(p,open)&&!IsStateInList(p,close)){
					if(p->x==t->x&&p->y==t->y) {
						t->f=p->f;
						t->father=p->father;
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
	printf("\n+TT Bat dau:(%d,%d)\n",s->x,s->y);
	printf("+TT Ket thuc:(%d,%d)\n\n",t->x,t->y);
	Printmaze();		
	if(!found){
		printf("\n\n+Khong tim thay TTKT\n\n");
	}else{
		printf("\n\n+Chuoi bien doi:\n\n");
		maze[t->x][t->y]=t->f+1;	
		nodeptr p=t;
		do{
			p=p->father;	
			maze[p->x][p->y]=p->f+1;			
		}while(p->father!=NULL);
	}
	Printmaze();		
}

int main(){	
	Init();	
	int max_d;	
	printf("*Nhap do sau toi da:");scanf("%d",&max_d);
	Depth_Deepening_Search(s,t,max_d);
	printf("\n");
	return 0;
}
