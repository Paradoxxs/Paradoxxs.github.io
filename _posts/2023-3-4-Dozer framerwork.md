Drozer is a security and attack framework for Android. It allows you to perform penetration testing on the application installed on a phone by installing an agent on the device. You can download it from [here](https://github.com/FSecureLABS/drozer/releases).

The utility of Drozer is quite narrow, as it is primarily used to find new methods of extracting information from applications that are not available through other means. While I won't go into specifics on how to find vulnerabilities within applications, it's important to be aware that the tool exists.

Installing Drozer can be a bit of a hassle since it runs on Python 2. You can find a troubleshooting guide for Drozer installation [here](https://blog.krybot.com/a?ID=00750-1d57cbc1-cea0-4750-a9c5-343358bf43d3).

The first step is to install the Drozer agent on the phone using ADB:

```
adb install .\drozer-agent-2.3.4.apk
```

Once you start the Drozer server on the phone, it will run a service on port 31415 to allow your host to communicate with the phone. You'll need to port forward the service from the phone to the host device using ADB:

```
adb forward tcp:31415 tcp:31415
```

Once forwarded, you need to connect the console to the device:

```
drozer console connect
```

Drozer has several commands you can use to interact with the device, retrieve information about applications, and test for potential vulnerabilities. Some examples of these commands include listing details about the application, reading the app manifest, listing possible attack surfaces for the app, and testing for SQL injection.

Mastering reverse engineering applications requires practice and understanding the thought patterns of application developers. With experience, you'll become proficient in identifying and exploiting vulnerabilities in Android applications using tools like Drozer.

**Possible commands**

| Commands    | Description                                                                                                          |
| ----------- | -------------------------------------------------------------------------------------------------------------------- |
| Help MODULE | Shows help of the selected module                                                                                    |
| list        | Shows a list of all drozer modules that can be executed in the current session.                                      |
| shell       | Start an interactive Linux shell on the device, in the context of the Agent.                                         |
| clean       | Remove temporary files stored by drozer on the Android device.                                                       |
| load        | Load a file containing drozer commands and execute them in sequence.                                                 |
| module      | Find and install additional drozer modules from the Internet.                                                        |
| unset       | Remove a named variable that drozer passes to any Linux shells that it spawns.                                       |
| set         | Stores a value in a variable that will be passed as an environmental variable to any Linux shells spawned by drozer. |
| shell       | Start an interactive Linux shell on the device, in the context of the Agent                                          |
| run MODULE  | Execute a drozer module                                                                                              |

**List details about the application**.\
Everything from the version of the app to the location of the data.

```
run app.package.info -a com.mypackage
```

**Read the app manifest page**

```
run app.package.manifest com.mypackage
```

**List possible attack surfaces for the app**\
This inter-process communication (IPC) can be used to interact with the application and possibly extract data from the application.

* *Activities* allow you to start an activity and possibly gain access to information that you should not have.
* *Content providers* can possibly give yo access to private data or exploit SQL injection or path traversal vulnerabilities.

```
run app.package.attacksurface mypackage
```

output:

```
Attack Surface:
  2 activities exported
  3 broadcast receivers exported
  0 content providers exported
  1 services exported
```

**Activity**

List the specific activity the application is exposing

```
run app.activity.info -a com.mypackage
```

launch activity

```
run app.activity.start --component com.mypackage activity
```

**provider**

*Information* Gather information about the content provider

```
run app.provider.info -a com.mypackage 
```

*Dictionary attack on provider* Tries to access content based on directory of common paths.

```
run scanner.provider.finduris -a com.mypackage
```

*Query content* Collection information from the content uri, sometimes you can even modify the data.

```
run app.provider.query content://com.mypackage.DBContentProvider/Passwords/
```

**SQL injection with query content**

A lot of android application uses SQLite to store user data, and as with any application running SQL, the mobile application can also be vulnerable to SQL injection.

```
run app.provider.query content://my.package.DBContentProvider/Passwords/ --projection "'"
```

**Automate test for SQL injection**

```
run scanner.provider.injection -a com.mypackage
```

**Reading file**

Can also be used to read files from the content provider You can try to exploit path traversal by using tricks such as _../_ to gain access to additional content.

```
run app.provider.read content://com.mypackage.FileBackupProvider/etc/hosts 
```

**Automatepath traversal**

```
run scanner.provider.traversal -a com.mypackage
```

Becoming good at reverse engineering application practice is key. It comes down to trying and understanding the thought pattern of the application developer.