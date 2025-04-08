#include "StaffEmployee.h"

StaffEmployee::StaffEmployee(const std::string& name) : Employee(name) {}

double StaffEmployee::calculateSalary() {
    if (qualification == "Junior") this->setBaseRate(500);
    else if (qualification == "Middle") this->setBaseRate(800);
    else if (qualification == "Senior") this->setBaseRate(1200);
    return baseRate;
}
