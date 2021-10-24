#include<cstdio>
#include<cstdlib>
#include "ResultPackage.h"
bool ResultList::InitList(int InitSize)
{
    Data = (ResultPackage*) malloc(sizeof(ResultPackage) * InitSize);
    if (Data == NULL) return false;
    Size = 0;
    return true;
}
bool ResultList::DestroyList()
{
    if(Data == NULL) return false;
    free(Data);
    return true;
}
bool ResultList::Insert(ResultPackage x)
{
    Data[Size] = x;
    ++Size;
    return true;
}
bool ResultList::PrintList(FILE* fout)
{
    for(int i = 0; i < Size; i++) fprintf(fout, "<%d, %d>\n", Data[i].Pos, Data[i].Cost);
    return true;
}