#ifndef STORE_H
#define STORE_H
#include <string>
#include <vector>
#include "product.h"
#include "staff.h"

class Store {
private:
	std::string storeName; //Name of the store
	std::vector<Product> inventory; //Vector containing all products in the store's inventory, using Product class
	std::vector<Staff> staff; //Vector containing all staff employed at store, using Staff class
	double storeTotalCash; //Amount of money in store registers

public:
	//Constructor
	Store(std::string name, std::vector<Product> inventory, std::vector<Staff> staff, double cash);

	//Getters
    const std::string& getName() const;
    const std::vector<Product>& getInventory() const;
    const std::vector<Staff>& getStaff() const;
    double getStoreTotalCash() const;

	
	//Staff management
	void addStaff(Staff& staff);
	void removeStaff(int employeeID);
	void viewStaffList();

	//Product management
	void addProduct(const Product& product, int quantity);
    void removeProduct(int productID, int quantity);
	void viewProductList();

	//Other methods
	void changeName(std::string newStoreName);
  	void addCash(double amount);
  	void removeCash(double amount);
};

#endif //STORE_H
