// Written by Billy Lai
// 5/8/18
// Reading and Writing LineItem FlatBuffers

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include "lineitem_generated.h"

using namespace std;
using namespace Tables;

void LINEITEM_add_fields(); // THIS IS UNUSED BUT HERE FOR INCASE NEEDED
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
	std::cout<<row<<std::endl;
	std::vector<std::string> parsedRow = split(row, '|');
	
	// Check Parsed Row
	cout<<endl;
	cout<<"Checking Parsed Row"<<endl;
	for(int i=0;i< (int)parsedRow.size();i++)
		std::cout<<parsedRow[i]<<"|";
	cout<<endl;
	cout<<"Done checking row"<< endl<<endl;
	
// ------------------------------------------------------------------------Initialize FlatBuffer ----------------------------------------
	//	 Create a 'FlatBufferBuilder', which will be used to create our LINEITEM FlatBuffers
	flatbuffers::FlatBufferBuilder builder(1024);
	//	 Creating temp variables to throw into the builder
	int orderkey = atoi(parsedRow[0].c_str());
	int partkey = atoi(parsedRow[1].c_str());
	int suppkey = atoi(parsedRow[2].c_str());
	int linenumber = atoi(parsedRow[3].c_str());
	float quantity = stof(parsedRow[4]);
	float extendedprice = stof(parsedRow[5]);
	float discount = stof(parsedRow[6]);
	float tax = stof(parsedRow[7]);
	
	int8_t returnflag = (int8_t) atoi(parsedRow[8].c_str());
	int8_t linestatus = (int8_t) atoi(parsedRow[9].c_str());
	//	 Parsing and Serializing of Date fields	
	vector<int> s,r,c;
	s = splitDate(parsedRow[10]);
	r = splitDate(parsedRow[11]);
	c = splitDate(parsedRow[12]);
	auto shipdate = Date(s[0], s[1], s[2]);
	auto commitdate = Date(r[0], r[1], r[2]);
	auto receiptdate = Date(c[0], c[1], c[2]);
	//	 Serializing String fields
	auto shipinstruct = builder.CreateString(parsedRow[13]);
	auto shipmode = builder.CreateString(parsedRow[14]);
	auto comment = builder.CreateString(parsedRow[15]);
	// Initialize our LINEITEM
	auto firstItem = CreateLINEITEM(builder, orderkey, partkey, suppkey, linenumber, // int32_t, 4 byte int
				quantity, extendedprice,discount,tax, // float
				returnflag,linestatus, // char as an int8_t
				&shipdate,&commitdate,&receiptdate, // serialized Date struct
				shipinstruct,shipmode,comment); // serialized string type

	builder.Finish(firstItem);
// --------------------------------------------Start Timing Rows--------------------------------------------------------------------
//
	struct timeval start, end;
	double t;

	uint8_t *buf = builder.GetBufferPointer();
	int size = builder.GetSize();
	std::cout<<"Buffer Size: "<<size<<std::endl;

	gettimeofday(&start, NULL);
	auto item = GetLINEITEM(buf);
	gettimeofday(&end, NULL);

	t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));
	std::cout<<"Reading LINEITEM took "<< t<< " microseconds"<<std::endl;


	assert(strcmp(item->L_SHIPINSTRUCT()->c_str(),parsedRow[13].c_str()) ==0);
	assert(strcmp(item->L_SHIPMODE()->c_str(),parsedRow[14].c_str()) ==0);
	assert(strcmp(item->L_COMMENT()->c_str(),parsedRow[15].c_str()) ==0);

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
void LINEITEM_add_fields() {
	
	flatbuffers::FlatBufferBuilder builder(1024);
	/*
	// Initialize
	LINEITEMBuilder lineitem_builder(builder);
	lineitem_builder.add_L_ORDERKEY(parsedRow[0]);
	lineitem_builder.add_L_PARTKEY(parsedRow[1]);
	lineitem_builder.add_L_SUPPKEY(parsedRow[2]);
	lineitem_builder.add_L_LINENUMBER(parsedRow[3]);
	lineitem_builder.add_L_QUANTITY(parsedRow[4]);
	lineitem_builder.add_L_EXTENDEDPRICE(parsedRow[5]);
	lineitem_builder.add_L_DISCOUNT(parsedRow[6]);
	lineitem_builder.add_L_TAX(parsedRow[7]);

	lineitem_builder.add_L_RETURNFLAG(parsedRow[8]);
	lineitem_builder.add_L_LINESTATUS(parsedRow[9]);

	lineitem_builder.add_L_SHIPDATE(parsedRow[10]);
	lineitem_builder.add_L_COMMITDATE(parsedRow[11]);
	lineitem_builder.add_L_RECEIPTDATE(parsedRow[12]);
	lineitem_builder.add_L_SHIPINSTRUCT(parsedRow[13]);
	lineitem_builder.add_L_SHIPMODE(parsedRow[14]);
	lineitem_builder.add_L_COMMENT(parsedRow[15]);
	// If we do not wish to set every field in a table
	// Use this instead of calling CreateLINEITEM()
	auto firstItem = lineitem_builder.Finish();
	

	// Call 'Finish()' to instruct the builder that this LINEITEM Is complete
	// Regardless of how 'firstItem' was created, we still need to call
	// 'Finish()' on the 'FlatBufferBuilder'
	builder.Finish(firstItem); // Could also call 'FinishLINEITEMBuffer(builder, firstItem);
	*/
}
