
#include "spline_calc.h"
#include<string>
#include<fstream>
#include<math.h>
#include<iostream>
void get_gammas(spline*& spln) {
    spline *temp = spln;
    int size = 0;
    while (temp) {
        temp=temp->next;
        size++;
    }
    temp = spln->next;
    float *A = new float[size];
    float *B = new float[size];
    float *C = new float[size];
    float *F = new float[size];
    float *gammas = new float[size];
    int i = 1;
    while (temp->next) {
        A[i] = temp->X - temp->prev->X;
        B[i] = 2 * (temp->next->X - temp->prev->X);
        C[i] = (temp->next->X - temp->X);
        F[i] = 6 * ((temp->next->Y - temp->Y) / (temp->next->X - temp->X)-(temp->Y - temp->prev->Y) / (temp->X - temp->prev->X));
        temp = temp->next;
        i++;

    }
    float *alpha = new float[size];
    float *beta = new float[size];
    alpha[2] = -C[1] / B[1];
    beta[2] = F[1] / B[1];
    for (i = 2; i < size - 1; i++) {
        alpha[i + 1] = -C[i] / (A[i] * alpha[i] + B[i]);
        beta[i + 1] = (F[i] - A[i] * beta[i]) / (alpha[i] * A[i] + B[i]);
    }
    gammas[size - 1] = 0;
    gammas[size - 2] = (F[size - 2] - A[size - 2] * beta[size - 2]) / (B[size - 2] + A[size - 2] * alpha[size - 2]);
    for (i = size - 3; i >= 1; i--) {
        gammas[i] = gammas[i + 1] * alpha[i + 1] + beta[i + 1];
    }
    gammas[0] = 0;
    temp = spln;
    for (i = 0; i <= size - 1; i++) {
        temp->gamma = gammas[i];
        temp = temp->next;
    }
    delete[] alpha;
    delete[] beta;
    delete[] gammas;
    delete[] A;
    delete [] B;
    delete[]C;
    delete[]F;
}

float F_1(float y,float xi,float x,float h) {
    return y * (xi - x) / h;
}
float F_2(float gamma,float xi,float x,float h)
{
    return gamma*(pow(xi-x,3)-pow(h,2)*(xi-x))/(6*h);
}

float spline_value(float x, spline* spln)
{

    spline* temp=spln;
    while((temp->next->next)&&(temp->next->X<=x))
        temp=temp->next;
    float h=temp->next->X-temp->X;
    return F_1(temp->Y,temp->next->X,x,h)+F_1(temp->next->Y,x,temp->X,h)+F_2(temp->gamma,temp->next->X,x,h)+F_2(temp->next->gamma,x,temp->X,h);
}

spline* initialize_points(std::string file)
{
    std::ifstream in(file);
    int size;
    spline* result=nullptr;
    in>>size;
    float X,Y;
    for(int i=0;i<=size-1;i++)
    {
        in>>X;
        in>>Y;
        add_last(result,X,Y);
    }
    return result;
}
void write_new_points_to_file(spline* spln,std::string file,int N) {
    float x;
    std::ofstream out(file);
    spline *temp;
    while (temp->next) {
        temp = temp->next;
    }
    for (int i = 0; i <= N; i++) {
        x = spln->X + i * (temp->X - spln->X) / N;
        out << x;
        out << " ";
        out << spline_value(x, spln);
        out << "\n";
    }
    out.close();
}