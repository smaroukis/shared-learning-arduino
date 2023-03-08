Tl;dr
- 4 pin [[SPI]], max data rate 10Mbps (also supports [[I2C]] and [[UART]])
- pins are 5V tolerant, but specified at 3.3V
- use the `MFRC522.h` library
- check out the DumpInfo example sketch for MVP


## Pinout
![[Pasted image 20230307203135.png]]

RST: low →power down, rising edge → reset
IRQ: interrupt pin will go high when the RFID tag is in the vicinity


> [!TIP]- Arduino SPI based on Board Type
> ![[Arduino SPI pins based on Board Type]]


>The RC522 RFID reader module is designed to create a 13.56MHz electromagnetic field and communicate with RFID tags (ISO 14443A standard tags). 

## Data Layout
![[Pasted image 20230307205202.png]]

> The last block of each sector is called a **Sector Trailer**. It contains information called **Access Bits** that provide read and write access to the remaining blocks in the sector. This means that only 3 blocks of each sector (Blocks #0, #1 and #2) are actually writable, in other words only 48 bytes per sector are available for use.

## Examples
[[Example - RFID Dumpinfo with MFRC522]]

