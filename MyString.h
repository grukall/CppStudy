class MyString
{
    char *string_content;
    int string_length;
    int memory_capacity;

    private:
    protected:
    public:

        //명시적 변환 지정, 암시적 변환 방지 (ex MyString s = 5 -> Error)
        explicit MyString(int capacity);
        MyString(char c);
        MyString(const char* str);

        //복사 생성자
        MyString(const MyString &str);
        ~MyString();

        //길이를 리턴한다.
        int length() const;
        //문자열 출력
        void print() const;
        //문자열 출력후 개행
        void println() const;

        MyString &assign(const char *str);
        MyString &assign(const MyString &str);

        int capacity() const;
        void reserve(int size);
        char at(int i) const;

        MyString &insert(int loc, const MyString& str);
        MyString &insert(int loc, const char* str);
        MyString &insert(int loc, char c);

        MyString &erase(int loc, int num);

        int find(int find_from, const MyString& str) const;
        int find(int find_from, const char* str) const;
        int find(int find_from, char c) const;

        int compare(const MyString& str);


        /*-------- Operator Overloading --------- */
        bool operator==(MyString &str);

};

