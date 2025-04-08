#pragma once
#include "Employee.h"

class EmployeeDecorator : public Employee {
protected:
    Employee* employee;
public:
    EmployeeDecorator(Employee* emp);
    virtual ~EmployeeDecorator();

    double calculateSalary() override;
    void setQualification(const std::string& level) override;
    std::string getQualification() const override;
};

class BonusDecorator : public EmployeeDecorator {
public:
    BonusDecorator(Employee* emp);
    double calculateSalary() override;
};

class PremiumDecorator : public EmployeeDecorator {
public:
    PremiumDecorator(Employee* emp);
    double calculateSalary() override;
};
