#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Fish {
protected:
    string name;
    string species;
    int age;
    bool health;

public:
    Fish(string _name, string _species) : name(_name), species(_species), age(0), health(true) {}

    virtual ~Fish() {}

    virtual void display() const = 0;

    bool isAlive() const {
        return health;
    }

    void incrementAge() {
        age++;
    }

    void die() {
        health = false;
        cout << name << " умер." << endl;
    }

    virtual void eat() = 0; // Абстрактный метод для питания

    virtual bool isPredatory() const = 0; // Абстрактный метод для определения, является ли рыба хищником
};

class Prey : public Fish {
public:
    Prey(string _name, string _species) : Fish(_name, _species) {}

    void display() const override {
        cout << "Имя: " << name << endl;
        cout << "Вид: " << species << endl;
        cout << "Возраст: " << age << endl;
        cout << "Тип: Добрая рыба" << endl;
    }

    void eat() override {
        cout << name << " съел водоросли!" << endl;
    }

    bool isPredatory() const override {
        return false;
    }

    string GetName() const {
        return name;
    }
};

class Predator : public Fish {
public:
    Predator(string _name, string _species) : Fish(_name, _species) {}

    void display() const override {
        cout << "Имя: " << name << endl;
        cout << "Вид: " << species << endl;
        cout << "Возраст: " << age << endl;
        cout << "Тип: Хищник" << endl;
    }

    void eat() override {
        cout << name << " съел еще одну рыбку!" << endl;
    }

    bool isPredatory() const override {
        return true;
    }

    string GetName() const {
        return name;
    }
};

class Seaweed {
private:
    string name;
    int quantity;

public:
    Seaweed(string _name, int _quantity) : name(_name), quantity(_quantity) {}

    void display() const {
        cout << "Имя: " << name << endl;
        cout << "Количество: " << quantity << endl;
    }

    bool hasEnough() const {
        return quantity > 0;
    }

    int getQuantity() const {
        return quantity;
    }

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void decrease(int amount) {
        if (quantity >= amount) {
            quantity -= amount;
        }
        else {
            cout << "Не хватает морских водорослей." << endl;
        }
    }

};

void AddSeaweed(vector<Seaweed>& seaweeds) {
    string name;
    int quantity;
    cout << "Введите название водоросли: ";
    cin >> name;
    cout << "Введите количество: ";
    cin >> quantity;
    Seaweed newSeaweed(name, quantity);
    seaweeds.push_back(newSeaweed);
}

void FeedFish(vector<Prey>& prey, vector<Predator>& predator, const vector<Seaweed>& seaweeds) {
    for (auto& fish : prey) {
        fish.eat();
    }

    for (auto& fish : predator) {
        if (!seaweeds.empty()) {
            int index = rand() % seaweeds.size();
            cout << fish.GetName() << " съел водоросли!" << endl;
        }
        else {
            cout << "Никаких водорослей не осталось для " << fish.GetName() << endl;
        }
    }
}

void DeleteFishRandomly(vector<Prey>& prey, vector<Predator>& predator) {
    srand(time(0));

    int randomIndex = rand() % 2;

    if (randomIndex == 0) {
        if (!prey.empty()) {
            int index = rand() % prey.size();
            cout << "Хищник убил свою жертву: " << prey[index].GetName() << endl;
            prey.erase(prey.begin() + index);
        }
        else {
            cout << "Добычи не осталось" << endl;
        }
    }
    else {
        if (!predator.empty()) {
            int index = rand() % predator.size();
            cout << "Жертва пережила нападение хищника: " << predator[index].GetName() << endl;
        }
        else {
            cout << "Не осталось ни одного хищника" << endl;
        }
    }
}

void ViewAquariumInformation(const vector<Prey>& prey, const vector<Predator>& predator, const vector<Seaweed>& seaweeds) {
    cout << "Добрых рыбок:" << endl;
    for (const auto& fish : prey) {
        fish.display();
        cout << endl;
    }

    cout << "Хищников:" << endl;
    for (const auto& fish : predator) {
        fish.display();
        cout << endl;
    }

    cout << "Общее количество добрых рыб: " << prey.size() << endl;
    cout << "Общее количество хищников: " << predator.size() << endl;

    cout << "Общее количество водорослей: ";
    int totalSeaweed = 0;
    for (const Seaweed& seaweed : seaweeds) {
        totalSeaweed += seaweed.getQuantity();
    }
    cout << totalSeaweed << endl;
}

void displayMenu(const vector<Prey>& prey, const vector<Predator>& predator, const vector<Seaweed>& seaweeds) {
    cout << "1. Добавить добрую рыбку" << endl;
    cout << "2. Добавить хищника" << endl;
    cout << "3. Добавить водоросли" << endl;
    cout << "4. Покормить рыбу" << endl;
    cout << "5. Симуляция" << endl;
    cout << "6. Общая информация о акавариуме" << endl;
    cout << "7. Выход" << endl;
    cout << "Текущее количество рыб: " << prey.size() + predator.size() << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");
    vector<Prey> prey;
    vector<Predator> predator;
    vector<Seaweed> seaweeds;

    int choice;
    do {
        displayMenu(prey, predator, seaweeds);
        cout << "Введите число: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, species;
            cout << "Введите имя: ";
            cin >> name;
            cout << "Введите вид: ";
            cin >> species;
            Prey newprey(name, species);
            prey.push_back(newprey);
            break;
        }

        case 2: {
            string name, species;
            cout << "Введите имя: ";
            cin >> name;
            cout << "Введите вид: ";
            cin >> species;
            Predator newpredator(name, species);
            predator.push_back(newpredator);
            break;
        }

        case 3:
            AddSeaweed(seaweeds);
            break;

        case 4:
            FeedFish(prey, predator, seaweeds);
            break;

        case 5:
            DeleteFishRandomly(prey, predator);
            break;

        case 6:
            ViewAquariumInformation(prey, predator, seaweeds);
            break;

        case 7:
            cout << "Пока, пока. Всего хорошего." << endl;
            break;

        default:
            cout << "Неверный выбор. Пожалуйста, введите число от 1 до 7." << endl;
        }
    } while (choice != 7);

    return 0;
}
