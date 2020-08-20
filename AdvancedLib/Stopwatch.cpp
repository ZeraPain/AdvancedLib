#include "Stopwatch.h"

Stopwatch::Stopwatch() noexcept
	: m_startPoint(clock::now())
	, m_endPoint(m_startPoint)
	, m_isRunning(true)
{
}

auto Stopwatch::start() noexcept -> void
{
	m_isRunning = true;
	m_startPoint = clock::now();
}

auto Stopwatch::restart() noexcept -> void
{
	start();
}

auto Stopwatch::stop() noexcept -> void
{
	if (m_isRunning)
	{
		m_isRunning = false;
		m_endPoint = clock::now();
	}
}

auto Stopwatch::is_running() const noexcept -> bool
{
	return m_isRunning;
}

auto Stopwatch::elapsed_hours() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::hours>();
}

auto Stopwatch::elapsed_minutes() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::minutes>();
}

auto Stopwatch::elapsed_seconds() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::seconds>();
}

auto Stopwatch::elapsed_milliseconds() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::milliseconds>();
}

auto Stopwatch::elapsed_microseconds() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::microseconds>();
}

auto Stopwatch::elapsed_nanoseconds() const noexcept -> int64_t
{
	return elapsed_time<std::chrono::nanoseconds>();
}
