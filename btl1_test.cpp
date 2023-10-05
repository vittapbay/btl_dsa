#include "main.h"

class imp_res : public Restaurant
{
	public:	
		imp_res() {};
		customer*X;
		int totalcustomer=0;
		customer*wait;
		int line=0;
		void RED(string name, int energy)
		{	
			if(totalcustomer<MAXSIZE)
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