#ifndef _LIB_TIMESTAMP_H_
#define _LIB_TIMESTAMP_H_

#include <iostream>
#include <string>
#include <boost/operators.hpp> //less_than_comparable,只要实现小于操作，剩下的> >= <=都自动推导出来

#define MAX_STRING_SIZE 1024
class Timestamp:public boost::less_than_comparable<Timestamp>
{
	public:
		Timestamp():m_mSeconds(0)
		{

		}

		explicit Timestamp(int64_t microSeconds)
			:m_mSeconds(microSeconds)
		{

		}

		bool valid()
		{
			return m_mSeconds > 0;
		}
	
		void swap(Timestamp& that)
		{
			std::swap(m_mSeconds,that.m_mSeconds);
		}
		std::string toString() const;
		std::string toFormattedString(bool showMicroseconds = true) const;
		//返回微秒数
		int64_t microSecondsSinceEpoch() const { return m_mSeconds; }
		//返回秒数
		time_t secondsSinceEpoch() const
		{ 
			return static_cast<time_t>(m_mSeconds / kMicroSecondsPerSecond); 
		}

		static Timestamp now();
		static Timestamp invalid()
		{
			return Timestamp();
		}

		static Timestamp fromUnixTime(time_t t)
		{
			return fromUnixTime(t, 0);
		}

		static Timestamp fromUnixTime(time_t t, int microseconds)
		{
			return Timestamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microseconds);
		}

		static const int kMicroSecondsPerSecond = 1000 * 1000;
	private:
		int64_t m_mSeconds; //微秒
		
};

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
	  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs,Timestamp rhs)
{
	return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline Timestamp addTime(Timestamp timestamp, double seconds)
{
	int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond); //转换为微秒
	return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

inline double timeDifference(Timestamp high, Timestamp low)
{
	  int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
	  return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

#endif //end _LIB_TIMESTAMP_H_
