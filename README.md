# Yune-OBJ-Parser

This is a sub-repository for Yune's parser, maintained in order to be seperately able to provide updates.

Use Yune-OBJ-Parser to convert .OBJ files to .rtt format which is supported by the Yune Renderer. Some requirements for the parser to succesfully convert the files are:

* Make sure the files are in .OBJ format.
* Grouping must be on.
* The tags used for grouping must either start with a 'g' or with an 'o'.

## Steps to convert:

* Extract the parser.
* Place the desired .OBJ file into the 'imports' folder.
* Run the parser and type in the name of the file.
* Wait until the parser tell you of the completion of conversion.
* Recover the converted file from the exports folder.
