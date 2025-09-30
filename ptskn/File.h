//
// Created by ptskn on 12/09/2025.
//

#ifndef SAASCORE_FILE_H
#define SAASCORE_FILE_H
// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "String.h"
#include "asio/ssl/stream.hpp"

namespace std
{

    class IMFile
    {
    public:
        static bool exists(const char *path)
        {
            return filesystem::exists(path);
        }

        static auto getSize(const char *path)
        {
            return filesystem::file_size(path);
        }




    };
class IMOutputFile : public IMFile
{
public :
    static ofstream open (const char *path)
    {
        return ofstream(path);
    }
    static void close(ofstream& f)
    {
        f.close();
    }
    static void write (ofstream *s,const char *dest, const char* data)
    {
        *s << data;
    }
    static void saveBinary(const char *path, const char *data, const size_t size)
    {
        ofstream f(path, ios::binary);
        f.write(data, size);
        f.close();
    }
};
class IMInputFile : public IMFile
{
public :
    static ifstream open (const char *path)
{
    return ifstream(path);
}
    static void close(ifstream& f)
{
    f.close();
}
    static ifstream readBinary(const char *path, char *data, const size_t size)
{
    ifstream f(path, ios::binary);
    f.read(data, size);
    return f;
}
    static string readString(const char *path)
{
    const ifstream f(path);
    return string(istreambuf_iterator<char>(f.rdbuf()), istreambuf_iterator<char>());
}

    /**
     *
     * @param f
     * @param lineRegex
     * @return 2d vector of strings, splitted by lines and regex
     */
    static vector<vector<string>> get2DStringsVector(ifstream& f,regex &lineRegex)
{
    IMString tokenizer;
    vector<vector<string>> arr;
    // tokenize
    string line;
    while (getline(f, line))
    {
        vector<vector<string>> splittedLines=tokenizer.tokenize(line,lineRegex);
        for (auto& l:splittedLines)
            arr.push_back(l);
    }
    return arr;
    }

    /**
     *
     * @param stream
     * @return vector of strings extracted from file's lines
     */
    static vector<string> getStringsVector(ifstream &stream)
    {
    vector<string> arr;
    string line;
    while (getline(stream, line))
    {
        arr.push_back(line);
    }
    return arr;
    }
        static bool isOpened(ifstream* f)
    {
        return f->is_open();
    }

};

}
#endif //SAASCORE_FILE_H