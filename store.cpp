//store.cpp
//Current issues:
//	need staff.h header to be defined
//	current linker between class declaration in store.h and class definition in store.cpp requires pointers in constructor
//	std::invalid_argument raises "type name not allowed" error
//  viewProduct() and viewStaffMember() not yet created

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "product.h"
#include "store.h"
#include "staff.h"

//Constructor definition
Store::Store(std::string name, std::vector<Product> inventory, std::vector<Staff> staff, double cash){
	this->storeName = name; //Requires pointers for constructor link
	this->inventory = inventory;
	this->staff = staff;
	this->storeTotalCash = cash;
}

//Getters
std::string Store::getName() {
	return storeName;
}
std::vector<Product> Store::getInventory() {
	return inventory;
}
std::vector<Staff> Store::getStaff() {
	return staff;
}
double Store::getStoreTotalCash() {
	return storeTotalCash;
}

//Other methods
//Changing the store name
void Store::changeName(std::string newName) {
	storeName = newName;
}

//Product handling
void Store::addProduct(Product& product, int number) { //Add a certain number of product
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory.at(i).getProductID() == product.getProductID()) { //at(i) too loop through staff vector
			inventory.at(i).increaseQuantity(number); //If product ID found, will simply incriment number of product by input variable number
			return;
		}
	}
	inventory.push_back(product); //If product is not found, add it to the vector
	return;
}

void Store::removeProduct(int productID, int number) {
	try {
		for (int i = 0; i < inventory.size(); i++) {
			if (inventory.at(i).getProductID() == productID) { //Looks at a specific vector in inventory, then uses .getProductID() to get product ID and compares with given product ID
				if (inventory.at(i).getQuantity() < number) {
					throw std::invalid_argument; //If there is less product than number we want to remove, throw exception
				}
				else {
					inventory.at(i).decreaseQuantity(number); //Remove number of products from inventory
					return;
				}
			}
		}
		throw std::invalid_argument;
	}
	catch (std::invalid_argument const& e) {
		std::cout << "Number of products asked to remove exceeds amount of products in inventory."; //Catch exception
	}
}

void Store::viewProductList() {
	for (int i = 0; i < inventory.size(); i++) {
		std::cout << inventory.at(i).printProduct() << std::endl; //Types out list of all products - refine later
	}
}

//Staff handling
void Store::addStaff(Staff& newStaffMember) {
	try {
		for (int i = 0; i < staff.size(); i++) { //Iterate through staff vector
			if (staff.at(i).getEmployeeID() == newStaffMember.getEmployeeID()) { //Check to see if employee ID already taken
				throw std::invalid_argument;
			}
			else {
				staff.push_back(newStaffMember); //If not taken, add new staff member to staff vector
				return;
			}
		}
	}
	catch (std::invalid_argument const& e) {
		std::cout << "There is already a staff member with that ID. Please try again."; //Catch exception
	}
}

void Store::removeStaff(int employeeID) {
	try {
		for (int i = 0; i < staff.size(); i++) { //Iterate through staff vector
			if (staff.at(i).getEmployeeID == employeeID) { //Find instance of employee ID to remove
				staff.at(i).erase(); //Remove staff member with that employee ID
				return;
			}
		}
		throw std::invalid_argument; //If employee ID not found in staff vector, throw exception
	}
	catch (std::invalid_argument const& e) {
		std::cout << "Employee ID not found. Please try again."; //Catch exception
	}
}

void Store::viewStaffList() {
	for (int i = 0; i < staff.size(); i++) {
		std::cout << staff.at(i).printStaffMember() << std::endl; //Types out list of all staff members - refine later
	}
}

//Cash handling
void Store::addCash(double amount) {
	try {
		if (amount <= 0) {
			throw std::invalid_argument; //Throw exception if cash amount is zero or negative
		}
		else {
			storeTotalCash = storeTotalCash + amount; //If okay value, add to register
		}
	}
	catch (std::invalid_argument const& e) {
		std::cout << "Invalid amount of cash. Please add a positive amount of cash to the register."; //Catch exception
	}
}

void Store::removeCash(double amount) {
	try {
		if (amount <= 0) {
			throw std::invalid_argument; //Ensure amount of cash to be removed is positive
		}
		else if (storeTotalCash < amount) {
			throw std::invalid_argument; //Ensure there is enough cash in the register to be removed
		}
		storeTotalCash = storeTotalCash - amount; //If value is okay, remove that much cash from the register
	}
	catch (std::invalid_argument const& e) {
		std::cout << "Invalid amount of cash. Amount to remove must be positive and no greater than amount currently in the register."; //Catch exception
	}
}
