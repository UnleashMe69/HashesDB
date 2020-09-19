# Usage example

So, you first need to import your hashes.
Let's say you have a file containing your hashes in the following format
hash:plaintext such as sql5.hashes included in the example folder.

After building HashesDB or using the compiled executable included, you then use the following command to:

1. Create a database named SQL5_db
2. Import your hashes from sql5.hashes to SQL5_db and you specify the hash type: SQL5
```bash
HashesDB.exe -i sql5.hashes SQL5 SQL5_db
```

At this point, your new database named SQL5_db is created (the db is a folder, containing many many files depending on the database size. You should not edit those files under any circumstances) and all hashes from sql5.hashes should be successfully imported.

The output should look like something like the following:

```bash
database created with success.
counting lines in pot file
1000 lines to import.
importing lines from pot file to database...

0% 10 20 30 40 50 60 70 80 90 100%
|----|----|----|----|----|----|----|----|----|----|
***************************************************
0 seconds to import 1000 lines.
```

Now, for cracking some hashes, you can download CMIYC.sql5 file containing randomly selected hashes from sql5.hashes.
To test the cracking process let's use the following command:

```bash
HashesDB.exe -c CMIYC.sql5 SQL5_db
```

At this point, HashesDB reads all hashes from CMIYC.sql5 and will look into the database sql5.hashes created previously if it contains the hashes we want to crack.
HashesDB then prints the cracked hashes in a new file named cracked_hashes.txt
The output should look something like the following:

```bash
counting number of hashes to crack
cracking hashes now...
0% 10 20 30 40 50 60 70 80 90 100%
|----|----|----|----|----|----|----|----|----|----|
***************************************************
0 seconds to crack 230 hashes.
```
