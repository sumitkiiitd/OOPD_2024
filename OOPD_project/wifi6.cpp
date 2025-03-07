#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <thread>
#include <algorithm>

//all entities
class Entity {
protected:
    int id;
public:
    Entity(int id) : id(id) {}
    virtual void transmit() = 0;
    int getId() const { return id; }
    virtual ~Entity() {}
};

// Packet 
class Packet {
private:
    int size; // Size in bytes
    double creationTime; // Creation timestamp
public:
    Packet(int size, double time) : size(size), creationTime(time) {}
    int getSize() const { return size; }
    double getCreationTime() const { return creationTime; }
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

// Frequency Sub-channel class for OFDMA
class SubChannel {
public:
    int bandwidth; 
    bool busy;

    SubChannel(int bandwidth) : bandwidth(bandwidth), busy(false) {}
    bool isFree() const { return !busy; }
    void occupy() { busy = true; }
    void release() { busy = false; }
};

// OFDMA Class
class OFDMA {
private:
    std::vector<SubChannel> subChannels; 
    size_t currentUserIndex; 

public:
    OFDMA() : currentUserIndex(0) {
        subChannels.push_back(SubChannel(2)); 
        subChannels.push_back(SubChannel(4)); 
        subChannels.push_back(SubChannel(10)); 
    }

    SubChannel* getNextAvailableSubChannel() {
        size_t start = currentUserIndex;
        do {
            if (subChannels[currentUserIndex].isFree()) {
                return &subChannels[currentUserIndex];
            }
            currentUserIndex = (currentUserIndex + 1) % subChannels.size();
        } while (currentUserIndex != start); 

        return nullptr; 
    }
};

// User class
class User : public Entity {
private:
    int retryLimit; 
    double backoffTime; 
    std::queue<Packet> packetQueue; 
    Channel* channel; 
    OFDMA* ofdma; 
    double latencyAccumulator;
    int successfulPackets; 
    double maxLatency; 

    double getRandomBackoff() {
        static std::default_random_engine engine;
        static std::uniform_real_distribution<double> dist(0.0, 0.001);
        return dist(engine);
    }

public:
    User(int id, Channel* ch, OFDMA* ofdma)
        : Entity(id), retryLimit(5), channel(ch), ofdma(ofdma), latencyAccumulator(0), successfulPackets(0), maxLatency(0) {}

    void addPacket(const Packet& packet) {
        packetQueue.push(packet);
    }

    void transmit() override {
        while (!packetQueue.empty()) {
            Packet packet = packetQueue.front();
            int retries = 0;

            while (retries < retryLimit) {
                SubChannel* subChannel = ofdma->getNextAvailableSubChannel();
                if (subChannel != nullptr && channel->isFree()) {
                    
                    channel->occupy();
                    subChannel->occupy();
                    double latency = currentTime() - packet.getCreationTime();
                    latencyAccumulator += latency;
                    successfulPackets++;
                    maxLatency = std::max(maxLatency, latency); 
                    channel->release();
                    subChannel->release();
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

// AccessPoint class
class AccessPoint : public Entity {
public:
    AccessPoint(int id) : Entity(id) {}
    void transmit() override {
        
     }
};

// Template 
template <typename T>
double calculateAverage(const std::vector<T>& values) {
    double sum = 0;
    for (const auto& val : values) {
        sum += val;
    }
    return values.empty() ? 0 : sum / values.size();
}

// Simulation class
class Simulation {
private:
    std::vector<User> users;
    AccessPoint ap;
    Channel channel;
    OFDMA ofdma;
    int totalPackets;

public:
    Simulation(int userCount, int apId, int packetsPerUser)
        : ap(apId), channel(), ofdma(), totalPackets(userCount * packetsPerUser) {
        for (int i = 0; i < userCount; i++) {
            users.emplace_back(i, &channel, &ofdma);
        }

        
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

        // Output results
        std::cout << "Result of Simulation:\n";
        std::cout << "Throughput: " << throughput << " bps\n";
        std::cout << "Average Latency: " << totalLatency / successfulPackets << " s\n";
        std::cout << "Maximum Latency: " << maxLatency << " s\n";
        std::cout << "Packets Successfully Transferred: " << successfulPackets << '\n';
    }
};

int main() {
    //1 User
    std::cout << "For 1 User\n";
    Simulation sim1(1, 0, 100);
    sim1.run();

    // 10 Users
    std::cout << "\nFor 10 Users\n";
    Simulation sim2(10, 0, 100);
    sim2.run();

    //100 Users
    std::cout << "\nFor 100 Users\n";
    Simulation sim3(100, 0, 100);
    sim3.run();

    return 0;
}

