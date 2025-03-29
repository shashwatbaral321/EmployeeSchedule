#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Employee {
    string name;
    vector<string> preferred_shifts;
    int assigned_days;
};

const vector<string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const vector<string> shifts = {"Morning", "Afternoon", "Evening"};

map<string, map<string, vector<string>>> schedule;

void assignShifts(vector<Employee>& employees) {
    srand(time(0)); // Seed for randomness
    
    for (const string& day : days) {
        for (const string& shift : shifts) {
            vector<string> assigned;
            for (Employee& employee : employees) {
                if (employee.assigned_days < 5 && find(employee.preferred_shifts.begin(), employee.preferred_shifts.end(), shift) != employee.preferred_shifts.end()) {
                    assigned.push_back(employee.name);
                    employee.assigned_days++;
                }
                if (assigned.size() == 2) break;
            }
            while (assigned.size() < 2) {
                for (Employee& employee : employees) {
                    if (employee.assigned_days < 5 && find(assigned.begin(), assigned.end(), employee.name) == assigned.end()) {
                        assigned.push_back(employee.name);
                        employee.assigned_days++;
                        if (assigned.size() == 2) break;
                    }
                }
            }
            schedule[day][shift] = assigned;
        }
    }
}

void printSchedule() {
    cout << "\nFinal Employee Schedule:" << endl;
    for (const string& day : days) {
        cout << "\n" << day << ":\n";
        for (const string& shift : shifts) {
            cout << shift << ": ";
            for (const string& employee : schedule[day][shift]) {
                cout << employee << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    int numEmployees;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;
    cin.ignore();
    
    vector<Employee> employees(numEmployees);
    for (int i = 0; i < numEmployees; ++i) {
        cout << "Enter employee name: ";
        getline(cin, employees[i].name);
        employees[i].assigned_days = 0;
        cout << "Enter preferred shifts (Morning, Afternoon, Evening) separated by space: ";
        string shift;
        getline(cin, shift);
        size_t pos = 0;
        while ((pos = shift.find(' ')) != string::npos) {
            employees[i].preferred_shifts.push_back(shift.substr(0, pos));
            shift.erase(0, pos + 1);
        }
        employees[i].preferred_shifts.push_back(shift);
    }
    
    assignShifts(employees);
    printSchedule();
    
    return 0;
}
