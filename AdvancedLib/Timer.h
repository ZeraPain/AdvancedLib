#pragma once
#include <functional>
#include <thread>
#include <chrono>
#include <atomic>

class Timer
{
public:
	explicit Timer() noexcept;
	Timer(Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(Timer) = delete;
	Timer& operator=(Timer&&) = delete;
	~Timer();

	template <class callable, class... arguments>
	static auto run_once(const int aMsDelay, callable&& aFunction, arguments&&... someArguments) noexcept -> void;

	template <class callable, class... arguments>
	auto run(const int aMsDelay, callable&& aFunction, arguments&&... someArguments) noexcept -> void;

	auto set_intervalCount(int aValue) noexcept -> void;
	auto stop() noexcept -> void;

private:
	std::thread			m_thread;
	std::atomic<bool>	m_isRunning;
	std::atomic<int>	m_maxIntervalCount;
	std::atomic<int>	m_currentIntervalCount;
};

template <class callable, class ... arguments>
auto Timer::run_once(const int aMsDelay, callable&& aFunction, arguments&&... someArguments) noexcept -> void
{
	std::function<typename std::result_of<callable(arguments ...)>::type()> callback{
		std::bind(std::forward<callable>(aFunction),
		          std::forward<arguments>(someArguments)...)
	};

	std::thread([aMsDelay, callback]()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(aMsDelay));

		try
		{
			callback();
		}
		catch (const std::exception&)
		{
		}
	}).detach();
}

template <class callable, class ... arguments>
auto Timer::run(const int aMsDelay, callable&& aFunction, arguments&&... someArguments) noexcept -> void
{
	m_isRunning = true;

	std::function<typename std::result_of<callable(arguments ...)>::type()> callback{
		std::bind(std::forward<callable>(aFunction),
		          std::forward<arguments>(someArguments)...)
	};

	m_thread = std::thread([this, aMsDelay, callback]()
	{
		while (m_isRunning)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(aMsDelay));
			if (!m_isRunning)
				break;

			try
			{
				callback();
			}
			catch (const std::exception&)
			{
				m_isRunning = false;
				break;
			}

			if (0 != m_maxIntervalCount && ++m_currentIntervalCount >= m_maxIntervalCount)
				break;
		};
	});
}
