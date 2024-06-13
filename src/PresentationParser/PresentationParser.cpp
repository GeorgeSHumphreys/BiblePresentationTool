/*MIT License

Copyright (c) 2024 George Humphreys

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include "PresentationParser.h"
#include <iostream>
#include <filesystem>
#include "PresentationGroup.h"

PresentationParser::PresentationParser()
{
}

PresentationParser::~PresentationParser()
{
    for (auto group : m_groups)
    {
        delete group;
    }
    m_groups.clear();
}

void PresentationParser::SetupFiles(std::string path)
{
    if (std::filesystem::exists(path))
    {
        for (const auto& entry : std::filesystem::directory_iterator(path))
        {
            PresentationGroup* group = new PresentationGroup();

            if (entry.is_directory())
            {
                group->AddPoints(entry.path().string());
            }
            m_groups.push_back(group);
        }
    }
}

bool PresentationParser::AdvanceGroup()
{
    if (PresentationGroup* group = GetGroup())
    {
        bool result = group->IncrementPoint();
        if (result)
        {
            IncrementGroup();
            return true;
        }
    }
    return false;
}

bool PresentationParser::ReverseGroup()
{
    if (PresentationGroup* group = GetGroup())
    {
        bool result = group->DecrementPoint();
        if (result)
        {
            DecrementGroup();
            return true;
        }
    }
    return false;
}

PresentationGroup* PresentationParser::GetGroup()
{
    if (m_currentGroup < m_groups.size())
    {
        return m_groups[m_currentGroup];
    }
    return nullptr;
}

PresentationGroup* PresentationParser::GetNextGroup()
{
    if (m_currentGroup + 1 < m_groups.size())
    {
        return m_groups[m_currentGroup + 1];
    }
    return nullptr;
}

void PresentationParser::IncrementGroup()
{
    m_currentGroup++;
    if (m_currentGroup >= m_groups.size())
    {
        m_currentGroup = m_groups.size() - 1;
    }
}

void PresentationParser::DecrementGroup()
{
    if (m_currentGroup != 0)
        m_currentGroup--;
}
