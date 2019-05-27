#pragma once

#include <vector>

template<typename Base, typename Passenger>
class CVehicleImpl : public Base
{
public:
	CVehicleImpl(size_t placeCount)
		: m_placeCount(placeCount)
	{
	}

	bool IsEmpty() const override
	{
		return m_passengers.empty();
	}

	bool IsFull() const override
	{
		return m_passengers.size() == m_placeCount;
	}

	size_t GetPlaceCount() const override
	{
		return m_placeCount;
	}

	size_t GetPassengerCount() const override
	{
		return m_passengers.size();
	}

	void RemoveAllPassengers() override
	{
		m_passengers.clear();
	}

	void AddPassenger(std::shared_ptr<Passenger> pPassenger) override
	{
		if (IsFull())
		{
			throw std::logic_error("vehicle is full");
		}
		m_passengers.push_back(pPassenger);
	}

	const Passenger &GetPassenger(size_t index) const override
	{
		return *m_passengers[index];
	}

	void RemovePassenger(size_t index) override
	{
		m_passengers.erase(m_passengers.begin() + index);
	}

private:
	size_t m_placeCount;
	std::vector<std::shared_ptr<Passenger>> m_passengers;
};