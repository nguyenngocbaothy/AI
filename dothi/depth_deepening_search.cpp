//thuat toan tim kiem theo do sau lap tren kg trang thai
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
//s:trang thai ban dau, t:trang thai ket thuc la t, d:do sau
int father[MAX];
int Depth_Limited_Search(int s, int t, int d) {	
	int open[MAX],close[MAX],depth[MAX];
	int top;//dinh cua open
	int k;//cuoi cua close
	int found=0,u,v;
	depth[s]=0;
	top=-1; open[++top]=s;
	k=0;	
	while(found==0){
		if(top==-1) break;
		u=open[top--];		
		close[k++]=u;
		if(depth[u]<d){
			for(v=1;v<=n;v++){
				if(a[u][v]==1){
					if (InList(v,open,0,top)==-1&&InList(v,close,0,k-1)==-1){
						father[v]=u;
						depth[v]=depth[u] + 1;
						if(v==t) {found=1;break;}
						open[++top]=v;
					}
				}
			}
		}
	}
	return found;	
}
void Depth_Deepening_Search (int s, int t, int max_d){
	if(s==t){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	int found=0;
	for (int d =0;d<= max_d;d++){
		found= Depth_Limited_Search (s,t,d);
		if (found==1) break;
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
	int s,t,max_d;
	DocFile();
	printf("nhap trang thai ban dau:");scanf("%d",&s);
	printf("nhap trang thai ket thuc:");scanf("%d",&t);
	printf("nhap do sau toi da:");scanf("%d",&max_d);
	Depth_Deepening_Search(s,t,max_d);
	printf("\n");
	return 0;
}
