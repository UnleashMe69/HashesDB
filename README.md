# HashesDB
Store your cracked hashes or your pot file in an embedded database.

For now, only leveldb is supported.

Requirements:
To build the project, leveldb library need to be installed and linked to the project.
Boost library need to be linked to the project.

Usage:
HashesDB has 2 functions:
  -i to import cracked hashes or a pot file in a newly created database.
  -c to crack hashes from a file using the database previously created.
  
The algorithms currently supported are:
  - any hash function 32 char long (MD5, NTLM ...)
  - any hash function 40 char long (SHA1, MySQL4.1/5 ...)

In case you do not want to build the project. a release (windows only) is available to download.

For a complete usage example, you can take a deeper look [here](https://github.com/UnleashMe69/HashesDB/blob/master/example/ReadMe.md)

## Full Disclaimer
**I do not repond to cracking requests! You can crack your own sh!t!**

**HashesDB does not and cannot crack hashes from thin air!**

**HashesDB is just an embedded database to store your _previously_ cracked hashes.**

**Using HashesDB means you have the permission of the owner to crack those hashes and to store them in your database.**

**In no way, I can be held responsible for the misuse of HashesDB and YOU as the _user_ takes full responsibility for your actions using HashesDB!**
