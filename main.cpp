#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility> // for the swap function
using namespace std;

// define a structure to hold course information
struct Course
{
    string courseNumber;
    string name;
    string prerequisites[3] = {"", "", ""};
};

// read data from file and load into vector
void loadCourseData(vector<Course> &courses)
{
    // open a file for input
    ifstream f("Courses.txt", ios::in);

    // check if the file opened successfully
    if (!f.is_open())
    {
        cout << "Error: Could not open file.\n";
        exit(1);
    }

    // string object to read the data into
    string courseData;

    // read data from the file
    while (getline(f, courseData))
    {
        // read data from the file into a Course object
        Course temp;

        // create an istringstream object
        istringstream ss(courseData);

        // read the courseNumber and name from the istringstream ss
        getline(ss, temp.courseNumber, ',');
        getline(ss, temp.name, ',');

        // create a temporary string to use as tokens for the istringstream 'ss;
        string preReqs;

        // read data into preReqs and keep assigning to the Course object temp's prerequisites;
        int i = 0;
        while (getline(ss, preReqs, ','))
        {
            temp.prerequisites[i] = preReqs;
            i++;
        }

        // once all the course data is read for 'temp', push it onto the vector 'courses'
        courses.push_back(temp);
    }

    // closing the input file
    f.close();
}

// function to print a course's information
void printCourse(Course course)
{
    cout << "Course Number: " << course.courseNumber << "\n";
    cout << "Course Name: " << course.name << "\n";
    cout << "Prerequisites: ";
    for (int j = 0; j < 3; j++)
        if (course.prerequisites[j] != "")
            cout << course.prerequisites[j] << "  \n";
    cout << "\n\n";
}

// selection sort to sort and print courses according to their course numbers
void printSortedList(vector<Course> &courses)
{
    int minPos, count = courses.size();

    // implement selection sort to sort the vector of courses
    for (int i = 0; i < count - 1; i++)
    {
        minPos = i;
        for (int j = i + 1; j < count; j++)
            if (courses[j].courseNumber < courses[minPos].courseNumber)
                minPos = j;

        // swap the current course with the minimum courseNumber
        swap(courses[minPos], courses[i]);
    }

    // print the list of courses
    for (int i = 0; i < count; i++)
        printCourse(courses[i]);
}

// return course information based on user input
void printCourseInfo(vector<Course> &courses)
{
    string courseNumber;
    cout << "What course do you want to know about?" << endl;
    cin >> courseNumber;

    bool found = false;
    for (int i = 0; i < courses.size(); i++)
    {
        if (courses[i].courseNumber == courseNumber)
        {
            found = true;
            printCourse(courses[i]);
            break;
        }
    }

    if (!found)
        cout << "\nThis course number does not exist.\n";
}

// menu display
void displayMenu()
{
    cout << "Welcome to the course planner.\n" << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "4. Exit " << endl;

    cout << "\nWhat would you like to do?" << endl;
}

int main()
{
    vector<Course> courses;
    int choice = 0;
    // Menu loop
    while (choice != 4)
    {
        displayMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            // call loadCourseData to read data from the file into the courses vector
            loadCourseData(courses);
            break;
        case 2:
            // call printSortedList to sort the courses and print them
            printSortedList(courses);
            break;
        case 3:
            // call printCourseInfo to search for a particular courseNumber
            printCourseInfo(courses);
            break;
        }
    }
}
