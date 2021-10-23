#include<cstdio>
#include<cstdlib>
#include "ResultPackage.h"
#include "ListByArray.h"
bool ListByArray::InitList(int InitSize)
{
    Data = (int*) malloc(sizeof(int) * InitSize);
    if (Data == NULL) return 0;
    Size = 0;
    return 1;
}
bool ListByArray::DestroyList()
{
    if(Data == NULL) return 0;
    free(Data);
    return 1;
}
bool ListByArray::Insert(int x)
{
    Data[Size] = x;
    ++Size;
    return 1;
}
bool ListByArray::PrintListForDebug()
{
    for(int i = 0; i < Size; i++) printf("%d%c", Data[i], i == Size - 1 ? '\n' : ' ');
    return 1;
}
bool ListByArray::MoveByMovement(int* NowPos, int Movement)
{
    (*NowPos) = ((*NowPos) + Movement) % Size;
    return 1;
}
bool ListByArray::GetSize(int *NowSize)
{
    (*NowSize) = Size;
    return 1;
}
bool ListByArray::IsEmpty()
{
    return (Size == 0);
}
bool ListByArray::DeleteElement(int NowPos, ResultPackage* NowPackage)
{
    if (NowPos >= Size) return 0;
    ResultPackage t;
    t.Pos = Data[NowPos];
    t.Cost = Size - NowPos - 1;
    (*NowPackage) = t;
    //(*NowPackage) = (ResultPackage) {Data[NowPos], Size - NowPos - 1};
    for (int i = NowPos; i < Size - 1; i++) Data[i] = Data[i + 1];    
    Size --;
    return 1;
}