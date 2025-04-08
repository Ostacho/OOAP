#pragma once
#include "EmployeeDecorator.h"

class BonusDecorator : public EmployeeDecorator {
public:
    using EmployeeDecorator::EmployeeDecorator;
    double calculateSalary() const override {
        return employee->calculateSalary() + 500;
    }
};