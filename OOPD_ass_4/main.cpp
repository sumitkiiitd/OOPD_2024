#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Class to represent an Author
class Author {
public:
    std::string name;
    std::string affiliation;

    Author(const std::string& name, const std::string& affiliation)
        : name(name), affiliation(affiliation) {}
};

// Class to represent a Publication
class Publication {
private:
    std::string title;
    std::string venue;
    std::vector<Author> authors;
    std::string doi;
    int year;

public:
    // Constructor
    Publication(const std::string& title, const std::string& venue, const std::vector<Author>& authors, int year, const std::string& doi = "")
        : title(title), venue(venue), authors(authors), doi(doi), year(year) {}

    // Method to check if the publication has at least one institute-affiliated author
    bool hasInstituteAffiliation(const std::string& institute) const {
        return std::any_of(authors.begin(), authors.end(), [&](const Author& author) {
            return author.affiliation == institute;
        });
    }

    // Display details of the publication
    void display() const {
        std::cout << "Title: " << title << "\n";
        std::cout << "Venue: " << venue << "\n";
        std::cout << "Year: " << year << "\n";
        if (!doi.empty()) {
            std::cout << "DOI: " << doi << "\n";
        }
        std::cout << "Authors:\n";
        for (const auto& author : authors) {
            std::cout << "  Name: " << author.name << ", Affiliation: " << author.affiliation << "\n";
        }
    }
};

// Main function
int main() {
    // Create authors
    Author author1("Alice Smith", "Institute A");
    Author author2("Bob Johnson", "Institute A");
    Author author3("Charlie Brown", "Other University");

    // Create publications
    Publication pub1("Research on AI", "Journal of AI", {author1, author3}, 2024, "https://doi.org/10.1234/ai2024");
    Publication pub2("Advances in Networking", "Networking Conference", {author2}, 2023);

    // Store publications in a vector
    std::vector<Publication> publications = {pub1, pub2};

    // Display all publications
    for (const auto& pub : publications) {
        pub.display();
        std::cout << "-----------------------------------\n";
    }

    // Filter and display publications with institute affiliation
    std::cout << "Publications with affiliation to 'Institute A':\n";
    for (const auto& pub : publications) {
        if (pub.hasInstituteAffiliation("Institute A")) {
            pub.display();
            std::cout << "-----------------------------------\n";
        }
    }

    return 0;
}
