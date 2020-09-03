# HashesDB
Store your cracked hashes or your pot file in an embedded database.

For now, only leveldb is supported.

Requirements:
leveldb library need to be installed and linked to the project.
Boost library need to be linked to the project.

Usage:
HashesDB has 2 functions:
  -i to import cracked hashes or a pot file in a newly created database.
  -c to crack hashes from a file using the database previously created.
  
The algorithms currently supported are:
  - any hash function 32 char long (MD5, NTLM ...)
  - any hash function 40 char long (SHA1, MySQL4.1/5 ...)

Current release is windows only.
