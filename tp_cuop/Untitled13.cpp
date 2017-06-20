#include <iostream>
#include <fstream>
using namespace std;
#define MAX 20
int ma_tran_ke[MAX][MAX]={0};
int tham[MAX] = {0};
int soDinh = 0;
void doc_file(){
	fstream f;
	f.open("d:/do_thi.txt", ios::in);
	int i, j;
	f >> soDinh;
	cout << "so dinh " << soDinh << endl;
	while (!f.eof()){
		f >> i >> j;
		cout << i << " " << j << endl;
		ma_tran_ke[i][j] = ma_tran_ke[j][i] = 1;
	}
	f.close();
}
void DSF1(int i){
	cout << i << " ";
	tham[i] = 1;
	for (int j = 1; j <= soDinh; j++){
		if (tham[j] == 0 && ma_tran_ke[i][j] == 1)
			DSF1(j);
	}
}
void DSF(){
	for (int i = 1; i <= soDinh; i++)
		if (tham[i] == 0)
			DSF1(i);
}
int main(){
	doc_file();	
	DSF();
	return 0;
}