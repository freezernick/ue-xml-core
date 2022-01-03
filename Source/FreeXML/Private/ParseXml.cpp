

#include "ParseXml.h"

UParseXml* UParseXml::ParseXml(const FString Path)
{
    UParseXml* ParserNode = NewObject<UParseXml>();
    ParserNode->Path = Path;
    return ParserNode;
}

void UParseXml::Activate()
{

}