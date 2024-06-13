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
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PresentationParser/PresentationParser.h"
#include "PointScreenWidget.h"
#include "BiblePresentationToolInstance.generated.h"

/**
 * 
 */
UCLASS()
class BIBLEPRESENTATIONTOOL_API UBiblePresentationToolInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBiblePresentationToolInstance();
	~UBiblePresentationToolInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	UFUNCTION(BlueprintCallable)
	void IncrementPoint();

	UFUNCTION(BlueprintCallable)
	void DecrementPoint();

	UFUNCTION(BlueprintCallable)
	void ShowPoint();

	UFUNCTION(BlueprintCallable)
	void ClosePoint();

	UFUNCTION(BlueprintCallable)
	bool IsHudOpen();

	UFUNCTION(BlueprintCallable)
	int GetPointIndex();

	UFUNCTION(BlueprintCallable)
	void SetQuestString(const FString& questTitle);

	void RegisterHud(UPointScreenWidget* hud) { m_hud = hud; }

	PresentationParser* GetPresentation() { return m_presentationParser; }

private:
	PresentationParser* m_presentationParser{ nullptr };

	UPROPERTY()
	UPointScreenWidget* m_hud{ nullptr }; // Copy from the Custom Player Controller

	bool m_hudOpen{ false };

	unsigned int m_pointIndex{ 0 };
};
