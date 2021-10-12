/*
       54
      /  \
    31    65
    /\   / \
  29 43 59 78
 /   /
10  36
 \
  20
*/
#include<iostream>
using namespace std;
struct NODE
{
    int data;
    NODE *pLeft;
    NODE *pRight;
};

void constructTree(NODE* &T);
NODE *constructNode(int x);
void addNode(NODE* &T, NODE *newNode);
void input(NODE* &T);
void travelNLR(NODE *T);
void travelLNR(NODE *T);
void travelLRN(NODE *T);
int countLeaf(NODE *T);
int max(int a, int b);
int min(int a, int b);
int highTree(NODE *T);
int minHighTree(NODE *T);
NODE *searchNode(NODE *T, int x);

int main()
{
    NODE *T;
    constructTree(T);
    cout<<"THU TU NHAP THEO DE BAI:  54, 31, 43, 29, 65, 10, 20, 36, 78, 59\n";
    for (int i = 1; i<=10; i++)
    {
        input(T);
    }
    cout<<"Duyet truoc (NLR): ";
    travelNLR(T);
    cout<<"\nDuyet giua (LNR): ";
    travelLNR(T);
    cout<<"\nDuyet sau (LRN): ";
    travelLRN(T);
    cout<<"\nLeaf node: "<<countLeaf(T);
    cout<<"\nDo sau lon nhat cua cay (chieu cao): "<<highTree(T);
    cout<<"\nDo sau nho nhat cua cay: "<<minHighTree(T);
    int x;
    cout<<"\nNhap phan tu can tim kiem: ";
    cin>>x;
    NODE *pSearch = searchNode(T, x);
    if (pSearch == NULL)
        cout<<"Khong ton tai";
    else
        cout<<"Co ton tai";
    return 0;
}
void constructTree(NODE* &T)
{
    T = NULL;
}
NODE *constructNode(int x)
{
    NODE *newNode = new NODE;
    newNode->data = x;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}
void addNode(NODE* &T, NODE *newNode) // nếu không có đệ quy xảy ra thì lúc này xem như nhập phần tử đầu tiên (ROOT), T lần đó sẽ luôn chỉ vào gốc cây chính, mọi đệ quy sau T hiểu là root các cây con 
{
    if(T == NULL)
    {
        T = newNode;
    }
    else
    {
        if(newNode->data<T->data)
        {
            addNode(T->pLeft, newNode);
        }
        else if(newNode->data>T->data) // khong co truong hop bang nhau trong binary tree
        {
            addNode(T->pRight, newNode);
        }
    }
}
void input(NODE* &T)
{
    int x;
    cout<<"HAY NHAP 1 SO NGUYEN: ";
    cin>>x;
    NODE *newNode = constructNode(x);
    addNode(T, newNode);
}
void travelNLR(NODE *T)
{
    if(T != NULL)
    {
        cout<<T->data<<" ";
        travelNLR(T->pLeft);
        travelNLR(T->pRight);
    }
}
void travelLNR(NODE *T)
{
    if (T != NULL)
    {
        travelLNR(T->pLeft);
        cout<<T->data<<" ";
        travelLNR(T->pRight);
    }
}
void travelLRN(NODE *T)
{
    if (T != NULL)
    {
        travelLRN(T->pLeft);
        travelLRN(T->pRight);
        cout<<T->data<<" ";
    }
}
int countLeaf(NODE *T)
{
    if (T == NULL)
        return 0;
    else if (T->pLeft == NULL && T->pRight == NULL)
        return 1;
    else
        return countLeaf(T->pLeft) + countLeaf(T->pRight);
}
int max(int a, int b)
{
    return (a > b)?a:b;
}
int min(int a, int b)
{
    return (a < b)?a:b;
}
int highTree(NODE *T)
{
    if (T == NULL)
     return 0;
    int left = highTree(T->pLeft);
    int right = highTree(T->pRight);
    return max(left, right) + 1;
}
int minHighTree(NODE *T)
{
    if (T == NULL)
     return 0;
    int left = minHighTree(T->pLeft);
    int right = minHighTree(T->pRight);
    return min(left, right) + 1;
}
NODE *searchNode(NODE *T, int x)
{
    if (T == NULL)
        return NULL;
    else if (x>T->data)
        return searchNode(T->pRight, x);
    else if (x<T->data)
        return searchNode(T->pLeft, x);
    return T;
}