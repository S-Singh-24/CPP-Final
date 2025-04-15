#ifndef TRANSACTIONS_H
#define	TRANSACTIONS_H

#include <vector>
#include "product.h"

class Transactions {
private:
	int transactionID; //way to identify specific transaction 
	int employeeID; //id of staff member who completed the transaction
	std::vector<Product> purchasedProducts;//way to dynamically store products purchased in the transaction
	double totalAmount;

public:
	//constructor
	Transactions(int transID, int empID);

	//getters
	int getTransactionID() const;
	int getEmployeeID() const;
	double getTotalAmount() const;
	std::vector<Product> getPurchasedProducts() const;

	//methods
	void addProduct(Product& product, int quantity);
	void removeProduct(int productID);
	void calcTotal();
	void printReceipt() const;

}; 

#endif 