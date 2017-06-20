//thuat toan giai toan - solvable
#include<stdio.h>
const int MAX=20;
int n,a[MAX][MAX],O[MAX];
bool T[MAX];
int m=0;//so phep toan
char *tenfile="e:\\baigiang\\ttnt\\baitap\\giaitoan\\solvable.txt";
void DocFile(){
	int i,j,k;
	FILE *f=fopen(tenfile,"r");
	fscanf(f,"%d",&n);
	//printf("so bai toan:%d\n",n);
	printf("Cac bai toan da biet cach giai:");
	for(i=1;i<=n;i++) T[i]=false;	
	do{		
		fscanf(f,"%d",&k);			
		if(k!=0){
			printf("%d ",k);
			T[k]=true;	
		}		
	}while(k!=0);
	printf("\n");
	m=0;
	do{
		m++;
		printf("Phep bien doi R%d:",m);		
		j=0;
		do{
			fscanf(f,"%d",&k);			
			a[m][++j]=k;	
			if(k!=0){
				if(j==1)printf("%d->",k);									
				else printf("%d ",k);	
			}	
		}while(k!=0);				
		printf("\n");
	}while(!feof(f));			
	printf("\n");	
	fclose(f);
}

bool IsLeaf(int u){
	for(int i=1;i<=m;i++)
		if(a[i][1]==u) return false;
	return true;
}
bool  Solvable(int u){
	int i,j,v;
	bool ok;
	if(T[u]) return true;//u la dinh ket thuc=>u giai duoc
	if(IsLeaf(u)) return false;//u kg la dinh kt va u la la=>u kg giai duoc	
	for(i=1;i<=m;i++){//xet cac toan tu Ri
		if(a[i][1]==u){//toan tu Ri ap dung duoc tai u tuc la co Ri:u=>...
			ok=true;j=2;
			do{
				v=a[i][j++];
				if(v!=0){
					if (!Solvable(v)) {ok =false; break;}									
				}	
			}while(v!=0);
			if (ok){//u giai duoc theo Ri
				O[u]=i; 
				return true;
			}
		}
	}
	return false;
}
void PrintResult(int u, int space){
	int i,j,v;
	for(i=1;i<=space;i++) printf(".");
	if(T[u]) printf("Bai toan %d da biet cach giai!\n",u);
	else{
		printf("Giai bai toan %d bang phep bien doi R%d\n",u,O[u]);
		i=O[u];j=2;
		do{
			v=a[i][j++];
			if(v!=0){
				PrintResult(v,space+5);									
			}	
		}while(v!=0);
	}
}
int main(){
	int u;	
	DocFile();	
	printf("Nhap bai toan can giai:");scanf("%d",&u);
	bool result=Solvable(u);
	if(result){		
		PrintResult(u,0);
	} 
	else printf("bai toan %d giai kg duoc!\n",u);
	printf("\n");
	return 0;
}
