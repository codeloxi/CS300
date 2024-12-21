//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jacob Bennett
// Version     : 1.0
// Description : Project Two
//============================================================================

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void readData();
void displayAllCourses();
void displayCourse();
void sortCourseList();
void menu();

//define a structure to hold course information
struct Course {
    string courseName;
    string courseNumber;
    vector<string> coursePreReqs;
};

//Define a vector to store courses
vector<Course> courseList;

//function designed to read file contents and load data into vector data structure
//https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
void readData() {
    //define file variable
    string fileName;

    //ask user for file name
    cout << "Please end the exact file name" << endl;
    cin >> fileName;

    //define fstream and open file
    ifstream infile;
    infile.open(fileName);

    if (infile.is_open()) {
        string tempLine;

        while (getline(infile, tempLine)) {
            //vector of string to save tokens
            vector<string> tokens;
            string intermediate;
            //stringstream class init
            stringstream ss(tempLine);

            //tokenizing the delimiter ","
            while (getline(ss, intermediate, ',')) {
                tokens.push_back(intermediate);
            }

            //instantiate course object & fill object
            Course course = Course();
            course.courseNumber = tokens[0];
            course.courseName = tokens[1];

            //if third colulmn/prereqs then add to course object
            if (tokens.size() > 2) {
                for (int t = 2; t < tokens.size(); t++) {
                    course.coursePreReqs.push_back(tokens[t]);
                }
            }
            //add course object to vector
            courseList.push_back(course);
        }
        cout << "Data Loaded Successfully" << endl;
    }

    else {
        cout << "File Not Found -- Did you correctly type in File Name?" << endl;
    }
    //close file
    infile.close();
}

//Displays menu choices and executes specific functions based on user input  
void menu() {
    int choice = 0;

    while (choice != 9) {
        //print choices
        cout << "Menu:" << endl;
        cout << "  1. Load Data into the Data Structure" << endl;
        cout << "  2. Display All Courses" << endl;
        cout << "  3. Display Individual Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        //get user input
        cin >> choice;
        //switch statements for the 3 choices
        switch (choice) {

        case 1: 
            readData();
            break;

        case 2: 
            displayAllCourses();
            break;

        case 3:
            displayCourse();
            break;
        }
    }
    cout << "Thank you for using the course planner!" << endl;
}

//Prints all courses
void displayAllCourses() {
   //call sort function
    sortCourseList();

   // print all courses
    cout << "All Courses: \n"  << endl;
    for (int i = 0; i < courseList.size(); i++) {
        cout << courseList[i].courseNumber << " | ";
        cout << courseList[i].courseName << endl;
    }
}

void displayCourse() {
    string input;
    cout << "What course do you want to know about? " << endl;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), toupper);


    //check vector by looping through
    for (int i = 0; i < courseList.size(); i++) {
        if (courseList[i].courseNumber == input) {
            cout << courseList[i].courseNumber << " | ";
            cout << courseList[i].courseName << endl;
            
            cout << "Prerequesites: " << endl;

            //check if there are prerequesites and print if they exist
            if (courseList[i].coursePreReqs.size() > 0) {
                for (int j = 0; j < courseList[i].coursePreReqs.size() - 1; j++) {
                    cout << courseList[i].coursePreReqs[j] << " | " << endl;
                }
            }
            break;
        }
        else {
            cout << "Course not found! " << endl;
        }
    }
}

//function to sort the course list 
void sortCourseList() {
    //sort courses 
    for (int i = 0; i < courseList.size() - 1; i++) {
        for (int j = 0; j < courseList.size() - i - 1; j++) {
            if (courseList[j].courseNumber > courseList[j + 1].courseNumber) {
                swap(courseList[j + 1], courseList[j]);
            }
        }
    }
}

//Main driver function
int main() {
    
    menu();
    return 0;
}

