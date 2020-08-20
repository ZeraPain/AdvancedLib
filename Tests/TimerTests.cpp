#include "Timer.h"
#include "MockClass.hpp"

TEST(TimerTests, TestRunOnce)
{
	TestMock tm;
	
	EXPECT_CALL(tm, method0()).Times(1);
	Timer::run_once(0, std::bind(&TestMock::method0, &tm));

	std::this_thread::sleep_for(std::chrono::milliseconds(2));
}

TEST(TimerTests, TestRunMultipleTimes)
{
	TestMock tm;
	Timer t;
	t.set_intervalCount(3);
	
	EXPECT_CALL(tm, method0()).Times(3);
	t.run(0, std::bind(&TestMock::method0, &tm));

	std::this_thread::sleep_for(std::chrono::milliseconds(2));
}
