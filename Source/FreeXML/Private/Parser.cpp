

#include "Parser.h"
#include "XmlFile.h"
#include "XmlNode.h"
#include "Misc/Paths.h"

/* Creates a UParser object */
UParser* UParser::CreateParser()
{
    return NewObject<UParser>();
}

/* Tries to load an xml file */
bool UParser::LoadFile(const FString Path)
{
    if(!FPaths::FileExists(Path))
    {
        return false;
    }
    CurrentFile = new FXmlFile(Path);
    return CurrentFile->IsValid();
}

/* Unloads a file */
void UParser::UnloadFile()
{
    CurrentFile->~FXmlFile();
}

/* Starts parsing */
void UParser::StartParsing()
{
    ParseNode(CurrentFile->GetRootNode());
    OnParsingFinished.Broadcast();
}

void UParser::ParseNode(FXmlNode* Node)
{
    TArray<FBPXmlAttribute> Attributes;
    for(const FXmlAttribute Attribute : Node->GetAttributes())
    {
        Attributes.Add(FBPXmlAttribute(Attribute.GetTag(), Attribute.GetValue()));
    }
    OnNextNode.Broadcast(FBPXmlNode(Node->GetContent(), Node->GetTag(), Attributes));
    Attributes.Empty();
    TArray<FXmlNode*> Children = Node->GetChildrenNodes();
    for(FXmlNode* ChildNode : Children)
    {
        ParseNode(ChildNode);
    }
}

/* Gets the root node of the file */
FBPXmlNode UParser::GetRoot()
{
    if(!CurrentFile->IsValid())
    {
        return FBPXmlNode();
    }
    TArray<FBPXmlAttribute> Attributes;
    for(const FXmlAttribute Attribute : CurrentFile->GetRootNode()->GetAttributes())
    {
        Attributes.Add(FBPXmlAttribute(Attribute.GetTag(), Attribute.GetValue()));
    }
    return FBPXmlNode(CurrentFile->GetRootNode()->GetContent(), CurrentFile->GetRootNode()->GetTag(), Attributes);
}