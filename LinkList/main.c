/********************************************
* File Name : LingList
*
* Function  : None
* Argument  : None
* Retval    : None
*
* Author    : Hrolf
* Data      : 4/10/2025
* Note      : None
*
* CopyRight (c)      Hrolf     All Right Reseverd
* @param c
* @return
*
* *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Define Data type
typedef int  DataType_t;

/********************************************
* File Name : LingList
*
* Function  : LinkedList
* Argument  : Data : store data
 *            next : a pointer points next address
 *
* Retval    : None
*
* Author    : Hrolf
* Data      : 4/10/2025
* Note      : Define a structure includes a data and a pointer
*
* CopyRight (c)      Hrolf     All Right Reseverd
* @param c
* @return
*
* *****************************************/
//构造空链表，包括数据和指针
typedef struct LinkedList
{
    DataType_t          Data; //节点数据域
    struct LinkedList  *next; //节点指针域
}LList_t;



/********************************************
* File Name : LingList
*
* Function  : LList_Create
* Argument  : None
* Retval    : An address of Head
* Author    : Hrolf
* Data      : 4/10/2025
* Note      : Create a new head structure node .
*
* CopyRight (c)      Hrolf     All Right Reseverd
* @param c
* @return
*
* *****************************************/
//创建空链表，空链表有一个头结点，对空链表初始化
LList_t * LList_Create(void)
{
    //1创建头节点，并且申请一个栈内存
    LList_t *Head = (LList_t *)calloc(1, sizeof(LList_t));
    if (NULL == Head){
        perror("Failure to calloc memory for Head");
        exit(-2);
    }
    //2成功申请，保证指针指向有效元素
    Head->next = NULL;
    //3返回头节点地址
    return Head;
}



/********************************************
* File Name : LingList
*
* Function  : LList_Create
* Argument  : None
* Retval    : An address of new node
* Author    : Hrolf
* Note      : Create a new structure node
*
*
* Data      : 4/10/2025
* CopyRight (c)      Hrolf     All Right Reseverd
* @param c
* @return
*
* *****************************************/
//创建新的节点，并且初始化
LList_t * LList_NewNode(DataType_t data)
{
    //1创建新节点，并且申请一个栈内存
    LList_t *New = (LList_t *)calloc(1, sizeof(LList_t));
    if (NULL == New) {
        perror("Failure to calloc memory for Head");
        return NULL;
    }

    //2对新节点的数据与和指针域进行初始化
    New->Data = data;
    New->next = NULL;

    return New;

}



//插入操作 首插
bool LList_HeadInsert (LList_t * Head, DataType_t data)
{
    //1创建新的节点
    LList_t *New = LList_NewNode(data);
    if (NULL == New){
        printf("Cannot Insert New Node\n");
        return false;
    }
    //2判断链表是否为空,空则直接插入
    if (NULL == Head->next){
        Head->next = New;
        return true;
    }
    //3非空,先让先结点指向头节点下一个，再让头节点指向新节点,防止数据丢失
    New->next = Head->next;
    Head->next = New;

    return true;

}



//向链表中插入元素  尾插
bool LList_TailInsert(LList_t *Head,DataType_t data)
{
    //1备份头节点
    LList_t *PHead = Head;
    //2创建新的节点
    LList_t *New = LList_NewNode(data);
    if (NULL == New){
        printf("Cannot Insert New Node\n");
        return false;
    }
    //3判断链表是否为空,空则直接插入
    if (NULL == PHead->next){
        PHead->next = New;
        return true;
    }
    //4非空,先遍历到尾节点，再让尾节点指向新节点，再让新结点指向NULL
    while (PHead->next){
        PHead = PHead->next;
    }
    PHead->next = New;
    return true;
}



