// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h" 
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class LOTTO_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:
    UFUNCTION(BlueprintCallable, Category = "Lotto")
        void GenerateRandomNumbers();

    UFUNCTION(BlueprintCallable, Category = "Lotto")
        FString GetLottoNumbersAsString() const;

    UFUNCTION()
        void OnGenerateNumbersButtonClicked();

    UFUNCTION()
        void RequestUserApi(const FString& ApiUrl, const FString& Email = TEXT(""), const FString& Password = TEXT(""));

    UFUNCTION()
        void OnLoginButtonClicked();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lotto")
        TArray<int32> LottoNumbers;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lotto", meta = (BindWidget))
        class UButton* GenerateNumbersButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lotto", meta = (BindWidget))
        class UButton* LoginButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lotto", meta = (BindWidget))
        class UTextBlock* LottoNumbersText;

    virtual void NativeConstruct() override; // �߰�
};