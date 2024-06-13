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
#include "PresentationGroup.h"
#include <iostream>
#include <filesystem>

#include "PresentationPointImage.h"
#include "PresentationPointVideo.h"

PresentationGroup::PresentationGroup()
{
}

PresentationGroup::~PresentationGroup()
{
	for (auto point : m_points)
	{
		delete point;
	}
	m_points.clear();
}

void PresentationGroup::AddPoints(std::string folderPath)
{
    for (const auto& entry : std::filesystem::directory_iterator(folderPath))
    {
		std::filesystem::path p(entry.path().string());
		
		std::string extension = ExtractFileExtension(p.filename().string());

		if (extension == "png")
		{
			PresentationPointImage* img = new PresentationPointImage();
			img->SetupFromPath(entry.path().string());
			m_points.push_back(img);
		}
		else if (extension == "mp4")
		{
			PresentationPointVideo* vid = new PresentationPointVideo();
			vid->SetupFromPath(entry.path().string());
			m_points.push_back(vid);
		}
    }
}

std::string PresentationGroup::ExtractFileExtension(std::string item)
{
	if (item.size() < 4)
		return "";

	std::string ext;
	std::size_t extpos = item.find(".");
	ext = item.substr(extpos + 1);

	return ext;
}

bool PresentationGroup::IncrementPoint()
{
	m_currentPoint++;
	if (m_currentPoint >= m_points.size())
	{
		m_currentPoint = m_points.size() - 1;
		return true;
	}
	return false;
}

bool PresentationGroup::DecrementPoint()
{
	if (m_currentPoint == 0)
		return true;

	m_currentPoint--;
	return false;
}

PresentationPoint* PresentationGroup::GetPoint()
{
	if (m_currentPoint < m_points.size())
	{
		return m_points[m_currentPoint];
	}
	return nullptr;
}
