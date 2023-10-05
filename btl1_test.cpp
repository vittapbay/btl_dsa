#include "main.h"

class imp_res : public Restaurant
{
	public:	
		imp_res() {};
		customer*X;
		int totalcustomer=0;
		customer*waitFront;
		customer*waitBack;
		int line=0;
		bool sameName(string name,customer* cus){
			
		}
		void RED(string name, int energy)
		{	if(!energy) return;
			if(totalcustomer<MAXSIZE/2){
				if(!totalcustomer){
					customer *cus = new customer (name, energy, nullptr, nullptr);//name eneegy prev next
					X=cus;
					totalcustomer++;
				}
				else{
					if(energy<X->energy){
						customer *cus = new customer (name, energy, X->prev, X);
						X=cus;
						totalcustomer++;
					}
					else{
						customer *cus = new customer (name, energy, X, X->next);
						X=cus;
						totalcustomer++;
					}
				}
			}
			else{
				if(totalcustomer<MAXSIZE){

					totalcustomer++;
				}
				else{
					if(line<MAXSIZE){
						if(!line){
							customer *cus = new customer (name, energy, nullptr, nullptr);
							totalcustomer++;
							waitBack=waitFront=cus;
						}
						else{
							customer *cus = new customer (name, energy, waitBack, nullptr);
							waitBack->next=cus;
							waitBack=cus;
							totalcustomer++;
						}
					}
				}
			}
			cout << name << " " << energy << endl;
			customer *cus = new customer (name, energy, nullptr, nullptr);
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