//向链表中插入元素  指定位置插入(插入后面)
bool LList_DestNextInsert (LList_t *Head, DataType_t DestVal, DataType_t data)
{
    //1备份头节点
    LList_t *PHead = Head->next;
    //2创建新的节点
    LList_t *New = LList_NewNode(data);
    if (NULL == New){
        printf("Cannot Insert New Node\n");
        return false;
    }
    //3判断链表是否为空,空则直接插入
    if (NULL == Head->next){
        Head->next = New;
        return true;
    }
    //4非空,先遍历到指定元素，并且判断DestVal是否存在,记录指定元素PHead
    while (PHead != NULL && DestVal != PHead->Data){
        PHead = PHead->next;
    }
    if (PHead == NULL){
        printf("Cannot Insert [%d],[%d] Is Not Exiting\n",data,DestVal);
        return false;
    }
    //5先让新元素指向指定元素下指定一个，再让指定元素指向新元素
    New->next = PHead->next;
    PHead->next = New;

    return true;
}




//向链表中插入元素  指定位置插入(插入后面)
bool LList_DestPrevInsert ( LList_t *Head, DataType_t DestVal, DataType_t data)
{
    //1备份头节点
    LList_t *PHead = Head->next;
    //2创建新的节点
    LList_t *New = LList_NewNode(data);
    if (NULL == New){
        printf("Cannot Insert New Node\n");
        return false;
    }
    //3创建DestVal直接前驱FrontNode
    LList_t *FrontNode = Head;
    //4判断链表是否为空,空则直接插入
    if (NULL == Head->next){
        Head->next = New;
        return true;
    }
    //5非空,先遍历到指定元素，并且判断DestVal是否存在,记录指定元素PHead和PHead直接前驱FrontNode
    while (PHead != NULL && DestVal != PHead->Data){
        FrontNode = PHead;
        PHead = PHead->next;
    }
    //6PHead为NULL说明链表中无指定元素DestVal
    if (PHead == NULL){
        printf("Cannot Insert [%d],[%d] Is Not Exiting\n",data,DestVal);
        return false;
    }
    //7判断指定元素PHead是否为首元素,即Front是否为NULL，是则用首插法
    if (FrontNode == NULL){
        New->next = Head->next;
        Head->next = New;
    }
    //8先让新元素New指向指定元素PHead，再让指定元素PHead原直接前驱FrontNode指向新元素New
    New->next = PHead;
    FrontNode->next = New;

    return true;
}



//对链表删除 头删
bool LList_HeadDel(LList_t *Head)
{
    //1备份头节点
    LList_t *PHead =Head;
    //2判断链表是否为空
    if (Head->next == NULL){
        printf("The LinkedList is NULL\n");
        return false;
    }
    //3链表不为空，用PHead代表首节点节点
    PHead =PHead->next;
    //4头节点指向首节点的下一个
    Head->next = PHead->next;
    //5把首首节点指向NULL，并且释放空间
    PHead->next = NULL;
    free(PHead);

    return true;
}



//对链表删除 尾删
bool LList_TaiDel ( LList_t *Head )
{
    //1判断链表是否为空，空直接退出
    if ( Head->next == NULL ){
        printf("The LinkedList is NULL\n");
        return false;
    }
    //2备份头节点
    LList_t *PHead = Head;
    //3创建新节点，来备份尾节点前一个结点
    LList_t *FTail = NULL;
    while ( PHead->next ){
        FTail = PHead;
        PHead = PHead->next;
    }
    //4首先让尾节点前一个节点指向NULL，再释放尾节点
    FTail->next = NULL;
    PHead->next = NULL;
    free(PHead);
    return true;
}


