#include "Employee.h"

Employee::Employee(const std::string& name) : name(name), qualification("Trainee"), hoursWorked(0) {}

int Employee::getHours() const {
    return hoursWorked;
}

void Employee::setQualification(const std::string& level) {
    qualification = level;
}

std::string Employee::getQualification() const {
    return qualification;
}

std::string Employee::getName() const {
    return name;
}

int Employee::getHoursWorked() const {
    return hoursWorked;
}

void Employee::addHours(int h) {
    hoursWorked += h;
}

void Employee::setBaseRate(double rate) {
    baseRate = rate;
}
