#include <iostream>
#include <string>
#include <vector>

#include <boost/lambda/lambda.hpp>
#include <gtest/gtest.h>

#include "linqxx.h"

namespace linqxx {
namespace {

using namespace std;
using boost::lambda::_1;

struct Person {
    string name;
    int age;
    Person(const string& aName, int anAge) : name(aName), age(anAge) {}
};

class LinqxxTest : public testing::Test {
  protected:
    virtual void SetUp() {
        guests_.reset(new vector<Person>());
        guests_->push_back(Person("John", 32));
        guests_->push_back(Person("Mike", 28));
        guests_->push_back(Person("Eliz", 27));
    }

    shared_ptr<vector<Person> > guests_;
};

TEST_F(LinqxxTest, Count) {
    EXPECT_EQ(3, from(guests_).count());
}

TEST_F(LinqxxTest, Where) {
    EXPECT_EQ(1, from(guests_).where(&_1 ->* &Person::age > 30).count());
}

TEST_F(LinqxxTest, Select) {
    EXPECT_EQ(3, from(guests_).select<int>(&_1 ->* &Person::age).count());
    shared_ptr<vector<int> > results = from(guests_)
            .select<int>(&_1 ->* &Person::age)
            .get();
    EXPECT_EQ(3, results->size());
    EXPECT_EQ(32, (*results)[0]);
}

TEST_F(LinqxxTest, Map) {
    EXPECT_EQ(3, from(guests_).map<int>(&_1 ->* &Person::age).count());
}

}  // anonymous namespace
}  // namespace linqxx
