using System;
using System.Collections.Generic;
using System.Linq;

namespace WeaponInventory
{
    public interface IWeapon
    {
        string Name { get; }
        double GetWeight();
        double GetPrice();
        int Year { get; }
    }

    public class Rifle : IWeapon
    {
        public string Name => "Rifle";
        public int Year { get; }
        public Rifle(int year) => Year = year;
        public double GetWeight() => 4.5;
        public double GetPrice() => 1500;
    }

    public class Pistol : IWeapon
    {
        public string Name => "Pistol";
        public int Year { get; }
        public Pistol(int year) => Year = year;
        public double GetWeight() => 1.2;
        public double GetPrice() => 700;
    }

    public abstract class WeaponDecorator : IWeapon
    {
        protected IWeapon _weapon;
        public abstract string Name { get; }
        public abstract int Year { get; }

        protected WeaponDecorator(IWeapon weapon) => _weapon = weapon;
        public abstract double GetWeight();
        public abstract double GetPrice();
    }

    public class Scope : WeaponDecorator
    {
        public Scope(IWeapon weapon) : base(weapon) { }
        public override string Name => _weapon.Name + " + Scope";
        public override int Year => _weapon.Year;
        public override double GetWeight() => _weapon.GetWeight() + 0.5;
        public override double GetPrice() => _weapon.GetPrice() + 300;
    }

    public class Suppressor : WeaponDecorator
    {
        public Suppressor(IWeapon weapon) : base(weapon) { }
        public override string Name => _weapon.Name + " + Suppressor";
        public override int Year => _weapon.Year;
        public override double GetWeight() => _weapon.GetWeight() + 0.3;
        public override double GetPrice() => _weapon.GetPrice() + 200;
    }

    public class NightVision : WeaponDecorator
    {
        public NightVision(IWeapon weapon) : base(weapon) { }
        public override string Name => _weapon.Name + " + Night Vision";
        public override int Year => _weapon.Year;
        public override double GetWeight() => _weapon.GetWeight() + 0.7;
        public override double GetPrice() => _weapon.GetPrice() + 500;
    }

    public class WeaponManager
    {
        private const double MAX_WEIGHT = 7.0;

        public bool IsValid(IWeapon weapon)
        {
            return weapon.GetWeight() <= MAX_WEIGHT;
        }

        public double GetDepreciatedPrice(IWeapon weapon)
        {
            int age = DateTime.Now.Year - weapon.Year;
            double depreciation = Math.Min(age * 0.05, 0.5);
            return weapon.GetPrice() * (1 - depreciation);
        }

        public IWeapon GetMostExpensive(List<IWeapon> weapons)
        {
            return weapons.OrderByDescending(w => GetDepreciatedPrice(w)).FirstOrDefault();
        }
    }

    class Program
    {
        static void Main()
        {
            var inventory = new List<IWeapon>();
            var manager = new WeaponManager();

            while (true)
            {
                Console.WriteLine("\n--- Menu ---");
                Console.WriteLine("1. Add weapon");
                Console.WriteLine("2. Show inventory");
                Console.WriteLine("3. Most expensive (with depreciation)");
                Console.WriteLine("4. Exit");
                Console.Write("Choice: ");
                var input = Console.ReadLine();

                switch (input)
                {
                    case "1":
                        inventory.Add(CreateWeapon());
                        break;
                    case "2":
                        ShowInventory(inventory, manager);
                        break;
                    case "3":
                        var best = manager.GetMostExpensive(inventory);
                        if (best != null)
                        {
                            Console.WriteLine($"Most expensive: {best.Name} — {manager.GetDepreciatedPrice(best):0.00} units");
                        }
                        break;
                    case "4":
                        return;
                    default:
                        Console.WriteLine("Invalid choice.");
                        break;
                }
            }
        }

        static IWeapon CreateWeapon()
        {
            Console.WriteLine("\nSelect weapon type:");
            Console.WriteLine("1. Rifle");
            Console.WriteLine("2. Pistol");
            Console.Write("Choice: ");
            int type = int.Parse(Console.ReadLine() ?? "1");

            Console.Write("Enter year of manufacture: ");
            int year = int.Parse(Console.ReadLine() ?? "2020");

            IWeapon weapon = type == 1 ? new Rifle(year) : new Pistol(year);

            while (true)
            {
                Console.WriteLine("\nAdd accessory?");
                Console.WriteLine("1. Scope");
                Console.WriteLine("2. Suppressor");
                Console.WriteLine("3. Night Vision");
                Console.WriteLine("4. Done");
                Console.Write("Choice: ");
                string acc = Console.ReadLine();

                if (acc == "1")
                    weapon = new Scope(weapon);
                else if (acc == "2")
                    weapon = new Suppressor(weapon);
                else if (acc == "3")
                    weapon = new NightVision(weapon);
                else if (acc == "4")
                    break;
                else
                    Console.WriteLine("Invalid choice.");
            }

            return weapon;
        }

        static void ShowInventory(List<IWeapon> inventory, WeaponManager manager)
        {
            if (inventory.Count == 0)
            {
                Console.WriteLine("Inventory is empty.");
                return;
            }

            Console.WriteLine("\n--- Inventory ---");
            for (int i = 0; i < inventory.Count; i++)
            {
                var w = inventory[i];
                Console.WriteLine($"{i + 1}. {w.Name} | Weight: {w.GetWeight():0.00} | Price: {w.GetPrice():0.00} | Depreciated: {manager.GetDepreciatedPrice(w):0.00} | Valid: {(manager.IsValid(w) ? "✔" : "✘")}");
            }
        }
    }
}
