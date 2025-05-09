#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   

class Car {
protected:
    std::string brand;
    int cylinders;
    double power;

public:
    Car() : brand("Unknown"), cylinders(0), power(0.0) {}
    Car(const std::string& b, int c, double p) : brand(b), cylinders(c), power(p) {}
    ~Car() {}

    void setBrand(const std::string& newBrand) {
        brand = newBrand;
    }

    void print() const {
        std::cout << "Brand: " << brand << ", Cylinders: " << cylinders << ", Power: " << power << std::endl;
    }

    void input(bool randomInput) {
        if (randomInput) {
            std::string brands[] = { "Toyota", "Honda", "Ford", "BMW", "Audi" };
            brand = brands[rand() % 5];
            cylinders = 2 + rand() % 8; 
            power = 50.0 + (rand() % 201); 
        }
        else {
            std::cout << "Enter brand: ";
            std::cin >> brand;
            std::cout << "Enter number of cylinders: ";
            std::cin >> cylinders;
            std::cout << "Enter power: ";
            std::cin >> power;
        }
    }
};

class Truck : public Car {
private:
    double loadCapacity;

public:
    Truck() : Car(), loadCapacity(0.0) {}
    Truck(const std::string& b, int c, double p, double cap) : Car(b, c, p), loadCapacity(cap) {}
    ~Truck() {}

    void setLoadCapacity(double newCap) {
        loadCapacity = newCap;
    }

    void print() const {
        Car::print();
        std::cout << "Load capacity: " << loadCapacity << " tons" << std::endl;
    }

    void input(bool randomInput) {
        Car::input(randomInput);
        if (randomInput) {
            loadCapacity = 1.0 + (rand() % 20); 
        }
        else {
            std::cout << "Enter load capacity (tons): ";
            std::cin >> loadCapacity;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0))); 

    int choice;
    std::cout << "Choose input method:\n1 - Manual\n2 - Random\nEnter choice: ";
    std::cin >> choice;

    bool randomInput = (choice == 2);

    Car car;
    car.input(randomInput);
    car.print();

    Truck truck;
    truck.input(randomInput);
    truck.print();

    return 0;
}
