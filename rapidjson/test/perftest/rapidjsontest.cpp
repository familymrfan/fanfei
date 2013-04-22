#include "perftest.h"

#if TEST_RAPIDJSON

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filestream.h"
#include <iostream>
#include <cmath>

/*#ifdef RAPIDJSON_SSE2
#define SIMD_SUFFIX(name) name##_SSE2
#elif defined(RAPIDJSON_SSE42)
#define SIMD_SUFFIX(name) name##_SSE42
#else
#define SIMD_SUFFIX(name) name
#endif*/

using namespace rapidjson;

class RapidJson : public PerfTest {
public:
	virtual void SetUp() {
		PerfTest::SetUp();

		// temp buffer for insitu parsing.
		temp_ = (char *)malloc(length_ + 1);

		// Parse as a document
		//EXPECT_FALSE(doc_.Parse<0>(json_).IsNull());
	}

	virtual void TearDown() {
		PerfTest::TearDown();
		free(temp_);
	}

protected:
	char *temp_;
	//Document doc_;
};

TEST_F(RapidJson, ReaderParseDOM) {
    for (size_t i = 0; i < kTrialCount; i++) {
        Document doc;
        doc.Parse<0>(json_);
        ASSERT_TRUE(doc.IsObject());
    }
}

TEST_F(RapidJson, ReaderParseSAX) {
    for (size_t i = 0; i < kTrialCount; i++) {
        InsituStringStream s(json_);
        BaseReaderHandler<> h;
        Reader reader;
        reader.Parse<kParseInsituFlag>(s, h);
    }
}


size_t Traverse(const Value& val) {
    size_t count = 1;
    if(kObjectType == val.GetType()){
        for (Value::ConstMemberIterator itr = val.MemberBegin(); itr != val.MemberEnd(); ++itr) {
            count += Traverse(itr->value);
        }
    }else if(kArrayType == val.GetType()){
        for (Value::ConstValueIterator itr = val.Begin(); itr != val.End(); ++itr)
            count += Traverse(*itr);
    }
    return count;
}

TEST_F(RapidJson,TraverseDOM){
    for (size_t i = 0; i < kTrialCount; i++) {
        Document doc;
        doc.Parse<0>(json_);
        std::cout<<Traverse(doc)<<std::endl;
    }
}

TEST_F(RapidJson,Write){
    Value root;
    char sz[256]; 
    memset(sz,0,256);
    InsituStringStream  os(sz);
    PrettyWriter<InsituStringStream> writer(os);
    os.PutBegin();
    writer.StartObject();
    writer.String("name",strlen("name"));
    writer.String("fanfei",strlen("fanfei"));
    writer.String("age",strlen("age"));
    writer.Int(24);
    writer.String("love",strlen("love"));
    writer.StartArray();
    writer.String("game",strlen("game"));
    writer.String("book",strlen("book"));
    writer.String("basketball",strlen("basketball"));
    writer.String("music",strlen("music"));
    writer.EndArray();
    writer.EndObject();
    os.PutEnd(sz);
    std::cout<<os.src_;
}

#endif // TEST_RAPIDJSON
