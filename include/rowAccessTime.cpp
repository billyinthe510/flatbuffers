// Written by Billy Lai
// 5/8/18
// Reading and Writing LineItem FlatBuffers

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include "lineitem_generated.h"

using namespace Tables;

std::vector<std::string> split(const std::string &s, char delim) {
	std::istringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while( getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

int main()
{
	// Create a 'FlatBufferBuilder', which will be used to create our
	// LINEITEM FlatBuffers
	flatbuffers::FlatBufferBuilder builder(1024);


	// Initial values for our first LINEITEM row
	auto ship_date = Date(1993.0f, 11.0f, 10.0f);
	auto ship_instruct = builder.CreateString("Use lots of tape");
	auto ship_mode = builder.CreateString("First Class Shipping");
	auto comment = builder.CreateString("Double check the shipping address!");

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
	for(int i=0;i<parsedRow.size();i++)
		std::cout<<parsedRow[i]<<" "<<std::endl;
/*	// Initialize
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

	struct timeval start, end;
	double t;

	uint8_t *buf = builder.GetBufferPointer();
	int size = builder.GetSize();
	std::cout<<size<<std::endl;

	gettimeofday(&start, NULL);
	auto item = GetLINEITEM(buf);
	gettimeofday(&end, NULL);

	assert(strcmp(item->L_SHIPINSTRUCT()->c_str(),"Use lots of tape")==0);
	
	t = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec));

	std::cout<<"Reading LINEITEM took "<< t<< " microseconds"<<std::endl;
*/
	return 0;
}

