#include "VendingMachine.h"
#include <iostream>
#include <iomanip>
#include <string>
#include<windows.h>
using namespace std;

VendingMachine::VendingMachine() {
	dimes_in_container = 20;
	nickels_in_container = 20;
	quarters_in_container = 20;
	dollars_in_container = 20;
	five_dollars_in_container = 20;
	amount_payed = 0;
	hours = 0;
	total_sales = 0;
}

void VendingMachine::refill() {

}

void VendingMachine::display_menu() {
	if (!this->is_on()) {
		cout << "Vending machine is off\n";
		cout << "Turning on....hold tight\n\n";
		this->is_vm_on = true;
	}
	Sleep(5000);
	while (hours < 6) {
		cout << setw(5) << left << "A1";
		cout << setw(10) << left << "Coke";
		cout << setw(1) << left << " ";
		cout << setw(10) << right << "$0.95" << endl;
		cout << setw(5) << left << "B2";
		cout << setw(10) << left << "Doritos";
		cout << setw(1) << left << " ";
		cout << setw(10) << right << "$0.75" << endl;
		cout << setw(5) << left << "C3";
		cout << setw(10) << left << "Snickers";
		cout << setw(1) << left << " ";
		cout << setw(10) << right << "$0.55" << endl;
		cout << setw(5) << left << "D4";
		cout << setw(10) << left << "Chex Mix";
		cout << setw(1) << left << " ";
		cout << setw(10) << right << "$0.60" << endl;
		cout << setw(5) << left << "E5";
		cout << setw(10) << left << "Pepsi";
		cout << setw(1) << left << " ";
		cout << setw(10) << right << "$0.90" << endl;
		cout << "\nHello, enter one of the following options A1, B2, C3, D4, or E5";
		string userChoice;
		cout << "\nor you can press r to View Records: ";
		try {
			cin >> userChoice;
			char upper = toupper(userChoice[0]);
			handle_user_selection(upper);
		}
		catch (exception e) {
			cout << "Something went wrong\n";
		}
		hours++;
	}
}

void VendingMachine::display_amount_paid(double a) {
	cout << "So far you've payed: $" << fixed << setprecision(2);
	cout << a << endl;
}

bool VendingMachine::is_on() {
	return is_vm_on; 
}

void VendingMachine::handle_user_selection(char choice) {
	cout << "This Vending Machine takes dimes, nickels, quarters, $1 bills, and $5 bills.\n";
	
	switch (choice) {
		case 'A':
			cout << "\nCoke selected!";
			handle_user_payment(coke);
			++coke.units_sold;
			break;
		case 'B':
			cout << "\nDoritos selected!";
			handle_user_payment(doritos);
			++doritos.units_sold;
			break;
		case 'C':
			cout << "\nSnickers selected!";
			handle_user_payment(snickers);
			++snickers.units_sold;
			break;
		case 'D':
			cout << "\nChex Mix selected!";
			handle_user_payment(chexmix);
			++chexmix.units_sold;
			break;
		case 'E':
			cout << "\nPepsi selected!";
			handle_user_payment(pepsi);
			++pepsi.units_sold;
			break;
		case 'R':
			handle_item_records();
		default:
			break;
	}
}

void VendingMachine::handle_user_payment(Item i) { 
	char payment = '0';
	double amount_payed = 0; this->amount_payed = 0;
	while (payment != 'e' && amount_payed < i.PRICE) {
		cout << "\nEnter q (add quarters) d (add dimes) n (add nickels) 1 (add $1) or 5 (add $5) bills or e to exit: ";
		try {
			cin >> payment;
			if (payment == 'q') {
				// Add quarters 
				add_quarters();
				amount_payed = this->amount_payed;
				display_amount_paid(amount_payed);
			}
			else if (payment == 'd') {
				// Add dimes
				add_dimes();
				amount_payed = this->amount_payed;
				display_amount_paid(amount_payed);
			}
			else if (payment == 'n') {
				// Add nickels
				add_nickels();
				amount_payed = this->amount_payed;
				display_amount_paid(amount_payed);
			}
			else if (payment == '1') {
				// Add 1 dollar
				add_dollar();
				amount_payed = this->amount_payed;
				display_amount_paid(amount_payed);
			}
			else if (payment == '5') {
				// Add 5 dollars
				add_5_dollars();
				amount_payed = this->amount_payed;
				display_amount_paid(amount_payed);
			}
			else if (payment == 'e')
				break;
			else
				cout << "\nInvalid option. Try again.";
		}
		catch (exception e) {
			cout << "Something went wrong\n";
		}
	}
	if (is_change(i, amount_payed)) {
		double change = compute_change(i, amount_payed);
		cout << fixed << setprecision(2);
		cout << "\nYou're change is $" << change << endl;
	}
	if (i.needs_refill())
		i.refill();
}

