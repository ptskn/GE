//
// Created by ptskn on 13/09/2025.
//

#ifndef SAASCORE_STRING_H
#define SAASCORE_STRING_H
#include <string>
#include <vector>
#include <regex>
#include <iostream>
namespace std
{
    class IMString
    {
    public:

        auto tokenize(string &s,regex& regex)
        {
            vector<vector<string>> res;
            smatch matches;
            auto from=s.cbegin();
            while (regex_search(from,s.cend(),matches,regex))
            {
                int nump=matches.size();
                vector<string> vec(nump) ;
                for (auto i=0;i<nump;++i)
                {
                    vec[i]=matches[i];
                }
                res.push_back(vec);
                from=matches.suffix().first;
            }
            return res;
        }
    };
}
#endif //SAASCORE_STRING_H