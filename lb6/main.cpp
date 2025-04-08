#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <memory>

class IEmployeeDataSource {
public:
    virtual std::string ReadEmployee(int id) = 0;
    virtual void WriteEmployee(int id, const std::string& name) = 0;
    virtual ~IEmployeeDataSource() = default;
};

class EmployeeDataSource : public IEmployeeDataSource {
private:
    static std::map<int, std::string> _database;

public:
    std::string ReadEmployee(int id) override {
        std::cout << "[DataSource] Reading employee data...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (_database.find(id) != _database.end()) {
            return _database[id];
        }
        else {
            return "[Not Found]";
        }
    }

    void WriteEmployee(int id, const std::string& name) override {
        std::cout << "[DataSource] Writing employee data...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        _database[id] = name;
    }
};

std::map<int, std::string> EmployeeDataSource::_database;

class EmployeeDataSourceProxy : public IEmployeeDataSource {
private:
    std::unique_ptr<EmployeeDataSource> realDataSource;

public:
    EmployeeDataSourceProxy() {
        realDataSource = std::make_unique<EmployeeDataSource>();
    }

    std::string ReadEmployee(int id) override {
        std::cout << "[Proxy] Requesting read for employee ID: " << id << "\n";
        return realDataSource->ReadEmployee(id);
    }

    void WriteEmployee(int id, const std::string& name) override {
        std::cout << "[Proxy] Requesting write for employee ID: " << id << "\n";
        realDataSource->WriteEmployee(id, name);
    }
};

class DataSourceFactory {
public:
    static std::unique_ptr<IEmployeeDataSource> CreateEmployeeDataSource() {
        return std::make_unique<EmployeeDataSourceProxy>();
    }
};

int main() {
    auto dataSource = DataSourceFactory::CreateEmployeeDataSource();

    dataSource->WriteEmployee(1, "Stepan Solid");
    std::cout << "Employee 1: " << dataSource->ReadEmployee(1) << "\n";

    dataSource->WriteEmployee(2, "Jennifer Stifler");
    std::cout << "Employee 2: " << dataSource->ReadEmployee(2) << "\n";

    std::cout << "Try reading non-existent ID 3:\n";
    std::cout << "Employee 3: " << dataSource->ReadEmployee(3) << "\n";

    return 0;
}
