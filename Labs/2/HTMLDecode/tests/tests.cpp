#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../HTMLDecode/Decoder.h"

TEST_CASE("GetChangedStr tests")
{
	CHECK(GetChangedStr("", "abcde", 'f') == "");
	CHECK(GetChangedStr("ewgabcewg", "abc", 'd') == "ewgdewg");
	CHECK(GetChangedStr("12312312345", "1231234", 'a') == "123a5");
}

TEST_CASE("HtmlDecode tests")
{
	CHECK(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
	CHECK(HtmlDecode("Cat <says> \"Meow\". M&M's") == "Cat <says> \"Meow\". M&M's");
}