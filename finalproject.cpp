/*
Creator: Dylan Coulter
Assignment: Project 3 
Date:02/16/2022
*/
#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
        To call this function, simply pass the function name in Python that you wish to call.
Example:
        callProcedure("printsomething");
Output:
        Python will print on the screen: Hello from python!
Return:
        None
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("python");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("PrintMe","Test");
Output:
        Python will print on the screen:
                You sent me: Test
Return:
        100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"python");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("doublevalue",5);
Return:
        25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"python");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}


void Draw_Menu() {

    //Initialize method-specific variables
    int menu_Loop = 0;   //counts the number of menu loops 
    int word_Count = 0;    //counts the number of times a specific searched word was found
    int item_Quantity = 0;   //Variable to contain an item quantity located from frequency.dat
    string srch_Term;     //Collects the users input for the search term
    string item_Name;      //Variable to contain an item name located from frequency.dat
    string grn_Color = "\033[32;1m";   //Sets the font color of the asterisks to green 
    string def_Color = "\033[0m";    //Set default font color for the console
    ifstream fileInput;     //Open ifstream for file

    while (menu_Loop != 4) {

        //Prompts the user for input and collects it 
        std::cout << "[1] Calculate the number of times each item appears" << std::endl;
        std::cout << "[2] Calculate the frequency of a specific item" << std::endl;
        std::cout << "[3] Create a histogram based on the number of appearances of each item" << std::endl;
        std::cout << "[4] Quit" << std::endl;

        std::cin >> menu_Loop;

        //verifies the users input is valid and if not prompts for a valid input
        while (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please input a valid selection: ";
            std::cin >> menu_Loop;
        }


        //Switch statement
        switch (menu_Loop) {


            //Calculates and prints a list of each time and items appears

        case 1:
            system("CLS");                                          //Clear the screen to tidy things up
            CallProcedure("Count_All");                      //Call the Python function "CountAll"
            std::cout << std::endl;                           //Add a bit of space in between the printed list and menu
            break;


            // Calculates and prints the number of times a specific item appears
        case 2:
            system("CLS");
            std::cout << "What item would you like to search for?" << std::endl;
            std::cin >> srch_Term;

            //Call Python function Count_Instances
            word_Count = callIntFunc("Count_Instances", srch_Term);

            //Print statement with returned word count.
            std::cout << std::endl << srch_Term << " : " << word_Count << std::endl << std::endl;

            break;


            //Similar to case 1 prints a histogram based on how many times each item appears, but this time with stars. 
        case 3:
            system("CLS");     //Clears the screen 
            CallProcedure("Collect_Data");    //Call the Python function "Collect_Data"

            fileInput.open("frequency.dat");    //Open frequency.dat

            fileInput >> item_Name;      //Collect first item on list
            fileInput >> item_Quantity;       //Collect first quantity on list


            // Prints a histogram for each line in the file after all line shas been have been parsed, break
            while (!fileInput.fail()) {
                //Set text color to white
                std::cout << def_Color;

                //Prints the item name
                //Prepare for the histogram
                std::cout << std::setw(14) << std::left << item_Name << std::setw(6);

                //chose to set the histogram color to green 
                std::cout << grn_Color;

                //Print item_Quantity number of asterisks
                for (int i = 0; i < item_Quantity; i++) {

                    //Print green asterisks in line.
                    std::cout << std::right << "*";
                }
                //Prepare for the next line, then set the next item's name and quantity.
                std::cout << std::endl;
                fileInput >> item_Name;
                fileInput >> item_Quantity;
            }

            //Closes frequency.dat and resets font color
            fileInput.close();
            std::cout << def_Color << endl;
            break;


            // Quits the program.
        case 4:
            return;

            // Invalid input
        default:
            std::cout << "Please input a valid selection.";
            std::cout << std::endl;
            break;
        }
    }
}

//Main method. Calls the Draw_Menu method to collect user input.
void main()
{
    //Draws the user menu.
    Draw_Menu();

}

