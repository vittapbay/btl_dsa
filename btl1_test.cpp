#include "main.h"

class imp_res : public Restaurant
{
	public:	
			class Node{
				public:
				customer*cust;
				int index;
				Node*next;
				Node*prev;
				Node(customer*cust, Node*prev,Node*next,int index){
					this->cust=cust;
					this->prev=prev;
					this->next=next;
					this->index=index;
				}
				string getName(){
					return cust->name;
				}
				int getEnergy(){
					return cust->energy;
				}
				~Node(){
					//cust=nullptr;
				}
			};
		class wating
		{		
		public:
			int line=0;
			Node*head;
			Node*tail;
		public:
			wating(){
				this->head=this->tail=nullptr;

			}
			void clear(){
				while(this->line){
					Node*temp=head->next;
					deleteCust(head->cust,nullptr);
					delete head;
					head=temp;	
					this->line--;				
				}
				head=tail=nullptr;
			}
			void clearTable(int& totalcustomer){
				while(totalcustomer){
					Node*temp=head->next;
					deleteCust(head->cust,nullptr);
					delete head;
					head=temp;	
					line--;	
					totalcustomer--;			
				}
			}
			void deleteCust(customer*cust,customer*x){
				if(cust->prev!=nullptr&&cust->next!=nullptr){
					customer*before=cust->prev;
					customer*after=cust->next;
					if(line==2&&before==after){
						if(x!=nullptr){
							x=before;
						}
						before->next=nullptr;
						after->prev=nullptr;
						delete cust;
						return;
					}
					if(x!=nullptr){
						x=(x->energy>0)?cust->next:cust->prev;
					}
					before->next=after;//vi tri2 tro di
					after->prev=before;
					//cout<<cust->prev->energy<<' '<<cust->name<<endl;
					delete cust;
					//  cap nhat cho X, chua cap nhat xong
				}
				else if(line==1){//1 pt
					x=nullptr;
					//delete cust;
					cust=nullptr;
				}
				else if(cust->prev==nullptr&&cust->next!=nullptr){//truong hop cho hang cho or 2 pt trong ban
					if(x!=nullptr){
							x=cust->next;
						}
					cust->next->prev=nullptr;
					delete cust;
				}
				else if(cust->prev!=nullptr&&cust->next==nullptr){// 2 pt trg ban
					if(x!=nullptr){
						x=cust->prev;
					}
					cust->prev->next=nullptr;
					delete cust;
				}
				
			}
			void current (){//dung cho shellsort
					Node*temp=head;
					for(int i=0;i<line;i++){
						temp->cust->print();
						temp=temp->next;
					}
					
					return ;
				}
			void deleteNode(int num, customer *x,int& total){//khi xoa truyen vi tri xoa
				if(num>=total||num>MAXSIZE){
					this->clearTable(total);				
				}
				else if(num==1){
					if(line>2){
						head=head->next;
						deleteCust(head->prev->cust,x);
						delete head->prev;
						head->prev=nullptr;
					}
					else{//=2
						deleteCust(head->cust,x);
						delete head;
						head=tail;
					}
					line--;
					total--;
				}
				else{
					Node*temp=head;
					while (--num)
					{
						temp=temp->next;
					}
					deleteCust(temp->cust,x);
					temp->prev->next=temp->next;
					temp->next->prev=temp->prev;
					delete temp;
					head->prev=nullptr;
					line--;
					total--;
				}
			}
			bool chekName(string name){
				if(head==nullptr) return true;
				else{
					Node*temp=head;
					for(int i=0;i<line;i++){
						if(temp->getName()==name)return false;
						temp=temp->next;
					}
					return true;
				}
			}
			void add(customer*cust){
				Node*temp=new Node(cust,nullptr,nullptr,line);
				if(!head){
					head=temp;
				}
				else{
					tail->next=temp;
					temp->prev=tail;
				}
				tail=temp;
				line++;
			}
			~wating(){
				clear();
			}
			int getLine(){
				return this->line;
			}
		};
		imp_res() {};
		customer*X;
		int totalcustomer=0;// total people in table
		wating* cust=new wating();// for waiting people
		wating* waiting4luv=new wating();// for people around table
		///
		bool sameName(string name){// checked X=nullptr ?
			customer*temp=X;
			for (int i=0;i<totalcustomer;i++)
			{
				if(temp->name==name)return true;
				temp=temp->next;
			}
			return false;
		}
		void RED(string name, int energy)
		{	
			if(energy==0) return;
			if(totalcustomer<MAXSIZE/2+MAXSIZE%2){//so khach trong ban <max/2
				if(totalcustomer==0){//truong hop ko co ai trong ban
					customer *cus = new customer (name, energy, nullptr, nullptr);//name eneegy prev next
					X=cus;
					totalcustomer++;
					waiting4luv->add(cus);
				}
				else{
					if(sameName(name))return;//check same name in table
					if(energy<X->energy){//energy<X   --->them nguoc chieu kim dong ho
					
						//ng 2 dc vao
							customer *cus = new customer (name, energy, X->prev, X);//can fix
							if(X->prev==nullptr){
								X->next=cus;
								cus->prev=X;        //1 pt---
							}
							else{
								X->prev->next=cus;
							}
							X->prev=cus;
							X=cus;
							totalcustomer++;
							waiting4luv->add(cus);
					}
					else{// energy>= X   them cung chieu kim clock
						
						
							customer *cus = new customer (name, energy, X, X->next);// can fix
							if(cus->next!=nullptr){
								X->next->prev=cus;
							}
							else{//so pt htai la 1
								X->prev=cus;
								cus->next=X;
							}
							X->next=cus;
							X=cus;
							totalcustomer++;
							waiting4luv->add(cus);
						
					}
				}
				
			}
			else{// TH >max/2
				if(sameName(name))return;//check same name in table
				
				if(totalcustomer<MAXSIZE){
					int sub=abs(energy)-abs(X->energy);
					int index=0;
					customer*temp=X;
					for(int i=0;i<totalcustomer;i++){
						if(abs(abs(energy)-abs(temp->energy))>abs(sub)){
							sub=abs(energy)-abs(temp->energy);
							index=i;
						}
						if(totalcustomer>2)temp=temp->next;
						else if(totalcustomer==2){
							 if(temp->next)temp=temp->next;
							 else temp=temp->prev;
						}
					}
					temp=X;
					for(int i=0;i<index;i++){
						if(temp->next)temp=temp->next;
						else temp=temp->prev;
					}
					if(sub<0){//am them nguoc chieu
							customer *cus = new customer (name, energy, temp->prev, temp);//can fix
							if(temp->prev==nullptr){
								temp->next=cus;
								cus->prev=temp;        //1 pt---
							}
							else{
								temp->prev->next=cus;
							}
							temp->prev=cus;
							X=cus;
							totalcustomer++;
							waiting4luv->add(cus);	
					}
					else{// khac 0 them cung chieu
						customer *cus = new customer (name, energy, temp, temp->next);// can fix
							if(cus->next!=nullptr){
								temp->next->prev=cus;
							}
							else{//so pt htai la 1
								temp->prev=cus;
								cus->next=temp;
							}
							temp->next=cus;
							X=cus;
							totalcustomer++;
							waiting4luv->add(cus);
					}
				}
				else{
					if(cust->getLine()==0) {//so ng trong hang doi=0
						customer*cus=new customer(name,energy,nullptr,nullptr);
						cust->add(cus);
						waiting4luv->add(cus);
					}
					else if(cust->getLine()<MAXSIZE){
						if(cust->chekName(name)){
							customer*cus=new customer(name,energy,nullptr,nullptr);
							cust->add(cus);
							waiting4luv->add(cus);
						}
					}
				}
			}
			
			//cout<<0<<endl;
		}	
		void pluss(Node*&temp){
			if(temp->getEnergy()==0) return;
			if(totalcustomer<MAXSIZE/2+MAXSIZE%2){//so khach trong ban <max/2
				if(totalcustomer==0){//truong hop ko co ai trong ban
					X=temp->cust;
					totalcustomer++;
				}
				else{
					if(sameName(temp->getName()))return;//check same name in table
					if(temp->getEnergy()<X->energy){//energy<X   --->them nguoc chieu kim dong ho
					
						//ng 2 dc vao
							customer *cus=temp->cust;
							cus->prev=X->prev;
							cus->next=X;
							if(X->prev==nullptr){
								X->next=cus;
								//cus->prev=X;        //1 pt---
							}
							else{
								X->prev->next=cus;
							}
							X->prev=cus;
							X=cus;X->print();
							totalcustomer++;
					}
					else{// energy>= X   them cung chieu kim clock
							customer*cus=temp->cust;
							cus->prev=X;
							cus->next=X->next;
							if(X->next!=nullptr){
								X->next->prev=cus;
							}
							else{//so pt htai la 1
								X->prev=cus;
								cus->next=X;
							}
							X->next=cus;
							X=cus;
							totalcustomer++;						
					}
				}
				
			}
			else{// TH >max/2
				if(sameName(temp->getName()))return;//check same name in table
				
				if(totalcustomer<MAXSIZE){
					int sub=abs(temp->getEnergy())-abs(X->energy);
					int index=0;
					customer*tem=X;
					for(int i=0;i<totalcustomer;i++){
						if(abs(abs(temp->getEnergy())-abs(tem->energy))>abs(sub)){
							sub=abs(temp->getEnergy())-abs(tem->energy);
							index=i;
						}
						if(totalcustomer>2)tem=tem->next;
						else if(totalcustomer==2){
							 if(temp->next)tem=tem->next;
							 else tem=tem->prev;
						}
					}
					tem=X;
					for(int i=0;i<index;i++){
						if(temp->next)temp=temp->next;
						else tem=tem->prev;
					}
					if(sub<0){//am them nguoc chieu
							customer*cus=temp->cust;
							cus->prev=tem->prev;
							cus->next=tem;
							if(tem->prev==nullptr){
								tem->next=cus;
								cus->prev=tem;        //1 pt---
							}
							else{
								tem->prev->next=cus;
							}
							tem->prev=cus;
							X=cus;
							totalcustomer++;
					}
					else{// khac 0 them cung chieu
						customer*cus=temp->cust;
						cus->prev=tem;
						cus->next=tem->next;
							if(cus->next!=nullptr){
								tem->next->prev=cus;
							}
							else{//so pt htai la 1
								tem->prev=cus;
								cus->next=tem;
							}
							tem->next=cus;
							X=cus;
							totalcustomer++;
					}
				}
				else{
					return;
				}
			}
		}
		Node*findCust(customer* s,wating* temp){
			Node*run=temp->head;
			if(temp->head==nullptr)return nullptr;	
			while(run->cust!=s){
				run=run->next;
				if(run==nullptr)break;
			}
			if(run==nullptr){//k co
				return nullptr;
			}
			return run;
		}
		void deleteOC(customer*&cus,int& line, customer*&x){
			if(cus->prev!=nullptr&&cus->next!=nullptr){
					customer*before=cus->prev;
					customer*after=cus->next;
					if(line==2&&before==after){
						if(x!=nullptr){
							x=before;
						}
						before->next=nullptr;
						after->prev=nullptr;
						delete cus;
						return;
					}
					if(x!=nullptr){
						x=(x->energy>0)?cus->next:cus->prev;
					}
					before->next=after;//vi tri2 tro di
					after->prev=before;
					//X->print();
					//cout<<cust->prev->energy<<' '<<cust->name<<endl;
					delete cus;
				}
				else if(line==1){//1 pt
					x=nullptr;
					//delete cust;
					cus=nullptr;
				}
				else if(cus->prev==nullptr&&cus->next!=nullptr){//truong hop cho hang cho or 2 pt trong ban
					if(x!=nullptr){
							x=cus->next;
						}
					cus->next->prev=nullptr;
					delete cus;
				}
				else if(cus->prev!=nullptr&&cus->next==nullptr){// 2 pt trg ban
					if(x!=nullptr){
						x=cus->prev;
					}
					cus->prev->next=nullptr;
					delete cus;
				}
				else{
					delete cus;
				}
				line--;
		}
		
