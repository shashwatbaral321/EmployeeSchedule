import random

def collect_employee_data():
    while True:
        try:
            num_employees = int(input("Enter the number of employees: "))
            if num_employees <= 0:
                print("Please enter a valid positive number.")
                continue
            break
        except ValueError:
            print("Invalid input! Please enter a number.")

    employees = {}
    for _ in range(num_employees):
        name = input("Enter employee name: ").strip()
        employees[name] = {
            "assigned_shifts": {},  # Store assigned shifts per day
            "assigned_days": 0      # Track number of days worked
        }

    return employees


def assign_shifts(employees):
    days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
    shifts = ["Morning", "Afternoon", "Evening"]
    schedule = {day: {shift: [] for shift in shifts} for day in days}

    for day in days:
        for shift in shifts:
            for employee in employees:
                if employees[employee]["assigned_days"] < 5 and len(schedule[day][shift]) < 2:
                    schedule[day][shift].append(employee)
                    employees[employee]["assigned_days"] += 1  # Track workdays

    return schedule


def display_schedule(schedule):
    print("\nFinal Employee Schedule:")
    for day, shifts in schedule.items():
        print(f"\n{day}:")
        for shift, employees in shifts.items():
            print(f"  {shift.capitalize()}: {', '.join(employees) if employees else 'No employees assigned'}")

if __name__ == "__main__":
    employees = collect_employee_data()
    schedule = assign_shifts(employees)
    display_schedule(schedule)
