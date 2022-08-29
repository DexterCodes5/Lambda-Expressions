#include <iostream>
#include <vector>
#include <algorithm>

class Person {
    friend std::ostream &operator<<(std::ostream &os, const Person &rhs);
private:
    std::string name;
    int age;
public:
    Person() = default;
    Person(std::string name, int age) : name{name}, age{age} {};
    Person(const Person &p): name{p.name}, age{p.age} { }
    ~Person() = default;
    std::string get_name() const { return name; }
    void set_name(std::string name) {this->name = name; };
    int get_age() const {return age; }
    void set_age(int age) {this->age = age; }
    
    auto change_person1() {return [this] (std::string new_name, int new_age) {name = new_name; age=new_age;};}
    auto change_person2() {return [=] (std::string new_name, int new_age) {name = new_name; age=new_age;};}
    auto change_person3() {return [&] (std::string new_name, int new_age) {name = new_name; age=new_age;};}
};

std::ostream &operator<<(std::ostream &os, const Person &rhs) {
    os << "[Person: " <<rhs.name << " : " <<rhs.age << "]";
    return os;
}

class People {
    std::vector<Person> people;
    int max_people;
public:
    People(int max = 10) : max_people{max} {}
    People(const People &p) = default;
    void add(std::string name, int age) {
        people.emplace_back(name, age);
    }
    void set_max_people(int max) {
        max_people = max;
    }
    int get_max_people() const {
        return max_people;
    }
    
    std::vector<Person> get_people(int max_age) {
        std::vector<Person> result;
        int count{0};
        std::copy_if(people.begin(), people.end(), std::back_inserter(result),
            [this, &count, max_age](const Person &p){return p.get_age() > max_age && ++count<=max_people;});
        return result; 
    }
};

int main(){
    People friends;
    friends.add("Larry", 18);
    friends.add("Curly", 25);
    friends.add("Moe", 35);
    friends.add("Frank", 28);
    friends.add("James", 65);
    
    auto result = friends.get_people(17);
    
    std::cout << std::endl;
    for (const auto &p: result)
        std::cout << p << std::endl;
        
    friends.set_max_people(3);
    
    result = friends.get_people(17);
    
    std::cout << std::endl;
    for (const auto &p: result)
        std::cout << p << std::endl;
        
    result = friends.get_people(50);
    std::cout << std::endl;
    for (const auto &p: result)
        std::cout << p << std::endl;
    
    return 0;
}
