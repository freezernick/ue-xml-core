## Structs

### BPXmlAttribute

![grafik](https://user-images.githubusercontent.com/27819706/120815026-be41be80-c54f-11eb-9d58-48c6237b70aa.png)


This struct represents an attribute of a node of an XML file. It consists of the attribute's name and its value.

### BPXmlNode

![grafik](https://user-images.githubusercontent.com/27819706/120815076-cb5ead80-c54f-11eb-931a-71b771582e45.png)

This struct represents a node of an XML file. It consists of the node's tag (the name), value (the content between the tags), and an array of attributes represented by BPXmlAttribute structs.

# Classes

## Parser

### Static Functions

#### Create Parser

![grafik](https://user-images.githubusercontent.com/27819706/120814975-b124cf80-c54f-11eb-9d50-1fc1b974652f.png)

Creates a new Parser object reference.

#### Set Content

![grafik](https://user-images.githubusercontent.com/27819706/120815117-d6194280-c54f-11eb-87fa-da603f14a778.png)

This node does nothing else than to call the Parser's member function Set Content. Having this (static) function allows that you can drag a BPXmlNode struct reference and call "Set Content" directly on it. This only matters for users with enabled context sensitivity: Every other user would also see the member function.

#### Append Node

![grafik](https://user-images.githubusercontent.com/27819706/120815185-e29d9b00-c54f-11eb-8b22-ce38ae7d7fab.png)

This node does nothing else than to call the Parser's member function Append Node. Having this (static) function allows that you can drag a BPXmlNode struct reference and call "Append Node" directly on it. This only matters for users with enabled context sensitivity: Every other user would also see the member function.

### Events / Delegates

#### On Next Node

![grafik](https://user-images.githubusercontent.com/27819706/120815299-f6e19800-c54f-11eb-808f-6adc0b63fb62.png)

This delegate gets called when the iterator created by Start Parsing reaches the next node. It has one BPXmlNode struct parameter representing the current node.
#### On Parsing Finished

![grafik](https://user-images.githubusercontent.com/27819706/120815364-095bd180-c550-11eb-9f50-819333f5e7e5.png)

This delegate gets called right after the last On Next Node call. It has no parameters.

### Public Member Functions
#### Append Node
![grafik](https://user-images.githubusercontent.com/27819706/120815491-27c1cd00-c550-11eb-95ad-c99c35e3f5ae.png)

This node allows to append a new XML node represented by a BPXmlNode struct to a specified parent node, also represented by a BPXmlNode struct.
#### Get Root

![grafik](https://user-images.githubusercontent.com/27819706/120815520-301a0800-c550-11eb-9fd8-79eb487f68de.png)

This node returns a BPXmlNode struct representing the root node of a currently loaded XML file.
#### Load File

![grafik](https://user-images.githubusercontent.com/27819706/120815552-37411600-c550-11eb-9d93-6277ff54b384.png)

Loads the file at the specified path. It has to be absoulte and include the .xml extension.
#### Start Parsing

![grafik](https://user-images.githubusercontent.com/27819706/120815576-3f995100-c550-11eb-8422-1dfa48140192.png)

Starts the parsing process. It calls the On Next Node delegate on each node parsed. When the On Next Node delegate for the last node was triggered it calls the On Parsing Finished delegate.
#### Set Content

![grafik](https://user-images.githubusercontent.com/27819706/120815615-47f18c00-c550-11eb-8367-f7dd34685753.png)

Changes the content between two tags.
#### Save File

![grafik](https://user-images.githubusercontent.com/27819706/120815660-517af400-c550-11eb-88ce-41c349992ce4.png)

Saves the changes to the disk. By default, the path of the loaded file is used but this can be overwritten with the optional "Overwrite Path" parameter. It has to be an absolute path including the .xml file extension.
#### Unload File

![grafik](https://user-images.githubusercontent.com/27819706/120815684-59d32f00-c550-11eb-8057-aadc65122dd5.png)

Frees the allocated resources.
