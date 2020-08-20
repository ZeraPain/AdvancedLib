#pragma once
#include <gmock/gmock.h>

class ITestMock
{
public:
	virtual auto method0() -> void = 0;
};

class TestMock : public ITestMock
{
public:
	MOCK_METHOD0(method0, void());
};
