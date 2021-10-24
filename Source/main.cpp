#include<cstdio>
#include "ResultPackage.h"
#include "ListByArray.h"
#include "ListByLink.h"
bool SolByArray(int InitN, int InitM)
{
    ListByArray List;
	ResultList resultList;
	FILE* fout = fopen("AnsByArray.out", "w");
    if(!List.InitList(InitN)) return false;
	if(!resultList.InitList(InitN)) return false;
    for (int i = 1; i <= InitN; i++) 
		if(!List.Insert(i)) 
			return false;
    int NowPos = 0;
    ResultPackage Result;
	int PreCost = 0;
    while(!List.IsEmpty())
    {
        if(!List.MoveByMovement(&NowPos, InitM - 1)) 
			return false;
        if(!List.DeleteElement(NowPos, &Result)) 
			return false;
		Result.Cost += PreCost;
		PreCost = Result.Cost;
        if(!resultList.Insert(Result)) 
			return false;
    }
	resultList.PrintList(fout);	
	if(!List.DestroyList()) return false;
	if(!resultList.DestroyList()) return false;
    fclose(fout);
	return true;
}
bool SolByLink(int InitN, int InitM)
{
	ListByLink List;
	ResultList resultList;
	FILE* fout = fopen("AnsByLink.out", "w");
	FILE* fout_d = fopen("demo.csv","w");
	if(!List.InitList()) return false;
	if(!InitDemo(List.Demo))return false;
	if(!resultList.InitList(InitN)) return false;
	for(int i = 1; i <= InitN; i++)
		if(!List.AddToTail(i))
			return false;
	ResultPackage Result;
	int PreCost = 0;
	while(!List.IsEmpty())
	{
		List.PrintListForDebug();
		if(!List.DeleteNextMthElement(InitM, &Result))
			return false;
		Result.Cost += PreCost;
		PreCost = Result.Cost;
		if(!resultList.Insert(Result)) 
			return false;
		fprintf(fout_d, "%d,",Result.Pos);
	}
	fprintf(fout_d, "\n");
	ListNode* temp = List.Demo.T;
    while(List.Demo.T->Next != temp){
        fprintf(fout_d, "%d,", List.Demo.T->Next->Data);
        List.Demo.T->Next = List.Demo.T->Next->Next;
    }
	if(!List.DestroyList()) return false;
	if(!resultList.DestroyList()) return false;
	fclose(fout);
	return true;
}
int main()
{
	int InitN, InitM;
	scanf("%d%d", &InitN, &InitM);
	if(!SolByArray(InitN, InitM))
		puts("ERROR!");
	if(!SolByLink(InitN, InitM))
		puts("ERROR!");
}