parent::[[Arduino Software Concepts]]

Order of operation is important especially when using compound operators. 

- `millis() >= (delayStart + 1000)` is mathematically equal to `millis() - delayStart >= 1000` but the order of evaluation is important
	- for the first case, since it is an unsigned long, when `millis()` overflows to `0` after around 50 days the expression will now always be false
	- and in the other case when `delayStart` is initialized after 50 days, it will immediately evaluate to true
