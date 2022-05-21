//
// Created by home on 21.05.22.
//

#include "intersection.h"
#include<iostream>
#include<math.h>
float Sub(spline* spln1,spline* spln2, float x)
{
    return spline_value(x,spln1)-spline_value(x,spln2);
}
float dSub(spline* spln1,spline* spln2,float x)
{
    float accuracy=0.00001;
    return (Sub(spln1,spln2,x+accuracy)-Sub(spln1,spln2,x))/accuracy;
}
float d2Sub(spline *spln1,spline* spln2, float x)
{
    float accuracy=0.00001;
    return (dSub(spln1,spln2,x+accuracy)-dSub(spln1,spln2,x))/accuracy;
}
void find_intersection(spline* spln1,spline* spln2,float error) {
    float a = (spln1->X > spln2->X) ? spln1->X : spln2->X;
    while (spln1->next)
        spln1 = spln1->next;
    while (spln2->next)
        spln2 = spln2->next;
    float b = (spln1->X < spln2->X) ? spln1->X : spln2->X;
    while (spln1->prev)
        spln1 = spln1->prev;
    while (spln2->prev)
        spln2 = spln2->prev;
    float curr_approx;
    if(Sub(spln1,spln2,a)*Sub(spln1,spln2,b)<=0) {
        if (d2Sub(spln1, spln2, b) * Sub(spln1, spln2, b) >= 0)
            curr_approx = b;
        else
            curr_approx = a;

    }
    else
    {
        std::cout<<"There's no intersections or more than 1 intersection\n";
        return;
    }
    while(abs(Sub(spln1,spln2,curr_approx))>=error)
        curr_approx-=Sub(spln1,spln2,curr_approx)/dSub(spln1,spln2,curr_approx);
    std::cout<<"X = "<<curr_approx<<"\n";


}