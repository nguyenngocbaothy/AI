#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
const int vc=100;
const int size=3;
int board[size][size]={0};//ban co	
struct node{
	int x,y;//vi tri	
};
 
//dem so duong co the thang cua player
//u la trang thai hien dang xet
int NumPathsWin(int player) {
    int s,i,j;
    s=0; 
    //dem so hang co the thang
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) 
            if (board[i][j] == 3-player) break;
        if (j == size) s++;
    }
    //dem so cot co the thang
    for (j = 0; j < size; j++) {
        for (i = 0; i < size; i++) 
            if (board[i][j] == 3-player) break;
        if (i == size) s++;
    }
    //duong cheo chinh co the thang
    for (i = 0; i < size; i++) 
        if (board[i][i] == 3-player) break;
    if (i == size) s++;
    //duong cheo phu co the thang
    for (i = 0; i < size; i++)
        if (board[i][size-1 - i] ==3-player) break;
    if (i == size) s++;
    return s;
}
int h() {
	return NumPathsWin(1) - NumPathsWin(2);
}
int Win(int player){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++)
			if(board[i][j]!=player) break;
		if(j==size) return 1;
	}
	for(j=0;j<size;j++){
		for(i=0;i<size;i++)
			if(board[i][j]!=player) break;
		if(i==size) return 1;
	}
	for(i=0;i<size;i++)
		if(board[i][i]!=player) break;	
	if(i==size) return 1;
	for(i=0;i<size;i++)
		if(board[i][size-1-i]!=player) break;	
	if(i==size) return 1;
	return 0;
}
int MinValue(int depth, int alpha, int beta);
int MaxValue(int depth, int alpha, int beta){
	if(Win(1)) return vc;
	if(Win(2)) return -vc;
	if (depth<=0) return h();
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(board[i][j]==0){
				board[i][j]=1;
				int val=MinValue(depth-1,alpha,beta);	
				board[i][j]=0;
				if(val>alpha) alpha=val;
				if(alpha>=beta) return alpha;
			}
		}
	}
	return alpha;
}
int MinValue(int depth, int alpha, int beta){
	if(Win(1)) return vc;
	if(Win(2)) return -vc;
	if (depth<=0) return h();
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(board[i][j]==0){
				board[i][j]=2;
				int val=MaxValue(depth-1,alpha, beta);
				board[i][j]=0;
				if(val<beta) beta=val;	
				if(alpha>=beta) return beta;
			}
		}
	}
	return beta;
}
node AlphaBeta(int player,int depth){	
	int val; 
	node v;
	int alpha = -vc, beta = vc;
	if (player==1){
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(board[i][j]==0){
					board[i][j]=1;
					val=MinValue(depth,alpha,beta);
					board[i][j]=0;
					if (val>alpha) {alpha=val; v.x=i;v.y=j;}								
				}
			}
		}		
	}else{		
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(board[i][j]==0){
					board[i][j]=2;
					val=MaxValue(depth,alpha,beta);
					board[i][j]=0;
					if (val<beta) {beta=val;v.x=i;v.y=j;}								
				}
			}
		}		
	}	
	board[v.x][v.y]=player;
	return v;
}
void PrintBoard(){
	printf("%2s"," ");
	for(int i=0;i<size;i++) printf("%4d",i+1);
	printf("\n\n");
	for(int i=0;i<size;i++){
		printf("%2d",i+1);
		for(int j=0;j<size;j++){
			switch(board[i][j]){
				case 0:	printf("%4s",".");break;
				case 1:	printf("%4s","X");break;
				case 2:	printf("%4s","O");break;
			}			
		}	
		printf("\n\n");
	}
	printf("\n\n");
}
int IsFullBoard(){
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
			if(board[i][j]==0) return 0;
	return 1;	
}
//nguoi choi
node Play2(){
	int i,j;
	node v;
	do{
		printf("Nhap hang,cot:");
		scanf("%d%d",&i,&j);			
	}while(i<1||i>size||j<1||j>size||board[i-1][j-1]!=0);
	printf("\n");
	board[i-1][j-1]=2; v.x=i;v.y=j;
	return v;
}
int main(){
	node u;
	int d=3;
	PrintBoard();
	while(1){
		u=AlphaBeta(1,d);
		PrintBoard();
		if(Win(1)==1) {printf("X thang!\n"); break;}	
		if(IsFullBoard()==1) {printf("Hoa!\n"); break;}
		u=Play2();
		//u=AlphaBeta(2,d);
		PrintBoard();
		if(Win(2)==1) {printf("O thang!\n"); break;}
		if(IsFullBoard()==1) {printf("Hoa!\n"); break;}	
	}
	printf("\n");
	return 1;
}