#include "Contractor.h"

Contractor::Contractor(const std::string& name) : Employee(name) {}

double Contractor::calculateSalary() {
    if (qualification == "Junior") this->setBaseRate(750);
    else if (qualification == "Middle") this->setBaseRate(1500);
    else if (qualification == "Senior") this->setBaseRate(2500);
    return baseRate * hoursWorked / 40;
}
