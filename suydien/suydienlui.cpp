//thuat toan suy dien lui
#include<stdio.h>
const int MAX=20;
int n,a[MAX][MAX],O[MAX];
bool T[MAX];
int m=0;//so phep toan
char *tenfile="e:\\baigiang\\ttnt\\baitap\\suydien\\suydien.txt";
char *benh[MAX]={
	"",
	"(1) sot cao",
	"(2) nhuc dau",
	"(3) cam cum",
	"(4) non oi",
	"(5) nhiem sieu vi",
	"(6) dau bung",
	"(7) an khong tieu",
	"(8) chong mat",
	"(9) co thai"
};
void DanhSachBenh(){
	printf("*Danh sach benh:\n");
	for(int i=1;i<=9;i++)
		printf("%s\n",benh[i]);
	printf("\n");
}
void DocFile(){
	int i,j,k;
	FILE *f=fopen(tenfile,"r");
	fscanf(f,"%d",&n);
	//printf("so bai toan:%d\n",n);
	printf("*Cac trieu chung da biet:\n");
	for(i=1;i<=n;i++) T[i]=false;	
	do{		
		fscanf(f,"%d",&k);			
		if(k!=0){
			printf("%s\n",benh[k]);
			T[k]=true;	
		}		
	}while(k!=0);
	printf("\n");
	m=0;
	printf("*Tap luat:\n");
	do{
		m++;
		printf("Luat R%d:",m);		
		j=0;
		do{
			fscanf(f,"%d",&k);			
			a[m][++j]=k;	
			if(k!=0){
				if(j==1)printf("%d<-",k);									
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
	if(T[u]) printf("Benh : '%s' da biet!\n",benh[u]);
	else{
		printf("Chan doan benh: '%s' bang luat 'R%d'\n",benh[u],O[u]);
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
	DanhSachBenh();
	DocFile();	
	printf("*Nhap ma benh chan doan:");scanf("%d",&u);
	bool result=Solvable(u);
	if(result){		
		PrintResult(u,0);
	} 
	else printf("*Khong the chan doan benh: '%s'!\n",benh[u]);
	printf("\n");
	return 0;
}
