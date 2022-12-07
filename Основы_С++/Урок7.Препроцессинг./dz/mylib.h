namespace my {
#pragma pack(push,1)
    struct Employee {
        long id;
        unsigned short age;
        double salary;
    };
#pragma pack(pop)

    void initArr (const size_t, float *);

    void printArray(const size_t, const float *);
    void printArray(const size_t, const int *);

    void countArr(const size_t, const float *);

    int gtNmbr();

    void sortArr(const size_t, int *);

    void printStruct(Employee*);
    void printStruct(Employee*, const char*);

}