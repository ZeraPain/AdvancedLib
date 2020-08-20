#include "Timer.h"

Timer::Timer() noexcept
	: m_isRunning(false)
	, m_maxIntervalCount(0)
	, m_currentIntervalCount(0)
{
}

Timer::~Timer()
{
	stop();
}

auto Timer::set_intervalCount(int aValue) noexcept -> void
{
	m_currentIntervalCount = 0;
	m_maxIntervalCount = aValue;
}

auto Timer::stop() noexcept -> void
{
	if (m_isRunning)
	{
		m_isRunning = false;
		if (m_thread.joinable())
		{
			try
			{
				m_thread.join();
			}
			catch (const std::exception&)
			{
				m_thread.detach();
			}
		}
	}
}
