#pragma once
#include<string>
struct spline
{
    spline* next;
    spline* prev;
    float gamma;
    float X,Y;
};
void add_last(spline*& cur_spln,float X,float Y);
void delete_spline(spline*& spln);
