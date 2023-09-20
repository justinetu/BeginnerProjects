#pragma once
#include <iostream>
class VendingMachine {
	// Nested classes
	class Item {
	public:
		Item();
		double PRICE;
		int num_items;
		bool needs_refill();
		void refill();
		void compute_tot_sales();
		double get_tot_sales();
		double cost_of_item; // 35% of selling cost
		double labor_cost;	// 25% of selling price
		double overhead;   // 5% of selling price
		double total_sales;
		int units_sold;
		
	};
	class Coke : public Item {
	public:
		Coke();
	};

	class Doritos : public Item {
	public:
		Doritos();
	};

	class Snickers : public Item {
	public:
		Snickers();
	};

	class ChexMix : public Item {
	public:
		ChexMix();
	};

	class Pepsi : public Item {
	public:
		Pepsi();
	};
	// class methods and variables for VendingMachine
public:
	VendingMachine();
	bool is_vm_on = false;
	int dimes_in_container, nickels_in_container, quarters_in_container, dollars_in_container, five_dollars_in_container, total_sales, hours; // They'll all be initialized to 20
	void refill();

	void display_menu();
	void display_amount_paid(double a);
	bool is_on();
	void handle_user_selection(char choice);
	void handle_user_payment(Item i);
	void handle_item_records();
	void compute_total_sales();
	double compute_total_cost();
	double compute_profit();

	void add_quarters();
	void add_dimes();
	void add_nickels();
	void add_dollar();
	void add_5_dollars();

	double amount_payed;

	bool is_change(Item i, double amount_payed);
	double compute_change(Item i, double amount);

	Coke coke;
	Doritos doritos;
	Snickers snickers;
	ChexMix chexmix;
	Pepsi pepsi;

};

