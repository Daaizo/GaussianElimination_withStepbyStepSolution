#include <iostream>
#include <math.h>
#include "array.h"
using namespace std;


class Gauss{

private :
    float numberCloseToZero = 1e-7;
    int rows;
    int cols;
    float ** array;

    void pickInput();
    void pickMethod();
    void getPrepared2DArray();
    void setArray(float ** ar, int r, int c);

    float* arrayWithCoefficients(int step);
    void defaultElimination();
    void getResultFromRowEchelonForm();  // macierz schodkowa
    bool isElementEqualZero(int i, int j);
    bool isEquationSolvable();
public :

    ~Gauss(){delete2Darray(this->array, this->rows);}
    void menu();

};




int main(){
    Gauss gauss;
    gauss.menu();


    return 0;
}

void Gauss::menu(){
    pickInput();
    pickMethod();

}

void Gauss::pickInput(){
    int choice = 0;
    cout << "\n1.Gotowy zbior danych\n2.Wprowadzanie danych z klawiatury" << endl;
    cin >> choice;
    switch(choice){
        case 1: {
            this->getPrepared2DArray();
            break;
        }
        case 2 : {
            //loaddata here
            break;
        }
        default:{
            cout << "Zly wybor ";
            exit(4);
        }
    }
}
void Gauss::getPrepared2DArray(){

    float example1[4][5] = { {1,1,0,-3,1}, {1,4,-1,-4,-2},{0.5,0.5,-3,-5.5,1.5} ,{1.5,3,-5,-9,-0.5}};
    float example2[4][5] = {{0,2,-1,2,0} ,{0,0,-2,4,4}, {0,-3,1.5,7,0}, {1,-1,1,6,-1}};
    float example3[4][5] = { {2.25,-2.5,4,-5.25,-1}, {-3,-7.5,6.5,0,17},{-6.25,-12.5,0.25,5.25,24.25},{9,10,7,-21,-33}};
    //float example4[3][4] = { {1,2,-1,-1},{-1,0,3,4},{-2,-3,1,-1}};
    float example4[3][4] = { {0,2,-1,0},{1,0,-2,4},{10,0,3,0}};

    int chooice;
    cout << "\nPrzyklad 1 : wynik poprawny  x4=-1 x3=1 x2=-1 x1=-1";
    print2DArray(example1, 4, 5);
    cout << "\nPrzyklad 2 : wynik poprawny  x4=0 x3=-2 x2=-1 x1=0";
    print2DArray(example2, 4, 5);
    cout << "\nPrzyklad 3 : wynik poprawny  x4=1 x3=1 x2=-1 x1=-1";
    print2DArray(example3, 4, 5);
    cout << "\nPrzyklad 4 : wynik poprawny   x3=2 x2=-1 x1=3";
    float ** tempP = copy2DArrayToPointer(example4, 3,4);
    print2DArray(tempP, 3, 4);
    delete2Darray(tempP, 3);
    cout <<"\n wybierz przyklad : ";
    cin >> chooice;
    if(chooice == 1) {
        float **ptr = copy2DArrayToPointer(example1,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 2){
        float **ptr = copy2DArrayToPointer(example2,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 3){
        float **ptr = copy2DArrayToPointer(example3,4,5);
        this->setArray(ptr, 4,5);
    }
    else if(chooice == 4){
        float **ptr = copy2DArrayToPointer(example4,3,4);
        this->setArray(ptr, 3,4);
    }
    else{
        cout << " wybrano zly numer przykladu";
        exit(0);
    }
}



void Gauss::pickMethod(){

    int choice = 0;
    cout << " \n1.Podstawowa elimacja Gaussa\n2.Elminacja z wyborem elementu max" ;
    cout << endl;
    cin >> choice;
    switch(choice){
        case 1:{
            defaultElimination();
            if(isEquationSolvable()){
                 getResultFromRowEchelonForm();
            }

            break;
        }
        case 2:{

            break;
        }
        default : {
            cout << " wybrano zly numer ";
            break;
        }
    }
}
void Gauss::getResultFromRowEchelonForm(){

    int rows = this->rows;
    float **ar = this->array;
    int lastColumn = this->cols -1 ;
    float *result = new float[rows];
    float temp = 0;
    rows--;
    result[rows] = (ar[rows][lastColumn])/(ar[rows][rows]);
    cout << "x"<<rows+1<< "=" << result[rows]<< "\t" ;
    for(int i = rows -1 ;i >= 0 ; i--){ // start od przedostatniego wiersza
        temp = 0 ;
        for(int j = i + 1 ; j <= rows ; j++){
            temp -= result[j]*ar[i][j];
            //cout << "\n i = " << i << " j= " << j;
            //cout << "\n wartosc  = " << temp ;
            //cout << " ostatnia kolumna : " << ar[i][lastColumn];
        }
        temp += ar[i][lastColumn];
        //cout << " temp po dodaniu : " << temp;
        result[i]  = temp / (ar[i][i]);
        cout << "x"<<i+1<< "=" <<result[i] <<  "\t" ;

    }
    delete [] result;



}

float* Gauss::arrayWithCoefficients(int step){
    int rows = this->rows;
    int startingRow = step;
    float *coef = new float[rows];


    cout << "\n tablica wspolczynnikow\n ";
    for(int i = startingRow , j = step - 1; i < rows; i++){
        coef[i] = (this->array[i][j])/(this->array[j][j]);
        cout << coef[i] << " ";
        startingRow++;
    }
    return coef;
}


void Gauss::defaultElimination(){
    int step = 1;
    int rows = this->rows;
    int cols = this->cols;
    int temp = 1;
    while(isElementEqualZero(0,0)){
        if(temp == rows){
            cout << "ukladu ma nieskonczenie wiele rozwiazan";
            exit(15);
        }
        swapRows(this->array, cols, 0, temp);
        print2DArray(this->array,rows,cols);
        temp++;
    }

    float *coefficients  ;
    while(step < rows){
        if(isElementEqualZero(step,step)){
            cout << "\n elemnt na przekatnej = 0, zamiana wierszy  ";
            int temp = step + 1;
            while(temp < rows || isElementEqualZero(step,step)){
                swapRows(this->array,cols, step, temp );
                print2DArray(this->array,rows,cols);
                temp++;
            }
            if(isElementEqualZero(step,step)){
                cout << "element na przekatnej = 0 w kazdym ukladzie wierszy, dana metoda gaussa nie moze byc kontynuowana";
                exit(3);
            }
            }
        cout << "\n\n krok " << step << endl;
        coefficients = arrayWithCoefficients(step);
        for(int i = step ; i < rows ; i++){
            for(int j = step-1; j < cols ;j++){
                if(coefficients[i]){
                    this->array[i][j] -=   (coefficients[i]*this->array[step-1][j]);
                }
                else  {
                        cout << " wspolczynnik dla wiersza nr " << i + 1 << " = 0, wartosci w tym wierszu nie zmienia sie \n";
                        j = cols -1;
                }
            }
        }
        print2DArray(this->array,rows,cols);
        step++;

    }

}

void Gauss::setArray(float ** ar, int r, int c){
        this->array = ar;
        this->rows = r;
        this->cols = c;
    }

bool Gauss::isEquationSolvable(){
    int lastColumn = this->cols - 1;
    int lastRow = this->rows - 1;
    if(this->array[lastRow][lastColumn - 1] == 0 && this->array[lastRow][lastColumn] == 0 ){
        cout << "Uklad rownan ma nieskonczenie wiele rozwiazan ";
        return false;
    }
    else if(this->array[lastRow][lastColumn - 1] == 0 && this->array[lastRow][lastColumn] != 0){
        cout << "Uklad sprzeczny - nie ma zadnego rozwiazania ";
        return false;
    }
    return true;

}

bool Gauss::isElementEqualZero(int i, int j){
    return  fabs(this->array[i][j]) <= this->numberCloseToZero;
}
