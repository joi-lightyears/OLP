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
    int bal = 0;
    NODE *pLeft;
    NODE *pRight;
};

void constructTree(NODE* &T);
NODE *constructNode(int x);
NODE *addNode(NODE* &T, NODE *newNode);
void input(NODE* &T);
void travelNLR(NODE *T);

int max(int a, int b);
int min(int a, int b);
int highTree(NODE *T);
int minHighTree(NODE *T);


int main()
{
    NODE *T;
    constructTree(T);
    cout<<"THU TU NHAP THEO DE BAI:  54, 31, 43, 29, 65, 10, 20, 36, 78, 59\n";
    for (int i = 1; i<=10; i++)
    {
        input(T);
    }
    
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
    newNode->bal = 0; // leaf
    return newNode;
}
NODE *addNode(NODE* &T, NODE *newNode) // nếu không có đệ quy xảy ra thì lúc này xem như nhập phần tử đầu tiên (ROOT), T lần đó sẽ luôn chỉ vào gốc cây chính, mọi đệ quy sau T hiểu là root các cây con 
{
    if(T == NULL)
    {
        return newNode;
    }
    else
    {
        if(newNode->data<T->data)
        {
            T->pLeft = addNode(T->pLeft, newNode);
        }
        else if(newNode->data>T->data) // khong co truong hop bang nhau trong binary tree
        {
            T->pRight = addNode(T->pRight, newNode);
        }
    }
    T->bal = highTree(T->pRight) - highTree(T->pLeft);
    // Left left
    if (T->bal < -1 && newNode->data <T->pLeft )
        rotate_LL(T);
    // Left right
    if (T->bal < -1 && newNode->data > T->pRight)
        rotate_LR(T);
    // Right right
    if (T->bal > 1 && newNode->data > T->pRight)
        rotate_RR(T);
    // Right left
    if (T->bal > 1 && newNode->data < T->pRight)
        rotate_RL(T);
    
    return T;
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
int max(int a, int b)
{
    return (a > b)?a:b;
}
int highTree(NODE *T)
{
    if (T == NULL)
     return 0;
    int left = highTree(T->pLeft);
    int right = highTree(T->pRight);
    return max(left, right) + 1;
}
void rotate_LL(NODE* &T)
{	NODE *T1 = T->pLeft;
	T->pLeft = T1->pRight; T1->pRight=T;
	switch(T1->bal)
	{
		case -1:
        {
            T->bal =0;
            T1->bal = 0;
            break;
        }
		case 0:
        {
            T->bal=0;

			break;
        }
	}
	T1->bal=0;
	T=T1;
}
