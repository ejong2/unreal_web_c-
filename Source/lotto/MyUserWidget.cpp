// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

void UMyUserWidget::GenerateRandomNumbers()
{

    UE_LOG(LogTemp, Log, TEXT("메서드실행실행"));


    LottoNumbers.Empty();
    while (LottoNumbers.Num() < 6)
    {
        int32 RandomNumber = FMath::RandRange(1, 45);
        if (!LottoNumbers.Contains(RandomNumber))
        {
            LottoNumbers.Add(RandomNumber);
        }
    }

    LottoNumbers.Sort(); 
}

FString UMyUserWidget::GetLottoNumbersAsString() const
{
    FString Result;
    for (int32 Number : LottoNumbers)
    {
        Result.Append(FString::FromInt(Number) + TEXT(", "));
    }

    if (Result.Len() > 0)
    {
        Result.RemoveAt(Result.Len() - 2, 2);
    }

    return Result;
}

void UMyUserWidget::OnGenerateNumbersButtonClicked()
{
    UE_LOG(LogTemp, Log, TEXT("클릭클릭"));
    GenerateRandomNumbers();

    FString ApiUrl = TEXT("http://localhost:8080/api/signup");

    // 이메일과 비밀번호를 생성합니다.
    FString Email = FString::Printf(TEXT("random_email_%d@example.com"), FMath::RandRange(1, 1000000));
    FString Password = FString::Printf(TEXT("random_password_%d"), FMath::RandRange(1, 1000000));

    // 생성된 이메일과 비밀번호를 사용하여 회원가입 API를 호출합니다.
    RequestUserApi(ApiUrl, Email, Password);

    FString NewText = GetLottoNumbersAsString();

    FString NumbersString;
    for (int32 Number : LottoNumbers)
    {
        NumbersString.Append(FString::Printf(TEXT("%d "), Number));
    }
    UE_LOG(LogTemp, Log, TEXT("난수난수: %s"), *NumbersString);

    if (LottoNumbersText)
    {
        FText NewTextAsFText = FText::FromString(NewText);
        LottoNumbersText->SetText(NewTextAsFText);
    }
}

void UMyUserWidget::RequestUserApi(const FString& ApiUrl, const FString& Email, const FString& Password)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
    HttpRequest->SetVerb("POST");
    HttpRequest->SetURL(ApiUrl);
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField("email", Email);
    JsonObject->SetStringField("password", Password);

    FString RequestBodyString;
    TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&RequestBodyString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

    HttpRequest->SetContentAsString(RequestBodyString);

    HttpRequest->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
        {
            if (bWasSuccessful)
            {
                FString ResponseStr = Response->GetContentAsString();
                UE_LOG(LogTemp, Log, TEXT("HTTP 요청 성공: %s"), *ResponseStr);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("HTTP 요청 실패"));
            }
        });

    HttpRequest->ProcessRequest();
}

void UMyUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (GenerateNumbersButton)
    {
        GenerateNumbersButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnGenerateNumbersButtonClicked);
    }

    if (LoginButton)
    {
        LoginButton->OnClicked.AddDynamic(this, &UMyUserWidget::OnLoginButtonClicked);
    }
}

void UMyUserWidget::OnLoginButtonClicked()
{
    FString Email = "random_email_336345@example.com"; // 실제 이메일로 변경
    FString Password = "random_password_992890"; // 실제 비밀번호로 변경

    FString LoginUrl = TEXT("http://localhost:8080/api/login");
    RequestUserApi(LoginUrl, Email, Password);
}
