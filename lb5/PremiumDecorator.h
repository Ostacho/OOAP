#pragma once
#include "EmployeeDecorator.h"

class PremiumDecorator : public EmployeeDecorator {
public:
    using EmployeeDecorator::EmployeeDecorator;
    double calculateSalary() const override {
        return employee->calculateSalary() + employee->calculateSalary();
    }
};