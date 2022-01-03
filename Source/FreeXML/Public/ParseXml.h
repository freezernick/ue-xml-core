
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ParseXml.generated.h"

/**
 * 
 */
UCLASS()
class FREEXML_API UParseXml : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

private:

	FString Path;

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UParseXml* ParseXml(const FString Path);

	// UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~UBlueprintAsyncActionBase interface
};
