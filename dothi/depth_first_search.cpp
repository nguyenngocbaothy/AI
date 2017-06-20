//thuat toan tim kiem theo do sau tren kg trang thai
//Depth_First_Search
#include<stdio.h>
const int MAX=20;
int n,a[MAX][MAX];
char *tenfile="e:\\baigiang\\ttnt\\baitap\\kgtt.txt";//hinh 7a
void DocFile(){
	int i,j;
	FILE *f=fopen(tenfile,"r");
	fscanf(f,"%d",&n);
	printf("so trang thai:%d\n",n);
	printf("khong gian trang thai:\n");
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			fscanf(f,"%d",&a[i][j]);
			printf("%3d",a[i][j]);
		}	
		printf("\n");
	}
	fclose(f);
}
//tim v trong list tu p den q
//tra ve vi tri tim thay hoac tra ve -1
int InList(int v, int list[],int p,int q){
	for(int i=p;i<=q;i++){
		if (list[i]==v) return i;
	}
	return -1;
}
void PrintOpen(int open[], int top){
	printf("Open:");
	for(int i=0;i<=top;i++){
		printf("%d ",open[i]);
	}
	printf("\n");
}
//trang thai ban dau la s, trang thai ket thuc la t
void Depth_First_Search(int s, int t) {
	if(s==t){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	int open[MAX],close[MAX],father[MAX];
	int top;//dinh cua open
	int k;//cuoi cua close
	int found=0,u,v;
	top=-1; open[++top]=s;k=0;
	printf("ban dau ");	PrintOpen(open,top);
	while(found==0){
		if(top==-1) break;
		u=open[top--];	
		printf("lay %d o cuoi open\n",u);			
		close[k++]=u;
		for(v=1;v<=n;v++){
			if(a[u][v]==1){
				if (InList(v,open,0,top)==-1&&InList(v,close,0,k-1)==-1){
					father[v]=u;
					if(v==t) {found=1;break;}
					open[++top]=v;
					printf("dua %d vao cuoi open\n",v);
				}
			}
		}
		PrintOpen(open,top);
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
	Depth_First_Search(s,t);
	printf("\n");
	return 0;
}
