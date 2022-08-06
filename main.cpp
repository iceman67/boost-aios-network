#include <iostream>
#include <string>
#include <cstdio>
#include <exception>

#include "merkle_tree.h"

#include <crypto++/sha.h>
#include <crypto++/files.h>
using CryptoPP::FileSource;
using CryptoPP::FileSink;
#include <crypto++/base64.h>

#include <crypto++/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
#include <boost/asio.hpp>

using namespace std;


std::string StringFromFile(string ofilename)
{

    std::string str;
    try {

       /*********************************\
       \*********************************/
	   
	   FileSource fs1(ofilename.c_str(), true, new StringSink(str));
	} catch (const exception& ex) {
		cerr << ex.what() << endl;
    }
    return str;


}
std::string SHA256HashStringFromFile(string ofilename)
{
	 
    std::string digest;
    CryptoPP::SHA256 hash;

	try {

       /*********************************\
       \*********************************/
	   
	   FileSource fs1(ofilename.c_str(), true,
           new CryptoPP::HashFilter(hash,
             new CryptoPP::Base64Encoder (
                new CryptoPP::StringSink(digest))));  
				   
	} catch (const exception& ex) {
		cerr << ex.what() << endl;
    }
    return digest;

}

std::string SHA256HashString(std::string aString){
    std::string digest;
    CryptoPP::SHA256 hash;

    CryptoPP::StringSource foo(aString, true,
    new CryptoPP::HashFilter(hash,
      new CryptoPP::Base64Encoder (
         new CryptoPP::StringSink(digest))));

    return digest;
}


string chain(string prev, string val) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    if (prev =="")  {
        return SHA256HashString(val);
    }
    else  {
        cout << "prev hash : " << prev << endl;
        return SHA256HashString( prev +chain("", val)) ;
    } 
}

boost::asio::io_context io_context;
boost::posix_time::seconds interval(1);  // 1 second
boost::asio::deadline_timer timer(io_context, interval);

void tick(const boost::system::error_code& /*e*/) {

    std::cout << "tick" << std::endl;

    // Reschedule the timer for 1 second in the future:
    timer.expires_at(timer.expires_at() + interval);
    // Posts the timer event
    timer.async_wait(tick);
}



// REF: https://github.com/sputnik1458/merkle-tree

int main(int argc, char* argv[])
{
    std::vector<Node*> leaves;

    // Schedule the timer for the first time:
    timer.async_wait(tick);
    io_context.run();

    cout << ">> Frame is added" << endl;
    string ofilename = "eukanuba-market-image-puppy-beagle.jpeg";
    //string s2 = SHA256HashStringFromFile(ofilename);
    string s2 =  StringFromFile(ofilename);
   
    string s1 = "abc";
    string x = chain("", s1);
    leaves.push_back(new Node(hash_sha256(x)));
    

    //create sample data
    //leaves.push_back(new Node(hash_sha256("abcdefg")));
    leaves.push_back(new Node(hash_sha256(s2)));

     x = chain(x, s2);
     leaves.push_back(new Node(hash_sha256(x)));
     leaves.push_back(new Node(SHA256HashString("qwerty12345")));


/*
    leaves.push_back(new Node(hash_sha256("qwerty12345")));
    leaves.push_back(new Node(hash_sha256("!@(@#)E&")));
    leaves.push_back(new Node(hash_sha256("ajosdhuhsdioa adsijd asjiod q9p0ad a.")));
    leaves.push_back(new Node(hash_sha256("test01234")));
    leaves.push_back(new Node(hash_sha256("7846546521")));
    leaves.push_back(new Node(hash_sha256("asd970123+_?>?< f")));
    leaves.push_back(new Node(hash_sha256("op_) 4654asd21")));
    leaves.push_back(new Node(hash_sha256("12893 d970123+_qweawdf")));
    */

    // initialize leaves
    for (unsigned int i = 0; i < leaves.size(); i++) {
        leaves[i]->left = NULL;
        leaves[i]->right = NULL;
    }

    MerkleTree *hashTree = new MerkleTree(leaves);
    std::cout << hashTree->root->hash << std::endl;
    hashTree->printTree(hashTree->root, 0);

    for (unsigned int k = 0; k < leaves.size(); k++) {
        delete leaves[k];
    }

    delete hashTree;

    return 0;
}
