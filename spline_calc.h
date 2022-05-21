#pragma once
#include<string>
#include"list_spln.h"
spline* initialize_points(std::string file);
void get_gammas(spline*& spln);
float spline_value(float x, spline* spln);
void write_new_points_to_file(spline* spln,std::string file,int N);;
