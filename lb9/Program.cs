using lb9;

class Program
{
    static void Main(string[] args)
    {
        var orders = new Dictionary<string, OrderContext>
        {
            { "Alice", new OrderContext("Alice", new OrderPlacedState()) },
            { "Bob", new OrderContext("Bob", new PackingOrderState()) },
            { "Charlie", new OrderContext("Charlie", new OrderShippedState()) }
        };

        string currentUser = "Alice";
        OrderContext currentOrder = orders[currentUser];

        while (true)
        {
            Console.WriteLine("\n--- Order Processing Menu ---");
            foreach (var user in orders)
            {
                Console.Write("- " + user.Key + " (");
                Console.ForegroundColor = user.Key == currentUser ? ConsoleColor.Yellow : ConsoleColor.Gray;
                user.Value.PrintShortStatus();
                Console.ResetColor();
                Console.WriteLine(")");
            }

            Console.WriteLine($"\nSelected User: {currentUser}");

            Console.WriteLine("1. Show All Order States");

            if (currentOrder.CanProceed())
                Console.WriteLine("2. Proceed to Next State (Current User)");

            if (currentOrder.CanCancel())
                Console.WriteLine("3. Cancel Order (Current User)");

            Console.WriteLine("4. Switch User");
            Console.WriteLine("5. List All Users");
            Console.WriteLine("0. Exit");
            Console.Write("Enter choice: ");
            string input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    Console.WriteLine("\n--- Order States for All Users ---");
                    foreach (var user in orders.Values)
                    {
                        user.PrintStatus();
                    }
                    break;

                case "2":
                    if (currentOrder.CanProceed())
                        currentOrder.Proceed();
                    else
                        Console.WriteLine("Cannot proceed from the current state.");
                    break;

                case "3":
                    if (currentOrder.CanCancel())
                        currentOrder.Cancel();
                    else
                        Console.WriteLine("Order cannot be cancelled at this stage.");
                    break;

                case "4":
                    Console.Write("Enter user name: ");
                    string newUser = Console.ReadLine();
                    if (orders.ContainsKey(newUser))
                    {
                        currentUser = newUser;
                        currentOrder = orders[currentUser];
                        Console.WriteLine($"Switched to {currentUser}.");
                    }
                    else
                    {
                        Console.WriteLine("User not found.");
                    }
                    break;

                case "5":
                    Console.WriteLine("Available Users:");
                    foreach (var user in orders.Keys)
                    {
                        Console.WriteLine("- " + user);
                    }
                    break;

                case "0":
                    return;

                default:
                    Console.WriteLine("Invalid option.");
                    break;
            }
        }
    }
}
