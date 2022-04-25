#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Node //链表节点类型定义
{
    string Name;
    string Tel;
    int sex;
    Node *next;
};

int num; //记录通讯录总人数

string menustr[] = {
    "1. 创建一个通信录链表",
    "2. 建立新联系人",
    "3. 遍历一个通信录链表",
    "4. 按姓名对链表排序",
    "5. 按性别对链表重排，女的在前，男的在后",
    "6. 在排序链表的基础上添加节点",
    "7. 删除指定姓名的节点",
    "0. 退出"};

Node *CreatlList()
{
    Node *h = new Node;
    h->next = NULL;
    return h;
}

void InsertNewNode(Node *head)
{
    Node *p = head;

    Node *node = new Node;
    cin >> node->Name >> node->Tel >> node->sex; //字符串变量不能被等号赋值，但可以通过cin初始化

    while (p->next != NULL)
        p = p->next;
    p->next = node;
    node->next = NULL;
}

void PrintList(Node *head)
{
    Node *h, *p;
    h = head;
    p = h->next;

    while (p != NULL)
    {
        cout << p->Name << '\t' << p->Tel << '\t' << p->sex << endl;
        p = p->next;
    }
}

bool Namecmp(string a, string b)
{
    return a > b;
}

void NameSort(Node *head)
{
    //采用冒泡排序
    Node *h = head;
    Node *p1, *p2, *p;
    p1 = head;
    p = p1->next;

    if (p->next != NULL)
        p2 = p->next;
    else
    {
        cout << "该链表不需排序" << endl;
        return;
    }

    int i = 0;

    while (i <= num)
    {
        while (p2 != NULL)
        {
            if (Namecmp(p->Name, p2->Name))
            {
                p1->next = p2;
                p->next = p2->next;
                p2->next = p;

                //将交换后的p与p2交换回来
                p = p2;
                p2 = p2->next;
            }

            p1 = p;
            p = p2;
            p2 = p2->next;
        }

        p1 = head;
        p = p1->next;
        p2 = p->next;

        i++;
    }
}

void GenderSort(Node *head)
{
    Node *h = head;
    Node *p, *p1, *p2;
    p = head->next;
    p1 = p->next;
    while (p1 != NULL)
    {
        if (p1->sex == 2)
        {
            p2 = p1;
            p1 = p1->next;
            p2->next = head->next;
            head->next = p2;
            p->next = p1;
        }
        else
        {
            p1 = p1->next;
            p = p->next;
        }
    }
}

void AddNodeBaseOnGenderSort(Node *head)
{
    Node *h = head;
    Node *p = h->next;
    Node *node = new Node;
    cin >> node->Name >> node->Tel >> node->sex;

    while(p->next->sex == 2)
        p = p->next;

    node->next = p->next;
    p->next = node;

}

void DeleteNode(Node *head)
{
    Node *h = head;
    Node *p = h;

    string name;
    cin >> name;

    while(1)
    {
        Node *p1;
        p1 = p->next;

        if(p1->Name == name)
        {
            if(p1->next == NULL)
            {
                p->next = NULL;
                delete p1;
            }
            else
            {
                p->next = p1->next;
                delete p1;
            }
            break;
        }

        if(p1->next == NULL)
        {
            cout << "未找到此节点" << endl;
            break;
        }

        p = p->next;
    }
}

void menu()
{
    for (int i = 0; i < sizeof(menustr) / sizeof(menustr[0]); i++)
        cout << menustr[i] << endl;
    cout << "请输入功能号：" << endl;
}

int main()
{
    int choice;
    Node *head = NULL;

    do
    {
        menu();        //显示菜单
        cin >> choice; //输入功能号
        switch (choice)
        {
        case 1:
            head = CreatlList();
            break;
        case 2:
            InsertNewNode(head);
            num++;
            break;
        case 3:
            PrintList(head);
            break;
        case 4:
            NameSort(head);
            cout << "按姓名排序完成" << endl;
            break;
        case 5:
            GenderSort(head);
            cout << "按性别排序完成" << endl;
            break;
        case 6:
            AddNodeBaseOnGenderSort(head);
            break;
        case 7:
            DeleteNode(head);
            break;
        }
        cout << endl;
    } while (choice != 0);

    return 0;
}