		void del(customer*te,wating*&temp){
				Node*tem=findCust(te,temp);
				if(!tem)return;// k co j trong temp
			if(temp->head==temp->tail){//1pt
				delete tem;
				temp->head=temp->tail=nullptr;
			}
			else if(tem==temp->head){
				temp->head=temp->head->next;
				delete tem;
				temp->head->prev=nullptr;
			}
			else if(tem==temp->tail){
				temp->tail=temp->tail->prev;
				delete tem;
				temp->tail->next=nullptr;
			}
			else{
				tem->next->prev=tem->prev;
				tem->prev->next=tem->next;
				delete tem;
			}
		}
		void BLUE(int num)
		{	if(num<totalcustomer)
			{
				while (num)
				{
					waiting4luv->deleteNode(1,X,totalcustomer);
					num--;
				}
				
			}
			else{
				waiting4luv->deleteNode(num,X,totalcustomer);
				X=nullptr;
			}
			Node*temp=waiting4luv->head;
				for (int i = 0; i < totalcustomer; i++)
				{
					temp=temp->next;
				}
				while (totalcustomer<MAXSIZE&&temp!=nullptr)
				{
					pluss(temp);
					del(temp->cust,cust);
					temp=temp->next;
					//X->print();
				}
				//X->print();
				//cout<<totalcustomer<<endl;
			//cout << "blue "<< num << endl;
		}

