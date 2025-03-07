#include <iostream>
#include <string>
#include <vector>


class Person {
protected:
    std::string name;
    std::string roomNumber;
    std::string phoneNumber;
    std::string email;

public:
    Person(std::string name, std::string room, std::string phone, std::string email)
        : name(name), roomNumber(room), phoneNumber(phone), email(email) {}

    std::string getName() const { return name; }
    std::string getRoomNumber() const { return roomNumber; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }

    void displayInfo() const {
        std::cout << "Name: " << name << "\nRoom: " << roomNumber
                  << "\nPhone: " << phoneNumber << "\nEmail: " << email << std::endl;
    }
};


class Registrar : public Person {
public:
    Registrar(std::string name, std::string room, std::string phone, std::string email)
        : Person(name, room, phone, email) {}
};


class Dean : public Person {
public:
    Dean(std::string name, std::string room, std::string phone, std::string email)
        : Person(name, room, phone, email) {}
};


class AssociateDean : public Person {
public:
    AssociateDean(std::string name, std::string room, std::string phone, std::string email)
        : Person(name, room, phone, email) {}
};


class Department {
private:
    std::string name;
    Dean* dean;
    AssociateDean* associateDean;
    std::vector<Person*> staff;
    bool headedByRegistrar;

public:
    
    Department(std::string name, Dean* dean, AssociateDean* assocDean, bool headedByRegistrar = false)
        : name(name), dean(dean), associateDean(assocDean), headedByRegistrar(headedByRegistrar) {}

    void addStaff(Person* person) {
        staff.push_back(person);
    }

    std::string getDepartmentName() const { return name; }

    Dean* getDean() const { return dean; }
    AssociateDean* getAssociateDean() const { return associateDean; }

    bool isHeadedByRegistrar() const { return headedByRegistrar; }

    Person* findPersonByName(const std::string& personName) const {
        if (dean && dean->getName() == personName) return dean;
        if (associateDean && associateDean->getName() == personName) return associateDean;
        
        for (auto& person : staff) {
            if (person->getName() == personName) return person;
        }

        return nullptr;  // Person not found
    }

    void displayLeadership() const {
        std::cout << "The " << name << " department is headed by the Registrar.";
        if (dean || associateDean) {
            std::cout << " However, it also has ";
            if (dean) {
                std::cout << "a Dean: " << dean->getName();
                if (associateDean) std::cout << " and ";
            }
            if (associateDean) {
                std::cout << "an Associate Dean: " << associateDean->getName();
            }
        }
        std::cout << "." << std::endl;
    }
};


class AdministrativeStructure {
private:
    Registrar* registrar;
    std::vector<Department*> departments;

public:
    AdministrativeStructure(Registrar* reg) : registrar(reg) {}

    void addDepartment(Department* dept) {
        departments.push_back(dept);
    }

    Person* findPerson(const std::string& name) {
        if (registrar->getName() == name) return registrar;

        for (auto& dept : departments) {
            
            if (dept->isHeadedByRegistrar()) {
                
                if (registrar->getName() == name) return registrar;
            }

            Person* person = dept->findPersonByName(name);
            if (person) return person;
        }

        return nullptr;  // Person not found
    }

    void getPersonDetails(const std::string& name) {
        Person* person = findPerson(name);
        if (person) {
            person->displayInfo();
            for (auto& dept : departments) {
                if (dept->findPersonByName(name)) {
                    dept->displayLeadership();
                }
            }
        } else {
            std::cout << "Person not found." << std::endl;
        }
    }
};


int main() {
    // Create Registrar
    Registrar* registrar = new Registrar("Dr. Deepika Bhaskar", "B-204 (Academic Block)", "+91-11-26907419", "deepika@iiitd.ac.in, registrar@iiitd.ac.in");

    
    Dean* dean_ird = new Dean("Vivek Ashok Bohara", "na", "+91-11-26907454", "dird@iiitd.ac.in");
    AssociateDean* assoc_dean_ird = new AssociateDean("Debarka Sengupta", "na", "+91-11-26907446", "adird@iiitd.ac.in");

    Dean* dean_academics = new Dean("Sumit J Darak", "na", "+91-11-26907427", "doaa@iiitd.ac.in");
    
    Dean* dean_student_affairs = new Dean("Shobha Sundar Ram", "na", "+91-11-26907460", "dosa@iiitd.ac.in");
    
    
    Department* irdDept = new Department("IRD", dean_ird, assoc_dean_ird);
    Department* academicsDept = new Department("Academics", dean_academics, nullptr);
    Department* studentAffairsDept = new Department("Student Affairs", dean_student_affairs, nullptr);
    Department* storeDept = new Department("Store & Purchase", nullptr, nullptr, true);  // Headed by Registrar
    Department* libraryDept = new Department("Library", nullptr, nullptr, true);         // Headed by Registrar

    
    irdDept->addStaff(new Person("Abhijeet Mishra", "003 (R & D Block)", " 011 26907 555", "abhijeet@iiitd.ac.in"));
    academicsDept->addStaff(new Person("Aakash Gupta", "B-207 (Academic Block)", "011 26907 135", "aakash@iiitd.ac.in"));
    studentAffairsDept->addStaff(new Person("Dr. Ravi Bhasin", "A-207-1 (Academic Block)", "011 26907 504", "ravi@iiitd.ac.in"));
    storeDept->addStaff(new Person("Ajay Kumar", "A-103(2) (Academic Block)", "011 26907 561", "ajay@iiitd.ac.in"));
    libraryDept->addStaff(new Person("Parikshita Behera", "na", "011 26907 503", "parikshita@iiitd.ac.in"));

    AdministrativeStructure adminStructure(registrar);
    adminStructure.addDepartment(irdDept);
    adminStructure.addDepartment(academicsDept);
    adminStructure.addDepartment(studentAffairsDept);
    adminStructure.addDepartment(storeDept);
    adminStructure.addDepartment(libraryDept);

    
    std::string inputName;
    while (true) {
        std::cout << "\nEnter name to fetch details (or type 'exit' to quit): ";
        std::getline(std::cin, inputName);

        if (inputName == "exit") {
            break;
        }

        adminStructure.getPersonDetails(inputName);
    }

    return 0;
}
