#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

struct MenuItem {
    std::string name;
    double price;
};

void displayMenu(const MenuItem menu[], int size) {
    std::cout << "Goldilocks Menu:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << i + 1 << ". " << std::setw(20) << std::left << menu[i].name
                  << " - $" << std::fixed << std::setprecision(2) << menu[i].price << std::endl;
    }
}

void displayOrder(const std::vector<std::string>& orders) {
    std::cout << "\nYour current order:" << std::endl;
    for (const auto& item : orders) {
        std::cout << "- " << item << std::endl;
    }
}

int main() {
    const int menuSize = 10;
    MenuItem menu[menuSize] = {
        {"Pancake", 5.99},
        {"Waffle", 6.49},
        {"French Toast", 7.99},
        {"Omelette", 8.99},
        {"Bacon and Eggs", 9.49},
        {"Bagel with Cream Cheese", 4.99},
        {"Fruit Salad", 6.99},
        {"Hash Browns", 5.49},
        {"Cinnamon Roll", 3.99},
        {"Granola Parfait", 7.49}
    };

    std::vector<std::string> orders;
    double totalBill = 0.0;
    bool isSenior = false;
    const double seniorDiscount = 0.1; // 10% discount for senior citizens

    char addMore;
    char seniorResponse;

    // Ask if the user is a senior citizen
    std::cout << "Are you a senior citizen? (y/n): ";
    std::cin >> seniorResponse;

    if (seniorResponse == 'y' || seniorResponse == 'Y') {
        isSenior = true;
    }

    do {
        // Display the menu
        displayMenu(menu, menuSize);

        // Display the current order
        displayOrder(orders);

        // Get user's choice
        int choice;
        std::cout << "Enter the number of the menu item you'd like to order: ";
        std::cin >> choice;

        // Validate the user's choice
        if (choice >= 1 && choice <= menuSize) {
            orders.push_back(menu[choice - 1].name);
            totalBill += menu[choice - 1].price;
            std::cout << "You ordered: " << menu[choice - 1].name << " - $"
                      << std::fixed << std::setprecision(2) << menu[choice - 1].price << std::endl;
        } else {
            std::cout << "Invalid choice. Please enter a number between 1 and " << menuSize << std::endl;
        }

        // Ask if the user wants to add more items
        std::cout << "Do you want to add more items to your order? (y/n): ";
        std::cin >> addMore;

        // Check if the user wants to cancel the last item
        if (addMore == 'n' || addMore == 'N') {
            char cancelOrder;
            std::cout << "Do you want to cancel the last item added to your order? (y/n): ";
            std::cin >> cancelOrder;

            if (cancelOrder == 'y' || cancelOrder == 'Y') {
                if (!orders.empty()) {
                    totalBill -= menu[choice - 1].price;
                    orders.pop_back();
                    std::cout << "Last item removed from your order." << std::endl;
                } else {
                    std::cout << "Your order is already empty." << std::endl;
                }
            }
        }

    } while (addMore == 'y' || addMore == 'Y');

    // Apply discount for senior citizens
    if (isSenior) {
        double discountAmount = totalBill * seniorDiscount;
        totalBill -= discountAmount;
        std::cout << "\nSenior Citizen Discount Applied: -$" << std::fixed << std::setprecision(2) << discountAmount << std::endl;
    }

    // Display the receipt
    std::cout << "\n===== Receipt =====" << std::endl;
    displayOrder(orders);
    std::cout << "Total Bill: $" << std::fixed << std::setprecision(2) << totalBill << std::endl;

    return 0;
}