//对链表删除 指定删
bool LList_DestDel(LList_t *Head, DataType_t data)
{
    //1备份头节点PHead
    LList_t *PHead = Head;
    //2创建新节点，来备份指定元素前节点PreNode
    LList_t *PrevHead = Head;
    //2判断是否为空,空则直接退出
    if ( PHead->next == NULL ){
        printf("The LinkedList is Null\n");
        return false;
    }
    //3遍历到指定元素，记录PHead和指定元素直接前驱PreHead
    while ( PHead->next ){
        PrevHead = PHead;
        PHead = PHead->next;
        if (PHead->Data == data){
            break;
        }
    }
    //4判断带删除元素是否存在,不存在返回false
    if ( PHead == NULL || PHead->Data != data){
        printf("The Element [%d] Is Not Exit\n",data);
        return false;
    }
    //5判断PHead是否为最后一个元素，若是，直接让PreHead指向NULL;
    if ( PHead->next == NULL ){
        PrevHead->next = NULL;
        free(PHead);
        return true;
    }
    //6首先让指定元素PHead前节点PrevHead指向待删元素元素下一个节点PHead.next，再让待删元素PHead指向空，最后释放PHead
    PrevHead->next = PHead->next;
    PHead->next = NULL;
    free(PHead);
    return true;
}



//删除单链表中 最小值
bool LList_DelMin(LList_t *Head)
{
    //1判断链表是否为空，空则直接退出函数
    if (Head == NULL || Head->next==NULL ) {
        printf("The Linked List IS NULl\n");
        return false;
    }
    //2记录最小值节点min和最小值节点直接前驱min_prev
    LList_t *min_prev   = Head;                //记录最最小直接点前地址
    LList_t *min        = Head->next; //记录最小值节点
    //3记录当前节点PHead和当前节点PHead直接前驱PHead_prev
    LList_t *PHead_prev = Head;       //记录当前节点直接前驱地址
    LList_t *PHead      = Head->next; //记录当前节点地址

    //4判断链表是否只有一个，是则直接让Head指向NULL，再释放Head.Next
    if (PHead->next == NULL){
        Head->next = NULL;
        free(PHead);
        printf("There IS Only One Element\n");
        return true;
    }

    //5遍历链表
    while ( PHead->next != NULL ){
        PHead_prev = PHead;
        PHead = PHead->next;

        //判断目前最小节点值值min 与 新的节点值PHead大小
        //若新节点值小，原最小值节点直接前驱min_prev指向新最小节点值直接前驱PHead_prev，最小值节点min指向新的节点PHead
        if ( min->Data > PHead->Data ){
            min_prev = PHead_prev;
            min = PHead;
        }
    }

    //6判断最小值是否为最后一个元素，若是，让最小值节点直接前驱min_prev指向NULL
    if (min->next == NULL){
        min_prev->next = NULL;
        free(min);
        printf("This Is The Last Element\n");
        return true;
    }

    //6最小值接点不为最后一个元素，让最小值节点直接前驱min_prev指向最小值节点min直接后驱，再让最小值指向NULL，最后free
    min_prev->next = min->next;
    free(min);
    return true;
}



//删除单链表中 最大值
bool LList_DelMax(LList_t *Head)
{
    //1判断链表是否为空，空则直接退出函数
    if (Head->next == NULL){
        printf("The Linked List IS NULl\n");
        return false;
    }

    //2记录最小值节点min和最小值节点直接前驱min_prev
    LList_t *max_prev   = Head;                //记录最最小直接点前地址
    LList_t *max        = Head->next; //记录最小值节点

    //3记录当前节点PHead和当前节点PHead直接前驱PHead_prev
    LList_t *PHead      = Head->next; //记录当前节点地址
    LList_t *PHead_prev = Head;       //记录当前节点直接前驱地址

    //4判断链表是否只有一个，是则直接让Head指向NULL，再释放Head.Next
    if (PHead->next == NULL){
        Head->next == NULL;
        free(PHead);
        printf("There IS Only One Element\n");
        return true;
    }

    //5遍历链表
    while ( PHead->next ){
        PHead_prev = PHead;
        PHead = PHead->next;
        //判断目前最小节点值值min 与 新的节点值PHead大小
        //若新节点值小，原最小值节点直接前驱min_prev指向新最小节点值直接前驱PHead_prev，最小值节点min指向新的节点PHead
        if (max->Data < PHead->Data ){
            max_prev = PHead_prev;
            max = PHead;
        }
    }
    if (max->next == NULL){
        max_prev = NULL;
        free(max);
        printf("This Is The Last Element\n");
        return true;
    }
    max_prev->next = max->next;
    max->next = NULL;
    free(max);
    return true;
}




