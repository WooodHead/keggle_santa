#ifndef FILE_PROVIDER
#define FILE_PROVIDER

#include <string>

using namespace std;

class file_provider;

const file_provider & file_prov();

class file_provider final{
public:
    string	BasePath(){return base_path;}

    inline
    string DataFile() const;

    inline
    string PathFile(string name) const;

    inline
    string sol_file1() const;

    inline
    string sol_file3() const;

    inline
    string sol_file6() const;

    inline
    string sol_file7() const{
        return PathFile("sol7.csv");
    }

    inline
    string sol_file9() const{
        return PathFile("sol9.csv");
    }

    inline
    string sol_file10() const{
        return PathFile("sol10.csv");
    }

    inline
    string sol_file11() const{
        return PathFile("sol11.csv");
    }

    inline
    string sol_file() const;

private:
    file_provider(){}

    #ifdef __linux
    string base_path = "/home/alexey/santa_data/";
    #else
    string base_path = "C:\\Users\\alexey\\Downloads\\";
    #endif

    friend
    const file_provider & file_prov();
};

string file_provider::DataFile() const{
    string res = base_path + "gifts.csv";
    return res;
}

string file_provider::PathFile(string name) const{
    return  base_path + name;
}

string file_provider::sol_file1() const{
    return PathFile("sol1.csv");
}

string file_provider::sol_file3() const{
    return PathFile("sol3.csv");
}

string file_provider::sol_file6() const{
    return PathFile("sol6.csv");
}

string file_provider::sol_file() const{
    return PathFile("sol.csv");
}



//#ifdef linux
//auto data_file = "/home/alexey/santa_data/gifts.csv";
//auto sol_file1 = "/home/alexey/santa_data/sol1.csv";
//auto sol_file = "/home/alexey/santa_data/sol.csv";
//auto sol_file6 = "/home/alexey/santa_data/sol6.csv";

//#else
//auto data_file = "C:\\Users\\alexey\\Downloads\\gifts.csv";
//auto sol_file1 = "C:\\Users\\alexey\\Downloads\\sol1.csv";
//auto sol_file = "C:\\Users\\alexey\\Downloads\\sol.csv";
//auto sol_file6 = "C:\\Users\\alexey\\Downloads\\sol6.csv";
//#endif
//auto sol_file2 = "/home/alexey/santa_data/sol2.csv";
//auto sol_file3 = "/home/alexey/santa_data/sol3.csv";
//auto sol_file4 = "/home/alexey/santa_data/sol4.csv";


#endif // FILE_PROVIDER

