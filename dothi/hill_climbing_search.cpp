//thuat toan tim kiem leo doi tren kg trang thai
//Hill_Climbing_Search 
#include<stdio.h>
const int MAX=20;
int n,a[MAX][MAX],f[MAX];
char *tenfile="e:\\baigiang\\ttnt\\baitap\\kgtt1.txt";//hinh 7a
void DocFile(){
	int i,j;
	FILE *fin=fopen(tenfile,"r");
	fscanf(fin,"%d",&n);
	printf("so trang thai:%d\n",n);
	printf("khong gian trang thai:\n");
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(fin,"%d",&a[i][j]);
			printf("%3d",a[i][j]);
		}	
		printf("\n");
	}
	printf("gia tri cua cac trang thai:\n");
	for(i=1;i<=n;i++){
		fscanf(fin,"%d",&f[i]);
		printf("%3d",f[i]);
	}	
	printf("\n");	
	fclose(fin);
}
//tim v trong list tu p den q
//tim thay tra ve vi tri tim thay nguoc lai tra ve -1
int InList(int v, int list[],int p,int q){
	for(int i=p;i<=q;i++){
		if (list[i]==v) return i;
	}
	return -1;
}
//chen v vao list co m phan tu 
//sau khi chen, list van sx tang theo gia tri
void Insert(int v,int list[],int &m){
	int i=m-1;
	while(i>=0&&f[list[i]]>f[v]) {
		list[i+1]=list[i]; 
		i--;	
	}	
	list[i+1]=v; m++;
}
//chep list co m phan tu vao open dang stack
void CopyList(int list[],int m,int open[],int &top){
	for(int i=m-1;i>=0;i--)
		open[++top]=list[i];
}
//trang thai ban dau la s, trang thai ket thuc la t
void Hill_Climbing_Search (int s, int t) {
	if(s==t){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	int open[MAX],close[MAX],father[MAX],list[MAX];
	int top=-1;//dinh cua open
	int k=0;//cuoi cua close
	int m=0;//cuoi cua list
	int found=0,u,v;
	open[++top]=s;	
	while(found==0){
		if(top==-1) break;
		u=open[top--];		
		close[k++]=u;
		m=0;
		for(v=1;v<=n;v++){
			if(a[u][v]==1){
				if (InList(v,open,0,top)==-1&&InList(v,close,0,k-1)==-1){
					father[v]=u;
					if(v==t) {found=1;break;}
					Insert(v,list,m);					
				}
			}
		}
		CopyList(list,m,open,top);
	}
	if(found==0){
		printf("khong tim thay trang thai %d\n",t);
	}else{
		printf("Chuoi cac phep bien doi trang thai:\n");
		printf("%d",t);
		do{
			t=father[t];	
			printf(" <- %d",t);
		}while(t!=s);
	}
}

int main(){
	int s,t;
	DocFile();
	printf("nhap trang thai ban dau:");scanf("%d",&s);
	printf("nhap trang thai ket thuc:");scanf("%d",&t);
	Hill_Climbing_Search(s,t);
	printf("\n");
	return 0;
}
