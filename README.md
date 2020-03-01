# SimpleApiForPly


SAP (Simple Api for Ply) is a C++ event-driven mechanism for parsing Ply (https://en.wikipedia.org/wiki/PLY_(file_format)) files. 

SAP is similar to SAX (Simple Api for Xml): it issues parsing events for Ply elements and their properties, while making a serial pass through the Ply file input stream.

To use SAP you just need to create a class that implements the IPlyContentHandler and IPlyErrorHandler interfaces. 

Refer to the Example folder for an example of how to use SAP.