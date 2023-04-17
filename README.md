# NUCLEO-F411RE_timeSetTest

HAL_RTC_SetTime function shows some errors for time setting. 
In some cases, the day exceeds 31 or the time exceeds 23:59:59.

To adjust the time,
the case statement for leap year is used to adjust the date and the time
in main.c


