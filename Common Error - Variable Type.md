#code 
garden-topic::[Arduino Variable Types](Arduino%20Variable%20Types.md)

The result is `255` since `baz` is a `byte` (which only goes from 0 to 255)

```cpp

byte foo = 2;
byte bar = 1;
byte baz;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 Serial.println("hello world..");

 if (foo < bar) {
   baz = 1;
   Serial.println(baz);
 }
 else {
 baz = -1;
   Serial.println(baz);

 }
}

void loop() {
  // put your main code here, to run repeatedly:


}
```