/*
Ket qua cay AVL duoc tao theo de bai
            17
         /      \
      7           23
    /   \        / \
  3      12    21   25
 /\     / \           \
1  5   9  15           27
a. Tạo cây AVL từ dãy A. Cho biết số phép so sánh cần thực hiện để tìm phần tử 21 trên cây AVL vừa tạo.
>> Lý thuyết: số phép ss cần thực hiện là 3  (ss với 17, với 23, với 21)
>> Kiểm chứng qua chạy chương trình: số lần ss là 3 (thuật toán dùng ở đây chỉ sử dụng 2 phép so sánh if
nếu phần tử đó tồn tại, vì trường hợp == ta trả về luôn node đó, nhưng ở đây ngầm hiểu nó có so sánh == nếu ta
chạy ct)

b. Chương trình cho câu b đã tạo ở file BST.cpp, kết quả cho ta thấy số lần so sánh để tìm ra node có key là 21
là 9.

c. Sở dĩ cây BST có phép ss nhiều hơn là vì ở cây BST node đầu tiên có key là 1 và các node sau theo thứ tự luôn có key lớn hơn
key của node trước nên thành ra nó tạo ra một danh sách không khác gì mấy linked list nên khi duyệt thì nó duyệt tuần
tự như ở linked list, trường hợp này nó chỉ dùng duy nhất một phép so sánh nên không mang lại hiệu quả như ở cây AVL

d. Đếm số node lá trên cây
Lý thuyết: có 6 node leaf
Kiểm chứng hàm đếm node leaf khi chạy ct: 6

f. Chiều cao của cây
Lý thuyết: 4
Kiểm chứng ct: 4

g. Đếm số node có bậc 1,2
Lý thuyết: Bậc 1: 1 | Bậc 2: 5
Kiểm chứng ct: Bậc 1: 1 | Bậc 2: 5

h. Tính tổng các phần tử
Lý thuyết: 165
Kiểm chứng ct: 165


*/
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
NODE *searchNode(NODE *T, int x, int &count);
int countLeaf(NODE *T);
int countNODE1(NODE *T);
int countNODE2(NODE *T);
int sumNLR(NODE *T);
void printAllLevel(NODE *T);
void printCurrentLevel(NODE *T, int level);
NODE *minValueNode(NODE *T);
NODE *Delete(NODE *&T, int x);

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
    cout << "THU TU NHAP THEO DE BAI:  1  3  5  7  9  12  15  17  21  23  25  27\n";
    for (int i = 1; i <= 12; i++)
    {
        input(T);
    }
    cout<<"Truoc khi xoa: ";
    travelNLR(T);
    T = Delete(T, 27);
    cout<<"\nSau khi xoa: ";
    travelNLR(T);
    /* int x, count = 0;
    cout << "\nNhap phan tu can tim kiem: ";
    cin >> x;
    NODE *pSearch = searchNode(T, x, count);
    if (pSearch == NULL)
        cout << "Khong ton tai";
    else
    {
        cout << "Co ton tai";
        cout << "\nSo phep so sanh la: " << count;
    }
    cout << "\nSo node leaf: " << countLeaf(T);
    cout << "\nChieu cao cua cay: " << highTree(T);
    cout << "\nSo node bac 1: " << countNODE1(T);
    cout << "\nSo node bac 2: " << countNODE2(T);
    cout<<"\nTong cac phan tu: "<<sumNLR(T);
    cout<<"\n In theo level: "; */
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
    }
    else if (bal < -1 && newNode->data > T->pLeft->data) // Left right
    {
        rotate_LR(T);
    }
    else if (bal > 1 && newNode->data > T->pRight->data) // Right right
    {
        rotate_RR(T);
    }
    else if (bal > 1 && newNode->data < T->pRight->data) // Right left
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
NODE *searchNode(NODE *T, int x, int &count)
{
    if (T == NULL)
    {
        count++;
        return NULL;
    }
    else if (x > T->data)
    {
        count++;
        return searchNode(T->pRight, x, count);
    }
    else if (x < T->data)
    {
        count++;
        return searchNode(T->pLeft, x, count);
    }
    count++;
    return T;
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
int countNODE1(NODE *T)
{
    int count = 0;
    if (T == NULL)
        return 0;
    else if ((T->pLeft == NULL && T->pRight != NULL) || (T->pLeft != NULL && T->pRight == NULL))
        count = 1;
    return count + countNODE1(T->pLeft) + countNODE1(T->pRight);
}
int countNODE2(NODE *T)
{
    int count = 0;
    if (T == NULL)
        return 0;
    else if (T->pLeft != NULL && T->pRight != NULL)
        count = 1;
    return count + countNODE2(T->pLeft) + countNODE2(T->pRight);
}
int sumNLR(NODE *T)
{
    int sum=0;
    if (T==NULL)
        return 0;
    else
        sum=T->data;
    return sum + sumNLR(T->pLeft) + sumNLR(T->pRight);
}
void printAllLevel(NODE *T)
{
    int h = highTree(T);
    for (int i = 1; i <= h; i++)
        printCurrentLevel(T, i);
}
void printCurrentLevel(NODE *T, int level)
{
    if (T == NULL)
        return;
    if (level == 1)
        cout << T->data << " ";
    else if (level > 1) {
        printCurrentLevel(T->pLeft, level - 1);
        printCurrentLevel(T->pRight, level - 1);
    }
}
NODE *minValueNode(NODE *T)
{
    NODE *current = T;
    /* loop down to find the leftmost leaf */
    while (current->pLeft != NULL)
        current = current->pLeft;
    //cout<<"min";
    //cout<<endl<<current->data;
    return current;
}
NODE *Delete(NODE *&T, int x)
{
    // empty
    //cout<<"GD";

    if (T == NULL)
        return T;
    if ( x < T->data )
        T->pLeft = Delete(T->pLeft, x);
    else if( x > T->data )
        T->pRight = Delete(T->pRight, x);
    else // T->data == x
    {
        // node with only one child or no child
        if( (T->pLeft == NULL) || (T->pRight == NULL) )
        {
            NODE *temp = T->pLeft ? T->pLeft : T->pRight;
            if (temp == NULL)
            {
                // temp chỉ đến T để sau đó cần giải phóng dữ liệu ta cần xóa
                temp = T;
                T = NULL;
            }
            else // One child case
                *T = *temp; // Copy the contents of the non-empty child
            free(temp); // giải phóng temp
        }
        else
        {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            NODE* temp = minValueNode(T->pRight);
            // Copy the inorder successor's data to this node
            T->data = temp->data;
            // Delete the inorder successor
            T->pRight = Delete(T->pRight, temp->data); // lúc này xem như xóa node lá
        }
    }
    if (T == NULL)
        return T;
    
    int balT = highTree(T->pRight) - highTree(T->pLeft);
    cout<<"bal1";
    int balRight = highTree(T->pRight->pRight) - highTree(T->pRight->pLeft);
    cout<<"bal2";
    int balLeft = highTree(T->pLeft->pRight) - highTree(T->pLeft->pLeft);
    cout<<"bal3";
    
    // If this node becomes unbalanced,
    // then there are 4 cases
    // Left left
    if (balT < -1 && balLeft <= 0)
    {
        rotate_LL(T);
    }
    else if (balT < -1 && balLeft > 0) // Left right
    {
        rotate_LR(T);
    }
    else if (balT > 1 && balRight >= 0) // Right right
    {
        rotate_RR(T);
    }
    else if (balT > 1 && balRight < 0) // Right left
    {
        rotate_RL(T);
    }
    //cout<<"GD";
    return T;
}
// copyrighted by 20H1120201_NguyenThanhDat