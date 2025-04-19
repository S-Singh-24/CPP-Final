#include "transactions.h"
#include <iostream>
#include <iomanip>

// Constructor
Transactions::Transactions(int transID, int empID)
    : transactionID(transID), employeeID(empID), totalAmount(0.0) {
}

// Getters
int Transactions::getTransactionID() const {
    return transactionID;
}

int Transactions::getEmployeeID() const {
    return employeeID;
}

double Transactions::getTotalAmount() const {
    return totalAmount;
}

std::vector<Product> Transactions::getPurchasedProducts() const {
    return purchasedProducts;
}

// Methods
void Transactions::addProduct(Product& product, int quantity) {
    Product productCopy = product;
    productCopy.setQuantity(quantity);
    purchasedProducts.push_back(productCopy);
    calcTotal(); // update total price after adding a product 
}

void Transactions::removeProduct(int productID) {
    // Iterate through the purchased products to find and remove the one with matching ID
    for (auto it = purchasedProducts.begin(); it != purchasedProducts.end(); ++it) {
        if (it->getProductID() == productID) {
            purchasedProducts.erase(it);
            break;
        }
    }
    calcTotal(); // update total price after removing a product 
}

void Transactions::calcTotal() {
    totalAmount = 0.0;
    for (const auto& product : purchasedProducts) {
        totalAmount += product.getPrice() * product.getQuantity();
    }
}

void Transactions::printReceipt() const {
    std::cout << "=== Receipt ===" << std::endl;
    std::cout << "Transaction ID: " << transactionID << std::endl;
    std::cout << "Employee ID: " << employeeID << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Items Purchased:" << std::endl;

    for (const auto& product : purchasedProducts) {
        std::cout << "- " << product.getName()
                  << " (x" << product.getQuantity()
                  << ") @ $" << product.getPrice()
                  << " each" << std::endl;
    }

    std::cout << "Total: $" << totalAmount << std::endl;
    std::cout << "================" << std::endl;
}
