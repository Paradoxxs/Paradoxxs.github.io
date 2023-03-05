# How to make a release Android App debuggable

This will make set an application on the play store to allow debug mode, This allows you to use the run-as command to gain access to the /data section for the application.\
It should be noted that this method will delete the existing data on the device, as it requires the application to be uninstalled, because of mismatching signature.\
The reason why you might want to make a production application debuggable is to help speed up the process the retrieving process when performing dynamic analysis, without having to perform advanced acquisition of the phone or root the device.

For this task, we'll be using [apktool](http://ibotpeaches.github.io/Apktool/). You can use it to disassemble the the APK

```
apktool d -o output-dir com.mypackage.apk
```

In the output directory, you will find the AndroidManifest.xml. Open the file, within the _application_ tag, add the following XML attribute:

```
android:debuggable="true"
```

Now to reassemble the application again. We do this by running:

```
apktool --use-aapt2 b -o com.mypackge output-dir
```

Before it gets pushed to a device, we need to resign the APK so that the device will accept it:

```
keytool -genkey -v -keystore resign.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000
```

```
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore resign.keystore com.mypackage.apk alias_name
```

That's it! You should now be able to transfer the new com.mypackage.apk back on to the device and run it.

```
adb install com.mypackage.apk
```

Now you should be able to run ADB shell run-as ls /data/data/com.mypackage/ without getting the debuggable error.


