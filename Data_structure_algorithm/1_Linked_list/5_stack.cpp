#include <iostream>
using namespace std;
// cau truc 1 node
struct NODE
{
    int data;
    NODE *pNext;
};
// cau truc cua danh sach
struct STACK
{
    NODE *pTop; // con tro tro toi dia chi tren dau cua stack
};
//*******(DECLARE FUNCTIONS)**********************
void constructStack(STACK &S);
NODE *constructNode(int x);
bool StackIsEmpty(STACK S);

void input(STACK &S);
void output(STACK S);
bool Push(STACK &S, NODE *newNode);
bool Pop(STACK &S, int x);
bool Top(STACK &S, int &x);

int main()
{
    STACK S;
    constructStack(S);
    input(S);
    input(S);
    input(S);
    output(S);
    int x;
    if(Pop(S, x))
    {
        cout<<"\nPop thanh cong\n";
        cout<<"Danh sach sau khi Pop: ";
        output(S);
    }else
    {
        cout<<"\nPop khong thanh cong";
    }
    if(Top(S, x))
    {
        cout<<"\nPhan tu dau stack: ";cout<<x;
    }else
    {
        cout<<"\nStack rong";
    }
    return 0;
}
//**********(DEFINE FUNCTIONS)**************
// khoi tao stack
void constructStack(STACK &S)
{
    S.pTop = NULL;
}
// khoi tao mot node
NODE *constructNode(int x)
{
    NODE *newNode = new NODE; // cap phat vung nho cho cai node moi vua tao (newNode)
    if (newNode == NULL)
    {
        cout<<"KHONG DU BO NHO DE CAP PHAT CHO NEWNODE";
        return NULL;
    }
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}
// check whether stack is empty or not
bool StackIsEmpty(STACK S)
{
    return (S.pTop == NULL)?true:false;
}
// them node moi vao dau stack
bool Push(STACK &S, NODE *newNode)
{
    if (newNode == NULL)
        return false; // failed to push 
    if(StackIsEmpty(S))
    {
        S.pTop = newNode;
    }else
    {
        newNode->pNext = S.pTop;
        S.pTop = newNode;
    }
    return true; //successfully push
}
// lay ra node tren cung cua stack va tra ve du lieu cua no
bool Pop(STACK &S, int x)
{
    if(StackIsEmpty(S))
    {
        return false; // failed to pop
    }else
    {
        NODE *temp = S.pTop;
        x = temp->data;
        S.pTop = S.pTop->pNext;
        delete temp;
    }
    return true; // successfully pop
}
// xem thong tin cua node tren cung cua stack nhung khong xoa (!= pop)
bool Top(STACK &S, int &x)
{
    if (StackIsEmpty(S))
    {
        return false;
    }else
    {
        x = S.pTop->data;
    }
    return true;
}
void input(STACK &S)
{
    int x;
    cout<<"NHAP 1 SO NGUYEN: ";
    cin>>x;
    NODE *newNode = constructNode(x);
    Push(S, newNode);
}
void output(STACK S)
{
    NODE *k = S.pTop; // co the dung truc tiep S.pTop de control vong lap
    while (k != NULL)
    {
        cout << k->data << " ";
        k = k->pNext;
    }
}