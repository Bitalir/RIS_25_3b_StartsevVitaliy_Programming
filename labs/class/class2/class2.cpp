#include <clocale>
#include <iostream>
using namespace std;

class ATM {
private:
	int ID;
	double balance;
	double max_sum;
public:
	ATM() {
		cout << "Конструктор без параметров: " << endl;
		this->ID = 0;
		this->balance = 0;
		this->max_sum = 0;
	}
	ATM(int ID, double balance, double max_sum) {
		this->ID = ID;
		this->balance = balance;
		this->max_sum = max_sum;
	}
	ATM(const ATM& ATM) {
		this->ID = ATM.ID;
		this->balance = ATM.balance;
		this->max_sum = ATM.max_sum;
	}
	void SetID(int ID) {
		this->ID = ID;
	}
	void SetBalance(double balance) {
		this->balance = balance;
	}
	void SetMax_sum(double max_sum) {
		this->max_sum = max_sum;
	}
	int GetID() {
		return this->ID;
	}
	double GetBalance() {
		return this->balance;
	}
	double GetMax_sum() {
		return this->max_sum;
	}
	void Print() {
		cout << "ID: " << ID << endl;
		cout << "Остаток денег в банкоате: " << balance << endl;
		cout << "Макс. сумма, которую можно снять: " << max_sum << endl;
		cout << endl;
	}
	~ATM() {
		cout << "Деструктор" << endl;
	}
};

int main(){
	setlocale(LC_ALL, "RU");
	ATM user1;
	user1.Print();
	ATM user2(547534, 500000, 100000);
	user2.Print();
	ATM user3 = user2;
	user3.Print();
	cout << "С помощью сеттеров: " << endl;
	user3.SetID(7647463);
	user3.SetBalance(300000);
	user3.SetMax_sum(100000);
	user3.Print();
	return 0;
}
