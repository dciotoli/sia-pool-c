# Sia-Pool-C
A stratum based Siacoin pool server. Written in C with a MySql Backend

## Todo
* Figure out how to get MySQL (or other persistent backend)
* Finish creating code skeleton
* Implement server functionality
* Create a web app that connects to same server to serve up stats to users

## Testing
Right now There's no tests or test client written, so the easiest way is to just test with netcat
(if you dont have netcat definitely get it).
Example:
```bash
	./stratum-server 7070 
```
Then run in another terminal tab
```bash
	nc localhost 7070
		{"method": "test"}
```
The server should echo the name of the method back at you... because thats as far as i've gotten right now. :-)