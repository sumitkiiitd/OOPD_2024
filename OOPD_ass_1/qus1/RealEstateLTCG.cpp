#include "RealEstateLTCG.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cmath>

// ====================
// InflationRate Class Implementation
// ====================

InflationRate::InflationRate(const std::string &csvFile) {
    loadCSV(csvFile);
}

void InflationRate::loadCSV(const std::string &csvFile) {
    std::ifstream file(csvFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + csvFile);
    }

    std::string line;
    std::getline(file, line);  // Skip the header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string yearStr, growthStr, inflationStr;

        std::getline(ss, yearStr, ',');
        std::getline(ss, growthStr, ',');
        std::getline(ss, inflationStr, ',');

        int year = std::stoi(yearStr.substr(0, 4));
        double inflation = std::stod(inflationStr);

        years.push_back(year);
        inflationRates.push_back(inflation);
    }
    file.close();
}

double InflationRate::getCumulativeInflation(int startYear, int endYear) const {
    double cumulativeInflation = 1.0;
    
    for (size_t i = 0; i < years.size(); ++i) {
        if (years[i] > startYear && years[i] <= endYear) {
            cumulativeInflation *= (1 + inflationRates[i] / 100);
        }
    }
    return cumulativeInflation;
}

// ====================
// PropertyGrowthRate Class Implementation
// ====================

PropertyGrowthRate::PropertyGrowthRate(const std::string &csvFile) {
    loadCSV(csvFile);
}

void PropertyGrowthRate::loadCSV(const std::string &csvFile) {
    std::ifstream file(csvFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + csvFile);
    }

    std::string line;
    std::getline(file, line);  // Skip the header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string yearStr, growthStr, inflationStr;

        std::getline(ss, yearStr, ',');
        std::getline(ss, growthStr, ',');
        std::getline(ss, inflationStr, ',');

        int year = std::stoi(yearStr.substr(0, 4));
        
        double growth = std::stod(growthStr);
    
        years.push_back(year);
        
        growthRates.push_back(growth);
    
    }
    file.close();
}

double PropertyGrowthRate::getCumulativeGrowth(int startYear, int endYear) const {
    double cumulativeGrowth = 1.0;

    
    for (size_t i = 0; i < years.size(); ++i) {
        
        if (years[i] > startYear && years[i] <= endYear) {
            cumulativeGrowth *= (1 + growthRates[i] / 100);
        }
    }
    return cumulativeGrowth;
}

// ====================
// RealEstateInvestment Class Implementation
// ====================

RealEstateInvestment::RealEstateInvestment(double initialPrice, int purchaseYear, const std::string &csvFile)
    : initialPrice(initialPrice), purchaseYear(purchaseYear), inflationRate(csvFile), growthRate(csvFile) {}

double RealEstateInvestment::calculateSellingPrice(int sellingYear) {
    double cumulativeGrowth = growthRate.getCumulativeGrowth(purchaseYear, sellingYear);
    return initialPrice * cumulativeGrowth;
}

double RealEstateInvestment::calculateTraditionalLTCG(int sellingYear) {
    double sellingPrice = calculateSellingPrice(sellingYear);
    double cumulativeInflation = inflationRate.getCumulativeInflation(purchaseYear, sellingYear);
    double inflationAdjustedCost = initialPrice * cumulativeInflation;
    double actualProfit = sellingPrice - inflationAdjustedCost;
    return 0.20 * actualProfit;
}
