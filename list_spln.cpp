//
// Created by home on 21.05.22.
//

#include "list_spln.h"
void add_last(spline*& cur_spln,float X,float Y)
{
    spline* new_elem =new spline();
    new_elem->X=X;
    new_elem->Y=Y;
    if(cur_spln) {
        spline *temp = cur_spln;
        while (temp->next)
            temp = temp->next;
        new_elem->prev=temp;
        temp->next=new_elem;
    }
    else
        cur_spln=new_elem;
}
void delete_spline(spline*& spln) {
    if (spln->next) {
        delete_spline(spln->next);
    }
    if(spln->prev) {
        spln->prev->next = nullptr;
    }
    delete(spln);
}



