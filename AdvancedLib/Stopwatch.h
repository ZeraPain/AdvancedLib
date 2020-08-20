#pragma once
#include <chrono>

class Stopwatch
{
public:
	explicit Stopwatch() noexcept;
	Stopwatch(Stopwatch&) = delete;
	Stopwatch(Stopwatch&&) = delete;
	Stopwatch& operator=(Stopwatch) = delete;
	Stopwatch& operator=(Stopwatch&&) = delete;
	~Stopwatch() = default;
	
	auto start() noexcept -> void;
	auto restart() noexcept -> void;
	auto stop() noexcept -> void;
	auto is_running() const noexcept -> bool;

	auto elapsed_hours() const noexcept -> int64_t;
	auto elapsed_minutes() const noexcept -> int64_t;
	auto elapsed_seconds() const noexcept -> int64_t;
	auto elapsed_milliseconds() const noexcept -> int64_t;
	auto elapsed_microseconds() const noexcept -> int64_t;
	auto elapsed_nanoseconds() const noexcept -> int64_t;

private:
	using clock = std::chrono::high_resolution_clock;
	
	template <class T>
	auto elapsed_time() const noexcept -> int64_t
	{
		return std::chrono::duration_cast<T>
			((m_isRunning ? clock::now() : m_endPoint) - m_startPoint).count();
	}
	
	clock::time_point	m_startPoint;
	clock::time_point	m_endPoint;

	bool	m_isRunning;
};