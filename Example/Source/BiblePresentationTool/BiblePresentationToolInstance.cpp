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

#include "BiblePresentationToolInstance.h"
#include <filesystem>

UBiblePresentationToolInstance::UBiblePresentationToolInstance()
{

}

UBiblePresentationToolInstance::~UBiblePresentationToolInstance()
{
}

void UBiblePresentationToolInstance::Init()
{
	m_presentationParser = new PresentationParser();
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string outPath = cwd.string() + "\\PresentationData";
	m_presentationParser->SetupFiles(outPath);

	FString name = cwd.c_str();
	UE_LOG(LogTemp, Warning, TEXT("PRESENTATION FOLDER: %s"), *name);
}

void UBiblePresentationToolInstance::Shutdown()
{
	if (m_presentationParser)
	{
		delete m_presentationParser;
		m_presentationParser = nullptr;
	}
}

void UBiblePresentationToolInstance::IncrementPoint()
{
	bool nextGroupSeen = false;
	PresentationGroup* nextGroup = m_presentationParser->GetNextGroup();

	if(nextGroup)
		nextGroupSeen = nextGroup->GetViewed();

	if (m_presentationParser->AdvanceGroup() && !nextGroupSeen)
	{
		ClosePoint();
	}
	else
	{
		ShowPoint();
	}
}

void UBiblePresentationToolInstance::DecrementPoint()
{
	if (m_presentationParser->ReverseGroup())
	{
		ShowPoint();
	}
}

void UBiblePresentationToolInstance::ShowPoint()
{
	if (m_hud)
	{
		PresentationGroup* group = m_presentationParser->GetGroup();
		group->SetViewed();
		PresentationPoint* point = group->GetPoint();
		FString path = point->GetFilePath().c_str();
		if (point->GetType() == PresentationPointType::Image)
		{
			m_hud->SetImage(path);
		}
		else if (point->GetType() == PresentationPointType::Video)
		{
			m_hud->SetVideo(path);
		}

		m_hudOpen = true;
	}
}

void UBiblePresentationToolInstance::ClosePoint()
{
	if (m_hud)
	{
		m_hud->ClosePoint();
		m_hudOpen = false;
	}
}

bool UBiblePresentationToolInstance::IsHudOpen()
{
	return m_hudOpen;
}

int UBiblePresentationToolInstance::GetPointIndex()
{
	return m_presentationParser->GetGroupIndex();
}

void UBiblePresentationToolInstance::SetQuestString(const FString& questTitle)
{
	if (m_hud)
	{
		m_hud->SetQuestTitle(questTitle);
	}
}
