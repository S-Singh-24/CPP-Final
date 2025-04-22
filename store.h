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
	Store(const std::string& name);

	//Getters
    const std::string& getName() const;
    const std::vector<Product>& getInventory() const;
    const std::vector<Staff>& getStaff() const;
    double getStoreTotalCash() const;

	
	//Staff management
	void addStaff(Staff& staff);
	void removeStaff(int employeeID);
	void viewStaffList();
	Staff* findStaff(int staffID);
	const Staff* findStaff(int staffID) const;

	//Product management
	void addProduct(const Product& product);
    void removeProduct(int productID, int quantity);
	void viewProductList();
	void restockProduct(int productID, int quantity);
	Product* findProduct(int productID);

	//Other methods
	void changeName(std::string newStoreName);
  	void addCash(double amount);
  	void removeCash(double amount);
	bool processTransaction(int staffID, const std::vector<std::pair<int, int>>& items);
	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename) const;
};

#endif //STORE_H
