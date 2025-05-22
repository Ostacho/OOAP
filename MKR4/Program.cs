using System;
using System.Collections.Generic;

class Memento
{
    public string State { get; }

    public Memento(string state)
    {
        State = state;
    }
}

class Talker
{
    private string _text = "";

    public void SayWord(string word)
    {
        _text += word + " ";
        Console.WriteLine($"Spoken: {word}");
    }

    public Memento Save()
    {
        return new Memento(_text);
    }

    public void Restore(Memento memento)
    {
        _text = memento.State;
        Console.WriteLine($"Restored to: {_text}");
    }

    public void ShowText()
    {
        Console.WriteLine($"Current text: {_text}");
    }
}

class Caretaker
{
    private Stack<Memento> _history = new Stack<Memento>();

    public void SaveState(Talker talker)
    {
        _history.Push(talker.Save());
    }

    public void Undo(Talker talker)
    {
        if (_history.Count > 0)
        {
            var memento = _history.Pop();
            talker.Restore(memento);
        }
        else
        {
            Console.WriteLine("No saved states to restore.");
        }
    }
}

class Program
{
    static void Main()
    {
        var talker = new Talker();
        var caretaker = new Caretaker();
        bool running = true;

        while (running)
        {
            Console.WriteLine("\nMenu:");
            Console.WriteLine("1. Say a word");
            Console.WriteLine("2. Show current text");
            Console.WriteLine("3. Undo last word");
            Console.WriteLine("4. Exit");
            Console.Write("Choose an option: ");
            string input = Console.ReadLine();

            switch (input)
            {
                case "1":
                    Console.Write("Enter word: ");
                    string word = Console.ReadLine();
                    talker.SayWord(word);
                    caretaker.SaveState(talker);
                    break;
                case "2":
                    talker.ShowText();
                    break;
                case "3":
                    caretaker.Undo(talker);
                    break;
                case "4":
                    running = false;
                    break;
                default:
                    Console.WriteLine("Invalid option.");
                    break;
            }
        }

        Console.WriteLine("Program ended.");
    }
}
