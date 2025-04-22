#include <iostream>
#include <vector>
#include <limits>  
#include "store.h"
#include "product.h"
#include "staff.h"
#include "transactions.h"

// Helper function to clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Displays main menu
int showMainMenu() {
    std::cout << "\n=== Store Management System ===\n";
    std::cout << "1. Product Management\n";
    std::cout << "2. Staff Management\n";
    std::cout << "3. Process Transaction\n";
    std::cout << "4. View Store Status\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter choice: ";
    
    int choice;
    std::cin >> choice;
    return choice;
}

// Product management submenu
void productManagement(Store& store) {
    int choice;
    do {
        std::cout << "\n--- Product Management ---\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Restock Product\n";
        std::cout << "3. View All Products\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id, quantity;
                double price;
                std::string name;
                
                std::cout << "Enter Product ID: ";
                std::cin >> id;
                clearInputBuffer();
                
                std::cout << "Enter Product Name: ";
                std::getline(std::cin, name);
                
                std::cout << "Enter Price: ";
                std::cin >> price;
                
                std::cout << "Enter Initial Quantity: ";
                std::cin >> quantity;
                
                Product newProduct(id, name, price, quantity);
                store.addProduct(newProduct);
                break;
            }
            case 2: {
                int id, quantity;
                std::cout << "Enter Product ID to restock: ";
                std::cin >> id;
                std::cout << "Enter Quantity to add: ";
                std::cin >> quantity;
                
                try {
                    store.restockProduct(id, quantity);
                    std::cout << "Restock successful.\n";
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3:
                store.viewProductList();
                break;
        }
    } while (choice != 4);
}

// Staff management submenu
void staffManagement(Store& store) {
    int choice;
    do {
        std::cout << "\n--- Staff Management ---\n";
        std::cout << "1. Add Staff Member\n";
        std::cout << "2. Deactivate Staff\n";
        std::cout << "3. View All Staff\n";
        std::cout << "4. Back to Main Menu\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string name, position;
                
                std::cout << "Enter Staff ID: ";
                std::cin >> id;
                clearInputBuffer();
                
                std::cout << "Enter Staff Name: ";
                std::getline(std::cin, name);
                
                std::cout << "Enter Position: ";
                std::getline(std::cin, position);
                
                Staff newStaff(id, name, position);
                store.addStaff(newStaff);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter Staff ID to deactivate: ";
                std::cin >> id;
                
                try {
                    store.removeStaff(id);
                    std::cout << "Staff deactivated.\n";
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 3:
                store.viewStaffList();
                break;
        }
    } while (choice != 4);
}

// Transaction processing
void processTransaction(Store& store) {
    int staffId;
    std::cout << "Enter Staff ID: ";
    std::cin >> staffId;
    
    // Verify staff exists and is active
    Staff* staff = store.findStaff(staffId);
    if (!staff || !staff->getIsActive()) {
        std::cerr << "Error: Invalid or inactive staff ID.\n";
        return;
    }
    
    std::vector<std::pair<int, int>> items; // productID, quantity
    char anotherItem = 'y';
    
    while (anotherItem == 'y') {
        int productId, quantity;
        
        std::cout << "Enter Product ID: ";
        std::cin >> productId;
        
        std::cout << "Enter Quantity: ";
        std::cin >> quantity;
        
        items.push_back({productId, quantity});
        
        std::cout << "Add another item? (y/n): ";
        std::cin >> anotherItem;
    }
    
    try {
        if (store.processTransaction(staffId, items)) {
            std::cout << "Transaction completed successfully!\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Transaction failed: " << e.what() << "\n";
    }
}

int main() {
    Store store("Awesome Electronics");
    
    // Load initial test data
    try {
        store.loadFromFile("data");
    } catch (const std::exception& e) {
        std::cerr << "Warning: " << e.what() << " (Starting with empty store)\n";
    }
    
    int choice;
    do {
        choice = showMainMenu();
        
        switch (choice) {
            case 1:
                productManagement(store);
                break;
            case 2:
                staffManagement(store);
                break;
            case 3:
                processTransaction(store);
                break;
            case 4:
                std::cout << "\n--- Store Status ---\n";
                std::cout << "Store Name: " << store.getName() << "\n";
                std::cout << "Register Balance: $" << store.getStoreTotalCash() << "\n";
                std::cout << "\nProducts:\n";
                store.viewProductList();
                std::cout << "\nStaff:\n";
                store.viewStaffList();
                break;
        }
        
    } while (choice != 5);
    
    // Save data before exiting
    try {
        store.saveToFile("data");
        std::cout << "Data saved successfully. Exiting...\n";
    } catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << "\n";
    }
    
    return 0;
}
