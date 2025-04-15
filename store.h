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
	std::string getName();
	std::vector<Product> getInventory();
	std::vector<Staff> getStaff();
	double getStoreTotalCash();

	//Other methods
	void addProduct(Product& product, int number);
	void removeProduct(int productID, int number);
	void viewProductList();
	void viewStaffList();
  void addCash(double amount);
  void removeCash(double amount);
};

#endif //STORE_H
