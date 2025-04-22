#include "product.h"
#include <stdexcept> // For std::invalid_argument

// Constructor
Product::Product(int id, std::string name, double price, int quantity) 
    : productID(id), name(name), price(price), quantityInStock(quantity) {
    
    // Input validation
    if (id <= 0) throw std::invalid_argument("Product ID must be positive");
    if (name.empty()) throw std::invalid_argument("Product name cannot be empty");
    if (price < 0.0) throw std::invalid_argument("Price cannot be negative");
    if (quantity < 0) throw std::invalid_argument("Quantity cannot be negative");
}

// Getters
int Product::getProductID() const {
    return productID;
}

std::string Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantityInStock;
}

// Setters
void Product::setName(std::string newName) {
    if (newName.empty()) {
        throw std::invalid_argument("Product name cannot be empty");
    }
    name = newName;
}

void Product::setPrice(double newPrice) {
    if (newPrice < 0.0) {
        throw std::invalid_argument("Price cannot be negative");
    }
    price = newPrice;
}

void Product::setQuantity(int newQuantity) {
    if (newQuantity < 0) {
        throw std::invalid_argument("Quantity cannot be negative");
    }
    quantityInStock = newQuantity;
}

// Methods
void Product::decreaseQuantity(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Decrease amount must be positive");
    }
    if (quantityInStock < amount) {
        throw std::invalid_argument("Insufficient stock");
    }
    quantityInStock -= amount;
}

void Product::increaseQuantity(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Increase amount must be positive");
    }
    quantityInStock += amount;
}