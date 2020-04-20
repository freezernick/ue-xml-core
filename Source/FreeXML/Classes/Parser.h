
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Parser.generated.h"

class FXmlFile;
class FXmlNode;

/* A struct representing attributes of an XML tag */
USTRUCT(BlueprintType)
struct FBPXmlAttribute
{
	GENERATED_BODY()

	/* The name of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Name;

	/* The value of the attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Value;

	FBPXmlAttribute()
	{
		Name = "";
		Value = "";
	}

	FBPXmlAttribute(const FString NameP, const FString ValueP)
	{
		Name = NameP;
		Value = ValueP;
	}
};

/* A struct representing the properties of an XML node */
USTRUCT(BlueprintType)
struct FBPXmlNode
{
	GENERATED_BODY()

	/* The tag of the node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Tag;

	/* The value of the node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	FString Value;

	/* The attributes of the node */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "F2P-Entertainment|Xml Parser")
	TArray<FBPXmlAttribute> Attributes;

	FBPXmlNode()
	{
		Tag = "";
		Value = "";
		Attributes = TArray<FBPXmlAttribute>();
	}

	FBPXmlNode(const FString ValueP, const FString TagP, const TArray<FBPXmlAttribute> AttributesP)
	{
		Tag = TagP;
		Value = ValueP;
		Attributes = AttributesP;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNextNode, FBPXmlNode, Node);
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

	const FString Meta = "<?xml version=\"1.0\"?>\n";

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

	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	bool CreateXml(const FString RootNode, const FString SavePath);

	FString DefaultPath;

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
	 * The actual parsing
	 * @param Node The node that should be parsed
	 * Calls ParseNode on all child-nodes
	 */
	void ParseNode(FXmlNode* Node);

	/**
	 * Returns the root node of the file
	 * @return A FBpXmlStruct representing the root node
	*/
	UFUNCTION(BlueprintPure, Category = "F2P-Entertainment|Xml Parser")
	FBPXmlNode GetRoot();

	/**
	 * Saves the Xml to the path where it was opened or the to the specified path
	 * @param OverwritePath Specify an absolute path to where to save the Xml into
	 * @return Whether the Xml could be saved or not
	 */
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = "OverwritePath"), Category = "F2P-Entertainment|Xml Parser")
	bool SaveFile(FString OverwritePath);

	/**
	 * Updates the content / value of the specified node
	 * @param Node The node with the altered content / value
	 */
	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	void SetContent(const FBPXmlNode Node) const;


	/**
	 * Updates the content / value of the specified node
	 * @param Node The node with the changed content / value
	 * @param Parser A reference to a UParser object with the loaded XML
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Content"), Category = "F2P-Entertainment|Xml Parser")
	static void UpdateContent(FBPXmlNode Node, UParser* Parser);

	/**
	 * Appends a new node to the specified node
	 * @param Parent The node to add the Child to
	 * @param Child The new node
	 */
	UFUNCTION(BlueprintCallable, Category = "F2P-Entertainment|Xml Parser")
	void AppendNode(const FBPXmlNode Parent, const FBPXmlNode Child);

	/**
	 * Appends a new node to the specified node
	 * @param Parent The node to add the Child to
	 * @param Child The new node
	 * @param Parser A reference to a UParser object with a loaded XML
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Append Node"), Category = "F2P-Entertainment|Xml Parser")
	static void AppendChildNode(const FBPXmlNode Parent, const FBPXmlNode Child, UParser* Parser);
};
