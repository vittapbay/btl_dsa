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
				Node*next;
				Node*prev;
				Node(customer*cust, Node*prev,Node*next){
					this->cust=cust;
					this->prev=prev;
					this->next=next;
				}
				string getName(){
					return cust->name;
				}
				int getEnergy(){
					return cust->energy;
				}
			};
			
		private:
			int line=0;
			Node*head;
			Node*tail;
		public:
			wating(){
				this->head=this->tail=nullptr;
				line++;
			}
			void clear(){
				Node*temp=this->head;
				while(line){
					Node*clone=temp->next;
					delete temp;
					temp=clone;
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
				Node*temp=new Node(cust,nullptr,nullptr);
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
		wating* cust=new wating();
		///
		bool sameName(string name){
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
				if(!totalcustomer){//truong hop ko co ai trong ban
					customer *cus = new customer (name, energy, nullptr, nullptr);//name eneegy prev next
					X=cus;
					totalcustomer++;
				}
				else{
					if(sameName(name))return;//check same name in table
					else if(energy<X->energy){//energy<X   --->them nguoc chieu kim dong ho
						customer *cus = new customer (name, energy, X->prev, X);
						X=cus;
						totalcustomer++;
					}
					else{// energy>= X   them cung chieu kim clock
						customer *cus = new customer (name, energy, X, X->next);
						X=cus;
						totalcustomer++;
					}
				}
			}
			else{
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
						temp=temp->next;
					}
					temp=X;
					for(int i=0;i<index;i++){
						temp=temp->next;
					}
					if(sub<0){//am them nguoc chieu
						customer *cus = new customer (name, energy, X->prev, X);
						X=cus;
					}
					else{// khac 0 them cung chieu
						customer *cus = new customer (name, energy, X, X->next);
						X=cus;
					}
					totalcustomer++;
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
			cout << name << " " << energy << endl;
			//customer *cus = new customer (name, energy, nullptr, nullptr);
		}	
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
		}
		void PURPLE()
		{
			cout << "purple"<< endl;
		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
		}
};