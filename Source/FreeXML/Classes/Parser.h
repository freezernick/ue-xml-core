
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "XmlFile.h"
#include "Parser.generated.h"

/**
 * A simple class to parse xml files
 */
UCLASS(Blueprintable)
class FREEXML_API UParser : public UObject
{
	GENERATED_BODY()

private:

	FXmlFile* CurrentFile;

public:

	/**
	 * Creates a UParser object
	 * @return The newly created UParser pointer / Parser Object Reference 
	 */
	UFUNCTION(BlueprintPure, Category = "F2P-Entertainment|Xml Parser")
	static UParser* CreateParser();

	/**
	 * Tries to load the specified xml file
	 * @param Path The absolute path to the file
	 * @return Whether the file could be loaded or not
	 */
	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	bool LoadFile(const FString Path);

	/**
	 * Unloads a file
	 */
	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	void UnloadFile();
};
