#include<cstdio>
#include "ResultPackage.h"
#include "ListByArray.h"
#include "ListByLink.h"
bool SolByArray(int InitN, int InitM)
{
    FILE* fout = fopen("AnsByArray.out", "w");
    ListByArray List;
    if(!List.InitList(InitN)) return false;
    for (int i = 1; i <= InitN; i++) if(!List.Insert(i)) return false;
    int NowPos = 0;
	bool DeleteOccur = 0;
    ResultPackage Result;
    while(!List.IsEmpty())
    {
        if(!List.MoveByMovement(&NowPos, InitM - DeleteOccur)) return false;
        if(!List.DeleteElement(NowPos, &Result)) return false;
		if(!DeleteOccur) DeleteOccur = 1;
        fprintf(fout, "<%d, %d>\n", Result.Pos, Result.Cost);
    }
	if(!List.DestroyList()) return false;
    fclose(fout);
	return true;
}
bool SolByLink(int InitN, int InitM)
{
	ListByLink List;
	FILE* fout = fopen("AnsByLink.out", "w");
    FILE* fout_d = fopen("demo.csv","w");
	List.InitList();
    InitDemo(List.Demo);
	for(int i = 1; i <= InitN; i++)
		if(!List.AddToTail(i))
			return false;
	// fprintf(stderr, "!!!\n");
	List.PrintListForDebug();
	// fprintf(stderr, "!!!%d\n", List.GetSize());
	ResultPackage Result;
	while(!List.IsEmpty())
	{
		if(!List.DeleteNextMthElement(InitM, &Result))
			return false;
		fprintf(fout, "<%d, %d>\n", Result.Pos, Result.Cost);
        fprintf(fout_d, "%d,",Result.Pos);
	}
    fprintf(fout_d, "\n");
    ListNode* temp = List.Demo.T;
    while(List.Demo.T->Next != temp){
        //fprintf(fout_d, "%d,", Result.Pos);
        fprintf(fout_d, "%d,", List.Demo.T->Next->Data);
        List.Demo.T->Next = List.Demo.T->Next->Next;
    }
	List.DestroyList();
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