## Structs

### BPXmlAttribute

image

This struct represents an attribute of a node of an XML file. It consists of the attribute's name and its value.

### BPXmlNode

image

This struct represents a node of an XML file. It consists of the node's tag (the name), value (the content between the tags), and an array of attributes represented by BPXmlAttribute structs.

# Classes

## Parser

### Static Functions

#### Create Parser

image

Creates a new Parser object reference.

#### Set Content

image

This node does nothing else than to call the Parser's member function Set Content. Having this (static) function allows that you can drag a BPXmlNode struct reference and call "Set Content" directly on it. This only matters for users with enabled context sensitivity: Every other user would also see the member function.

#### Append Node

image

This node does nothing else than to call the Parser's member function Append Node. Having this (static) function allows that you can drag a BPXmlNode struct reference and call "Append Node" directly on it. This only matters for users with enabled context sensitivity: Every other user would also see the member function.

### Events / Delegates

#### On Next Node

image

This delegate gets called when the iterator created by Start Parsing reaches the next node. It has one BPXmlNode struct parameter representing the current node.
#### On Parsing Finished

image

This delegate gets called right after the last On Next Node call. It has no parameters.

### Public Member Functions
#### Append Node

image

This node allows to append a new XML node represented by a BPXmlNode struct to a specified parent node, also represented by a BPXmlNode struct.
#### Get Root

image

This node returns a BPXmlNode struct representing the root node of a currently loaded XML file.
#### Load File

image

Loads the file at the specified path. It has to be absoulte and include the .xml extension.
#### Start Parsing

image

Starts the parsing process. It calls the On Next Node delegate on each node parsed. When the On Next Node delegate for the last node was triggered it calls the On Parsing Finished delegate.
#### Set Content

image

Changes the content between two tags.
#### Save File

image

Saves the changes to the disk. By default, the path of the loaded file is used but this can be overwritten with the optional "Overwrite Path" parameter. It has to be an absolute path including the .xml file extension.
#### Unload File

image

Frees the allocated resources.