#include "../debug.hpp"
#include <memory>
#include <string>
#include <vector>

struct Address {
    std::string street;
    std::string city;
    int zip;
};
DBG_PRETTY_STRUCT(Address, street, city, zip);

struct Employee {
    std::string name;
    int id;
    std::shared_ptr<Address> address; // Indirection via pointer
};
DBG_PRETTY_STRUCT(Employee, name, id, address);

struct Project {
    std::string title;
    std::vector<Employee> assignees;
};
DBG_PRETTY_STRUCT(Project, title, assignees);

struct Department {
    std::string name;
    Project active_project;
    Project future_project;
};
DBG_PRETTY_STRUCT(Department, name, active_project, future_project);

struct Company {
    std::string name;
    std::vector<Department> departments;
};
DBG_PRETTY_STRUCT(Company, name, departments);

int main() {
    auto addr1 = std::make_shared<Address>(
        Address{"123 Tech Blvd", "San Francisco", 94107}
    );
    auto addr2 =
        std::make_shared<Address>(Address{"456 Code Lane", "New York", 10001});

    Employee e1{"Alice", 101, addr1};
    Employee e2{"Bob", 102, addr2};

    Project p1{"AI Agent", {e1}};
    Project p2{
        "Quantum Leap",
        {e2, e1}
    };

    Department d1{"R&D", p1, p2};
    Department d2{"Ops", p2, p1};

    Company mega_corp{
        "MegaCorp",
        {d1, d2}
    };

    std::cout << "--- Deeply Nested Company Structure ---" << std::endl;
    dbg(mega_corp);

    return 0;
}
