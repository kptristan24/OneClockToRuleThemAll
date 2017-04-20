#ifndef TIMES_H
#define TIMES_H

struct timeS{
        timeS(const int &m, const int &h){
                minute = m;
                hour = h;
        }
        bool equals(const timeS &lH, const timeS &rH) const {
                return (rH.minute == lH.minute)
                    && (rH.hour == lH.hour);
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
