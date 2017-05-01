#ifndef TIMES_H
#define TIMES_H

struct timeS{
        timeS(){minute = 0; hour = 0;}
        timeS(const int &m, const int &h){
                minute = m;
                hour = h;
        }
        void set(const int &h, const int &m){
                hour = h;
                minute = m;
        }
        bool equals(const timeS &lH, const timeS &rH) const {
                return (rH.minute == lH.minute)
                    && (rH.hour == lH.hour);
        }
        bool operator ==(const timeS &other) const {
                return (this->minute == other.minute)
                    && (this->hour == other.hour);
        }
        bool operator>(const timeS &rH) const {
                return (hour > rH.hour)
                    || ((hour == rH.hour) && (minute > rH.minute));
        }
        bool operator<(const timeS &rH) const {
                return (hour < rH.hour)
                    || ((hour == rH.hour) && (minute < rH.minute));
        }

        uint8_t minute;
        uint8_t hour;
};

#endif
