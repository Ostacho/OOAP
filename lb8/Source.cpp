#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <memory>

class GeoNode {
    std::string name;
    std::vector<std::shared_ptr<GeoNode>> children;
public:
    GeoNode(const std::string& name) : name(name) {}

    void addChild(std::shared_ptr<GeoNode> child) {
        children.push_back(child);
    }

    const std::string& getName() const {
        return name;
    }

    const std::vector<std::shared_ptr<GeoNode>>& getChildren() const {
        return children;
    }
};

struct NodeWithDepth {
    std::shared_ptr<GeoNode> node;
    int depth;
};

class GeoIterator {
    std::stack<NodeWithDepth> nodeStack;
public:
    GeoIterator(std::shared_ptr<GeoNode> root) {
        if (root) nodeStack.push({ root, 0 });
    }

    bool hasNext() const {
        return !nodeStack.empty();
    }

    NodeWithDepth next() {
        auto current = nodeStack.top();
        nodeStack.pop();

        const auto& children = current.node->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack.push({ *it, current.depth + 1 });
        }

        return current;
    }
};

void printWithIndentation(const std::string& name, int depth) {
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }
    std::cout << (depth > 0 ? "- " : "") << name << "\n";
}

int main() {
    auto country = std::make_shared<GeoNode>("Ukraine");

    auto region1 = std::make_shared<GeoNode>("West");
    auto region2 = std::make_shared<GeoNode>("East");

    auto district1 = std::make_shared<GeoNode>("Lviv");
    auto district2 = std::make_shared<GeoNode>("Zakarpatia");
    auto district3 = std::make_shared<GeoNode>("Zaporizhzhia");

    auto town1 = std::make_shared<GeoNode>("Gai");
    auto town2 = std::make_shared<GeoNode>("Uzhorod");
    auto town3 = std::make_shared<GeoNode>("Kryglik");

    auto street1 = std::make_shared<GeoNode>("Zagirria");
    auto street2 = std::make_shared<GeoNode>("Akademik Shpenik");
    auto street3 = std::make_shared<GeoNode>("Zagirska");
    auto street4 = std::make_shared<GeoNode>("Dachna");

    country->addChild(region1);
    country->addChild(region2);

    region1->addChild(district1);
    region1->addChild(district2);
    region2->addChild(district3);

    district1->addChild(town1);
    district2->addChild(town2);
    district3->addChild(town3);

    town1->addChild(street1);
    town2->addChild(street2);
    town2->addChild(street3);
    town3->addChild(street4);

    GeoIterator it(country);
    while (it.hasNext()) {
        NodeWithDepth current = it.next();
        printWithIndentation(current.node->getName(), current.depth);
    }

    return 0;
}
