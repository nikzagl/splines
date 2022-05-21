#include <iostream>
#include <math.h>
#include<string>
#include <fstream>
#include "intersection.h"
#include "list_spln.h"
#include "spline_calc.h"
int main() {

    int command=0;
    std::string input_1;
    std::string input_2;
    std::string output;
    spline* spln1;
    spline* spln2;
    float error;
    while(true) {
        std::cout
                << "Command:\n 0 - exit, 1 - calculate the spline value in N dots, 2 - determine x of the intersection/minimal distance between splines\n";
        std::cin >> command;
        if (!command)
            break;
        if (command == 1) {
            std::cout << "Input file:\n";
            std::cin >> input_1;
            std::cout << "Output file: \n";
            std::cin >> output;
            std::cout << "N: \n";
            int N;
            std::cin >> N;
            spln1=nullptr;
            spln1= initialize_points(input_1);
            get_gammas(spln1);
            write_new_points_to_file(spln1, output, N - 1);
            std::cout<<"Done!";
            delete_spline(spln1);
        }
        if (command==2)
        {
            std::cout<<"1st input file:\n";
            std::cin >> input_1;
            std::cout<<"2nd input file: \n";
            std::cin>>input_2;
            std::cout<<"Maximal error: \n";
            std::cin>>error;
            spln1=nullptr;
            spln2=nullptr;
            spln1= initialize_points(input_1);
            spln2= initialize_points(input_2);
            get_gammas(spln1);
            get_gammas(spln2);
            find_intersection(spln1,spln2,error);
            delete_spline(spln1);
            delete_spline(spln2);
        }
    }
    return 0;

}
