#pragma once
#include <map>
#include <fstream>

//!
//! \class DataBase
//!
//! \brief The DataBase keeps all the Transaction and their current status of validation by the BlockChain.
//! \brief Implement a File System that will save the DataBase into File if necessary
//! \author Louis Henri Franc
//!
class DataBase
{
	using data_cuple = std::pair<std::string, std::pair<int, std::string> >;

public:
	DataBase();
	~DataBase();

	void	   request(const std::string&, std::ostream&) const;
	void	   request(const std::string& domainName) const;

	data_cuple get(std::string)	const;
	int		   get_statusTransaction(const std::string&) const;
	int		   get_statusMessage(const std::string&, const std::string&) const;
	void	   save(const std::string&) const;

	void	  update(const std::string&, int);
	void	  print() const;
	bool      push_back(const std::string&);
	size_t    size() const;

	enum {
		NOT_FOUND_TRANSACTION = 0,
		NOT_VALIDATED_TRANSACTION = 1,
		VALIDATED_TRANSACTION = 2,
		OTHER_SAME_TRANSACTION_ALREADY_VALID = 3
	};

private:
	std::map<std::string, std::string> hashTransaction_to_hashMessage;
	std::multimap<std::string, data_cuple> hashMessage_to_Message;
};

