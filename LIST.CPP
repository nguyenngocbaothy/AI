
struct list{
	nodeptr head;
	nodeptr tail;	
};
void InitList(list &l){
	l.head=l.tail=NULL;	
}
//chen node p vao dau list l
void InsertFirstList(nodeptr p, list &l){
	if(l.head==NULL) l.tail=l.head=p;
	else{
		p->next=l.head;
		l.head=p;
	}
}
//chen node  vao cuoi list l
void InsertLastList(nodeptr p, list &l){
	if(l.head==NULL) l.tail=l.head=p;
	else{
		l.tail->next=p;	
		l.tail=p;
	}
}
//chen p sau q, q khac cuoi
void InsertAfterList(nodeptr p, nodeptr q){
	p->next=q->next;
	q->next=p;
}
//chen node p vao list l sao cho list sx giam theo f
void InsertSortDecList(nodeptr p, list &l){
	if(l.head==NULL) l.tail=l.head=p;
	else{
		nodeptr q=l.head,r;
		while(q!=NULL&&q->f>p->f){
			r=q; q=q->next;
		}
		if(q==NULL){
			InsertLastList(p,l);
		}else{
			if(q==l.head) InsertFirstList(p,l);
			else{
				InsertAfterList(p,r);	
			}			
		}
	}
}
//chen node p vao list l sao cho list sx tang theo f
void InsertSortAscList(nodeptr p, list &l){
	if(l.head==NULL) l.tail=l.head=p;
	else{
		nodeptr q=l.head,r;
		while(q!=NULL&&q->f<p->f){
			r=q; q=q->next;
		}
		if(q==NULL){
			InsertLastList(p,l);
		}else{
			if(q==l.head) InsertFirstList(p,l);
			else{
				InsertAfterList(p,r);	
			}			
		}
	}
}
//huy node dau list l
void DelFirstList(list &l){
	if(l.head==NULL) return;
	nodeptr p=l.head;
	l.head=p->next;
	delete p;
	if(l.head==NULL) l.tail=NULL;
}
//huy node sau nut p cua list l
void DelAfterList(nodeptr p,list &l){
	nodeptr q=p->next;
	if(q!=NULL){
		p->next=q->next;
		if(l.tail==q) l.tail=p;
		delete q;	
	}
}
//chuyen nut dau l1 qua dau l2
nodeptr MoveFirstToFirst(list &l1, list &l2){
	if(l1.head==NULL) return NULL;
	nodeptr p=l1.head; 
	l1.head=p->next;
	if(l1.head==NULL) l1.tail=NULL;
	p->next=NULL;
	InsertFirstList(p, l2);
	return p;
}
//chuyen cac nut trong ds l1 vao dau ds l2
//thu tu se dao nguoc
void MoveList(list &l1, list &l2){
	while(MoveFirstToFirst(l1,l2)!=NULL);
}
//tra ve ds thu tu cac nut tren duong di tu s den t
list Path(nodeptr s, nodeptr t){
	list l;
	InitList(l);
	InsertFirstList(t,l);
	nodeptr p=t;
	do{
		p=p->father;	
		InsertFirstList(p,l);	
	}while(p!=s);
	return l;
}
