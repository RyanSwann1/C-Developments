#pragma once

#include <iostream>

class Timer
{
public:
	Timer();
	~Timer();

	inline void setExpirationTime(const float expirationTime) { m_expirationTime = expirationTime; }
	void activate();
	inline bool isFinished() const { return m_isFinished; }

	void update(const float elaspedTime);
	void deactivate();	
	inline bool isActive() const { return m_isActive; }

private:
	float m_timeElasped;
	float m_expirationTime;
	bool m_isActive;
	bool m_isFinished;

	inline bool isExpired() const { return m_timeElasped >= m_expirationTime; }
};
