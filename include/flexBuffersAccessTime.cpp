// Written by Billy Lai
// 5/15/18
// Reading and Writing LineItem FlexBuffers

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include "flatbuffers/flexbuffers.h"

using namespace std;

std::vector<std::string> split(const std::string &s, char delim);
std::vector<int> splitDate(const std::string &s);

int main()
{

	// Open .tbl file
	std::ifstream inFile;
	inFile.open("lineitem-10K-rows.tbl", std::ifstream::in);
	if(!inFile)
	{
		std::cout<<"Cannot open file!!!";
		return 0;
	}		
	// Get a row
	std::string row;
	std::getline(inFile, row);
	inFile.close();
	// Split by '|' deliminator
	std::vector<std::string> parsedRow = split(row, '|');
	
// ------------------------------------------------------------------------Initialize FlatBuffer ----------------------------------------
	
	//	 Creating temp variables to throw into the builder
	int orderkey = atoi(parsedRow[0].c_str());
	int partkey = atoi(parsedRow[1].c_str());
	int suppkey = atoi(parsedRow[2].c_str());
	int linenumber = atoi(parsedRow[3].c_str());
	double quantity = stof(parsedRow[4]);
	double extendedprice = stof(parsedRow[5]);
	double discount = stof(parsedRow[6]);
	double tax = stof(parsedRow[7]);
	
	int8_t returnflag = (int8_t) atoi(parsedRow[8].c_str());
	int8_t linestatus = (int8_t) atoi(parsedRow[9].c_str());
	//	 Parsing of Date fields	
	vector<int> shipdate,receiptdate,commitdate;
	shipdate = splitDate(parsedRow[10]);
	receiptdate = splitDate(parsedRow[11]);
	commitdate = splitDate(parsedRow[12]);
	//	 String fields
	string shipinstruct = parsedRow[13];
	string shipmode = parsedRow[14];
	string comment = parsedRow[15];
	// Initialize our LINEITEM
	// 	Create a flexbuffer
	flexbuffers::Builder fbb;
	fbb.Map([&]() {
		fbb.UInt("orderkey", orderkey);
		fbb.UInt("partkey", partkey);
		fbb.UInt("suppkey", suppkey);
		fbb.UInt("linenumber", linenumber);
		fbb.

	fbb.Finish();
// --------------------------------------------Start Timing Rows--------------------------------------------------------------------
//
	struct timeval start, end;
	double t;

	uint8_t *buf = builder.GetBufferPointer();
	int size = builder.GetSize();
	std::cout<<"Buffer Size: "<<size<<endl<<endl;

	volatile auto item = GetLINEITEM(buf);

	volatile int32_t _orderkey, _partkey, _suppkey, _linenumber;
	volatile float _quantity, _extendedprice, _discount, _tax;
	volatile int8_t _returnflag, _linestatus;
	const Tables::Date* _shipdate, *_commitdate, *_receiptdate;
	const flatbuffers::String*  _shipinstruct, *_shipmode, *_comment;


// ------------------------------------------------- DOUBLE CHECKING CONTENTS OF LINEITEM IN BUFFER -----------------------------------
	assert(_orderkey == orderkey);
	assert(_partkey == partkey);
	assert(_suppkey == suppkey);
	assert(_linenumber == linenumber);
	
	assert(_quantity == quantity);
	assert(_extendedprice == extendedprice);
	assert(_discount == discount);
	assert(_tax == tax);

	assert(_returnflag == returnflag);
	assert(_linestatus == linestatus);


	return 0;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::istringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while( getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}
std::vector<int> splitDate(const std::string &s) {
	std::istringstream ss(s);
	std::string item;
	std::vector<int> tokens;
	while( getline(ss, item, '-')) {
		tokens.push_back(atoi(item.c_str()));
	}
	return tokens;
}
