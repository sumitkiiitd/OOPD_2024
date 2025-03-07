#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

// Utility to handle date and time
using TimePoint = system_clock::time_point;

class Train {
private:
    string train_id;
    TimePoint arrival_time;
    bool is_through;

public:
    Train(string id, TimePoint time, bool through = false)
        : train_id(id), arrival_time(time), is_through(through) {}

    string getTrainID() const { return train_id; }
    TimePoint getArrivalTime() const { return arrival_time; }
    bool isThroughTrain() const { return is_through; }
};

class Platform {
private:
    int platform_number;
    vector<pair<Train, TimePoint>> schedule;

public:
    Platform(int number) : platform_number(number) {}

    bool canAccommodateTrain(const Train& train) const {
        for (const auto& scheduled : schedule) {
            TimePoint scheduled_time = scheduled.second;

            long long diff_minutes = duration_cast<minutes>(train.getArrivalTime() - scheduled_time).count();
            if (train.isThroughTrain()) {
                if (abs(diff_minutes) < 10) {
                    return false;
                }
            } else {
                if (abs(diff_minutes) < 30) {
                    return false;
                }
            }
        }
        return true;
    }

    bool addTrain(const Train& train) {
        if (canAccommodateTrain(train)) {
            schedule.push_back({train, train.getArrivalTime()});
            return true;
        }
        return false;
    }

    int getPlatformNumber() const { return platform_number; }
};

class Line {
private:
    string line_id;
    vector<string> stations;

public:
    Line(string id, vector<string> station_list)
        : line_id(id), stations(std::move(station_list)) {}

    string getLineID() const { return line_id; }
    vector<string> getStations() const { return stations; }
};

class Station {
private:
    variant<int, string> station_id; // Supports both int and string types for ID
    vector<Platform> platforms;
    vector<Line> lines;

public:
    Station(variant<int, string> id, vector<Platform> platform_list, vector<Line> line_list)
        : station_id(id), platforms(std::move(platform_list)), lines(std::move(line_list)) {}

    variant<int, string> getStationID() const { return station_id; }

    bool addTrainToPlatform(const Train& train, int platform_number) {
        for (auto& platform : platforms) {
            if (platform.getPlatformNumber() == platform_number) {
                if (platform.addTrain(train)) {
                    return true;
                } else {
                    cout << "Train " << train.getTrainID() << " cannot be scheduled at this time.\n";
                    return false;
                }
            }
        }
        cout << "Platform " << platform_number << " not found.\n";
        return false;
    }

    vector<string> listLines() const {
        vector<string> line_ids;
        for (const auto& line : lines) {
            line_ids.push_back(line.getLineID());
        }
        return line_ids;
    }
};

// Example usage of the library
int main() {
    variant<int, string> station_id = "NDLS"; // or int station_id = 1234;
    
    vector<Platform> platforms = { Platform(1), Platform(2) };
    vector<Line> lines = { Line("Blue Line", {"NDLS", "SDAH"}), Line("Red Line", {"NDLS", "CNB"}) };
    
    // Create a station
    Station station(station_id, platforms, lines);

    // Schedule a train
    TimePoint arrival_time = system_clock::now() + minutes(15);
    Train train1("Train123", arrival_time, false);
    station.addTrainToPlatform(train1, 1);

    // Schedule another train with a potential conflict
    TimePoint arrival_time_conflict = system_clock::now() + minutes(20);
    Train train2("Train456", arrival_time_conflict, false);
    station.addTrainToPlatform(train2, 1);

    return 0;
}
