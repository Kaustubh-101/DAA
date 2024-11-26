#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <sstream>

struct Item {
    int product_id;
    double value;
    double weight;
    int shelf_life;
    double ratio;

    Item(int id, double v, double w, int s)
        : product_id(id), value(v), weight(w), shelf_life(s) {
        ratio = (weight > 0 && shelf_life > 0) ? (value / weight) * (1.0 / shelf_life) : 0;
    }
};

void generateItemsCSV(const std::string &filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create the CSV file!" << std::endl;
        return;
    }

    srand(42); // Set seed for reproducibility
    file << "Item_ID,Shelf_Life_Days,Weight_tonnes,Value_INR\n";
    for (int i = 1; i <= 100; ++i) {
        int shelf_life = rand() % 99 + 1; // Random shelf life between 1 and 99
        double weight = 5 + static_cast<double>(rand()) / RAND_MAX * (50 - 5); // Random weight between 5 and 50
        double value = 10000 + static_cast<double>(rand()) / RAND_MAX * (1000000 - 10000); // Random value
        file << i << "," << shelf_life << "," << weight << "," << value << "\n";
    }
    file.close();
}

double fractionalKnapsack(std::vector<Item> &items, double capacity, std::vector<Item> &selected_items) {
    std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
        return a.ratio > b.ratio;
    });

    double total_value = 0.0;
    for (const auto &item : items) {
        if (capacity <= 0)
            break;

        if (item.weight <= capacity) {
            total_value += item.value;
            selected_items.push_back(item);
            capacity -= item.weight;
        } else {
            double fraction = capacity / item.weight;
            total_value += item.value * fraction;

            selected_items.push_back(Item(item.product_id, item.value * fraction, capacity, item.shelf_life));
            break;
        }
    }
    return total_value;
}

int main() {
    const std::string csvFilePath = "fractional_knapsack_shipping.csv";

    // Generate the items CSV
    generateItemsCSV(csvFilePath);

    // Read the CSV file and create Item objects
    std::ifstream file(csvFilePath);
    std::vector<Item> items;
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Skip header
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id, shelf_life;
            double weight, value;
            char comma;

            ss >> id >> comma >> shelf_life >> comma >> weight >> comma >> value;
            items.emplace_back(id, value, weight, shelf_life);
        }
        file.close();
    } else {
        std::cerr << "Error: Could not open the CSV file!" << std::endl;
        return 1;
    }

    double capacity = 200.0;
    std::vector<Item> selected_items;

    // Fractional knapsack algorithm
    double max_value = fractionalKnapsack(items, capacity, selected_items);

    // Print results
    std::cout << "\nMaximum value that can be accommodated in the knapsack: " << max_value << "\n";
    std::cout << "Selected items:\n";
    for (const auto &item : selected_items) {
        std::cout << "Product ID: " << item.product_id
                  << ", Value: " << item.value
                  << ", Weight: " << item.weight
                  << ", Shelf Life: " << item.shelf_life << "\n";
    }

    return 0;
}
