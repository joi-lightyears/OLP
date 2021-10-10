#include <iostream>
#include <windows.h>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
// cau truc 1 node
struct NODE
{
    int data;
    NODE *pNext;
    NODE *pPrev;
};
// cau truc cua danh sach
struct LIST
{
    NODE *pHead;
    NODE *pTail;
};
//******(DECLARE FUNCTIONS)**************
void constructList(LIST &L);
NODE *constructNode(int x);
void insertHead(LIST &L, NODE *newNode);
void insertTail(LIST &L, NODE *newNode);
void deleteHead(LIST &L);
void deleteTail(LIST &L);
void insertAfterPos(LIST L, int pos, NODE *newNode);
void printList(LIST L);

int main()
{
    LIST L;
    constructList(L);
    NODE *newNode = constructNode(1);
    insertHead(L, newNode);
    newNode = constructNode(2);
    insertTail(L, newNode);
    newNode = constructNode(3);
    insertTail(L, newNode);
    printList(L);
    //***********(INSERT AFTER A POSITION)*******************************
    SetConsoleTextAttribute(h, 2);
    cout << "\nINSERT 10 AFTER POSITION 2\n";
    SetConsoleTextAttribute(h, 7);
    newNode = constructNode(10);
    insertAfterPos(L, 2, newNode); // insert newNode after position 2
    printList(L);
    //***********(DELETE FIRST/LAST NODE)********************************
    SetConsoleTextAttribute(h, 2);
    cout << "\nDELETE HEAD AND TAIL:\n";
    SetConsoleTextAttribute(h, 7);
    deleteHead(L);
    deleteTail(L);
    printList(L);

    return 0;
}
//******(DEFINE FUNCTIONS)******************
// khoi tao danh sach lien ket
void constructList(LIST &L)
{
    L.pHead = NULL;
    L.pTail = NULL;
}
// khoi tao mot node
NODE *constructNode(int x)
{
    NODE *newNode = new NODE; // cap phat vung nho cho cai node moi vua tao (newNode)
    newNode->data = x;
    newNode->pNext = NULL;
    newNode->pPrev=NULL;
    return newNode;
}
// them node moi vao dau danh sach
void insertHead(LIST &L, NODE *newNode)
{
    if (L.pHead == NULL) // case: chua co node nao trong list
        L.pHead = L.pTail = newNode;
    else
    {
        newNode->pNext=L.pHead;
        L.pHead->pPrev=newNode;
        L.pHead=newNode;
    }
    L.pHead->pPrev=L.pTail;
    L.pTail->pNext=L.pHead;
}
// them mot node moi vao cuoi danh sach
void insertTail(LIST &L, NODE *newNode)
{
    if (L.pHead == NULL)
        L.pHead = L.pTail = newNode;
    else
    {
        newNode->pPrev=L.pTail;
        L.pTail->pNext=newNode;
        L.pTail=newNode;
    }
    L.pHead->pPrev=L.pTail;
    L.pTail->pNext=L.pHead;
}

void deleteHead(LIST &L)
{
    if (L.pHead != NULL)
    {
        NODE *temp = L.pHead;
        L.pHead = L.pHead->pNext;
        // L.pHead->pPrev=NULL;
        delete temp; // giai phong bo nho
    }
    L.pHead->pPrev=L.pTail;
    L.pTail->pNext=L.pHead;
}
void deleteTail(LIST &L)
{
    if (L.pTail != NULL)
    {
        // NODE *k = L.pHead;
        // while (k->pNext != L.pTail)
        //     k = k->pNext;
        // NODE *temp = L.pTail;
        // L.pTail = k;
        // k->pNext = NULL;
        NODE *temp=L.pTail;
        L.pTail=L.pTail->pPrev;
        // L.pTail->pNext=NULL;
        delete temp; //giai phong bo nho
    }
    L.pHead->pPrev=L.pTail;
    L.pTail->pNext=L.pHead;
}
void insertAfterPos(LIST L, int pos, NODE *newNode)
{
    NODE *k = L.pHead;
    int i = 1;
    while (k != NULL && i != pos)
    {
        k = k->pNext;
        i++;
    }
    if (k != NULL)
    {
        newNode->pNext = k->pNext;
        k->pNext->pPrev=newNode;
        newNode->pPrev=k;
        k->pNext = newNode;
    }
}

void printList(LIST L)
{
    NODE *k = L.pHead; // co the dung truc tiep L.pHead de control vong lap
    do
    {
        cout << k->data << " ";
        k = k->pNext;
    }while (k != L.pHead);
}