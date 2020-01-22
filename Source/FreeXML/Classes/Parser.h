
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Parser.generated.h"

class FXmlFile;

/* A struct representing the properties of an XML node */
USTRUCT(BlueprintType)
struct FBpXmlNode
{
	GENERATED_BODY()

	/* The value of the node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Value;

	/* The tag of the node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Tag;

	FBpXmlNode()
	{
		Value = FString();
		Tag = FString();
	}

	FBpXmlNode(FString ValueP, FString TagP)
	{
		Value = ValueP;
		Tag = TagP;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNextNode, FBpXmlNode, Node);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedParsing);

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

	/* Called when the parsing loop reaches the next node */
	UPROPERTY(BlueprintAssignable, Category = "F2P-Entertainment|Xml Parser")
	FNextNode OnNextNode;

	/* Called when the parsing loop finishes his task */
	UPROPERTY(BlueprintAssignable, Category = "F2P-Entertainment|Xml Parser")
	FFinishedParsing OnParsingFinished;

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

	/**
	 * Starts iterating over each node of a file
	 * Calls OnNextNode
	 */
	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	void StartParsing();

	/**
	 * Returns the root node of the file
	 * @return A FBpXmlStruct representing the root node
	*/
	UFUNCTION(BlueprintPure, Category = "F2P-Entertainment|Xml Parser")
	FBpXmlNode GetRoot();
};
