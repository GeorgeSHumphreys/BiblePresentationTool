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
#include "BiblePresentationToolPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABiblePresentationToolPlayerController::ABiblePresentationToolPlayerController()
{

}

void ABiblePresentationToolPlayerController::BeginPlay()
{
	Super::BeginPlay();
	m_hud = CreateWidget<UPointScreenWidget>(this, m_hudBP);
	if (m_hud)
	{
		m_hud->AddToViewport(9999);
		m_instanceCache = Cast<UBiblePresentationToolInstance>(GetGameInstance());
		m_instanceCache->RegisterHud(m_hud);
		m_instanceCache->ShowPoint();
	}
}

void ABiblePresentationToolPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ABiblePresentationToolPlayerController::AdvancePoint);
			EnhancedInputComponent->BindAction(BackAction, ETriggerEvent::Started, this, &ABiblePresentationToolPlayerController::ReversePoint);
		}
	}
}

void ABiblePresentationToolPlayerController::AdvancePoint()
{
	if (m_instanceCache)
	{
		if(m_instanceCache->IsHudOpen())
			m_instanceCache->IncrementPoint();
	}
}

void ABiblePresentationToolPlayerController::ReversePoint()
{
	if (m_instanceCache)
	{
		m_instanceCache->DecrementPoint();
	}
}
