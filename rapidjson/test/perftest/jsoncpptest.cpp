#include "perftest.h"

#if TEST_JSONCPP

#include "jsoncpp/src/lib_json/json_reader.cpp"
#include "jsoncpp/src/lib_json/json_value.cpp"
#include "jsoncpp/src/lib_json/json_writer.cpp"
#include <iostream>

using namespace Json;

class JsonCpp : public PerfTest {
public:
	virtual void SetUp() {
		PerfTest::SetUp();
		Reader reader;
		ASSERT_TRUE(reader.parse(json_, root_));
	}

protected:
	Value root_;
};

TEST_F(JsonCpp, ReaderParseDOM) {
	for (size_t i = 0; i < kTrialCount; i++) {
		Value root;
		Reader reader;
		ASSERT_TRUE(reader.parse(json_, root));
	}
}

size_t Traverse(const Value& val){
    size_t count = 1;   
    if(objectValue == val.type() || nullValue == val.type())
    {
        std::vector<std::string> memname = val.getMemberNames();
        for(size_t i=0;i<memname.size();i++){
            count += Traverse(val[memname[i]]);
        }
    }else if(arrayValue == val.type()){
        for(size_t i=0;i<val.size();i++){
            count += Traverse(val[i]);
        }
    }
    return count;
}

TEST_F(JsonCpp,Traverse){
    for (size_t i = 0; i < kTrialCount; i++) {
        Value root;
        Reader reader;
        ASSERT_TRUE(reader.parse(json_, root));
        //std::cout<<Traverse(root)<<std::endl;
    }
}

TEST_F(JsonCpp,Write){
  for (size_t i = 0; i < kTrialCount; i++) {
    Value root;
    Json::StyledWriter writer;
    root["name"] = "fanfei";
    root["name"].setComment("/*This is me!*/",commentAfterOnSameLine);
    root["age"] = 24;
    root["love"].append("game");
    root["love"].append("book");
    root["love"].append("basketball");
    root["love"].append("music");
    std::string outputConfig = writer.write( root );
    //std::cout<<outputConfig;
  }
}

#endif // TEST_JSONCPP
