parent::[Computer Networks](Computer%20Networks)
see-also::[Static IP Address](Static%20IP%20Address)

Related protocols:: [UDP](UDP)

It simply allows devices (phone, pc, etc) to be assigned a unique _local_ IP address by the DHCP server (typ. the router). Note that the _dynamic_ means that the unique IP address is periodically changed (vs. Static IP Address) by the Server. 

Many times, since this is done by the router, the configuration can be setup on the Router's DHCP, or LAN, settings page.

DHCP is supposed to be simple to use - clients automatically look for a DHCP server to ask for an available IP address to be assigned to themselves.

**Advanced Settings**
- IPv6, SLAAC, And RA: allow auto-assigning of IP addresses for clients
- Lease Time: how long clients keep their address assigned by the server (typ. 0 = infinite)
-  

> Dynamic Host Configuration Protocol DHCP is a network protocol that helps us to assign an IP address and related IP information to the devices such as servers, desktops, or mobile equipment in the network. Many [network switches](https://www.fs.com/c/network-switches-3079?c_site=community&c_ctype=knowledge&c_from=wordlink&c_cat=BMCS220008-Enterprise_Switches-Wiki&c_rel=19545) also apply DHCP to provide valuable [TCP/IP network](https://community.fs.com/blog/tcpip-vs-osi-whats-the-difference-between-the-two-models.html) services, for example, it helps to automatically upgrade software on client systems.

> Features: 1. Provide additional information such as IP addresses of the host and Subnet mask of the computer. 2. Assigns IP to host for a particular lease time.

> DHCP works by leasing IP addresses and IP information to network clients for a period of time. To achieve this, the DHCP client has to interact with DHCP servers through a series of DHCP messages, which mainly include DHCP DISCOVER, DHCP OFFER, DHCP REQUEST, and DHCP ACK, as shown in the following figure.

`DHCP DISCOVER`: The client looks for a DHCP server by broadcasting its [MAC address](MAC%20address) and name.
Then there is a back-and-forth between the server and client:

> Simply put, it’s a story of “take and give” between DHCP client (A) and DHCP server (B):
> A: Who can give me an IP address?
> B: Ummm, let me check…There is One available!
> A: Great! Give me, please!
> B: No problem, here you are.

Source: https://community.fs.com/blog/dhcp-and-dns-difference.html

