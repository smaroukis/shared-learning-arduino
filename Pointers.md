parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)

> [!EXAMPLE]- Example Code - Writing to EEPROM ^[https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory]
> ```cpp
> // ************************************************
> // Write floating point values to EEPROM
> // ************************************************
> void EEPROM_writeDouble(int address, double value)
> {
>    byte* p = (byte*)(void*)&value;
> // ************************************************
> // write floating point values to eeprom
> // ************************************************
> void eeprom_writedouble(int address, double value)
> {
>    byte* p = (byte*)(void*)&value;
>    for (int i = 0; i < sizeof(value); i++)
>    {
>       eeprom.write(address++, *p++);
>    }
> }
> 
> // ************************************************
> // read floating point values from eeprom
> // ************************************************
> double eeprom_readdouble(int address)
> {
>    double value = 0.0;
>    byte* p = (byte*)(void*)&value;
>    for (int i = 0; i < sizeof(value); i++)
>    {
>       *p++ = EEPROM.read(address++);
>    }
>    return value;
> }