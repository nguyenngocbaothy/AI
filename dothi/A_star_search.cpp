//thuat toan A* - A_star_search
#include<iostream.h>
#include <fstream.h>

const int MAX=20;
int n,a[MAX][MAX]={0};
int father[MAX];
int g[MAX]={0},h[MAX]={0},f[MAX]={0};
char *tenfile="e:\\baigiang\\ttnt\\bt\\dothi\\astar.txt";

void DocFile(){
	int i,j,k;
	ifstream f(tenfile);
	f>>n;
	//cout<<n<<endl;
	for (i=1; i<=n; i++){
		f>>h[i];
		//cout<<h[i]<<" ";
	}
	//cout<<endl;
	while(f>>i>>j>>k){
		//cout<<i<<","<<j<<","<<k<<endl;
		a[i][j]=k;
	}
	f.close();
}


//tim v trong list tu vi tri d den vi tri c-1
//neu tim thay tra ve vi tri tim thay, nguoc lai tra ve -1
int InList(int v, int list[],int d,int c){
	for(int i=d;i<c;i++){
		if (list[i]==v) return i;
	}
	return -1;
}

//chen v vao open theo thu tu tang cua f
void Insert(int v,int open[],int d,int &c){
	int i=c-1;
	while(i>=d&&f[open[i]]>f[v]){
		open[i+1]=open[i];
		i--;	
	} 	
	open[i+1]=v; c++;
}

void PrintOpen(int open[], int d, int c){
	cout<<"*open:";
	for(int i=d;i<c;i++){
		int v=open[i];
		cout<<v<<"("<<g[v]<<","<<f[v]<<","<<father[v]<<"); ";
	}
	cout<<endl;
}
void PrintClose(int close[], int c){
	cout<<"close:";
	for(int i=0;i<c;i++){
		cout<<close[i]<<"; ";
	}
	cout<<endl;
}
//trang thai ban dau la s, trang thai ket thuc la t
bool A_Star_Search(int s, int t) {
	int open[MAX],close[MAX];
	int d=0,c=0;//dau, cuoi cua open
	int k=0;//cuoi cua close
	int u,v,i,j,gv,fv;
	//buoc khoi tao: kt ttbd va cat ttbd vao open
	g[s]=0;f[s]=h[s];open[c++]=s;
	bool found=false;
	//buoc lap
	while(true){
		PrintOpen(open,d,c);
		PrintClose(close,k);
		if(d==c) {found=false; break;}//kg tim thay ttkt
		u=open[d++];//lay 1 dinh u trong open
		if(u==t) {found=true; break;} //neu u la ttkt thi tim thay
		close[k++]=u;//cat u vao close
		for(v=1;v<=n;v++){//xet nhung dinh v ke u
			if(a[u][v]!=0){				
				gv=g[u]+ a[u][v]; fv =gv + h[v]; //tinh gt f[v]									
				i=InList(v,open,d,c);j=InList(v,close,0,k);
				if (i==-1&&j==-1){//neu v chua co trong open va close
					g[v]=gv; f[v]=fv; father[v]=u;
					Insert(v,open,d,c);//them v vao open theo thu tu tang cua f
				}else{					
					if(i!=-1){//neu v da co trong open
						if(fv<f[v]){//gia tri v nho hon gia tri cu
							g[v]=gv; f[v]=fv;father[v]=u;//cap nhat gia tri v
							int t=i-1;//sx lai open theo tt tang cua f
							while(t>=d&&f[open[t]]>fv) {
								open[t+1]=open[t];
								t--;
							}
							open[t+1]=v;
						}
					}
				}
			}
		}
	}
	if(!found){
		cout<<"khong tim thay trang thai "<<t;
	}else{
		cout<<"\nChi phi tim kiem:" <<g[t]<<endl;
		cout<<"Chuoi cac phep bien doi trang thai:";
		cout<<t<<" ";
		do{
			t=father[t];	
			cout<<t<<" ";
		}while(t!=s);		
	}
	cout<<endl;
	return found;
}

int main(){
	int s,t;
	DocFile();
	cout<<"Trang thai ban dau:";cin>>s;
	cout<<"Trang thai ket thuc:";cin>>t;
	A_Star_Search(s,t);	
	return 0;
}
