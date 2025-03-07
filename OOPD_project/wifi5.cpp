#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

// Packet
class Packet {
protected:
    int size;  
    std::string type;  

public:
    Packet(int size, std::string type) : size(size), type(type) {}
    virtual ~Packet() = default;

    int getSize() const { return size; }
    std::string getType() const { return type; }
};

// CSI packet
class CsiPacket : public Packet {
public:
    CsiPacket(int size = 200) : Packet(size, "CSI") {}  
};

// FrequencyChannel 
class FrequencyChannel {
private:
    int bandwidth;  
    bool isBusy;    

public:
    FrequencyChannel(int bandwidth) : bandwidth(bandwidth), isBusy(false) {}

    bool isChannelAvailable() const { return !isBusy; }
    void setChannelStatus(bool status) { isBusy = status; }
    int getBandwidth() const { return bandwidth; }
};

//  Data packet
class DataPacket : public Packet {
public:
    DataPacket(int size = 200) : Packet(size, "Data") {}

};



// User class
class User {
private:
    std::string id; 
    int csiPacketSize;  
    int dataPacketSize; 

public:
    User(std::string id, int csiPacketSize = 200, int dataPacketSize = 200)
        : id(id), csiPacketSize(csiPacketSize), dataPacketSize(dataPacketSize) {}

    virtual ~User() = default;

    std::string getId() const { return id; }
    int getCsiPacketSize() const { return csiPacketSize; }
    int getDataPacketSize() const { return dataPacketSize; }

    virtual Packet* sendCsiPacket() const {
        return new CsiPacket(csiPacketSize);
    }

    virtual Packet* sendDataPacket() const {
        return new DataPacket(dataPacketSize);
    }
};




// Round Robin Scheduler 
class RoundRobinScheduler {
private:
    size_t currentIndex;

public:
    RoundRobinScheduler() : currentIndex(0) {}

    User* getNextUser(const std::vector<User*>& users) {
        if (users.empty()) return nullptr;  // Empty user list handling
        currentIndex = (currentIndex + 1) % users.size();
        return users[currentIndex];
    }
};


// MU_MIMO class
class MU_MIMO {
public:
    void enableParallelTransmission(const std::vector<User*>& users) {
        for (const auto& user : users) {
            // Each user can send data in parallel after CSI exchange
            Packet* data = user->sendDataPacket();
            //data->printDetails();
            delete data;
        }
    }
};

// AccessPoint 
class AccessPoint {
private:
    FrequencyChannel channel;
    std::vector<User*> users;
    MU_MIMO muMimo;

public:
    AccessPoint(int bandwidth) : channel(bandwidth) {}

    void addUser(User* user) {
        users.push_back(user);
    }

    // Simulate broadcasting and receiving CSI
    void broadcastAndReceiveCsi() {
        if (channel.isChannelAvailable()) {
            channel.setChannelStatus(true);  
        }
    }
};

// Simulation class
class Simulation {
private:
    AccessPoint ap;
    RoundRobinScheduler scheduler;
    MU_MIMO muMimo;
    int totalSuccessfulPackets;
    double totalDataTransferred;  
    double totalLatency; 
    double maxLatency;

public:
    Simulation(int bandwidth) : ap(bandwidth), totalSuccessfulPackets(0), totalDataTransferred(0), totalLatency(0), maxLatency(0) {}

    void runSimulation(int userCount) {
        std::vector<User*> users;
        for (int i = 1; i <= userCount; ++i) {
            users.push_back(new User("User" + std::to_string(i)));
            ap.addUser(users.back());
        }

        
        ap.broadcastAndReceiveCsi();
        muMimo.enableParallelTransmission(users);
        totalSuccessfulPackets = users.size();  

        
        calculateStatistics(users);

        
        for (auto user : users) {
            delete user;
        }
    }

    void calculateStatistics(const std::vector<User*>& users) {
        double totalTime = 15.0;  
        double totalData = 0;
        double totalLatencyForUsers = 0;

        for (const auto& user : users) {
            totalData += user->getDataPacketSize();
            double latency = rand() % 10 + 1;  
            totalLatencyForUsers += latency;
            maxLatency = std::max(maxLatency, latency);
        }

        totalDataTransferred = totalData;
        totalLatency = totalLatencyForUsers / users.size();
        double throughput = (totalData * 8) / (totalTime / 1000); 

       
       
        std::cout << std::fixed << std::setprecision(0); 
        std::cout << "Throughput: " << throughput << " bps\n";  
        
        std::cout << "Average Latency: " << totalLatency << " ms\n";
        std::cout << "Maximum Latency: " << maxLatency << " ms\n";
        std::cout << std::defaultfloat;
        std::cout << "Total Packets Transmitted Successfully: " << totalSuccessfulPackets << "\n";
    }
};




int main() {
    srand(time(0));  

    Simulation sim1(20);  // Bandwidth 

    //  1 user
    std::cout << "Simulation for 1 User:\n";
    sim1.runSimulation(1);

    // Scenario 2: 10 users
    Simulation sim2(20);
    std::cout << "\nSimulation for 10 Users:\n";
    sim2.runSimulation(10);

    // Scenario 3: 100 users
    Simulation sim3(20);
    std::cout << "\nSimulation for 100 Users:\n";
    sim3.runSimulation(100);

    return 0;
}

