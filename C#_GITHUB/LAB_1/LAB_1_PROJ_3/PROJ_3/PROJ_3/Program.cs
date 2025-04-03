using System;

interface IAnimal
{
    void Speak();
}

struct Dog : IAnimal
{
    public void Speak()
    {
        Console.WriteLine("Woof!");
    }
}

class Program
{
    static void Main()
    {
        Dog d = new Dog();
        d.Speak(); // Woof!
    }
}
