# fridge  
fridge is a simple arduino driver for camping fridge.  
The fridge is cooled by peltier module and powered from an old car battery.  
Temperature is measured by Dallas thermometer.
## basic principles  
Set temperature can be changed by pressing + and - buttons  
hysteresis is set to +-2C  
the driver switches the relay powering the peltier module and fans.  
the current and set temperature can be read from I2C LCD.  
