

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
    DefaultPath = Path;
    return CurrentFile->IsValid();
}

bool UParser::CreateXml(const FString RootNode, const FString Path)
{
    CurrentFile = new FXmlFile(Meta + "<" + RootNode + ">\n" "</" + RootNode + ">");
    DefaultPath = Path;
    return CurrentFile->IsValid();
}

/* Unloads a file */
void UParser::UnloadFile()
{
    DefaultPath = "";
    CurrentFile->~FXmlFile();
}

/* Starts parsing */
void UParser::StartParsing()
{
    ParseNode(CurrentFile->GetRootNode());
    OnParsingFinished.Broadcast();
}

/* The actual parsing */
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

/* Saves the currently loaded Xml */
bool UParser::SaveFile(FString OverwritePath = "")
{
    if(!CurrentFile->IsValid()) { return false; }

    return CurrentFile->Save(OverwritePath == "" ? DefaultPath : OverwritePath);
}

/* Changes the content / value a node */
void UParser::SetContent(const FBPXmlNode BP) const
{
    FXmlNode* Node = CurrentFile->GetRootNode()->FindChildNode(BP.Tag);
    if(!Node) { return; }
    Node->SetContent(BP.Value);
}

/* Helper for Context Sensitivity */
void UParser::UpdateContent(FBPXmlNode Node, UParser* Parser)
{
    if(!Parser) { return; }
    Parser->SetContent(Node);
}

/* Appends a new node to the selected node */
void UParser::AppendNode(const FBPXmlNode Parent, const FBPXmlNode Child)
{
    if(!CurrentFile->IsValid()) { return; }
    FXmlNode* Node = CurrentFile->GetRootNode();
    if(Parent.Tag != Node->GetTag())
    {
        Node = Node->FindChildNode(Parent.Tag);
    }
    if(!Node) { return; }
    Node->AppendChildNode(Child.Tag, Child.Value);
}

/* Helper for Context Sensitivity */
void UParser::AppendChildNode(const FBPXmlNode Parent, const FBPXmlNode Child, UParser* Parser)
{
    if(!Parser) { return; }
    Parser->AppendNode(Parent, Child);
}