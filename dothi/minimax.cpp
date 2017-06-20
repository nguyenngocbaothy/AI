#include <stdio.h>
#include <Math.h>
const int MAX=30;
int n,a[MAX][MAX],f[MAX];
char *tenfile="e:\\baigiang\\ttnt\\baitap\\dothi\\game_tree.txt";//hinh 14
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
	printf("gia tri ban dau cua cac trang thai:\n");
	for(i=1;i<=n;i++){
		fscanf(fin,"%d",&f[i]);
		printf("%3d",f[i]);
	}	
	printf("\n");	
	fclose(fin);
}
int IsLeaf(int u){
	for(int v=1;v<=n;v++)
		if(a[u][v]==1) return 0;
	return 1;		
}
int Max(int a, int b){
	if(a>b) return a; else return b;
}
int Min(int a, int b){
	if(a>b) return b; else return a;
}
int MinVal(int u);

int MaxVal(int u){
	int val=-100;
	if (IsLeaf(u)) val= f[u];
	else {	
		for(int v=1;v<=n;v++){
			if(a[u][v]==1){
				val=Max(val,MinVal(v));									
			}		
		}
	}
	printf("dinh=%d,gt=%d\n",u,val);
	return val;
}
int MinVal(int u){
	int val=100;
	if (IsLeaf(u)) val= f[u];
	else {	
		for(int v=1;v<=n;v++){
			if(a[u][v]==1){
				val=Min(val,MaxVal(v));									
			}		
		}
	}
	printf("dinh=%d,gt=%d\n",u,val);
	return val;
}
//tim nuoc di w cho dinh trang u
int White_Minimax(int u, int &w){	
	int val=-100;
	for(int v=1;v<=n;v++){
		if(a[u][v]==1){
			int tempval=MinVal(v);			
			if (tempval> val) {
				val = tempval; w = v;		
				printf("dinh chon=%d,gt=%d\n",v,val);
			}		
		}
	}
	return val;
}
//tim nuoc di w cho dinh den u
int Black_Minimax(int u, int &w){	
	int val=100;
	for(int v=1;v<=n;v++){
		if(a[u][v]==1){
			int tempval=MaxVal(v);			
			if (tempval<val) {
				val = tempval; w = v;		
				printf("dinh chon=%d,gt=%d\n",v,val);
			}		
		}
	}
	return val;
}
int main(){
	DocFile();
	int u,w,val,loai;
	printf("nhap dinh ban dau:"); scanf("%d",&u);
	printf("trang hay den(0/1)?:");scanf("%d",&loai);
	if(loai==0){
		val=White_Minimax(u, w);
		printf("\ntu %d, trang se di tiep %d\n",u,w);		
	}else{
		val=Black_Minimax(u, w);
		printf("\ntu %d, den se di tiep %d\n",u,w);		
	}	
	printf("\n");
	return 0;
}