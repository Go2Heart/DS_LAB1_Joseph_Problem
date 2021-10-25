#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<string>
using namespace std;
int GetLive(int Cur, int InitM)
{
	if(Cur == 1)return 1;
	return (GetLive(Cur - 1, InitM) + InitM - 1) % Cur + 1;
}
int main()
{
	srand(time(NULL));
	string prefix1, prefix2, suffix1, suffix2, now;
	prefix1 = "TestData/Input",prefix2 = "test", suffix1 = ".in",suffix2 = ".out";
	for(int TestRound = 1; TestRound <= 4; TestRound++)
	{
	//此循环用来自动将我们设计好的4个测试用例(TestData/Input.in)载入test.in以供main.cpp读取
	//并将运行结果与TestData文件夹下内置的输出文件 调用cmd中 fc指令进行比较
	//若比较无误则会输出  Test xx Passed!  字样
		char tmp[20];
		int InitN, InitM;
		itoa(TestRound, tmp, 10);
		now = tmp;
		FILE *fin = fopen((prefix1 + now + suffix1).c_str(), "r");
		FILE *testin = fopen((prefix2 + suffix1).c_str(), "w");
		fscanf(fin, "%d%d", &InitN, &InitM);
		fprintf(testin, "%d %d\n", InitN, InitM);
		fclose(fin);
		fclose(testin);
		system("Test");
		string prefix3 = "fc AnsByArray.out TestData/AnsByArray";
		string prefix4 = "fc AnsByLink.out TestData/AnsByLink";
		if(system((prefix3 + now + suffix2).c_str()) || system((prefix4 + now + suffix2).c_str()))
		{
			puts("ERROR!");
			return 0;
		} else 
		{
			fprintf(stderr, "Test %d Passed!\n", TestRound);
		}
	}
	fprintf(stderr, "Fixed TestData(Test 1~4) Passed!\n");
	for(int TestRound = 5; TestRound <= 10 ; TestRound++)
	{   
	//此循环将自动生成6组随机数据载入test.in以供main.cpp读取
	//并将运行结果与本程序中使用GetLive程序得到的答案 调用cmd中 fc指令进行比较
	//若比较无误则会输出  Test xx Passed!  字样
		int InitN = rand() % 2000 +1, InitM = rand() % 5000 + 1;
		FILE *testin = fopen((prefix2 + suffix1).c_str(), "w");
		fprintf(testin, "%d %d\n", InitN, InitM);
		fclose(testin);
		FILE *testout = fopen("CorrectAnswer.out", "w");
		if(InitN > 0 && InitM > 0) fprintf(testout, "%d\n", GetLive(InitN,InitM));
		else fprintf(testout, "ERROR!\n");
		fclose(testout);
		system("Test");
		if(system("fc AnsForChecker.out CorrectAnswer.out"))
		{
			puts("ERROR!");
			return 0;
		} else 
		{
			fprintf(stderr, "Test %d Passed!\n", TestRound);
		}
	}
	fprintf(stderr, "Random TestData(Test 5~10) Passed!\n");
}
