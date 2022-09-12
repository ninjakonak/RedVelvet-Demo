#include "../include/Timer.h"

namespace EngineUtils {
	Timer* Timer::sIntance = nullptr;

	Timer* Timer::Instance() {
		if (sIntance == nullptr)
			sIntance = new Timer();
		return sIntance;
	}

	void Timer::Release() {
		delete sIntance;
		sIntance = nullptr;
	}

	Timer::Timer() {
		Reset();
		mTimeScale = 1.0f;
		mDeltaTime = std::chrono::duration<float>(0.0f);
	}

	Timer::~Timer() {

	}

	void Timer::Reset() {
		mStartTime = std::chrono::system_clock::now();
	}

	float Timer::DeltaTime() {
		return mDeltaTime.count();
	}

	void Timer::TimeScale(float t) {
		mTimeScale = t;
	}

	float Timer::TimeScale() {
		return mTimeScale;
	}

	void Timer::Tick() {
		mDeltaTime = std::chrono::system_clock::now() - mStartTime;
	}
}