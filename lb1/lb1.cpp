#include <iostream>
#include <string>
#include <string_view>

class Fruit
{
public:
	Fruit(std::string_view name, std::string_view color)
		: m_name{ name }, m_color{ color }
	{
	}

	const std::string& getName() const { return m_name; }
	const std::string& getColor() const { return m_color; }

private:
	std::string m_name{};
	std::string m_color{};
};

class Apple : public Fruit
{
public:

	Apple(std::string_view color = "red", std::string_view name = "apple", double fiber = 0.5)
		:Fruit{ name, color }, m_fiber{ fiber }
	{
	}

	double getFiber() const { return m_fiber; }



private:
	double m_fiber{};
};

std::ostream& operator<<(std::ostream& out, const Apple& a)
{
	out << "Apple(" << a.getName() << ", " << a.getColor() << ", " << a.getFiber() << ')';
	return out;
}

class Banana : public Fruit
{
public:

	Banana(std::string_view name = "banana", std::string_view color = "yellow")
		:Fruit{ name, color }
	{
	}

};

std::ostream& operator<<(std::ostream& out, const Banana& a)
{
	out << "Banana(" << a.getName() << ", " << a.getColor() << ')';
	return out;
}



int main()
{
	Apple a{ "red" };
	Banana b{};

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";

	return 0;
}