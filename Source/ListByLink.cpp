#include <cstdio>
#include <cstdlib>
#include "ResultPackage.h"
#include "ListByLink.h"

bool ListNodeInit(ListNode **x)
{
	*x = (ListNode*) malloc(sizeof(ListNode));
	if(x == NULL)
		return false;
	(*x) -> Next = NULL;
	return true;
}

bool InitDemo(DemoList &L)
{
    if(!ListNodeInit(&L.T)) return false;
    L.T->Next = L.T;
    L.T->Data = -1;

    return true;
}

bool isEmpty(DemoList &L)
{
    if (L.T->Data == -1) return true;
    else return false;
}

bool TailAdd(DemoList &L, int x)
{
    if(!L.T) return false;
    if(isEmpty(L)) {
        L.T->Data = x;
        return true;
    }
    ListNode *Temp;
    ListNodeInit(&Temp);
    Temp->Next = L.T->Next;
    Temp->Data = x;
    L.T->Next = Temp;
    L.T = Temp;
    return true;
}

bool ListByLink::InitList()
{
	if(!ListNodeInit(&Tail))
		return false;
	Tail -> Next = Tail;
	ListLength = 0;
	return true;
}

bool ListByLink::AddToTail(int x)
{
	if(Tail == NULL)
		return false;
	if(ListLength == 0)
	{
		Tail -> Data = x;
		ListLength++;
		return true;
	}
	ListNode *Tmp = Tail -> Next;
	Tail -> Next = NULL;
	if(!ListNodeInit(&(Tail -> Next)))
		return false;
	Tail -> Next -> Next = Tmp;
	Tail = Tail -> Next;
	Tail -> Data = x;
	Cur = Tail;
	ListLength++;
	// fprintf(stderr, "%d\n====\n", Cur -> Data);
	return true;
}

bool ListByLink::PrintListForDebug()
{
	if(Tail == NULL)
		return false;
	ListNode *Tmp = Tail -> Next;
	for(; Tmp != Tail; Tmp = Tmp -> Next)
		if(Tmp == NULL)
			return false;
	Tmp = Tail -> Next;
	printf("Length: %d\n", ListLength);
	for(; Tmp != Tail; Tmp = Tmp -> Next)
		printf("%d ", Tmp -> Data);
	printf("%d\n", Tail -> Data);
	return true;
}

bool ListByLink::DestroyList()
{
	if(ListLength == 0 && Tail == NULL)
		return true;
	if(ListLength == 0 && Tail != NULL)
		return false;
	if(Tail == NULL || Tail -> Next == NULL)
		return false;
	ListLength = 0;
	ListNode *Tmp = Tail -> Next;
	while(Tmp != Tail)
	{
		if(Tmp == NULL)
			return false;
		ListNode *Del = Tmp;
		Tmp = Tmp -> Next;
		free(Del);
		if(Del != NULL)
			return false;
	}
	free(Tail);
	Tail = NULL;
	return true;
}

bool ListByLink::DeleteNextElement(ResultPackage *Result)
{
	if(Cur == NULL)
		return false;
	if(Cur -> Next == NULL)
		return false;
	ListLength--;
	ListNode* Tmp = Cur -> Next;
	if(Tmp == Tail)
	{
		Tail = Cur;
		if(Cur == Tmp)
			Tail = NULL;
	}
	Result -> Pos = Tmp -> Data;
	Tmp = Tmp -> Next;
	free(Cur -> Next);
	Cur -> Next = Tmp;
	return true;
}

bool ListByLink::DeleteNextMthElement(int m, ResultPackage *Result)
{
	if(Cur == NULL || ListLength == 0)
		return false;
	Result -> Cost = (m - 1) % ListLength;
	for(int i = 1; i <= Result -> Cost; i++)
	{
		if(Cur -> Next == NULL)
			return false;
		Cur = Cur -> Next;
		TailAdd(Demo, Cur->Data);
	}
	if(!DeleteNextElement(Result))
		return false;
	TailAdd(Demo, Result->Pos);
	return true;
}

int ListByLink::GetSize()
{
	return ListLength;
}

bool ListByLink::IsEmpty()
{
	return ListLength == 0;
}
