struct ListByArray
{
    int Size;
    int *Data;
    bool InitList(int InitSize);
    bool DestroyList();
    bool Insert(int x);
    bool PrintListForDebug();
    bool MoveByMovement(int* NowPos,int Movement);
    bool GetSize(int* NowSize);
    bool IsEmpty();
    bool DeleteElement(int NowPos, ResultPackage* NowPackage);
};