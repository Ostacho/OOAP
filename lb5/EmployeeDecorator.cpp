#include "EmployeeDecorator.h"

EmployeeDecorator::EmployeeDecorator(Employee* emp) : Employee(emp->getName()), employee(emp) {}

EmployeeDecorator::~EmployeeDecorator() {
    delete employee;
}

double EmployeeDecorator::calculateSalary() {
    return employee->calculateSalary();
}

void EmployeeDecorator::setQualification(const std::string& level) {
    employee->setQualification(level);
}

std::string EmployeeDecorator::getQualification() const {
    return employee->getQualification();
}

BonusDecorator::BonusDecorator(Employee* emp) : EmployeeDecorator(emp) {}

double BonusDecorator::calculateSalary()  {
    return employee->calculateSalary() + 300;
}

PremiumDecorator::PremiumDecorator(Employee* emp) : EmployeeDecorator(emp) {}

double PremiumDecorator::calculateSalary()  {
    return employee->calculateSalary() * 2;
}
