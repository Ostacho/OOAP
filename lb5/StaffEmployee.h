#pragma once
#include "Employee.h"

class StaffEmployee : public Employee {
public:
    StaffEmployee(const std::string& name);
    double calculateSalary() override;
};
