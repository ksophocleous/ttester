ttester
===

very simple unit test library; it can be integrated with an application

example usage:


```C++
#include <ttester/tmain.h>

int main(int argc, char* argv[])
{
	ttester::tmain tm(argc, argv);

	// proceed with your normal application code here

	// or just run tests no matter the parameter passed
	return tm.RunAllTests();
}
```

In some other file, perhaps `all_tests.cpp`
```C++
#include <ttester/tmain.h>

using ttester::tsuite;

class myclass_test : public tsuite
{
	public:
		myclass_test() : tsuite("my test suite")
		{
			// construct your objects for this test suite here
		}

		virtual void RunTests()
		{
			tsuite::test_exception<runtime_error>("some bad object instantiation perhaps", [] () {
				throw runtime_error("an example; this exception will make this test pass");
			});

			tsuite::test("some good object instantiation perhaps", [] () {
				// all good
			});

			tsuite::test("failure", [] () {
				throw runtime_error("this test will fail");
			});

			tsuite::test_exception<runtime_error>("failure", [] () {
				// this test will fail
			});
		}
};

REGISTER_TEST_CLASS(myclass_test);
```

to run the tests do `./exe_name --test`. Note that the `--test` will issue an exit() when the tests are done.
