#include "perftest.h"

#if TEST_YAJL

extern "C" {
#include "yajl/yajl_gen.h"
#include "yajl/yajl_parse.h"
#include "yajl/yajl_tree.h"
};

class Yajl : public PerfTest {
public:
	virtual void SetUp() {
		PerfTest::SetUp();
		//root_ = yajl_tree_parse(json_, NULL, 0);
		//ASSERT_TRUE(root_ != NULL);
	}

	virtual void TearDown() {
		PerfTest::TearDown();
		//yajl_tree_free(root_);
	}

protected:
	//yajl_val root_;
};


TEST_F(Yajl, ReaderParseSAX) {
    for (size_t i = 0; i < kTrialCount; i++) {
        yajl_handle hand = yajl_alloc(NULL, NULL, NULL);
        yajl_config(hand, yajl_allow_comments, 1);
        yajl_status stat = yajl_parse(hand, (unsigned char*)json_, length_ - 1);
        //ASSERT_EQ(yajl_status_ok, stat);
        if (stat != yajl_status_ok) {
            unsigned char * str = yajl_get_error(hand, 1, (unsigned char*)json_, length_ + 1);
            fprintf(stderr, "%s", (const char *) str);
        }
        stat = yajl_complete_parse(hand);
        ASSERT_EQ(yajl_status_ok, stat);
        yajl_free(hand);
    }
}

TEST_F(Yajl, ReaderParseDOM_yajl_tree_parse) {
    for (size_t i = 0; i < kTrialCount; i++) {
        yajl_val root = yajl_tree_parse(json_, NULL, 0);
        ASSERT_TRUE(root != NULL);
        yajl_tree_free(root);
    }
}

size_t Traverse(const yajl_val& val){
    size_t count = 1;   
    if(yajl_t_object == val->type)
    {
        for (size_t i = 0; i < val->u.object.len; i++) {
            count += Traverse(val->u.object.values[i]);
        }
    }else if(yajl_t_array == val->type){
        for (size_t i = 0; i < val->u.array.len; i++) {
            count += Traverse(val->u.array.values[i]);
        }
    }
    return count;
}

TEST_F(Yajl,Traverse){
    for (size_t i = 0; i < kTrialCount; i++) {
        yajl_val root = yajl_tree_parse(json_, NULL, 0);
        ASSERT_TRUE(root != NULL);
        std::cout<<Traverse(root)<<std::endl;
        yajl_tree_free(root);
    }
}

TEST_F(Yajl,Write){
    yajl_gen g;
    g = yajl_gen_alloc(NULL);  
    yajl_gen_config(g, yajl_gen_beautify, 1);  
    yajl_gen_config(g, yajl_gen_validate_utf8, 1); 
    yajl_gen_map_open(g);  
    yajl_gen_string(g, (const unsigned char *)"name", strlen("name"));
    yajl_gen_string(g, (const unsigned char *)"fanfei", strlen("fanfei"));
    yajl_gen_string(g, (const unsigned char *)"age", strlen("age"));  
    yajl_gen_integer(g, 24);
    yajl_gen_string(g, (const unsigned char *)"love", strlen("love"));
    yajl_gen_array_open(g);
    yajl_gen_string(g, (const unsigned char *)"game", strlen("game"));  
    yajl_gen_string(g, (const unsigned char *)"book", strlen("book"));
    yajl_gen_string(g, (const unsigned char *)"basketball", strlen("basketball")); 
    yajl_gen_string(g, (const unsigned char *)"music", strlen("music"));
    yajl_gen_array_close(g);
    yajl_gen_map_close(g);
    const unsigned char * buf;  
    size_t len;  
    yajl_gen_get_buf(g, &buf, &len);  
    std::cout<<buf;
    yajl_gen_clear(g);

    yajl_gen_free(g);
}

#endif // TEST_YAJL
