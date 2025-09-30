//
// Created by ptskn on 14/09/2025.
//

#ifndef SAASCORE_AITEST_H
#define SAASCORE_AITEST_H


class AiTest
{
public:
    AiTest() = default;
    ~AiTest() = default;

    AiTest(const AiTest&) = default;
    AiTest(AiTest&&) noexcept = default;

    AiTest& operator=(const AiTest&) = default;
    AiTest& operator=(AiTest&&) noexcept = default;

    void loadTest();
};


#endif //SAASCORE_AITEST_H