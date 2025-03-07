#ifndef REALESTATELTCG_H
#define REALESTATELTCG_H

#include <vector>
#include <string>

class InflationRate {
public:
    InflationRate(const std::string &csvFile);
    double getCumulativeInflation(int startYear, int endYear) const;

private:
    std::vector<int> years;
    std::vector<double> inflationRates;
    void loadCSV(const std::string &csvFile);
};

class PropertyGrowthRate {
public:
    PropertyGrowthRate(const std::string &csvFile);
    double getCumulativeGrowth(int startYear, int endYear) const;

private:
    std::vector<int> years;
    std::vector<double> growthRates;
    void loadCSV(const std::string &csvFile);
};

class RealEstateInvestment {
public:
    RealEstateInvestment(double initialPrice, int purchaseYear, const std::string &csvFile);
    double calculateSellingPrice(int sellingYear);
    double calculateTraditionalLTCG(int sellingYear);

private:
    double initialPrice;
    int purchaseYear;
    InflationRate inflationRate;
    PropertyGrowthRate growthRate;
};

#endif // REALESTATELTCG_H
