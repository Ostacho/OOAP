#include "PayrollSystem.h"
#include "StaffEmployee.h"
#include "Contractor.h"

void setUp(PayrollSystem& system)
{
    system.addEmployee(new Contractor("Alex"));
    system.addEmployee(new StaffEmployee("Mira"));
    system.addEmployee(new Contractor("Oleh"));
    system.addEmployee(new StaffEmployee("Nina"));
    system.addEmployee(new StaffEmployee("Tomas"));

    system.setQualification("Alex", "Senior");
    system.setQualification("Mira", "Junior");
    system.setQualification("Oleh", "Middle");
    system.setQualification("Nina", "Senior");
    system.setQualification("Tomas", "Middle");
}

int main() {
    PayrollSystem system;

    setUp(system);

    system.printSalaries();

    system.addQualificationLevel("Strong Middle", 2500);
    system.setQualification("Oleh", "Strong Middle");

    system.logHours("Alex", 42);
    system.logHours("Mira", 30);
    system.logHours("Oleh", 25);  
    system.logHours("Nina", 29); 
    system.logHours("Tomas", 15);

    system.printSalaries();

    system.applyBonus("Oleh");

    system.rewardTop10();
    system.printSalaries();
}
