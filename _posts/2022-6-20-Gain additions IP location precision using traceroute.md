# Gain additions IP location precision using traceroute 

When doing IP geo location on user IP address is can be very difficult to any kind of mening full preciession because the user get assinged a random IP address by DHCP. <br>
One way to over come this problem is to use traceroute command on the IP in question, using instead the last routing hop and geo locate on that IP address instead, can yield much better results, the reason this work better is because using routing infrastructure will yield more accurate results is because they do not change as much over time. <br>
One major down fall to this technique is that most routing traffic infasture block IMCP packages, leaving you unable to get the routing IP.