struct ListNode
{
	int Data;
	ListNode *Next;
};

bool ListNodeInit(ListNode **x);
struct DemoList
{
    ListNode* T;
};
bool InitDemo(DemoList &L);
bool isEmpty(DemoList &L);
bool TailAdd(DemoList &L, int x);
struct ListByLink
{
	DemoList Demo;
	ListNode *Tail, *Cur;
	int ListLength;
	bool InitList();
	bool DestroyList();
	bool AddToTail(int x);
	bool DeleteNextElement(ResultPackage *Result);
	bool DeleteNextMthElement(int m, ResultPackage *Result);
	bool PrintListForDebug();
	int GetSize();
	bool IsEmpty();
};
