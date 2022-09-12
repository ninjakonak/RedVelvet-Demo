#ifndef _TIMER_H
#define _TIMER_H
#include<chrono>

namespace EngineUtils {
	class Timer {
	private:
		static Timer* sIntance;
		std::chrono::system_clock::time_point mStartTime;
		std::chrono::duration<float> mDeltaTime;
		float mTimeScale;

	public:
		static Timer* Instance();
		static void Release();

		void Reset();

		float DeltaTime();

		void TimeScale(float t=1.0f);

		float TimeScale();

		void Tick();

	private:
		Timer();
		~Timer();
	};

}


#endif