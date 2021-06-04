## Table of Contents
* [Usage](#usage)
   * [Creating the Parser](#creating-the-parser)
   * [Loading a File](#loading-the-file)
   * [Event Bindings](#creating-the-event-bindings)
   * [Start Parsing](#start-parsing)
   * [Manipulating a Node](#manipulating-a-node)
   * [Saving a File](#saving-your-changes)

# Usage   

## Creating the Parser    

The first step is to create a Parser Object Reference using the [Create Parser](API/1.0#create-parser) node. You have to save the output of this node as a variable! Doing otherwise will result in a new parser being created every time you use the return value, making it useless.   
![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/creating_parser.jpg)

## Loading the File

With your newly created Parser Object Reference you can call the [Load File](API/1.0#load-file) node. The path to the file has to be an absolute path and must include the extension `.xml`!
The Boolean that gets returned is for your error handling only. You can safely call all other parsing related nodes on a parser with no file: They will just do nothing.   
![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/load.jpg)

## Creating the Event Bindings

At the current state (1.0) you can only parse a file with the help of events. In order to do so, we have to bind a custom event to the [On Next Node](API/1.0#on-next-node) delegate.  
**Tip:** If you drag the event pin of the "Bind Event to On Next Node" node to an empty space in your blueprint graph, you can create a custom event with the matching "Node" pin easily!

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/next_node.jpg)

Now all you need to do is to use the [BPXmlNode](API/1.0#bpxmlnode) struct that is returned by the event to do what you want! You could simply save it away, or look for specific values / tags.

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/parsing.jpg)

You should also consider binding an event to the [On Parsing Finished](API/1.0#on-parsing-finished) delegate. Using this event you'll know when the parsing is done!

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/finished.jpg)

## Start Parsing!

To start the actual parsing process you have to simply call the [Start Parsing](API/1.0#start-parsing) node. It is as easy as that!

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/start.jpg)

## Manipulating a Node

There are two ways to manipulate a node:
1. You can change its content / value using one of the [Set Content](API/1.0#set-content) nodes:

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/set_content.jpg)

2. You can append new nodes to it using one of the [Append Node](API/1.0#append-node) nodes:

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/append.jpg)

## Saving your changes

When you are done you have to save your changes with the [Save File](API/1.0#save-file) node. By default, the file is saved with the same path used when loading, but you can override the location here with an absoulte path include the `.xml` extension.

![image](https://raw.githubusercontent.com/wiki/Free2Play-Entertainment/FreeXML/images/save_file.jpg)
