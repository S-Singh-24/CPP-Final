//store.cpp

#include <iostream>
#include <string>
#include <vector>
#include "product.h"
#include "store.h"
#include "staff.h"
#include "transactions.h"
#include <stdexcept>
#include <fstream>
#include <sstream>

//Constructor definition
Store::Store(std::string name, std::vector<Product> inventory, std::vector<Staff> staff, double cash)
	: storeName(name), inventory(inventory), staff(staff), storeTotalCash(cash) {
	
	//Input validation
	if (name.empty()) throw std::invalid_argument("Store must have a name.");
	if (inventory.empty()) throw std::invalid_argument("Must have at least one product to start with.");
	if (staff.empty()) throw std::invalid_argument("Must have at least one staff member to start with.");
	if (cash < 0) throw std::invalid_argument("Must have a positive amount of cash in the register.");
}
Store::Store(const std::string& name) : 
    storeName(name), 
    storeTotalCash(0.0) 
{
    // Initialize with empty inventory/staff
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
void Store::addProduct(const Product& product) {
    // Check if product exists
    for (auto& p : inventory) {
        if (p.getProductID() == product.getProductID()) {
            p.increaseQuantity(product.getQuantity());
            return;
        }
    }
    // If not found, add new product
    inventory.push_back(product);
}

void Store::restockProduct(int productID, int quantity) {
    for (auto& product : inventory) {
        if (product.getProductID() == productID) {
            product.increaseQuantity(quantity);
            return;
        }
    }
    throw std::runtime_error("Product not found");
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
		inventory.at(i).printProduct();
		std::cout << std::endl;
	}
}

Product* Store::findProduct(int productID) {
    for (auto& product : inventory) {
        if (product.getProductID() == productID) {
            return &product;
        }
    }
    return nullptr;
}

//Staff handling
void Store::addStaff(Staff& newStaffMember) {
	try {
		for (auto& staffMember : staff) { //Iterate through staff vector
			if (staffMember.getStaffID() == newStaffMember.getStaffID()) { //Check to see if employee ID already taken
				throw std::invalid_argument("There is already a staff member with that ID. Please try again.");
			}
		}
		//Else add new staff member
		staff.push_back(newStaffMember); //If not taken, add new staff member to staff vector
		return;
	}
	catch (std::invalid_argument const& e) {
		std::cout << e.what(); //Catch exception
	}
}

Staff* Store::findStaff(int staffID) {
    for (auto& staffMember : staff) {
        if (staffMember.getStaffID() == staffID) {
            return &staffMember;
        }
    }
    return nullptr;  // Not found
}

const Staff* Store::findStaff(int staffID) const {
    for (const auto& staffMember : staff) {
        if (staffMember.getStaffID() == staffID) {
            return &staffMember;
        }
    }
    return nullptr;
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

//Updated to reflect implementation of printStaffMember() in Staff
void Store::viewStaffList() {
	for (int i = 0; i < staff.size(); i++) {
		staff.at(i).printStaffMember(); //Loops through each staff member, printing info one by one
		std::cout << std::endl;
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

bool Store::processTransaction(int staffID, const std::vector<std::pair<int, int>>& items) {
    // Verify staff exists and is active
    Staff* staff = findStaff(staffID);
    if (!staff || !staff->getIsActive()) {
        throw std::runtime_error("Invalid or inactive staff ID");
    }

    // Process each item
    double total = 0.0;
    for (const auto& item : items) {
        int productID = item.first;
        int quantity = item.second;
        
        Product* product = findProduct(productID);
        if (!product) {
            throw std::runtime_error("Product ID " + std::to_string(productID) + " not found");
        }
        
        if (product->getQuantity() < quantity) {
            throw std::runtime_error("Insufficient stock for product ID " + std::to_string(productID));
        }
        
        // Update inventory and calculate total
        product->decreaseQuantity(quantity);
        total += product->getPrice() * quantity;
    }

    // Update store cash
    storeTotalCash += total;
    return true;
}

void Store::loadFromFile(const std::string& filename) {
    std::ifstream productFile(filename + "_products.txt");
    std::ifstream staffFile(filename + "_staff.txt");
    
    // Load products
    std::string line;
    while (std::getline(productFile, line)) {
        std::istringstream iss(line);
        int id, quantity;
        double price;
        std::string name;
        char comma;
        
        if (iss >> id >> comma && std::getline(iss, name, ',') >> 
            comma >> price >> comma >> quantity) {
            inventory.emplace_back(id, name, price, quantity);
        }
    }
    
    // Load staff
    while (std::getline(staffFile, line)) {
		std::istringstream iss(line);
		std::string token;
		std::vector<std::string> tokens;
		
		// Split line by commas
		while (std::getline(iss, token, ',')) {
			tokens.push_back(token);
		}
		
		// Should have 4 fields: ID,Name,Position,Active
		if (tokens.size() == 4) {
			try {
				int id = std::stoi(tokens[0]);
				std::string name = tokens[1];
				std::string position = tokens[2];
				bool active = static_cast<bool>(std::stoi(tokens[3]));
				
				Staff staff(id, name, position);
				staff.setIsActive(active);
				this->staff.push_back(staff);
			} catch (...) {
				// Handle conversion errors
				continue;
			}
		}
	}
}

void Store::saveToFile(const std::string& filename) const {
    std::ofstream productFile(filename + "_products.txt");
    std::ofstream staffFile(filename + "_staff.txt");
    
    // Save products
    for (const auto& product : inventory) {
        productFile << product.getProductID() << ","
                   << product.getName() << ","
                   << product.getPrice() << ","
                   << product.getQuantity() << "\n";
    }
    
    // Save staff
    for (const auto& staffMember : staff) {
        staffFile << staffMember.getStaffID() << ","
                 << staffMember.getName() << ","
                 << staffMember.getPosition() << ","
                 << staffMember.getIsActive() << "\n";
    }
}
