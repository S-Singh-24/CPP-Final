//store.cpp
//Current issues:
//  viewProduct() and viewStaffMember() not yet created

#include <iostream>
#include <string>
#include <vector>
#include "product.h"
#include "store.h"
#include "staff.h"
#include <stdexcept>

//Constructor definition
Store::Store(std::string name, std::vector<Product> inventory, std::vector<Staff> staff, double cash)
	: storeName(name), inventory(inventory), staff(staff), storeTotalCash(cash) {
}

//Getters
const std::string& Store::getName() const {
	return storeName;
}
const std::vector<Product>& Store::getInventory() const {
	return inventory;
}
const std::vector<Staff>& Store::getStaff() const {
	return staff;
}
double Store::getStoreTotalCash() const {
	return storeTotalCash;
}

//Other methods
//Changing the store name
void Store::changeName(std::string newName) {
	storeName = newName;
}

//Product handling
void Store::addProduct(const Product &product, int number) { //Add a certain number of product
	for (int i = 0; i < inventory.size(); i++) {
		if (inventory.at(i).getProductID() == product.getProductID()) { //at(i) to loop through staff vector
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
					throw std::invalid_argument("Number of products asked to remove exceeds amount of products in inventory."); //If there is less product than number we want to remove, throw exception
				}
				else {
					inventory.at(i).decreaseQuantity(number); //Remove number of products from inventory
					return;
				}
			}
		}
		throw std::invalid_argument("Product not found.");
	}
	catch (std::invalid_argument const& e) {
		std::cout << e.what(); //Catch exception
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
			if (staff.at(i).getStaffID() == newStaffMember.getStaffID()) { //Check to see if employee ID already taken
				throw std::invalid_argument("There is already a staff member with that ID. Please try again.");
			}
			else {
				staff.push_back(newStaffMember); //If not taken, add new staff member to staff vector
				return;
			}
		}
	}
	catch (std::invalid_argument const& e) {
		std::cout << e.what(); //Catch exception
	}
}

// Update removeStaff() to deactivate instead of erase:
void Store::removeStaff(int employeeID) {
	for (auto& s : staff) {
		if (s.getStaffID() == employeeID) {
			s.setIsActive(false);
			return;
		}
	}
	throw std::invalid_argument("Employee ID not found");
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
			throw std::invalid_argument("Invalid amount of cash. Please add a positive amount of cash to the register."); //Throw exception if cash amount is zero or negative
		}
		else {
			storeTotalCash = storeTotalCash + amount; //If okay value, add to register
		}
	}
	catch (std::invalid_argument const& e) {
		std::cout << e.what(); //Catch exception
	}
}

void Store::removeCash(double amount) {
	try {
		if (amount <= 0) {
			throw std::invalid_argument("Invalid amount of cash. Amount to remove must be positive and no greater than amount currently in the register."); //Ensure amount of cash to be removed is positive
		}
		else if (storeTotalCash < amount) {
			throw std::invalid_argument("Invalid amount of cash. Amount to remove must be positive and no greater than amount currently in the register."); //Ensure there is enough cash in the register to be removed
		}
		storeTotalCash = storeTotalCash - amount; //If value is okay, remove that much cash from the register
	}
	catch (std::invalid_argument const& e) {
		std::cout << e.what(); //Catch exception
	}
}
