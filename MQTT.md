> MQTT is an OASIS standard messaging protocol for the Internet of Things (IoT). It is designed as an extremely lightweight publish/subscribe messaging transport that is ideal for connecting remote devices with a small code footprint and minimal network bandwidth

![Pasted image 20221028113639](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221028113639.png)
Image from IBM https://www.ibm.com/developerworks/community/blogs/c565c720-fe84-4f63-873f-607d87787327/entry/tc_overview?lang=en


### Raw

- the protocol is event driven and connects devices using the publish /subscribe (Pub/Sub) pattern. The sender (Publisher) and the receiver (Subscriber) communicate via Topics and are decoupled from each other. The connection between them is handled by the MQTT broker. The MQTT broker filters all incoming messages and distributes them correctly to the Subscribers.
- https://www.hivemq.com/mqtt-essentials/
- MQTT would be standardized under the wings of OASIS, an open organization with the purpose of advancing standards
- MQTT publish/subscribe pattern (also known as pub/sub) provides an alternative to traditional client-server architecture. In the client-sever model, a client communicates directly with an endpoint.The pub/sub model **decouples the client that sends a message (the publisher) from the client or clients that receive the messages (the subscribers)**. The publishers and subscribers never contact each other directly. In fact, they are not even aware that the other exists. **The connection between them is handled by a third component (the broker)**
-   **Space decoupling:** Publisher and subscriber do not need to know each other (for example, no exchange of IP address and port).
-   **Time decoupling:** Publisher and subscriber do not need to run at the same time.
-   **Synchronization decoupling:** Operations on both components do not need to be interrupted during publishing or receiving.
- ** MQT Pub/Sub scales better than the traditional client-server approach**. This is because operations on the broker can be highly parallelized and messages can be processed in an event-driven way.
- Subject, Content, or Type based message filtering
	- The receiving client subscribes to the broker for topics of interest. From that point on, the broker ensures that the receiving client gets all message published to the subscribed topics. In general, topics are strings with a hierarchical structure that allow filtering based on a limited number of expressions
- Quality of Service - we can have the broker and client send handshakes to make sure the data was recieved
- persistent sessions - if a client is offline the broker will save the message (this is like a message queue
- MQTT includes a keep alive function that provides a workaround for the issue of half-open connections (or at least makes it possible to assess if the connection is still open).)
- > The single-socket state-full connection does have a tradeoff in that, while not a lot of data is transmitted, it does have to hold that socket connection openOn the other hand, connections are so light and fast, maybe your publication application is OK with connecting every time needs to send data
- once you CONNECT you can PUBLISH and SUBSCRIBE immediately without any other headers. That means we can stream data in and out of multiple 'topics' quickly and easily
- Since the protocol's state-machine is simple, full MQTT clients can fit in microcontrollers with as little as 32KB of Flash and 2KB of RAM

### Resources
- https://learn.adafruit.com/alltheiot-protocols/mqtt