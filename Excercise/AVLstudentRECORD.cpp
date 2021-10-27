
#include <iostream>
#include<string>
#include<iomanip> //setw()
using namespace std;
struct NODE
{
    string mssv, name, birth;
    float gpa;
    NODE *pLeft;
    NODE *pRight;
};
void menu(NODE *&T);
void actions(int menuOpt, NODE *&T);
void constructTree(NODE *&T);
NODE *constructNode(int x);
NODE *addNode(NODE *T, NODE *newNode);
void input(NODE *&T);
void travelNLR(NODE *T);

int max(int a, int b);
int highTree(NODE *T);
void rotate_LL(NODE *&T);
void rotate_LR(NODE *&T);
void rotate_RR(NODE *&T);
void rotate_RL(NODE *&T);

int main()
{
    NODE *T;
    constructTree(T);
    menu(T);
    
    return 0;
}
void menu(NODE *&T)
{
    cout<<"/////////////////////////////////////////////\n";
    cout<<"                   MENU                      \n";
    cout<<"            1. THEM SINH VIEN                \n";
    cout<<"            2. HIEN THI DANH SACH            \n";
    cout<<"/////////////////////////////////////////////\n";
    int menuOpt;
    cout<<"CHON NHIEM VU (1, 2,...): ";
    cin>>menuOpt;
    cin.ignore();
    actions(menuOpt, T);
}
void actions(int menuOpt, NODE *&T)
{
    switch(menuOpt)
    {
        case 1:
        {
            input(T);
            menu(T);
            break;
        }
        case 2:
        {
            cout<<"DANH SACH\n\n";
            cout<<setw(15)<<left<<"MSSV";
            cout<<setw(30)<<left<<"HO VA TEN";
            cout<<setw(20)<<left<<"DATE OF BIRTH";
            cout<<setw(10)<<left<<"GPA"<<endl;
            travelNLR(T);
            system("pause");
            menu(T);
        }
    }
}
// Khoi tao node goc cua tree
void constructTree(NODE *&T)
{
    T = NULL;
}
// Tao mot node chua du lieu vua nhap vao
NODE *constructNode()
{
    NODE *newNode = new NODE;
    cout<<"NHAP MA SO SINH VIEN: ";
    cin>>newNode->mssv;
    cout<<"NHAP HO VA TEN SINH VIEN: ";
    cin.ignore();
    getline(cin, newNode->name);
    cout<<"NHAP NGAY THANG NAM SINH (dd/mm/yy): ";
    getline(cin, newNode->birth);
    cout<<"NHAP DIEM GPA: ";
    cin>>newNode->gpa;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}
// them node vua tao vao cay va dieu chinh sao cho cay luon can bang
NODE *addNode(NODE *T, NODE *newNode)
{
    if (T == NULL)
    {
        return newNode;
    }
    else // neu tai node T da co data thi xet qua 2 ben left right cua node T do
    {
        if (newNode->gpa < T->gpa)
        {
            T->pLeft = addNode(T->pLeft, newNode);
        }
        else if (newNode->gpa > T->gpa) // khong co truong hop bang nhau trong binary tree
        {
            T->pRight = addNode(T->pRight, newNode);
        }
    }
    int bal = highTree(T->pRight) - highTree(T->pLeft); // bal = -1 left | 0 balance | 1 right
    // Left left
    if (bal < -1 && newNode->gpa < T->pLeft->gpa)
    {
        rotate_LL(T);
    }
    else if (bal < -1 && newNode->gpa > T->pLeft->gpa) // Left right
    {
        rotate_LR(T);
    }
    else if (bal > 1 && newNode->gpa > T->pRight->gpa) // Right right
    {
        rotate_RR(T);
    }
    else if (bal > 1 && newNode->gpa < T->pRight->gpa) // Right left
    {
        rotate_RL(T);
    }
    return T;
}
void input(NODE *&T)
{
    char choose = 'Y';
    NODE *newNode;
    do
    {
        newNode = constructNode();
        T = addNode(T, newNode);
        cout<<"BAN CO MUON NHA THEM SINH VIEN KHONG? (Y/N): ";
        cin>>choose;
        cin.ignore();
    }while(choose=='y'|| choose=='Y');
}
void travelNLR(NODE *T)
{
    if (T != NULL)
    {
        cout<<setw(15)<<left<<T->mssv;
        cout<<setw(30)<<left<<T->name;
        cout<<setw(20)<<left<<T->birth;
        cout<<setw(10)<<left<<T->gpa<<endl;
        travelNLR(T->pLeft);
        travelNLR(T->pRight);
    }
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int highTree(NODE *T)
{
    if (T == NULL)
        return 0;
    int left = highTree(T->pLeft);
    int right = highTree(T->pRight);
    return max(left, right) + 1;
}
// Left left
void rotate_LL(NODE *&T) // su dung & o day de T trong ham addNode cung thay doi
{
    NODE *T1 = T->pLeft;
    T->pLeft = T1->pRight;
    T1->pRight = T;
    T = T1;
    /*
         T                    T1 
        / \                 /   \
       T1  R      =>      L1     T
      / \                / \    /\ 
    L1  R1             x   y   R1 R
    /\
   x  y
   (x/y) la  VI TRI node da duoc them vao o ham addNode()
   x y o day khong the xuat hien dong thoi ma nos chi dai dien cho vi tri node duoc them
   vi khi node duoc them o vi tri x hoac y thi khi do ct se tu can bang lai va ta se cos 1 hinhf dang tree khac
  */
}
void rotate_LR(NODE *&T)
{
    NODE *T1 = T->pLeft;
    NODE *T2 = T1->pRight;
    T->pLeft = T2;
    T1->pRight = T2->pLeft;
    T2->pLeft = T1;
    rotate_LL(T);
    /*
         T               T            T2
        / \            /   \         /  \ 
      T1   R          T2    R      T1    T
     / \      =>    /  \      =>  / \   / \
   L1   T2         T1   y       L1  x  y  R
       / \        / \
      x  y      L1   x
    chuyen dang left right thanh left left roi goi lai ham rotate_LL() thuc hien lai T binh thuong
    */
}
void rotate_RR(NODE *&T)
{
    NODE *T1 = T->pRight;
    T->pRight = T1->pLeft;
    T1->pLeft = T;
    T = T1;
}
void rotate_RL(NODE *&T)
{
    NODE *T1 = T->pRight;
    NODE *T2 = T1->pLeft;
    T->pRight = T2;
    T1->pLeft = T2->pRight;
    T2->pRight = T1;
    rotate_RR(T);
}

// copyrighted by 20H1120201_NguyenThanhDat