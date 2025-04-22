#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
private:
    int productID;
    std::string name;
    double price;
    int quantityInStock;
    
public:
    Product(int id, std::string name, double price, int quantity);
    
    //getter
    int getProductID() const;
    std::string getName() const;
    double getPrice() const;
    int getQuantity() const;
    
    //setters
    void setName(std::string newName);
    void setPrice(double newPrice);
    void setQuantity(int newQuantity);
    
    //methods
    void decreaseQuantity(int amount);
    void increaseQuantity(int amount);
    void printProduct();
};

#endif // PRODUCT_H
