using System;
using System.Collections.Generic;
using System.Linq;


interface ITraversalStrategy
{
    string Name { get; }
    bool CanPassWith(List<IArtifact> artifacts);
}

interface IArtifact
{
    string Name { get; }
    bool Supports(ITraversalStrategy trial);
}

class ForestTrial : ITraversalStrategy
{
    public string Name => "Forest";
    public bool CanPassWith(List<IArtifact> artifacts) =>
        artifacts.Any(a => a.Supports(this));
}

class RiverTrial : ITraversalStrategy
{
    public string Name => "River";
    public bool CanPassWith(List<IArtifact> artifacts) =>
        artifacts.Any(a => a.Supports(this));
}

class MountainTrial : ITraversalStrategy
{
    public string Name => "Mountain";
    public bool CanPassWith(List<IArtifact> artifacts) =>
        artifacts.Any(a => a.Supports(this));
}

class SwampTrial : ITraversalStrategy
{
    public string Name => "Swamp";
    public bool CanPassWith(List<IArtifact> artifacts) =>
        artifacts.Any(a => a.Supports(this));
}

// Конкретні артефакти
class ForestAmulet : IArtifact
{
    public string Name => "Forest Amulet";
    public bool Supports(ITraversalStrategy trial) => trial is ForestTrial;
}

class RiverStone : IArtifact
{
    public string Name => "River Stone";
    public bool Supports(ITraversalStrategy trial) => trial is RiverTrial;
}

class MountainBoots : IArtifact
{
    public string Name => "Mountain Boots";
    public bool Supports(ITraversalStrategy trial) => trial is MountainTrial;
}

class SwampCloak : IArtifact
{
    public string Name => "Swamp Cloak";
    public bool Supports(ITraversalStrategy trial) => trial is SwampTrial;
}

class Unit
{
    public string Name { get; }
    private List<IArtifact> artifacts;

    public Unit(string name, IArtifact artifact1, IArtifact artifact2)
    {
        Name = name;
        artifacts = new List<IArtifact> { artifact1, artifact2 };
    }

    public void TryPassScenario(List<ITraversalStrategy> trials)
    {
        Console.WriteLine($"\nUnit '{Name}' is trying to pass the scenario:");
        foreach (var trial in trials)
        {
            if (trial.CanPassWith(artifacts))
            {
                Console.WriteLine($":) Passed {trial.Name}");
            }
            else
            {
                Console.WriteLine($":( Failed {trial.Name} — scenario ended.");
                return;
            }
        }
        Console.WriteLine("Scenario completed successfully!");
    }

}

static class GameScenario
{
    public static List<ITraversalStrategy> Scenario1() =>
        new List<ITraversalStrategy> { new ForestTrial(), new RiverTrial() };

    public static List<ITraversalStrategy> Scenario2() =>
        new List<ITraversalStrategy> { new MountainTrial(), new SwampTrial() };

    public static List<ITraversalStrategy> Scenario3() =>
        new List<ITraversalStrategy> { new ForestTrial(), new MountainTrial(), new SwampTrial() };

    public static List<ITraversalStrategy> Scenario4() =>
        new List<ITraversalStrategy> { new RiverTrial(), new SwampTrial() };
}

class Program
{
    static void Main()
    {
        Unit elf = new Unit("Elf", new ForestAmulet(), new RiverStone());
        Unit dwarf = new Unit("Dwarf", new MountainBoots(), new SwampCloak());
        Unit mage = new Unit("Mage", new SwampCloak(), new ForestAmulet());

        Console.WriteLine("=== Scenario 1 ===");
        elf.TryPassScenario(GameScenario.Scenario1());

        Console.WriteLine("\n=== Scenario 2 ===");
        dwarf.TryPassScenario(GameScenario.Scenario2());

        Console.WriteLine("\n=== Scenario 3 ===");
        mage.TryPassScenario(GameScenario.Scenario3());

        Console.WriteLine("\n=== Scenario 4 ===");
        elf.TryPassScenario(GameScenario.Scenario4());
    }
}
