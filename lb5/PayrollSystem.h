#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "Employee.h"
#include "EmployeeDecorator.h"

class PayrollSystem {
    std::vector<Employee*> employees;
    std::unordered_map<std::string, double> qualificationRates;
public:
    void addEmployee(Employee* emp);
    void addQualificationLevel(const std::string& name, double baseRate);
    void setQualification(const std::string& name, const std::string& level);
    void logHours(const std::string& name, int hours);
    void rewardTop10();
    void applyBonus(const std::string& name);
    void printSalaries() const;
    ~PayrollSystem();
};