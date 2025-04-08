#pragma once
#include <string>

class Employee {
protected:
    std::string name;
    std::string qualification;
    int hoursWorked;
    double baseRate = 0.0;

public:
    Employee(const std::string& name);
    virtual ~Employee() {}

    virtual int getHours() const;  
    virtual double calculateSalary() = 0;
    virtual void setQualification(const std::string& level);
    virtual std::string getQualification() const;
    std::string getName() const;
    int getHoursWorked() const;
    void addHours(int h);
    virtual void setBaseRate(double rate);
};