//删除指定元素前面一个
bool LList_PrevDestDel(LList_t *Head, DataType_t data)
{
    //1备份头节点PHead
    LList_t *PHead = Head->next;
    //2创建新节点，来备份指定元素前两个节点Prev2Head
    LList_t *Prev2Head = NULL;
    //2判断是否为空,或者为一个元素,如果是，则直接退出
    if (PHead->next == NULL || PHead == NULL){
        printf("The LinkedList Is Null OR There Is Only One Element");
        return false;
    }
    //3遍历到指定元素，记录PHead和指定元素直接前驱Prev2Head
    while (PHead->next){
        Prev2Head = PHead;
        PHead = PHead->next;
        if (PHead->Data == data){
            break;
        }
    }
    //4首先让指定元素PHead前节点Prev2Head指向待删元素元素下一个节点PHead.next，再让待删元素PHead指向空，最后释放PHead
    Prev2Head->next = PHead->next;
    PHead->next = NULL;
    free(PHead);
    return true;
}



//删除指定元素后面一个
bool LList_NextDestDel(LList_t * Head, DataType_t data)
{
    //1备份头节点PHead
    LList_t *PHead = Head->next;

    //2判断是否为空,或者为一个元素,如果是，则直接退出
    if ( PHead->next ==NULL || Head->next == NULL ){
        printf("The LinkedList Is Null OR There Is Only One Element\n");
        return false;
    }

    //2创建新节点，来备份指定元素前两个节点NextHead
    LList_t *NextHead = NULL;

    //3遍历到指定元素，记录PHead和指定元素直接前驱NextHead
    while (PHead->next){
        PHead = PHead->next;
        if (PHead->Data == data){
            break;
        }
    }

    //4判断PHead之后是否还有元素,或者指定元素节点PHead是否为链表最后一个元素，若满足其一，返回false
    if (PHead->next == NULL || PHead->next->next == NULL) {
        printf("There Is No Element Left [%d] Or There Is No Element [%d] In Linked List\n", data, data);
        return false;
    }

    //5让NextHead指向指定元素PHead下一个元素PHead.next
    NextHead = PHead->next;

    //6首先让指定元素PHead指向待删元素元素 下下 一个节点PHead.next.next，再释放NextHead
    PHead->next = NextHead->next;
    free(NextHead);
    return true;
}



//删除指定元素前面n个
bool LList_nPrevDestDel(LList_t  * Head , int n)
{
    LList_t * FrontNode = NULL;
    for (int i = 0; i <= n; ++i) {

    }

}



//删除指定元素后面n个
bool LList_nNextDestDel();



//遍历,输出
void LList_Print(LList_t * Head)
{
    //1对头节点进行备份
    LList_t *PHead= Head;
    while (PHead->next != NULL){
        //把当前节点的直接后继作为新节点的直接后继
        PHead=PHead->next;
        //输出当前节点数据域
        printf(" %d",PHead->Data);
    }
}



