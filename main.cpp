#include <iostream>
#include <fstream>
#include <cassert>
#include <chrono>
#include <leveldb/db.h>
#include <boost/progress.hpp>

void crack_hashes(std::string, std::string);
void import_hashes (std::string, std::string, std::string );

int main(int argc, char* argv[]){
    if ((argc <3) || (strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "-h") == 0)){
    std::cout << "\nUsage: " << argv[0] << '\n' << '\n' <<
    "-h, --help: print this help" << '\n' <<
    "-c, --crack [file name] [database name]: crack hashes in [file name] using hashes from [database name] and print results in new file" <<'\n' <<
    "-i, --import [file name] [hash name] [database name]: import a [file name] containing hashes [hash name] into [database name]" << '\n' << std::endl;
    exit(-1);
    }

    if ((strcmp(argv[1], "--crack") == 0) || (strcmp(argv[1], "-c") == 0)){
            if(argc != 4){
                std::cout << "name of the hash file or the database name is missing" << '\n'
                << "the command is -c, --crack [file name] [database name]" << std::endl;
                exit(-1);
            }
            else{
                crack_hashes(argv[2], argv[3]);
                exit(-1);
                }
    return 0;
    }


    if ((strcmp(argv[1], "--import") == 0) || (strcmp(argv[1], "-i") == 0)){
            if(argc != 5){
                std::cout << "name of the hash file or the database name is missing" << '\n'
                << "the command is -i, --import [file name] [database name]" << std::endl;
                exit(-1);
            }
            else{
                import_hashes(argv[2], argv[3], argv[4]);
                return 0;
                }
    return 0;
    }

}

void crack_hashes(std::string file_name, std::string db_name){
    leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = false;
	options.error_if_exists = false;
	leveldb::Status status = leveldb::DB::Open(options, db_name, &db);

	if (!status.ok()) {
            std::cerr << "The database '" << db_name << "' does not exists." << '\n'
            << "Please specify the name of another database or first import hashes to a new one." << std::endl;
            delete db;
            exit(-1);
	}
	else{
	    auto start = std::chrono::steady_clock::now();



        std::size_t num_lines(0);
        std::size_t counter(0); // how many hashes are cracked
        std::cout << "counting number of hashes to crack" << std::endl;
        std::string line(""); // we read one line (from hash_file) at the time and we put it in $line
        std::ifstream h_file (file_name);
        if(h_file.is_open()){
                while(getline(h_file,line)){
                        ++num_lines;
                }
        }
        line = "";
        std::ifstream hash_file (file_name);
        std::string value(""); // If found, we store the value of the key from the database in $value; it's the pair (key,value)

        std::ofstream cracked_hashes("cracked_hashes.txt");
        if (cracked_hashes.is_open()){
            leveldb::Status s;
            if(hash_file.is_open()){
                std::cout << "cracking hashes now..." << '\n' << std::endl;
                boost::progress_display show_progress(num_lines);


                    for(std::size_t it(0); it < num_lines; it++){
                        getline(hash_file,line);
                        s = db->Get(leveldb::ReadOptions(), line, &value);
                        if(value != ""){
                            cracked_hashes << line << ":" << value << std::endl;
                            ++counter;
                        }
                        line = "";
                        value = "";
                        ++show_progress;
                    }
                    }

                else{
                    std::cout << "Cannot open " << file_name << " ." << std::endl;
                    }
            }
            else{
                std::cout << "Cannot create the output file." << std::endl;
            }
            delete db;
            hash_file.close();
            cracked_hashes.close();

             auto end = std::chrono::steady_clock::now();

            if(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < 60e9){
                std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
                << " seconds to crack " << counter << " hashes." << std::endl;
            }
            else if(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < 3600e9){
                    std::cout << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
                    << " minutes to crack " << counter << " hashes." << std::endl;

            }
            else{
                std::cout << std::chrono::duration_cast<std::chrono::hours>(end - start).count()
                << " hours to crack " << counter << " hashes." << std::endl;
            }

}
}



void import_hashes (std::string file_name, std::string hash_name, std::string db_name){


    // we start measuring time of importing hashes to a new db

    std::size_t num_lines(0);


    leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	options.error_if_exists = true;
	leveldb::Status status = leveldb::DB::Open(options, db_name, &db);
	std::cout << "database created with success." << std::endl;

    leveldb::Status s;
    int len_hash(32); // length of the hash. for example, MD5 is 32 char long
    if ((hash_name.compare("md5") == 0) || (hash_name.compare("MD5") == 0)
        || ((hash_name.compare("ntlm") == 0) || (hash_name.compare("NTLM") == 0)))  len_hash = 32;

    else if ((hash_name.compare("sha1") == 0) || (hash_name.compare("SHA1") == 0)
             || (hash_name.compare("sql5") == 0) || (hash_name.compare("SQL5") == 0)) len_hash = 40;

    std::cout << "" << std::endl;
    std::cout << "counting lines in pot file" << std::endl;
    std::string line(""); // we read one line (from hash_file) at the time and we put it in $line
    std::ifstream h_file (file_name);
    if(h_file.is_open()){
            while(getline(h_file,line)){
                    ++num_lines;
            }
    }
    h_file.close();
    std::cout << "" << std::endl;
    std::cout << num_lines << " lines to import." << std::endl;
    line = "";

    std::ifstream hash_file (file_name);
    auto start = std::chrono::steady_clock::now();

    if(hash_file.is_open()){

        std::cout << "" << std::endl;
        std::cout << "importing lines from  pot file to database..." << std::endl;
        boost::progress_display show_progress(num_lines);

        for(std::size_t i(0); i < num_lines; i++){
            getline(hash_file,line);
            std::string  hashed(line.substr(0,len_hash)); // the hash is $len_hash char long for MD5 for example
            std::string plain_text(line.substr(len_hash + 1, line.length() - len_hash)); // plain text is after ':'
            s = db->Put(leveldb::WriteOptions(), hashed, plain_text);
            if (!s.ok()) std::cerr << s.ToString() << std::endl;
            ++show_progress;
            }
            }
            hash_file.close();

            delete db;

            auto end = std::chrono::steady_clock::now();

            if(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < 60e9){
                std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
                << " seconds to import " << num_lines << " lines." << std::endl;
            }
            else if(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() < 3600e9){
                    std::cout << std::chrono::duration_cast<std::chrono::minutes>(end - start).count()
                    << " minutes to import " << num_lines << " lines." << std::endl;

            }
            else{
                std::cout << std::chrono::duration_cast<std::chrono::hours>(end - start).count()
                << " hours to import " << num_lines << " lines." << std::endl;
            }

    }
