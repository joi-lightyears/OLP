
#include <iostream>
using namespace std;
struct NODE
{
    int data;
    NODE *pLeft;
    NODE *pRight;
};

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
    cout << "THU TU NHAP THEO DE BAI:  50 20 30 10 -5 7 15 35 57 65 55 -1\n";
    for (int i = 1; i <= 12; i++)
    {
        input(T);
    }
    travelNLR(T);
    return 0;
}
// Khoi tao node goc cua tree
void constructTree(NODE *&T)
{
    T = NULL;
}
// Tao mot node chua du lieu vua nhap vao
NODE *constructNode(int x)
{
    NODE *newNode = new NODE;
    newNode->data = x;
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
        if (newNode->data < T->data)
        {
            T->pLeft = addNode(T->pLeft, newNode);
        }
        else if (newNode->data > T->data) // khong co truong hop bang nhau trong binary tree
        {
            T->pRight = addNode(T->pRight, newNode);
        }
    }
    // sau khi co duoc 2 node left right phia tren
    // ta tinh balance bang cach tinh do cao max cua moi node do bang hamf highTree()
    // sau do lay do cao max ben node phai tru di do cao max ben node trai
    // o day co 1 nhuoc diem la moi lan de quy se phai tinh chieu cao
    // cua cay o lan de quy do, ma tinh lai chieu cao thi phai de quy ham highTree() nhieu lan
    // nhu vay de ct nhanh hon thi nen luu tri so balance hoac tri so height chieu cao cua moi goc (T)
    // o day nen su dung height vi no de hinh dung va code hon la luu tri so balance
    int bal = highTree(T->pRight) - highTree(T->pLeft); // bal = -1 left | 0 balance | 1 right
    // Left left
    if (bal < -1 && newNode->data < T->pLeft->data)
    {
        rotate_LL(T);
    }else if (bal < -1 && newNode->data > T->pLeft->data) // Left right
    {
        rotate_LR(T);
    }else if (bal > 1 && newNode->data > T->pRight->data) // Right right
    {
        rotate_RR(T);
    }else if (bal > 1 && newNode->data < T->pRight->data) // Right left
    {
        rotate_RL(T);
    }
    // sau khi xay ra rotate hoac khong xay ra rotate thi ta tra ve node do (chinh la T)
    // T se tra ve T o ham input (tuc la node goc chinh cua cay) khi o de quy lan cuoi
    // T se tra ve T->pLeft hoac T->pRight o ham addNode() khi chua phai la lan de quy cuoi (tuc la no se tra ve node goc cua cay con)
    return T;
}
void input(NODE *&T)
{
    int x;
    cout << "HAY NHAP 1 SO NGUYEN: ";
    cin >> x;
    NODE *newNode = constructNode(x);
    T = addNode(T, newNode);
}
void travelNLR(NODE *T)
{
    if (T != NULL)
    {
        cout << T->data << " ";
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