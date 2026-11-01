
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Student
{
public:
    string name;
    int mark;
    char grade;
};

int main()
{
    int n;

    cout << "Enter number of students: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid number of students!" << endl;
        return 0;
    }

    vector<Student> students(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter name of student " << i + 1 << ": ";
        cin >> students[i].name;

        cout << "Enter marks of " << students[i].name << ": ";
        cin >> students[i].mark;
    }

    // Sort students based on marks
    sort(students.begin(), students.end(),
    [](Student a, Student b)
    {
        return a.mark > b.mark;
    });

    // Assign grades using transform
    transform(students.begin(), students.end(),
    students.begin(),
    [](Student s)
    {
        if (s.mark >= 90)
            s.grade = 'A';
        else if (s.mark >= 75)
            s.grade = 'B';
        else if (s.mark >= 50)
            s.grade = 'C';
        else
            s.grade = 'F';

        return s;
    });

    // Find first student scoring above 80
    auto it = find_if(students.begin(), students.end(),
    [](Student s)
    {
        return s.mark > 80;
    });

    // Calculate total marks using accumulate
    int total = accumulate(students.begin(), students.end(), 0,
    [](int sum, Student s)
    {
        return sum + s.mark;
    });

    float average = (float)total / students.size();

    // Additional feature: Count students who passed
    int passed = count_if(students.begin(), students.end(),
    [](Student s)
    {
        return s.mark >= 50;
    });

    float passPercentage =
        (float)passed / students.size() * 100;

    // Display results
    cout << "\nStudent Grade Analyzer\n";
    cout << "---------------------\n";
    cout << "Name\tMark\tGrade\n";

    for (Student s : students)
    {
        cout << s.name << "\t"
             << s.mark << "\t"
             << s.grade << endl;
    }

    if (it != students.end())
    {
        cout << "\nFirst student scoring above 80: "
             << it->name << endl;
    }
    else
    {
        cout << "\nNo student scored above 80." << endl;
    }

    cout << "Total Marks: " << total << endl;
    cout << "Average Mark: " << average << endl;

    // Display pass statistics
    cout << "Students Passed: " << passed << endl;
    cout << "Pass Percentage: " << passPercentage
         << "%" << endl;

    return 0;
}
