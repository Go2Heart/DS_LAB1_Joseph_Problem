#include<cstdio>
#include "ResultPackage.h"
#include "ListByArray.h"
#include "ListByLink.h"
int Debug = 0;
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
	#ifdef TEST
	{
		FILE* fdebug = fopen("AnsForChecker.out", "w");
		fprintf(fdebug, "%d\n", Result.Pos);
		fclose(fdebug);
	}
	#endif
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
		if(!List.DeleteNextMthElement(InitM, &Result)) return false;	
		Result.Cost += PreCost;
		PreCost = Result.Cost;
		if(!resultList.Insert(Result)) return false;
		fprintf(fout_d, "%d,",Result.Pos);
	}
	fprintf(fout_d, "\n");
	ListNode* temp = List.Demo.T;
	while(List.Demo.T->Next != temp){
		fprintf(fout_d, "%d,", List.Demo.T->Next->Data);
		List.Demo.T->Next = List.Demo.T->Next->Next;
	}
	resultList.PrintList(fout);
	if(!List.DestroyList()) return false;
	if(!resultList.DestroyList()) return false;
	fclose(fout);
	fclose(fout_d);
	return true;
}
int main()
{
	printf("Joseph Problem Solving\nPlease type in N,M (divided by space,such as 15 3)\n");
	int InitN, InitM;
	#ifdef TEST
	{
		FILE* fin = fopen("test.in", "r");
		fscanf(fin, "%d%d", &InitN, &InitM);
		fclose(fin);
	}
	#else 
		scanf("%d%d", &InitN, &InitM);
	#endif
	bool PassTest = 1;
	if(InitN <= 0 || InitM <= 0) 
	{
		FILE* fout = fopen("AnsByLink.out", "w");
		fprintf(fout, "ERROR!\n");
		fclose(fout);
		fout = fopen("AnsByArray.out", "w");
		fprintf(fout, "ERROR!\n");
		fclose(fout);
		PassTest = 0;
	}
	if(PassTest)
	{
		if(!SolByArray(InitN, InitM)) PassTest = 0;
		if(!SolByLink(InitN, InitM)) PassTest = 0;
	}
	if(Debug && PassTest == 0)
	{
		FILE* fdebug = fopen("AnsForChecker.out", "w");
		fprintf(fdebug, "ERROR!\n");
		fclose(fdebug);
	}
}