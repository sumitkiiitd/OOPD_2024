#include "RealEstateLTCG.h"
#include <iostream>
#include <string>
#include <iomanip>  // For std::fixed, std::setprecision

int main() {
    // File containing the inflation and property growth rates
    std::string csvFile = "inflation_growth.csv";  // Update this with your actual CSV file path
    
    // Initial property price and purchase year
    double initialPrice = 5000000.0;  // Rs 50 lakhs
    int purchaseYear = 2010;

    // Create a RealEstateInvestment object
    RealEstateInvestment investment(initialPrice, purchaseYear, csvFile);

    // Get the year of selling from the user
    int sellingYear;
    std::cout << "Enter the year of selling: ";
    std::cin >> sellingYear;

    // Validate the input
    if (sellingYear <= purchaseYear) {
        std::cerr << "Error: Selling year must be greater than the purchase year." << std::endl;
        return 1;
    }

    try {
        // Question 1: Traditional LTCG Calculation

        // Calculate the estimated selling price
        double sellingPrice = investment.calculateSellingPrice(sellingYear);
        
        // Calculate the traditional LTCG tax (20% with inflation adjustment)
        double traditionalTax = investment.calculateTraditionalLTCG(sellingYear);
        
        // Output the results for Question 1
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\n=== Traditional LTCG Calculation ===\n";
        std::cout << "Estimated Selling Price: Rs " << sellingPrice << std::endl;
        std::cout << "Traditional LTCG Tax (20% with inflation adjustment): Rs " << traditionalTax << std::endl;
        if (traditionalTax <= 0) {
            std::cout << "So tax paid is zero.\n";
        }


    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
