#pragma once
#include "Employee.h"

class Contractor : public Employee {
public:
    Contractor(const std::string& name);
    double calculateSalary() override;
};
