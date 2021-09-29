
#include "cxx_examples.h"
#include "catch2/catch2.hpp"


using namespace cxx_examples;

TEST_CASE("negative square_root should throw exception ", "[cxx_examples]") {
    

    // expects std::invalid_argument exception, if it is not thrown test fails        
    REQUIRE_THROWS_AS( square_root(-1.0), std::invalid_argument);

    REQUIRE(square_root(0.0) == Approx(0.0));
}


TEST_CASE("square_root >= 0 should give positive result ", "[cxx_examples]") {
                
    REQUIRE(square_root(4.0) == Approx(2.0));
}


TEST_CASE("say_hello should produce a string ", "[cxx_examples]") {
    
    REQUIRE( cxx_examples::say_hello("peppo") == std::string("hello peppo"));        
}





