

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
    FXmlNode* Root = CurrentFile->GetRootNode();
    OnNextNode.Broadcast(FBpXmlNode(Root->GetContent(), Root->GetTag()));
    TArray<FXmlNode*> Children = Root->GetChildrenNodes();
    for(FXmlNode* Node : Children)
    {
        OnNextNode.Broadcast(FBpXmlNode(Node->GetContent(), Node->GetTag()));
    }
    OnLastNode.Broadcast();
}

/* Gets the root node of the file */
FBpXmlNode UParser::GetRoot()
{
    if(!CurrentFile->IsValid())
    {
        return FBpXmlNode();
    }
    return FBpXmlNode(CurrentFile->GetRootNode()->GetContent(), CurrentFile->GetRootNode()->GetTag());
}