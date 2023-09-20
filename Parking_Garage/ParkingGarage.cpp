#include<iostream>
#include<string>
#include<queue>
#include<iomanip>
using namespace std;
struct Car {
	string Owner_Name;
	string License_Plate;
	string Car_Model;
	int Ticket_Number;
	int Check_in;
	int Check_Out;
};

class Lot {
public:
	queue<Car> carLot;
	const int MAX_CARS = 10;
	double owed = 0;
	double finalTotal = 0;
	int day = 1;
	int prevDay = day;

	void displayMenu() {
		int choice;
		bool expression = true;
		while (expression) {
			cout << "Day " << day << endl;
			cout << "1. Add car" << endl << "2. Remove car" << endl << "3. Move a head a day" << endl << "4. Exit "
				<< endl << "Select an option: ";
			cin >> choice;
			if (choice == 4)
				break;
			handleUserChoice(choice);
		}
	}

	void handleUserChoice(int choice) {
		switch (choice) {
		case 1:
			readData();
			break;
		case 2:
			pop();
			break;
		case 3:
			increaseDay();
			break;
		case 4:
			break;
		default:
			cout << "\nInvalid option bra!\n";
			break;
		}
	}

	void readData() {
		Car car;
		cout << "Enter owner name: ";
		getline(cin >> ws, car.Owner_Name); // ws extracts all whitespace characters after cin
		cout << "\nEnter license plate number: ";
		cin >> car.License_Plate;
		cout << "\nEnter car model: ";
		cin >> car.Car_Model;
		cout << "\nEnter ticket number: ";
		cin >> car.Ticket_Number;
		cout << "\nEnter check-in time: ";
		cin >> car.Check_in;
		cout << endl;
		push(car);
		cout << "\nCar added to lot.\n";
		
	}

	void push(Car car) {
		if (carLot.size() <= MAX_CARS)
			carLot.push(car);
		else
			"\nCar Parking Lot is full.\n";
	}

	void printMoneyMade() {
		cout << fixed << setprecision(2) << "\nTotal made today is: $"
			<< getTotal() << "\n";
	}

	Car printFrontLot() {
		if (!carLot.empty()) {
			return carLot.front();
		}
	}

	void pop() {
		if (carLot.size() >= 1) {
			int ticket = carLot.front().Ticket_Number;
			cout << "Enter your check-out time for tikcet #" << ticket << ": ";
			cin >> carLot.front().Check_Out;
			owed = calculateCharge(carLot.front().Check_in, carLot.front().Check_Out);
			finalTotal += owed;
			cout << fixed << setprecision(2);
			cout << carLot.front().Owner_Name << "'s amount owed: $" << owed << endl << endl;
			carLot.pop();
		}
		else
			cout << "No cars in lot\n";
		
	}

	double calculateCharge(double checkIn, double checkOut) {
		double timeSpent = checkOut - checkIn;
		double charge = 0;
		double tip;
		if (day != prevDay)
			charge = 20.00;
		else {
			if (timeSpent >= 0 && timeSpent <= .30)
				charge = 3.00;
			else if (timeSpent >= .31 && timeSpent <= .59)
				charge = 5.00;
			else if (timeSpent >= 1 && timeSpent <= 5)
				charge = 10.00;
			else if (timeSpent >= 6 && timeSpent <= 12)
				charge = 15.00;
		}
		tip = 0.15 * charge;
		return charge + tip; 
	}

	double getTotal() {
		return finalTotal;
	}

	double monthlyIncome() {
		double weeklyIncome;
		if (day == 7) {
			weeklyIncome = finalTotal * day;
			double monthlyIncome = weeklyIncome * 4;
			monthlyIncome = monthlyIncome - (0.55 * monthlyIncome);
			return monthlyIncome;
		}
		return 0;
	}

	double yearlyNetIncome() {
		return monthlyIncome() * 12;
	}

	void increaseDay() {
		day += 1;
	}

};

int main() {
	Car car;
	Lot lot;
	lot.displayMenu();
	lot.printMoneyMade();
	cout << "\nMonthly Income is $" << lot.monthlyIncome() << endl;
	cout << "Yearly Income is $" << lot.yearlyNetIncome() << endl;
	cout << "Predicted Annual Income generated from parking garage: $" << fixed << setprecision(2) << (lot.finalTotal * 7) * 52;
}