int main(void)
{
    printf("/********/\n");
    printf("Create An Linked List\n");
    LList_t * Head = LList_Create();

    //1判断Head是否为空，NULL则返回
    if (Head == NULL){
        perror("Memory allocation is failed\n");
        return -2;
    }

    //2插入元素 头插法
    LList_HeadInsert(Head,20);
    LList_HeadInsert(Head,0);
    LList_HeadInsert(Head,21);
    LList_HeadInsert(Head,5);
    LList_HeadInsert(Head,7);
    //输出元素 7 5 21 0 20
    printf("Head Insert Expected Order: 7 5 21 0 20\n");
    LList_Print(Head);


    //3插入元素 尾插法
    LList_TailInsert(Head,1);
    LList_TailInsert(Head,411);
    LList_TailInsert(Head,211);
    LList_TailInsert(Head,511);
    LList_TailInsert(Head,6);
    //输出元素 7 5 21 0 20 1 411 211 511 6
    printf("Tail Insert Expected Order: 7 5 21 0 20 1 411 211 511 6\n");
    LList_Print(Head);
    printf("\n");

    //4指定插入 插入后面
    LList_DestNextInsert(Head, 4, 1003);
    LList_DestNextInsert(Head, 20, 22);
    LList_DestNextInsert(Head, 7, 41);
    LList_DestNextInsert(Head, 6, 17);
    //输出元素 7 41 5 21 0 20 22 1 411 211 511 6 17
    printf("Dest Next InsertExpected Order: 7 41 5 21 0 20 22 1 411 211 511 6 17\n");
    LList_Print(Head);
    printf("\n");

    //5指定插入 插入前面
    LList_DestPrevInsert(Head,9,1001);
    LList_DestPrevInsert(Head,7,13);
    LList_DestPrevInsert(Head,17,2);
    //输出元素  13 7 41 5 21 0 20 22 1 411 211 511 6 17 2
    printf("Head Prev Insert Expected Order: 13 7 41 5 21 0 20 22 1 411 211 511 6 17 2\n");
    LList_Print(Head);
    printf("\n");

    //6删除链表元素 头删
    LList_HeadDel(Head);
    printf("Head Delete Expected Order: 7 41 5 21 0 20 22 1 411 211 511 6 17 2\n");
    //输出元素 7 41 5 21 0 20 22 1 411 211 511 6 17 2
    LList_Print(Head);
    printf("\n");

    //7删除链表元素 尾删
    LList_TaiDel(Head);
    printf("Tail Delete Expected Order: 7 41 5 21 0 20 22 1 411 211 511 6 17\n");
    //输出元素 7 41 5 21 0 20 22 1 411 211 511 6 17
    LList_Print(Head);
    printf("\n");

    //8删除链表元素 指定删除
    LList_DestDel( Head, 50);
    LList_DestDel( Head, 7);
    LList_DestDel( Head, 411);
    LList_DestDel( Head, 0);
    LList_DestDel( Head, 17);
    printf("Dest Delete Expected Order: 41 5 21 20 22 1 211 511 6\n");
    LList_Print(Head);
    LList_DestPrevInsert(Head,20,0);
    //41 5 21 0 20 22 1 211 511 6
    printf("\n");



    //9笔试题：单链表寻找最小值
    //单链表删除最小值   41 5 21 20 22 1 211 511 6
    LList_DelMin(Head);
    //输出元素
    printf("Delete Minimum Value Expect Value: 41 5 21 20 22 1 211 511 6\n");
    LList_Print(Head);
    printf("\n");
    //单链表删除大值    41 5 21 20 22 1 211 6
    LList_DelMax(Head);
    //输出元素
    printf("Delete Maximum Value Expect Value:41 5 21 20 22 1 211 6\n");
    LList_Print(Head);
    printf("\n");


    //10删除指定元素  前一个元素
    LList_PrevDestDel(Head,41);
    LList_PrevDestDel(Head,1);
    LList_PrevDestDel(Head,55);
    //输出  41 5 21 20 1 211 6
    printf("Delete Dest Prev One Value. Expect Value:41 5 21 20 1 211 6\n");
    LList_Print(Head);
    printf("\n");

    //11删除指定元素  后一个元素
    LList_NextDestDel(Head,11);
    LList_NextDestDel(Head,20);
    LList_NextDestDel(Head,6);
    LList_NextDestDel(Head,41);
    //打印元素  41 21 20 211 6
    printf("Delete Dest Next One Value. Expect Value: 41 21 20 211 6\n");
    LList_Print(Head);



    printf("Hello, World!\n");


    return 100;
}
