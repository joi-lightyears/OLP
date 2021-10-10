#include <iostream>
using namespace std;
// cau truc 1 node
struct NODE
{
    int data;
    NODE *pNext;
};
// cau truc cua danh sach
struct QUEUE
{
    NODE *pHead; // con tro tro toi dia chi dau cua queue
    NODE *pTail; // tro toi cuoi queue

};
//*******(DECLARE FUNCTIONS)**********************
void constructQueue(QUEUE &Q);
NODE *constructNode(int x);
bool QueueIsEmpty(QUEUE Q);
bool Enqueue(QUEUE &Q, NODE *newNode);
bool Dequeue(QUEUE &Q, int x);
bool Top(QUEUE &Q, int &x);
void input(QUEUE &Q);
void output(QUEUE Q);

int main()
{
    QUEUE Q;
    constructQueue(Q);
    input(Q);
    input(Q);
    input(Q);
    input(Q);
    input(Q);
    output(Q);
    int x;
    if(Dequeue(Q, x))
    {
        cout<<"\nSAU KHI DEQUEUE: ";
        output(Q);
    }else
    {
        cout<<"\n DEQUEUE KHONG THANH CONG";
    }
    if(Top(Q, x))
    {
        cout<<"\nPHAN TU DAU QUEUE: ";
        cout<<x;
    }
    return 0;
}
//**********(DEFINE FUNCTIONS)**************
// khoi tao queue
void constructQueue(QUEUE &Q)
{
    Q.pHead = Q.pTail = NULL;
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
// check whether queue is empty or not
bool QueueIsEmpty(QUEUE Q)
{
    return (Q.pHead == NULL)?true:false;
}
// them node moi vao cuoi queue
bool Enqueue(QUEUE &Q, NODE *newNode)
{
    if (newNode == NULL)
        return false;
    if(QueueIsEmpty(Q))
    {
        Q.pHead = Q.pTail = newNode;
    }else
    {
        Q.pTail->pNext = newNode;
        Q.pTail = newNode;
    }
    return true;
}
// lay ra node tren cung cua stack va tra ve du lieu cua no
bool Dequeue(QUEUE &Q, int x)
{
    if(QueueIsEmpty(Q))
    {
        return false; // failed to pop
    }else
    {
        NODE *temp = Q.pHead;
        x = temp->data;
        Q.pHead = Q.pHead->pNext;
        delete temp;
    }
    return true; // successfully pop
}
// xem thong tin cua node tren cung cua stack nhung khong xoa (!= pop)
bool Top(QUEUE &Q, int &x)
{
    if (QueueIsEmpty(Q))
    {
        return false;
    }else
    {
        x = Q.pHead ->data;
    }
    return true;
}
void input(QUEUE &Q)
{
    int x;
    cout<<"NHAP 1 SO NGUYEN: ";
    cin>>x;
    NODE *newNode = constructNode(x);
    Enqueue(Q, newNode);
}
void output(QUEUE Q)
{
    NODE *k = Q.pHead; // co the dung truc tiep S.pTop de control vong lap
    while (k != NULL)
    {
        cout << k->data << " ";
        k = k->pNext;
    }
}