		Node* ptr(int num,wating*hangdoi){
			Node*temp=hangdoi->head;
			for(int i=0;i<num;i++){
				temp=temp;
			}
			return temp;
		}
		void inssort2(wating*&list , int n, int incr,int &time) {
		for (int i=incr; i<n; i+=incr)//a[]=list
		{
			for (int j=i; (j>=incr) &&(prior(ptr(j,list),ptr(j-incr,list))); j-=incr){
				Node*a=ptr(j,list);
				Node*b=ptr(j-incr,list);
				swap(a,b);time++;
				}
			}
		}
		void swap(Node*&a,Node*&b){
			// index a > index b ////      b  a
			//case b next to a/ b head or a tail
			if(b->next==a){
				Node*bPre=b->prev;
				Node*aNext=a->next;
				if(aNext)aNext->prev=b;
				if(bPre)bPre->next=a;
				b->prev=a;
				a->next=b;
				b->next=aNext;
				a->prev=bPre;
			}
			else{
				Node*bPre=b->prev;
				Node*aNext=a->next;
				Node*bNext=b->next;
				Node*aPre=a->prev;
				if(aNext)aNext->prev=b;
				if(bPre)bPre->next=a;//   bPre a bNext  aPre  b aNext
				a->next=bNext;
				b->prev=aPre;
				b->next=aNext;
				a->prev=bPre;

			}
		}
		bool prior(Node* a,Node*b){
			if(a->getEnergy()<=b->getEnergy()) return true;
			return false;
		}
		int sort(wating*&list, int n) { // Shellsort
			int time=0;
			for (int i=n/2; i>2; i/=2){ // For each increment
				for (int j=0; j<i; j++){ // Sort each sublist
				inssort2(list, n-j, i,time);
				inssort2(list, n, 1,time);
				}
			}
			return time;
		}
		int findMax(wating*temp){//index cua |energy| cao nhat moi vao
			int index=0;
			int max=0;
			Node*run=temp->head;
			int i=0;
			while(run){
				if(max<abs(run->getEnergy())){
					max=abs(run->getEnergy());
					index=i;
				}
				run=run->next;i++;
			}
			return index;
		}
		void PURPLE()
		{	int n=findMax(cust);
			//cout << "purple"<< endl;
			int timeswap=sort(cust,n);
			BLUE(timeswap%MAXSIZE);
			//cout<<n<<endl;
			//cout<<"purple "<<timeswap<<endl;
			//cust->head->cust->print();
		}
		void swap(customer*&onleft,customer*&onright){
			if(onleft->prev!=onright&&onleft->next!=onright){
				customer*leftPrev=onleft->next;
				customer*leftRight=onleft->prev;
				customer*rightR=onright->next;
				customer*rightL=onright->prev;
				leftRight->next=onright;
				onright->prev=leftRight;
				onright->next=leftPrev;
				leftPrev->prev=onright;
				rightL->next=onleft;
				onleft->prev=rightL;
				rightR->prev=onleft;
				onleft->next=rightR;
			}
			else{
				if(onleft->next==onright&&onleft->prev==onright){
					return;
				}
				else if(onleft->next==onright){//case1
					customer*leftRight=onleft->prev;
					customer*rightR=onright->next;
					leftRight->next=onright;
					onright->prev=leftRight;
					rightR->prev=onleft;
					onleft->next=rightR;
					onright->next=onleft;
					onleft->prev=onright;
				}
				else if(onleft->prev==onright){//case2
					customer*leftPrev=onleft->next;
					customer*rightL=onright->prev;
					onright->next=leftPrev;
					leftPrev->prev=onright;
					rightL->next=onleft;
					onleft->prev=rightL;
					onleft->next=onright;
					onright->prev=onleft;
				}
			}
		}
		void REVERSAL()
		{
			//cout << "reversal" << endl;
			int oan_linh=0;
			int gojo=0;
			customer*temp=X;
			for(int i=0;i<totalcustomer;i++){
				if(temp->energy>0)gojo++;
				else oan_linh++;
				temp=temp->next;
			}
			//case chu su
			customer*curr=X;
			customer*runR=X->next;
			if(runR==nullptr) return;
			while(curr!=runR&&gojo){
				if(gojo==1)break;
				if(curr->energy>0&&runR->energy>0){
					swap(curr,runR);
					gojo-=2;
					runR=runR->next;
					curr=curr->prev;
				}
				else if(curr->energy>0 && runR->energy<0){
					runR=runR->next;
				}
				else if(curr->energy<0 && runR->energy>0){
					curr=curr->prev;
				}
				else {
					runR=runR->next;
					curr=curr->prev;
				}
			}
			//case oan lin
			customer*cur=X;
			customer*run=X->next;
			while(curr!=runR&&gojo){
				if(oan_linh==1)break;
				if(cur->energy<0&&run->energy<0){
					swap(cur,run);
					oan_linh-=2;
					run=run->next;
					cur=cur->prev;
				}
				else if(cur->energy<0 && run->energy>0){
					run=run->next;
				}
				else if(cur->energy>0 && run->energy<0){
					cur=cur->prev;
				}
				else {
					run=run->next;
					cur=cur->prev;
				}
			}
			//cout<<"Reversal"<<endl;
		}
		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			//cout << "domain_expansion" << endl;
			int sumOfGojo=0;
			int sumOfSukuna=0;
			Node*temp=waiting4luv->head;
			for(int i=0;i<waiting4luv->getLine();i++){
				if(temp->cust->energy>0)sumOfGojo=sumOfGojo+temp->cust->energy;
				else sumOfSukuna=sumOfSukuna+temp->cust->energy;
				temp=temp->next;
			}
			if(sumOfGojo==0||sumOfSukuna==0) return;
			if(sumOfGojo>=abs(sumOfSukuna)){//kick oan linh
				Node*temp=waiting4luv->tail;
				while (temp!=nullptr)
				{	
					Node*copy=temp->prev;
					if(temp->cust->energy<0){
						temp->cust->print();
						customer*rr=temp->cust;
						del(rr,waiting4luv);
						 if(findCust(rr,cust)){
							del(rr,cust);
						 	deleteOC(rr,waiting4luv->line,X);
						 }
						else {
							del(rr,cust);
							deleteOC(rr,waiting4luv->line,X);
							totalcustomer--;
						}
					}
					temp=copy;
				}
				
			}
			else{//kick oan linh
				Node*temp=waiting4luv->tail;
				while (temp!=nullptr)
				{	
					Node*copy=temp->prev;
					if(temp->cust->energy>0){
						temp->cust->print();
						customer*rr=temp->cust;
						del(rr,waiting4luv);
						 if(findCust(rr,cust)){
							del(rr,cust);
						 	deleteOC(rr,waiting4luv->line,X);
						 }
						else {
							del(rr,cust);
							deleteOC(rr,waiting4luv->line,X);
							totalcustomer--;
							//cout<<totalcustomer<<endl;
						}
					}
					temp=copy;
				}
			}
			Node*test=waiting4luv->head;
				for (int i = 0; i < totalcustomer; i++)
				{
					test=test->next;				
				}
				//X->print();
				while (totalcustomer<MAXSIZE&&test!=nullptr)
				{	Node*tam=test->next;
					pluss(test);
					customer*ss=test->cust;
					del(ss,cust);
					test=tam;
					//X->print();
				}//cout<<totalcustomer;
			//cout<<"banh truong lanh dia"<<endl;
		}
		void LIGHT(int num)
		{	
				customer*s=X;
				if(num>0){
					for(int i=0;i<totalcustomer;i++){
						s->print();
						s=s->next;
					}	
				}
				else if(num<0){
					for(int i=0;i<totalcustomer;i++){
						s->print();
						s=s->prev;
					}	
				}
			else{
				wating*te=cust;
				te->current();
			}
			//cout << "light " << num << endl;
		}
		~imp_res(){
			delete waiting4luv;
			while(cust->line--){
				Node*temp=cust->head->next;
				delete cust->head;
				cust->head=temp;
			}
		}
};