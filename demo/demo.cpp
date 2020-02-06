/**
 * \file demo.cpp
 * \brief File regrouping all the possible test
 * This file is interactive : the user can choose which test to perform
 * \author Clara.B
 * \version 0.1
 * \date 02/02/20
 */

#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    string choice;
    cout << "+------------------------------------------------------+" << endl;
    cout << "|        DIGITAL ANALYSIS OF FINGERPRINTS - DEMO       |" << endl;
    cout << "+------------------------------------------------------+" << endl;

    do {
        cout << endl;
        cout << "------------------------- MENU -------------------------" << endl;
        cout << "Part 0: Unit tests" << endl;
        cout << "Part 1: Image loading, saving and pixels manipulation" << endl;
        cout << "Part 2: Geometrical warps" << endl;
        cout << "Part 3: Linear filtering" << endl;
        cout << "Part 4: Morphological filtering" << endl;
        cout << "Part 5: Optimization" << endl << endl;

        cout << "Enter the number of the part you want to test: ";
        int part;
        cin >> part;

        while (part < 0 || part > 5) {
            cout << "The number is not correct. Please enter a number between 0 and 5: ";
            cin >> part;
        }

        if (part == 0) {
            cout << endl;
            system("./test/tests");
        } else {
            int test;
            cout << endl;
            cout << "------------------------- MENU -------------------------" << endl;
            switch (part)
            {
                case 1:
                cout << "Test 1: Rectangles" << endl;
                cout << "Test 2: Symmetries" << endl;
                cout << "Test 3: Variation of pressure" << endl << endl;
                cout << "Enter the number of the test you want to execute: ";
                cin >> test;

                while (test < 1 || test > 3){
                    cout << "The number is not correct. Please enter a number between 1 and 3: ";
                    cin >> test;
                }
                
                switch (test)
                {
                case 1:
                    system("./demo/rectangles");
                    break;
                case 2:
                    system("./demo/symmetries");
                    break;
                case 3:
                    system("./demo/pressure");
                    break;
                default:
                    break;
                }
                break;
                
            case 2:
                cout << "Test 1 : Rotations" << endl;
                cout << "Test 2 : Skin elasticity" << endl << endl;;
                cout << "Enter the number of the test you want to execute: ";
                cin >> test;
                
                while (test < 1 || test > 2){
                    cout << "The number is not correct. Please enter a number between 1 and 2: ";
                    cin >> test;
                }
                
                switch (test)
                {
                case 1:
                    system("./demo/rotations");
                    break;
                case 2:
                    system("./demo/elasticity");
                    break;
                default:
                    break;
                }
                break;

            case 3:
                system("./demo/linear_filtering");
                break;

            case 4:
                system("./demo/morphological_filtering");
                break;

            case 5:
                cout << "Test 1 : Translations" << endl;
                cout << "Test 2 : Optimization" << endl << endl;
                cout << "Enter the number of the test you want to execute: ";
                cin >> test;

                while (test < 1 || test > 2){
                    cout << "The number is not correct. Please enter a number between 1 and 2: ";
                    cin >> test;
                }
                
                switch (test)
                {
                case 1:
                    system("./demo/translation");
                    break;
                case 2:
                    system("./demo/optimization");
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
        }

        cout << endl;

        cout << "Do you want to launch another test?" << endl;
        cout << "yes(y)/no(n): ";

        cin >> choice;

        while (choice.compare("y") != 0 && choice.compare("n") != 0) {
            cout << "Please answer either with yes(y) or with no(n): ";
            cin >> choice;
        }

    } while (choice.compare("n") != 0);


    return 0;
}
