// Written by Billy Lai
// 5/6/18
// Reading and Writing LineItem FlatBuffers

#include <iostream>
#include "lineitem_generated.h"

using namespace Tables;

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

	// If we do not wish to set every field in a table
	// Use this instead of calling CreateLINEITEM()
	LINEITEMBuilder lineitem_builder(builder);
	lineitem_builder.add_L_SHIPDATE(&ship_date);
	lineitem_builder.add_L_SHIPINSTRUCT(ship_instruct);
	lineitem_builder.add_L_SHIPMODE(ship_mode);
	lineitem_builder.add_L_COMMENT(comment);
	auto firstItem = lineitem_builder.Finish();

	// Call 'Finish()' to instruct the builder that this LINEITEM Is complete
	// Regardless of how 'firstItem' was created, we still need to call
	// 'Finish()' on the 'FlatBufferBuilder'
	builder.Finish(firstItem); // Could also call 'FinishLINEITEMBuffer(builder, firstItem);

	uint8_t *buf = builder.GetBufferPointer();
	int size = builder.GetSize();
	std::cout<<size<<std::endl;

	return 0;
}

