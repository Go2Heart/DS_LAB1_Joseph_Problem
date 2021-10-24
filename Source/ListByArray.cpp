#include<cstdio>
#include<cstdlib>
#include "ResultPackage.h"
#include "ListByArray.h"

bool ListByArray::InitList(int InitSize)
{
    Data = (int*) malloc(sizeof(int) * InitSize);
    if (Data == NULL) return false;
    Size = 0;
    return true;
}

bool ListByArray::DestroyList()
{
    if(Data == NULL) return false;
    free(Data);
    return true;
}

bool ListByArray::Insert(int x)
{
    Data[Size] = x;
    ++Size;
    return true;
}

bool ListByArray::PrintListForDebug()
{
    for(int i = 0; i < Size; i++) printf("%d%c", Data[i], i == Size - 1 ? '\n' : ' ');
    return true;
}

bool ListByArray::MoveByMovement(int* NowPos, int Movement)
{
    (*NowPos) = ((*NowPos) + Movement) % Size;
    return true;
}

bool ListByArray::GetSize(int *NowSize)
{
    (*NowSize) = Size;
    return true;
}

bool ListByArray::IsEmpty()
{
    return (Size == 0);
}

bool ListByArray::DeleteElement(int NowPos, ResultPackage* NowPackage)
{
    if (NowPos >= Size) return false;
    (*NowPackage) = (ResultPackage) {Data[NowPos], Size - NowPos - 1};
    for (int i = NowPos; i < Size - 1; i++) Data[i] = Data[i + 1];    
    Size --;
    return true;
}