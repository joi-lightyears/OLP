#include <iostream>  // general
#include <windows.h> // to set color
#include <string.h>  // to use string, getline(), find()
#include <iomanip>   // to use: setw
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// cau truc 1 node
struct student
{
    string mssv, name;
    int birth;
    float gpa;
    student *pNext;
};
typedef student NODE;
// cau truc cua danh sach
struct LIST
{
    NODE *pHead;
    NODE *pTail;
};
/////////////(FUNCTION DECLARATIONS)////////////////////////////
void menu(LIST &L);
void actions(int menuOpt, LIST &L);
void constructList(LIST &L);
NODE *constructNode();
void input(LIST &L);
void insertTail(LIST &L, NODE *newNode);
void printList(LIST L);
void searchSV(LIST L);
void insertAfterPos(LIST L, string mssvInsert, NODE *newNode);
void deleteSV(LIST &L, string mssvDel);
///////////(MAIN PROGRAM)//////////////////////////////////////
int main()
{
    LIST L;
    constructList(L);
    menu(L);
    
    return 0;
}
//////////////(FUNCTIONS DEFINITIONS)///////////////////////////
//********(FEATURES MENU)************************
void menu(LIST &L)
{
    SetConsoleTextAttribute(h, 2);
    cout<<"/////////////////////////////////////////////\n";
    cout<<"                   MENU                      \n";
    cout<<"            1. THEM SINH VIEN                \n";
    cout<<"            2. CHEN SINH VIEN                \n";
    cout<<"            3. XOA SINH VIEN                 \n";
    cout<<"            4. HIEN THI DANH SACH            \n";
    cout<<"            5. TIM KIEM SINH VIEN            \n";
    cout<<"            6. EXIT                          \n";
    cout<<"/////////////////////////////////////////////\n";
    SetConsoleTextAttribute(h, 7);
    int menuOpt;
    cout<<"CHON NHIEM VU (1, 2, 3...): ";
    cin>>menuOpt;
    cin.ignore();
    actions(menuOpt, L);
}
void actions(int menuOpt, LIST &L)
{
    switch(menuOpt)
    {
        case 1:
        {
            //******(NHAP DANH SACH SINH VIEN)*******************
            input(L);
            menu(L);
            break;
        }
        case 2:
        {
            //*****(CHEN SINH VIEN SAU MSSV CHO TRUOC)***********
            string mssvInsert;
            SetConsoleTextAttribute(h, 2);
            cout << "\nNHAP THONG TIN SINH VIEN CAN CHEN\n";
            SetConsoleTextAttribute(h, 7);
            NODE *newNode = constructNode();
            SetConsoleTextAttribute(h, 2);
            cout << "BAN MUON CHEN SAU MA SO SINH VIEN NAO: ";
            cin >> mssvInsert;
            SetConsoleTextAttribute(h, 7);
            cin.ignore();
            insertAfterPos(L, mssvInsert, newNode);
            SetConsoleTextAttribute(h, 2);
            cout<<"DANH SACH SAU KHI INSERT\n";
            SetConsoleTextAttribute(h, 7);
            printList(L);
            menu(L);
            break;
        }
        case 3:
        {
            //*****(XOA SINH VIEN)*****************************
            string mssvDel;
            SetConsoleTextAttribute(h, 2);
            cout<<"\nNHAP MA SO SINH VIEN CAN XOA: ";
            cin>>mssvDel;
            SetConsoleTextAttribute(h, 7);
            deleteSV(L, mssvDel);
            SetConsoleTextAttribute(h, 2);
            cout<<"\nDANH SACH SAU KHI DELETE\n";
            SetConsoleTextAttribute(h, 7);
            printList(L);
            menu(L);
            break;
        }
        case 4:
        {
            //******(HIEN THI DANH SACH)********************
            SetConsoleTextAttribute(h, 2);
            cout<<"DANH SACH SAU KHI NHAP\n";
            SetConsoleTextAttribute(h, 7);
            printList(L);
            menu(L);
            break;
        }
        case 5:
        {
            //*****(TIM KIEM THONG TIN SINH VIEN)****************
            searchSV(L);
            menu(L);
            break;
        }
        case 6:
        {
            exit(0);
        }
        default:
        {
            cout<<"<<--INVALID OPTION-->>";
        }
    }
}
// khoi tao danh sach lien ket
void constructList(LIST &L)
{
    L.pHead = NULL;
    L.pTail = NULL;
}
// khoi tao mot node chua student record vua nhap o ham input()
NODE *constructNode()
{
    NODE *newNode = new NODE; // cap phat vung nho cho cai node moi vua tao (newNode)
    cout << "NHAP MA SO SINH VIEN: ";
    // cin.ignore();
    getline(cin, newNode->mssv);
    cout << "NHAP HO VA TEN SINH VIEN: ";
    // cin.ignore();
    getline(cin, newNode->name);
    cout << "NHAP NAM SINH CUA SINH VIEN: ";
    cin >> newNode->birth;
    cout << "NHAP DIEM TRUNG BINH CUA SINH VIEN: ";
    cin >> newNode->gpa;
    cin.ignore();
    newNode->pNext = NULL;
    return newNode;
}
// input student record
void input(LIST &L)
{
    char choose = 'Y';
    NODE *newNode;
    do
    {
        newNode = constructNode();
        insertTail(L, newNode);
        SetConsoleTextAttribute(h, 2);
        cout << "BAN CO MUON NHAP THEM SINH VIEN KHONG (Y/N): ";
        cin >> choose;
        SetConsoleTextAttribute(h, 7);
        cout<<endl;
        cin.ignore();
    } while (choose == 'y' || choose == 'Y');
}
// them mot node moi vao cuoi danh sach
void insertTail(LIST &L, NODE *newNode)
{
    if (L.pHead == NULL)
        L.pHead = L.pTail = newNode;
    else
    {
        L.pTail->pNext = newNode;
        L.pTail = newNode;
    }
}
void printList(LIST L)
{
    NODE *k = L.pHead; // co the dung truc tiep L.pHead de control vong lap
    while (k != NULL)
    {

        cout << k->mssv << " " << k->name << " " << k->birth << " " << k->gpa << endl;
        k = k->pNext;
    }
}
void searchSV(LIST L)
{
    string findName;
    string::size_type idx;
    SetConsoleTextAttribute(h, 2);
    cout << "\nHAY NHAP HO VA TEN SINH VIEN CAN TIM: ";
    getline(cin, findName);
    SetConsoleTextAttribute(h, 7);
    NODE *k = L.pHead;
    while (k != NULL)
    {
        idx = k->name.find(findName);
        if (idx < k->name.length() && idx >= 0)
        {
            cout << k->mssv << " " << k->name << " " << k->birth << " " << k->gpa << endl;
        }
        k = k->pNext;
    }
}
void insertAfterPos(LIST L, string mssvInsert, NODE *newNode)
{
    NODE *k = L.pHead;
    while (k != NULL && k->mssv != mssvInsert)
    {
        k = k->pNext;
    }
    if (k != NULL)
    {
        newNode->pNext = k->pNext;
        k->pNext = newNode;
    }
}

void deleteSV(LIST &L, string mssvDel)
{
    NODE *k = L.pHead;
    if (k->mssv==mssvDel)
    {
        NODE *temp=L.pHead;
        L.pHead=L.pHead->pNext;
        delete temp;
    }else
    {
        while (k != NULL && k->pNext->mssv != mssvDel)
        {
            k = k->pNext;
        }
        if (k!= NULL)
        {
            NODE *temp = k->pNext;
            k->pNext=k->pNext->pNext;
            delete temp; //giai phong bo nho
        }
    }
}