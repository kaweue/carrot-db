#include "carrotdb/model/value.h"
#include "boost/lexical_cast.hpp"
#include "boost/uuid/uuid.hpp"
#include "gtest/gtest.h"

namespace
{
    TEST(value_test, create_value_without_content)
    {
        // when value without content is created
        model::value value;
        auto content = value.get_content();
        // then content is empty
        EXPECT_TRUE(content.empty());
        // then id is a valud random based uuid
        auto id = value.id();
        EXPECT_FALSE(id.empty());
        auto uuid = boost::lexical_cast<boost::uuids::uuid>(id);
        EXPECT_EQ(uuid.version(), boost::uuids::uuid::version_random_number_based);
    }

    TEST(value_test, create_value_with_content)
    {
        // given some content
        auto content = std::string("content content");
        // when content is passed to value
        model::value value(std::move(content));
        // then content is empty
        EXPECT_TRUE(content.empty());
        // then id is a valud random based uuid
        auto id = value.id();
        EXPECT_FALSE(id.empty());
        auto uuid = boost::lexical_cast<boost::uuids::uuid>(id);
        EXPECT_EQ(uuid.version(), boost::uuids::uuid::version_random_number_based);
        // then stored content is not empty
        auto stored_content = value.get_content();
        EXPECT_FALSE(stored_content.empty());
        // then stored content is equal to provided one
        EXPECT_EQ(stored_content, "content content");
    }
    TEST(value_test, move_value)
    {
        // given a value with content and empty target value
        model::value value(std::string("content content"));
        model::value target_value;

        // then value is moved to another variable
        target_value = std::move(value);
        EXPECT_TRUE(value.empty());
        EXPECT_FALSE(target_value.empty());
        // then stored content is not empty
        auto stored_content = target_value.get_content();
        EXPECT_FALSE(stored_content.empty());
        // then stored content is equal to provided one
        EXPECT_EQ(stored_content, "content content");
    }
} // namespace