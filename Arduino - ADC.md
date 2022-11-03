parent::[[Introduction to Arduino - Hardware]]

The ADC, or Analog to Digital Converter, converts the analog voltages to a discrete number (integer). For the Arduino 10-bit ADC by default it converts a voltage between 0-5V to an integer decimal between 0-1023. The upper value, 5V, is the reference value and can be changed with  `analogReference();`

Converting from a standard 5V reference:
$$ k_{ADC} = 204.6 * V_{in}$$

For any reference voltage:
$$ k_{ADC} = (V_{in} * 1024)/V_{ref} $$
$$ V_{in} = (k_{ADC} *V_{ref})/1024 $$ 
Getting more specific, each decimal output corresponds to a *range* of analog inputs (over ~5mV). For example, assuming our reference voltage is exactly 5.0V, when we the ADC gives us a value of 1023, we cannot exactly map 1023 to 5V, but rather _only to a value above or equal to 4.995V_. 

## List of Commands
- `analogReference(); // changes the reference from the default 5.0V`
- `analogReadResolution(); // changes the resolution from the default of 10 bits` [^1]

## Pro-Tips

From the official Arduino forum user `Robin2`, we can easily divide a number by 1024 using bit-shifting: (see more on [[bit-shifting.md|bit-shifting]]
```
dividedValue = originalValue >> 10;
```


[^1]: the Uno's ADC resolution is 10 bits, but other families of Arduino have higher resolution, so we need to change it in the code 

## Further Reading
- https://forum.arduino.cc/t/10-bit-adc-divide-by-1024-or-1023/657174/3