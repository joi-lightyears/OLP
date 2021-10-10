#include <windows.h>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
struct TEST{
    void tPASSED(){
        SetConsoleTextAttribute(h,7|BACKGROUND_GREEN);
        cout<<"[ PASSED ]";
        SetConsoleTextAttribute(h,7|0);
    };
    void tFAILED(){
        SetConsoleTextAttribute(h,7|BACKGROUND_RED);
        cout<<"[ FAILED ]";
        SetConsoleTextAttribute(h,7|0);
    };
}T;
class ptBac3
{
    float a, b, c, x1, x2, delta, real, imaginary, flag; //real va imaginary de tinh so thuc neu delta < 0
public:
    void input();
    void output();
    void calculateDelta();
    void checkDelta();
    //FUNCTION FOR TEST
    void inputTEST(float A, float B, float C);
    void checkTEST();
};
void ptBac3::input()
{
    cout << "Phuong trinh ax^2 + bx + c = 0\n";
    cout << "Nhap a: "; cin >> a;
    cout << "Nhap b: "; cin >> b;
    cout << "Nhap c: "; cin >> c;
}
void ptBac3::output()
{
    if (flag == 1)
    {
        cout << "Nghiem la so thuc va bang nhau: "; cout << "x1 = x2 = " <<x1;
    }else if(flag == 2)
    {
        cout << "2 nghiem la so thuc va khac nhau: " << endl;
        cout << "x1 = " << x1 << "; ";
        cout << "x2 = " << x2 << endl;
    }else
    {
        cout << "2 nghiem la so phuc: ";
        cout << "\nx1 = " << real << "+" << imaginary << "i" << endl;
        cout << "x2 = " << real << "-" << imaginary << "i" << endl;
    }
}
void ptBac3::calculateDelta()
{
    delta = b * b - 4 * a * c;
}
void ptBac3::checkDelta()
{
    flag = 0;
    if (delta == 0)
    {
        x1= roundf(-b / (2 * a)*1000)/1000;
        flag = 1;
    }
    else if (delta > 0)
    {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        // lam tron den so thap phan thu 3
        x1 = roundf(x1*1000)/1000;
        x2 = roundf(x2*1000)/1000;
        flag = 2;
    }
    else
    {
        real = -b / (2 * a);
        real = roundf(real*1000)/1000; // lam tron den so thap phan thu 3
        imaginary = sqrt(-delta) / (2 * a);
        imaginary = roundf(imaginary*1000)/1000; // lam tron den so thap phan thu 3
    }
}

// TEST SECTION kiem tra cac truong hop khac nhau
void ptBac3::inputTEST(float A, float B, float C)
{
    a=A;b=B;c=C;
}

void ptBac3::checkTEST()
{
    //TEST CASE 1
    if (delta<0)
    {
        float realExpect = -0.25;
        float imaginaryExpect = 0.52;
        if(real == realExpect&&imaginary==imaginaryExpect)
        {
            T.tPASSED();
        }else{
            T.tFAILED();
        }
    }else if(delta==0)
    {
        float rootExpect = -1;
        if (rootExpect==x1)
        {
            T.tPASSED();
        }else
        {
            T.tFAILED();
        }
    }else{
        float expectX1= -0.219, expectX2=-2.281;
        if(expectX1==x1&&expectX2==x2)
        {
            T.tPASSED();
        }else{
            T.tFAILED();
        }
    }
}
int main()
{
    ptBac3 solve;
    
    solve.input();
    solve.calculateDelta();
    cout << endl;
    solve.checkDelta();
    solve.output();
    
    //TEST CASES
    /*
    SetConsoleTextAttribute(h,2);
    cout<<"TEST CASES================================================\n";
    SetConsoleTextAttribute(h,7);
    solve.inputTEST(6,3,2); // so phuc
    solve.calculateDelta();
    cout << endl;
    solve.checkDelta();
    solve.checkTEST();
    solve.inputTEST(1,2,1);// nghiem kep
    solve.calculateDelta();
    cout << endl;
    solve.checkDelta();
    solve.checkTEST();
    solve.inputTEST(2,5,1);// nghiem thuc
    solve.calculateDelta();
    cout << endl;
    solve.checkDelta();
    solve.checkTEST();
    */
    
    return 0;
}
