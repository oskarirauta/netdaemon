#pragma once

#include <string>
#include <ctime>

struct timespan;

struct clock_time {

	private:
		bool tomorrow = false;
		clock_time(bool tomorrow, char hour, char minute) : tomorrow(tomorrow), hour(hour), minute(minute) {}
		clock_time(const clock_time &ct, bool tomorrow) : tomorrow(tomorrow), hour(ct.hour), minute(ct.minute) {}

		friend timespan;

	public:
		char hour, minute;

		clock_time() : tomorrow(false), hour(0), minute(0) {}

		clock_time(char hour, char minute) : tomorrow(false), hour(hour), minute(minute) {

			if ( !(this -> hour >= 0 && this -> hour < 24 && this -> minute >= 0 && this -> minute < 60 )) {
				this -> hour = 0;
				this -> minute = 0;
			}
		}

		clock_time(time_t ct) {

			struct tm *tm_struct = localtime(&ct);

			this -> tomorrow = false;
			this -> hour = tm_struct -> tm_hour;
			this -> minute = tm_struct -> tm_min;
		}

		inline int minute_of_day(void) const {
			return ( this -> hour * 60 ) + minute;
		}

		inline void reset(void) {
			this -> hour = 0;
			this -> minute = 0;
		}

		inline bool is_valid(void) const {
			return this -> hour >= 0 && this -> hour < 24 && this -> minute >= 0 && this -> minute < 60;
		}

		inline bool operator==(const clock_time& another) const {
			return this -> hour == another.hour && this -> minute == another.minute;
		}

		inline bool operator!=(const clock_time& another) const {
			return !(this -> hour == another.hour && this -> minute == another.minute);
		}

		inline bool operator<(const clock_time& another) const {
			return this -> minute_of_day() < another.minute_of_day();
		}

		inline bool operator<=(const clock_time& another) const {
			return this -> minute_of_day() <= another.minute_of_day();
		}

		inline bool operator>(const clock_time& another) const {
			return this -> minute_of_day() > another.minute_of_day();
		}

		inline bool operator>=(const clock_time& another) const {
			return this -> minute_of_day() >= another.minute_of_day();
		}

		inline clock_time& operator=(const clock_time& another) {
			this -> hour = another.hour;
			this -> minute = another.minute;
			return *this;
		}

		inline clock_time operator+(const clock_time& another) {
			clock_time res { this -> hour, this -> minute };
			for ( char h = another.hour; h > 0; h-- )
				res.hour = res.hour > 23 ? 0 : ( res.hour + 1 );
			for ( char m = another.minute; m > 0; m-- ) {
				res.minute = res.minute > 59 ? 0 : ( res.minute + 1 );
				res.hour = res.minute != 0 ? res.hour : ( res.hour == 23 ? 0 : res.hour + 1 );
			}
			return res;
		}

		inline clock_time& operator+=(const clock_time& another) {
                        clock_time res { this -> hour, this -> minute };
                        for ( char h = another.hour; h > 0; h-- )
                                res.hour = res.hour > 23 ? 0 : ( res.hour + 1 );
                        for ( char m = another.minute; m > 0; m-- ) {
                                res.minute = res.minute > 59 ? 0 : ( res.minute + 1 );
                                res.hour = res.minute != 0 ? res.hour : ( res.hour == 23 ? 0 : res.hour + 1 );
                        }
			this -> hour = res.hour;
			this -> minute = res.minute;
                        return *this;
		}

		inline clock_time operator-(const clock_time& another) {
			clock_time res { this -> hour, this -> minute };
			for ( char h = another.hour; h > 0; h-- )
				res.hour = res.hour < 1 ? 23 : ( res.hour - 1 );
			for ( char m = another.minute; m > 0; m-- ) {
				res.minute = res.minute < 1 ? 59 : ( res.minute - 1 );
				res.hour = res.minute != 59 ? res.hour : ( res.hour == 0 ? 23 : res.hour - 1 );
			}
			return res;
		}

		inline clock_time& operator-=(const clock_time& another) {
			clock_time res { this -> hour, this -> minute };
			for ( char h = another.hour; h > 0; h-- )
				res.hour = res.hour < 1 ? 23 : ( res.hour - 1 );
			for ( char m = another.minute; m > 0; m-- ) {
				res.minute = res.minute < 1 ? 59 : ( res.minute - 1 );
				res.hour = res.minute != 59 ? res.hour : ( res.hour == 0 ? 23 : res.hour - 1 );
			}
			this -> hour = res.hour;
			this -> minute = res.minute;
			return *this;
		}

		inline bool ends_tomorrow(void) const {
			return this -> tomorrow;
		}

		inline std::string to_string(void) const {
			return ( this -> hour < 10 ? "0" : "" ) + std::to_string(this -> hour) + "." + ( this -> minute < 10 ? "0" : "" ) + std::to_string(this -> minute);
		}

};

struct timespan {

	public:
		clock_time begin, end;

		timespan() : begin(clock_time()), end(clock_time()) {}

		timespan(clock_time begin, clock_time end) : begin(begin), end(clock_time(end, end < begin)) {}

		inline bool is_valid() const {
			return this -> begin.is_valid() && this -> end.is_valid() && this -> begin != this -> end;
		}

		inline bool contains(const clock_time& ct) const {

			if ( !this -> is_valid() || !ct.is_valid())
				return false;
			else if ( this -> end.tomorrow )
				return ct >= this -> begin ? true : ( this -> end >= ct ? true : false);
			else
				return ct >= this -> begin && this -> end >= ct;
		}

		inline bool ends_tomorrow(void) const {
			return this -> end.ends_tomorrow();
		}

		inline std::string to_string(void) const {
			return this -> begin.to_string() + " - " + this -> end.to_string();
		}

};


const std::string to_string(const clock_time& ct);
const std::string to_string(const timespan& ts);
