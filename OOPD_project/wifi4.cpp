#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <thread>
#include <iomanip> 

// Forward declaration of formatLatency
std::string formatLatency(double latencyInSeconds);

// Base class
class Entity {
protected:
    int ID;
public:
    Entity(int ID) : ID(ID) {}
    virtual void transmit() = 0;
    int getId() const { return ID; }
    virtual ~Entity() {}
};

// Channel 
class Channel {
private:
    bool busy; 
public:
    Channel() : busy(false) {}
    bool isFree() const { return !busy; }
    void occupy() { busy = true; }
    void release() { busy = false; }
};


// Packet 
class Packet {
private:
    int size; 
    double creationTime;
public:
    Packet(int size, double time) : size(size), creationTime(time) {}
    int getSize() const { return size; }
    double getCreationTime() const { return creationTime; }
};


// User
class User : public Entity {
private:
    int retryLimit; 
    double backoffTime; 
    std::queue<Packet> packetQueue; 
    Channel* channel; 
    double latencyAccumulator; 
    int successfulPackets; 
    double maxLatency; 

    double getRandomBackoff() {
        static std::default_random_engine engine;
        static std::uniform_real_distribution<double> dist(0.0, 0.001); 
        return dist(engine);
    }

public:
    User(int ID, Channel* ch)
        : Entity(ID), retryLimit(5), channel(ch), latencyAccumulator(0), successfulPackets(0), maxLatency(0) {}

    void addPacket(const Packet& packet) {
        packetQueue.push(packet);
    }

    void transmit() override {
        while (!packetQueue.empty()) {
            Packet packet = packetQueue.front();
            int retries = 0;

            while (retries < retryLimit) {
                if (channel->isFree()) {
                    // Transmit packet
                    channel->occupy();
                    double latency = currentTime() - packet.getCreationTime();
                    latencyAccumulator += latency;
                    successfulPackets++;
                    maxLatency = std::max(maxLatency, latency); 
                    channel->release();
                    packetQueue.pop();
                    break;
                } else {
                    
                    retries++;
                    backoffTime = getRandomBackoff();
                    wait(backoffTime);
                }
            }
        }
    }

    int getSuccessfulPackets() const { return successfulPackets; }
    double getTotalLatency() const { return latencyAccumulator; }
    double getMaxLatency() const { return maxLatency; }

    static double currentTime() {
        return std::chrono::duration<double>(
                   std::chrono::steady_clock::now().time_since_epoch())
            .count();
    }

    static void wait(double seconds) {
        std::this_thread::sleep_for(std::chrono::duration<double>(seconds));  
    }
};

// Access Point 
class AccessPoint : public Entity {
public:
    AccessPoint(int ID) : Entity(ID) {}
    void transmit() override {
        
    }
};

// Template for --> average calculation
template <typename T>
double calculateAverage(const std::vector<T>& values) {
    double sum = 0;
    for (const auto& val : values) {
        sum += val;
    }
    return values.empty() ? 0 : sum / values.size();
}

// Simulation 
class Simulation {
private:
    std::vector<User> users;
    AccessPoint ap;
    Channel channel;
    int totalPackets;

public:
    Simulation(int userCount, int apId, int packetsPerUser)
        : ap(apId), channel(), totalPackets(userCount * packetsPerUser) {
        for (int i = 0; i < userCount; i++) {
            users.emplace_back(i, &channel);
        }

        // Add packets to each user
        double startTime = User::currentTime();
        for (auto& user : users) {
            for (int j = 0; j < packetsPerUser; j++) {
                user.addPacket(Packet(1024, startTime));
            }
        }
    }

   void run() {
    std::vector<double> latencies;
    int successfulPackets = 0;
    double maxLatency = 0;

    for (auto& user : users) {
        try {
            user.transmit();
            successfulPackets += user.getSuccessfulPackets();
            latencies.push_back(user.getTotalLatency());
            maxLatency = std::max(maxLatency, user.getMaxLatency());
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
        }
    }

    // Metrics
    double totalLatency = calculateAverage(latencies);
    double throughput = (successfulPackets * 1024 * 8) / User::currentTime();

    
    std::cout << "Simulation Results:\n";
    std::cout << "Throughput: " << throughput << " bps\n";
    std::cout << std::fixed << std::setprecision(8); 

    std::cout << "Average Latency: " << formatLatency(totalLatency / successfulPackets) << '\n';
    std::cout << "Maximum Latency: " << formatLatency(maxLatency) << '\n';
    std::cout << std::defaultfloat;
    std::cout << "Total Packets Successfully Transferred: " << successfulPackets << '\n';
}
};

std::string formatLatency(double latencyInSeconds) {
    if (latencyInSeconds >= 1e-3) {
        return std::to_string(latencyInSeconds * 1e3) + " ms"; 
    } else if (latencyInSeconds >= 1e-6) {
        return std::to_string(latencyInSeconds * 1e6) + " μs"; 
    } else {
        return std::to_string(latencyInSeconds * 1e9) + " ns"; 
    }
}

int main() {
    //1 User
    std::cout << "\n 1 User\n";
    Simulation sim1(1, 0, 100);
    sim1.run();

    //  10 Users
    std::cout << "\n\n10 Users\n";
    Simulation sim2(10, 0, 100);
    sim2.run();

    //  100 Users
    std::cout << "\n\n100 Users\n";
    Simulation sim3(100, 0, 100);
    sim3.run();

    return 0;
}

