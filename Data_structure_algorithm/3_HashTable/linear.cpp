#include<iostream>
#include<string.h>
using namespace std;
int count=0;
struct NODE
{
    int mssv, gpa;
    string name;
};
void inputInfo(NODE **&array, NODE *temp, int size);
int Hash(int a, int size);
void Search(NODE **array, NODE *temp, int size);
void DisplayHashTable(NODE **array, int size);

int main()
{
    int size;
    cout<<"Nhap so luong sinh vien: ";
    cin>>size;
    NODE** arra = new NODE*[size];
    NODE* temp= new NODE;
    for (int i =0; i<size; i++)
    {
        arra[i]= NULL;
    }
    for (int i=1; i<=size;i++)
    {
        cout<<"Nhap ma so sinh vien: ";
        cin>>temp->mssv;
        cout<<"Nhap ho va ten sinh vien: ";
        cin.ignore();
        getline(cin, temp->name);
        cout<<"Nhap GPA: ";
        cin>>temp->gpa;
        inputInfo(arra, temp, size);
    }
    cout<<"Nhap ma so sinh vien can tiem kiem: ";
    cin>>temp->mssv;
    Search(arra, temp, size);
    DisplayHashTable(arra, size);
    return 0;
}
void inputInfo(NODE **&arra, NODE *temp, int size)
{
    if (count == size)
    {
        cout<<"FULL [!]";
        return;
    }
    int HashIndex = Hash(temp->mssv, size);
    while(arra[HashIndex] != NULL)
    {
        HashIndex = (HashIndex + 1) % size;
    }
    arra[HashIndex] = new NODE;
    arra[HashIndex]->mssv = temp->mssv;
    arra[HashIndex]->name = temp->name;
    arra[HashIndex]->gpa = temp->gpa;
    count++;
}
int Hash(int a, int size)
{   
    return a%size;
}
void Search(NODE **arra, NODE *temp, int size)
{
    int SearchHashIndex = Hash(temp->mssv, size);
    int origin = SearchHashIndex;
    while (true)
    {
        if ((arra[SearchHashIndex] == NULL) || (arra[SearchHashIndex]->mssv != temp->mssv))
        {
            SearchHashIndex = (SearchHashIndex + 1)%size;
            if (SearchHashIndex == origin)
                break;
        }
        else
        {
            cout<<"STUDENT FOUND\n";
            cout<<"Ma so sinh vien: "<<arra[SearchHashIndex]->mssv<<endl;
            cout<<"Ho va Ten: "<<arra[SearchHashIndex]->name<<endl;
            cout<<"GPA: "<<arra[SearchHashIndex]->gpa<<endl;
            return;
        }
    }
    cout<<"STUDENT NOT FOUND";
}
void DisplayHashTable(NODE **arra, int size)
{
    for (int i = 0; i< size; i++)
    {
        cout<<"\nMa so sinh vien thu "<<i+1<<": "<<arra[i]->mssv<<endl;
        cout<<"Ho va Ten: "<<arra[i]->name<<endl;
        cout<<"GPA: "<<arra[i]->gpa<<endl;
        cout<<"=================================================\n";
    }
}