void VendingMachine::handle_item_records() {
	compute_total_sales();
	cout << "\n==================================\n";
	cout << fixed << setprecision(2) << "Total Sales for Coke: $" << coke.total_sales << endl;
	cout << "==================================\n";
	cout << "\n==================================\n";
	cout << fixed << setprecision(2) << "Total Sales for Doritos: $" << doritos.total_sales << endl;
	cout << "==================================\n";
	cout << "\n==================================\n";
	cout << fixed << setprecision(2) << "Total Sales for Snickers: $" << snickers.total_sales << endl;
	cout << "==================================\n";
	cout << "\n==================================\n";
	cout << fixed << setprecision(2) << "Total Sales for Chex Mix: $" << chexmix.total_sales << endl;
	cout << "==================================\n";
	cout << "\n==================================\n";
	cout << fixed << setprecision(2) << "Total Sales for Pepsi: $" << pepsi.total_sales << endl;
	cout << "==================================\n";
	cout << fixed << setprecision(2) << "Total Sales Combined: $" << this->total_sales << endl;
	cout << "==================================\n";
	cout << "\nTotal Cost of all items: $" << compute_total_cost() << endl;
	if(compute_profit() > compute_total_cost())
		cout << "\nProfit: $" << compute_profit() << endl;
}

void VendingMachine::compute_total_sales() {
	coke.total_sales = coke.PRICE * coke.units_sold * hours;

	doritos.total_sales = doritos.PRICE * doritos.units_sold * hours;

	snickers.total_sales = snickers.PRICE * snickers.units_sold * hours;

	chexmix.total_sales = chexmix.PRICE * chexmix.units_sold * hours;

	pepsi.total_sales = pepsi.PRICE * pepsi.units_sold * hours;

	this->total_sales = coke.total_sales + doritos.total_sales
		+ snickers.total_sales + chexmix.total_sales + pepsi.total_sales;
}

double VendingMachine::compute_total_cost() {
	double total = coke.cost_of_item + doritos.cost_of_item
		+ chexmix.cost_of_item + snickers.cost_of_item + pepsi.cost_of_item;
	return total;
}

void VendingMachine::add_quarters() {
	int newQuarters;
	cout << "\nEnter number of quarters you wanna add: ";
	cin >> newQuarters;
	if (quarters_in_container <= 100)
		quarters_in_container += newQuarters;
	else
		quarters_in_container = 20;
	this->amount_payed += newQuarters * 0.25;
}

double VendingMachine::compute_profit() {
	return this->total_sales - compute_total_cost();
}

void VendingMachine::add_dimes() {
	int newDimes;
	cout << "\nEnter number of dimes you wanna add: ";
	cin >> newDimes;
	if (dimes_in_container <= 100)
		dimes_in_container += newDimes;
	else
		dimes_in_container = 20;
	this->amount_payed += newDimes * 0.10;
}

void VendingMachine::add_nickels() {
	int newNickels;
	cout << "\nEnter number of nickels you wanna add: ";
	cin >> newNickels;
	if (nickels_in_container <= 100)
		nickels_in_container += newNickels;
	else
		nickels_in_container = 20;
	this->amount_payed += newNickels * 0.05;
}

void VendingMachine::add_dollar() {
	int newDollar;
	cout << "\nEnter number of dollars you wanna add: ";
	cin >> newDollar;
	if (dollars_in_container <= 100)
		dollars_in_container += newDollar;
	else
		dollars_in_container = 20;
	this->amount_payed += newDollar * 1.00;
}

void VendingMachine::add_5_dollars() {
	int newFiveDollar = 1;
	//cout << "\nEnter number of five dollar bills you wanna add: ";
	//cin >> newFiveDollar;
	if (five_dollars_in_container <= 60)
		five_dollars_in_container += newFiveDollar;
	else
		five_dollars_in_container = 20;
	this->amount_payed += newFiveDollar * 5.00;
}

bool VendingMachine::is_change(Item i, double amount_payed) {
	if (amount_payed > i.PRICE) {
		return true;
	}
	return false;
}

double VendingMachine::compute_change(Item i, double amount) {
	return amount - i.PRICE;
}

bool VendingMachine::Item::needs_refill() {
	if (this->num_items < 5)
		return true;
	return false;
}

void VendingMachine::Item::refill() {
	this->num_items = 30;
}

double VendingMachine::Item::get_tot_sales() {
	return this->total_sales;
}

void VendingMachine::Item::compute_tot_sales() {
	this->total_sales = this->PRICE * this->units_sold;
}

VendingMachine::Item::Item() {
	num_items = 30;
	PRICE = 0;
	cost_of_item = 0;
	labor_cost = 0;
	overhead = 0;
	units_sold = 0;
	total_sales = 0;
}

VendingMachine::Coke::Coke() {
	PRICE = 0.95;
	cost_of_item = 0.35 * PRICE;
	labor_cost = 0.25 * PRICE;
	overhead = 0.05 * PRICE;
	units_sold = 0;
}

VendingMachine::Doritos::Doritos() {
	PRICE = 0.75;
	cost_of_item = 0.35 * PRICE;
	labor_cost = 0.25 * PRICE;
	overhead = 0.05 * PRICE;
}

VendingMachine::Snickers::Snickers() {
	PRICE = 0.55;
	cost_of_item = 0.35 * PRICE;
	labor_cost = 0.25 * PRICE;
	overhead = 0.05 * PRICE;
}

VendingMachine::ChexMix::ChexMix() {
	PRICE = 0.60;
	cost_of_item = 0.35 * PRICE;
	labor_cost = 0.25 * PRICE;
	overhead = 0.05 * PRICE;
}

VendingMachine::Pepsi::Pepsi() {
	PRICE = 0.90;
	cost_of_item = 0.35 * PRICE;
	labor_cost = 0.25 * PRICE;
	overhead = 0.05 * PRICE;
}




