#define BOOST_TEST_MODULE ChutesAndLaddersTest

#include <boost/test/included/unit_test.hpp>

// TODO:
BOOST_AUTO_TEST_CASE(ChutesAndLaddersTest) {
  // To simplify this example test, let's suppose we'll test 'float'.
  // Some test are stupid, but all should pass.
  float x = 9.5f;

  BOOST_CHECK(x != 0.0f);
  BOOST_CHECK_EQUAL((int)x, 9);
  BOOST_CHECK_CLOSE(x, 9.5f, 0.0001f); // Checks differ no more then 0.0001%
}
