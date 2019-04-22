# Arduino Analog Serial



## Context:

In the context of my research work, I need it to log an analogue input signal. We need to do initial analysis, but the idea was to leave the set-up as a control log in the future.

For this second reason, a low cost option was preferred and the Arduino platform seemed appropriate as it was have been reported to have ADC rates of 153.8 KHz \[[1](http://yaab-arduino.blogspot.com/2015/02/fast-sampling-from-analog-input.html)\]. Such rates seemed enough for the vibration measurements from a cryostat vacuum set-up we wanted to perform.

The question was how to get such data into a file, so it could be analyse afterwards.

### Test1:

The ADC clock prescaler makes no difference as it is the serial transfer that is limiting the speed of the acquisition. The time between two points is of 595us.

### Test2:

I also tried using a buffer to store the data on the Arduino side, and then send it in one go through the serial. This lead to a 120us interval between data points in each buffer, but to 125ms gap between data buffers. Again, the prescaler had no influence.

