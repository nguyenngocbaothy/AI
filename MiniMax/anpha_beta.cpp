#include <stdio.h>
#include <Math.h>
const int MAX=30;
int n,a[MAX][MAX],f[MAX];
char *tenfile="e:\\baigiang\\ttnt\\bt\\minimax\\game_tree.txt";//hinh 4.8
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
int MinVal(int u, int alpha, int beta);

int MaxVal(int u, int alpha, int beta){
	int val,tempval,thoat=0;
	if (IsLeaf(u)) val= f[u];
	else {	
		for(int v=1;v<=n;v++){
			if(a[u][v]==1){
				tempval=MinVal(v, alpha, beta);			
				alpha=Max(alpha,tempval);					
				if(alpha>=beta) {
					thoat=1;break;
				}				
			}		
		}
		val=alpha;
	}
	printf("\ndinh=%d,alpha=%d,beta=%d,val=%d",u,alpha,beta,val);
	if(thoat==1) printf("\ndinh %d co alpha>=beta nen bo cac dinh ke con lai",u);				
	return val;
}
int MinVal(int u, int alpha, int beta){
	int val,tempval,thoat=0;
	if (IsLeaf(u)) val=f[u];
	else {	
		for(int v=1;v<=n;v++){
			if(a[u][v]==1){
				tempval=MaxVal(v, alpha, beta);				
				beta=Min(beta,tempval);
				if(alpha>=beta) {
					thoat=1;break;
				}
			}		
		}
		val=beta;
	}
	printf("\ndinh=%d,alpha=%d,beta=%d,val=%d",u,alpha,beta,val);
	if(thoat==1) printf("\ndinh %d co alpha>=beta nen bo cac dinh ke con lai",u);
	return val;
}
//tim nuoc di w cho dinh trang u
int White_Alpha_Beta(int u, int &w){
	int alpha = -100, beta = 100;	
	for(int v=1;v<=n;v++){
		if(a[u][v]==1){
			int val=MinVal(v, alpha, beta);			
			if (val> alpha) {
				alpha = val; w = v;
				printf("\ndinh=%d,alpha=%d,beta=%d,val=%d",u,alpha,beta,val);
			}		
		}
	}
	return alpha;
}
//tim nuoc di w cho dinh den u
int Black_Alpha_Beta(int u, int &w){
	int alpha = -100, beta = 100;	
	for(int v=1;v<=n;v++){
		if(a[u][v]==1){
			int val=MaxVal(v, alpha, beta);			
			if (val< beta) {
				beta = val; w = v;
				printf("\ndinh=%d,alpha=%d,beta=%d,val=%d",u,alpha,beta,val);
			}		
		}
	}
	return beta;
}
int alpha = -100, beta = 100;
int main(){
	DocFile();
	int u,w,val,loai;
	printf("nhap dinh ban dau:"); scanf("%d",&u);
	printf("trang hay den(0/1)?:");scanf("%d",&loai);
	if(loai==0){
		val=MaxVal(u, alpha, beta);
		printf("\ngia tri dinh trang %d la: %d\n",u,val);		
	}else{
		val=MinVal(u, alpha, beta);
		printf("\ngia tri dinh den %d la: %d\n",u,val);		
	}	
	printf("\n");
	return 0;
}