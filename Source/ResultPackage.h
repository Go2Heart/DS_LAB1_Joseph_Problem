struct ResultPackage
{
    int Pos, Cost;
};
struct ResultList
{
    int Size;
    ResultPackage *Data;
    bool InitList(int InitSize);
    bool DestroyList();
    bool Insert(ResultPackage x);
    bool PrintList(FILE* fout);
};