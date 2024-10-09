#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::make_unique;

class StormTrooper {
public:
    virtual ~StormTrooper() {}

    virtual int FirePower() const = 0;
    virtual int Armor() const = 0;

    virtual StormTrooper* Clone() const = 0;

    virtual void DisplayInfo() const = 0;
};

class Commander : public StormTrooper {
public:
    Commander() {}
    Commander(const Commander&) = default;

    int FirePower() const override {
        return 100;
    }

    int Armor() const override {
        return 50;
    }

    Commander* Clone() const override {
        return new Commander(*this);
    }

    void DisplayInfo() const override {
        cout << "Commander: FirePower = " << FirePower() << ", Armor = " << Armor() << endl;
    }
};

class Infantry : public StormTrooper {
public:
    Infantry() {}
    Infantry(const Infantry&) = default;

    int FirePower() const override {
        return 50;
    }

    int Armor() const override {
        return 25;
    }

    Infantry* Clone() const override {
        return new Infantry(*this);
    }

    void DisplayInfo() const override {
        cout << "Infantry: FirePower = " << FirePower() << ", Armor = " << Armor() << endl;
    }
};

int main() {
    unique_ptr<StormTrooper> commander = make_unique<Commander>();
    unique_ptr<StormTrooper> infantry = make_unique<Infantry>();

    commander->DisplayInfo();
    infantry->DisplayInfo();

    unique_ptr<StormTrooper> clonedCommander(commander->Clone());
    unique_ptr<StormTrooper> clonedInfantry(infantry->Clone());

    clonedCommander->DisplayInfo();
    clonedInfantry->DisplayInfo();

    return 0;
}
