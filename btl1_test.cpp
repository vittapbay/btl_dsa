#include "main.h"

class imp_res : public Restaurant
{
	public:	
		class wating
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
					cust=nullptr;
				}
			};
			
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
					line--;				
				}
				head=tail=nullptr;
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
			void current (int index){//dung cho shellsort
					Node*temp=head;
					for(int i=0;i<index;i++){
						temp=temp->next;
					}
					cout<<temp->getName()<<" "<<temp->getEnergy();
					return ;
				}
			void deleteNode(int num, customer *x){//khi xoa truyen vi tri xoa
				if(num>=line||num>MAXSIZE){
					this->clear();				
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
			if(totalcustomer<MAXSIZE/2){//so khach trong ban <max/2
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
					}
					else if(cust->getLine()<MAXSIZE){
						if(cust->chekName(name)){
							customer*cus=new customer(name,energy,nullptr,nullptr);
							cust->add(cus);
						}
					}
				}
			}
			
			//cout<<0<<endl;
		}	
		void BLUE(int num)
		{	if(num<waiting4luv->getLine())
			{
				while (num)
				{
					waiting4luv->deleteNode(1,X);
					num--;
				}
			}
			else{
					waiting4luv->deleteNode(num,X);
			}
			wating*tes=waiting4luv;
			cout<<tes->getLine();
			customer*s=X;
			
			for(int i=0;i<1;i++){
				//s->print();
				//s=s->prev;
				//tes->current(i);cout<<endl;
			}			
			
			//cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			//cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			//cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			//cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			//cout << "light " << num << endl;
		}
};