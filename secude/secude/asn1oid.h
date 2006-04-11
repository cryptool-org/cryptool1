/*###*****************************************
 *###
 *### SECUDE IT Security GmbH
 *###
 *### Copyright (c) 2004-2006
 *###
 *### File ./include/secude/asn1oid.h
 *###
 *### global functions:
 *###
 *###*****************************************/

/* This file defines the structure wich is used to build the
   OBJECT IDENTIFIER decoding table 
*/

typedef struct ASN1OIDTableEntry {
    int  delta_next; 
    int  index;
    char *name;
} ASN1OIDTableEntry;

/*

The oid-tree is representet by an array of OIDTableEntry's

The first child of a node is allway the next entry in the array !!

delta_next is the distance to the next object in the same subtree
there are to exeptions :

delta_next == -1 => there is no next but this node has a child
delta_next == -2 => there is no next and no child

index and name :
iso(1) => index=1,name="iso"

Example :

OIDTableEntry OIDtable[] = {
\*     0 *\ { 2, 1, "iso" },
\*     1 *\ { -2, 3, "org" },
\*     2 *\ { -1, 2, "joint-iso-ccitt" },
\*     3 *\ { 1, 4, "remote-operations" },
\*     4 *\ { -1, 5, "ds" },
\*     5 *\ { 1, 1, "module" },
\*     6 *\ { -1, 6, "objectClass" },
\*     7 *\ { 1, 0, "top" },
\*     8 *\ { 1, 1, "alias" },
\*     9 *\ { -2, 2, "country" },
};

defines the following tree :

+iso(1)
| |
| +-Àorg(3)
|
+joint-iso-ccitt(2)
  |
  +-remote-operations(4)
  |
  +-ds(5)
    |
    +-module(1)
    |
    +-objectClass(6)
      |
      +-top(0)
      |
      +-alias(1)
      |
      +-country(2)

*/




