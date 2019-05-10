#ifndef UTF8string_hpp
#define UTF8string_hpp

#include <vector>

class UTF8string {
   public:
    std::string str;
    int size;
    int byte;
    std::vector<int> byteNum;
    std::vector<int> eachChar;

    // constructor and destructor
    UTF8string();
    UTF8string(std::string);
    UTF8string(const char[]);
    UTF8string(std::string, int, int);
    UTF8string(std::string, int, int, std::vector<int>, std::vector<int>);
    ~UTF8string(){};

    // overload operator
    friend std::ostream &operator<<(std::ostream &, const UTF8string &);
    UTF8string operator+(const UTF8string &);
    void operator+=(const UTF8string &);
    UTF8string operator*(const int);
    friend UTF8string operator*(int, const UTF8string &);
    UTF8string operator!();

    // member functions
    int length();
    int bytes();
    int find(std::string);
    int replace(UTF8string, UTF8string);
};

#endif