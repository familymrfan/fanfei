#include "pugixml.hpp"
#include "string.h"
#include <iostream>

int main(){
    const char source[] = "<mesh name='sphere'><bounds>0 0 1 1</bounds></mesh>";
    size_t size = sizeof(source);
    // You can use load_buffer_inplace to load document from mutable memory block; the block's lifetime must exceed that of document
    char* buffer = new char[size];
    memcpy(buffer, source, size);
    pugi::xml_document doc;
    // The block can be allocated by any method; the block is modified during parsing
    pugi::xml_parse_result result = doc.load_buffer_inplace(buffer, size);
    std::cout<<doc.child("mesh").attribute("name").value()<<std::endl;
    // You have to destroy the block yourself after the document is no longer used
    delete[] buffer;
    return 0;
}