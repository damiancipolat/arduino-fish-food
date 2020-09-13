<img src="https://github.com/damiancipolat/arduino101/blob/master/doc/logo.png?raw=true" width="150px" align="right" />

# Arduino Fish food :fish: :tropical_fish: :blowfish:
A personal arduino project, created with the goal of helping me remember to feed my fish.

## Hardware:
- Arduino NANO
- Tiny RTC clock
- Mini protoboard
- 2 leds (red/blue)
- Buzzer
- 1 button press
- 5 wires.

## Configuration:
The program has configurated with this times, to change go to /src/fish/fish.ino.

```c
//Define times;
clock_time current_time;
clock_time FOOD_START = createTime(9,0,0);
clock_time FOOD_END = createTime(12,0,00);
clock_time SLEEP_START = createTime(23,0,0);
clock_time SLEEP_END = createTime(8,0,0);
```

- **Feed time**: 09:00 to 12:00
- **Sleep mode**: 23:00 to 08:00
