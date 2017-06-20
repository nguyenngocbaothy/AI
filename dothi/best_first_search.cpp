//thuat toan tim kiem tot nhat dau tien tren kg trang thai
//Best_First_Search
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
//tra ve vi tri tim thay hoac tra ve -1
int InList(int v, int list[],int p,int q){
	for(int i=p;i<=q;i++){
		if (list[i]==v) return i;
	}
	return -1;
}
//chen v vao list trong doan p,q 
//sao cho sau khi chen, open van sx tang theo gia tri f
void Insert(int v,int open[],int p,int q){
	int i,j;
	i=q;
	while(i>=p&&f[open[i]]>f[v]){
		open[i+1]=open[i];
		i--;	
	} 	
	open[i+1]=v;
}
//trang thai ban dau la s, trang thai ket thuc la t
void Best_First_Search(int s, int t) {
	if(s==t){
		printf("trang thai ban dau la trang thai ket thuc\n");
		return;
	}
	int open[MAX],close[MAX],father[MAX];
	int d,c;//dau, cuoi cua open
	int k;//cuoi cua close
	int found=0,u,v;
	d=c=0; open[c++]=s;
	k=0;
	while(found==0){
		if(d==c) break;
		u=open[d++];
		close[k++]=u;
		for(v=1;v<=n;v++){
			if(a[u][v]==1){
				if (InList(v,open,d,c-1)==-1&&InList(v,close,0,k-1)==-1){
					father[v]=u;
					if(v==t) {found=1; break;}
					Insert(v,open,d,c-1);
					c++;
				}
			}
		}
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
	Best_First_Search(s,t);
	printf("\n");
	return 0;
}
