#include "PayrollSystem.h"
#include "Contractor.h"
#include "StaffEmployee.h"

void PayrollSystem::addEmployee(Employee* emp) {
    employees.push_back(emp);
}

void PayrollSystem::logHours(const std::string& name, int hours) {
    for (auto emp : employees) {
        if (emp->getName() == name) {
            emp->addHours(hours);
            break;
        }
    }
}

void PayrollSystem::printSalaries() const {
    for (auto emp : employees) {
        std::cout << emp->getName() << " (" << emp->getQualification() << "): "
            << emp->calculateSalary() << "$" << std::endl;
    }
    std::cout << '\n';
}

void PayrollSystem::addQualificationLevel(const std::string& name, double baseRate) {
    qualificationRates[name] = baseRate;
}

void PayrollSystem::setQualification(const std::string& name, const std::string& level) {
    for (auto emp : employees) {
        if (emp->getName() == name) {
            emp->setQualification(level);
            if (qualificationRates.count(level)) {
                emp->setBaseRate(qualificationRates[level]);
            }
            else {
                emp->setBaseRate(300);
            }
        }
    }
}

void PayrollSystem::rewardTop10() {
    std::vector<Employee*> eligible;

    for (auto& emp : employees) {
        BonusDecorator* bonusCheck = dynamic_cast<BonusDecorator*>(emp);
        if (bonusCheck) continue;

        Contractor* contractor = dynamic_cast<Contractor*>(emp);
        StaffEmployee* staff = dynamic_cast<StaffEmployee*>(emp);

        if ((contractor && contractor->getHours() >= 40) ||
            (staff && staff->getHours() >= 28)) {
            eligible.push_back(emp);
        }
    }

    std::sort(eligible.begin(), eligible.end(), [](Employee* a, Employee* b) {
        return a->getHours() > b->getHours();
        });

    for (size_t i = 0; i < std::min<size_t>(10, eligible.size()); ++i) {
        Employee* original = eligible[i];

        for (auto& emp : employees) {
            if (emp == original) {
                emp = new PremiumDecorator(emp);
                break;
            }
        }
    }
}

void PayrollSystem::applyBonus(const std::string& name) {
    for (auto& emp : employees) {
        if (emp->getName() == name) {
            emp = new BonusDecorator(emp);
            break;
        }
    }
}


PayrollSystem::~PayrollSystem() {
    for (auto emp : employees)
        delete emp;
}
