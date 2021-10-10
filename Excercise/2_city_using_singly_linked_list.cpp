#include <iostream>  // general
#include <windows.h> // to set color
#include <string.h>  // to use string, getline(), find()
#include <iomanip>   // to use: setw
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// cau truc 1 node
struct city
{
    string cityName;
    double area, citizen;
    city *pNext;
};
typedef city NODE;
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
void searchCity(LIST L);
void deleteCity(LIST &L);
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
    cout<<"         1. THEM THANH PHO                   \n";
    cout<<"         2. HIEN THI DANH SACH               \n";
    cout<<"         3. TIM THANH PHO                    \n";
    cout<<"         4. XOA THANH PHO HA NOI             \n";
    cout<<"         5. SAP XEP DAN SO                   \n";
    cout<<"/////////////////////////////////////////////\n";
    SetConsoleTextAttribute(h, 7);
    int menuOpt;
    cout<<"CHON NHIEM VU (1, 2, 3): ";
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
            //******(NHAP DANH SACH THANH PHO)*******************
            input(L);
            menu(L);
            break;
        }
        case 2:
        {
            //******(HIEN THI DANH SACH)********************
            SetConsoleTextAttribute(h, 2);
            cout<<"DANH SACH SAU KHI NHAP\n";
            SetConsoleTextAttribute(h, 7);
            printList(L);
            menu(L);
            break;
        }
        case 3:
        {
            //*****(TIM KIEM THONG TIN THANH PHO)****************
            searchCity(L);
            menu(L);
            break;
        }
        case 4:
        {
            deleteCity(L);
            cout<<"DANH SACH THANH PHO SAU KHI DA XOA THANH PHO HA NOI\n";
            printList(L);
            menu(L);
            break;
        }
        default:
        {
            cout<<"<<--INVALID OPTION-->>";
            menu(L);
        }
    }
}
// khoi tao danh sach lien ket
void constructList(LIST &L)
{
    L.pHead = NULL;
    L.pTail = NULL;
}
// khoi tao mot node chua city record vua nhap o ham input()
NODE *constructNode()
{
    NODE *newNode = new NODE; // cap phat vung nho cho cai node moi vua tao (newNode)
    cout << "NHAP TEN THANH PHO: ";
    // cin.ignore();
    getline(cin, newNode->cityName);
    cout << "NHAP DIEN TICH THANH PHO: ";
    // cin.ignore();
    cin>>newNode->area;
    cout << "NHAP DAN SO: ";
    cin >> newNode->citizen;
    cin.ignore();
    newNode->pNext = NULL;
    return newNode;
}
// input city record
void input(LIST &L)
{
    char choose = 'Y';
    NODE *newNode;
    do
    {
        newNode = constructNode();
        insertTail(L, newNode);
        SetConsoleTextAttribute(h, 2);
        cout << "BAN CO MUON NHAP THEM THANH PHO KHONG (Y/N): ";
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

        cout << k->cityName << " " << k->area << " " << k->citizen << endl;
        k = k->pNext;
    }
}
void searchCity(LIST L)
{
    string findCityName;
    string::size_type idx;
    SetConsoleTextAttribute(h, 2);
    cout << "\nHAY NHAP TEN THANH PHO CAN TIM: ";
    getline(cin, findCityName);
    SetConsoleTextAttribute(h, 7);
    NODE *k = L.pHead;
    while (k != NULL)
    {
        idx = k->cityName.find(findCityName);
        if (idx < k->cityName.length() && idx >= 0)
        {
            cout << k->cityName << " " << k->area << " " << k->citizen << endl;
        }
        k = k->pNext;
    }
}

void deleteCity(LIST &L)
{
    NODE *k = L.pHead;
    if (k->cityName=="Ha Noi")
    {
        NODE *temp=L.pHead;
        L.pHead=L.pHead->pNext;
        delete temp;
    }else
    {
        while (k != NULL && k->pNext->cityName != "Ha Noi")
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