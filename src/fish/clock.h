//Time representation.
struct clockTime{
  uint8_t wday;
  uint8_t day;
  uint8_t month;
  uint8_t year;
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t active;
};

typedef struct clockTime clock_time;

//Short time.
struct shortTime{  
  uint8_t hour;
  uint8_t minute;  
};

typedef struct shortTime short_time;

//Functions.
void setupClock();
clock_time read_ds1307();
uint8_t bcd2bin(uint8_t bcd);
void print_time(clock_time timeParam);
int convertTime(int hour, int minutes);
boolean inTime(clock_time now, clock_time start, clock_time end);
clock_time createTime(int hs, int min, int sec);
