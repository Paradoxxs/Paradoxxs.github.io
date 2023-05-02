Windows application compatibility database is used by Windows to identify possible application compatibility challenges when executing PE files. Execution files get shimmed as soon as they hit the disk. If the executable is moved, rename or modified, the executable gets re-shimmed by the system, adding new entries into shimcache database. Any executable that has existed on the system can be found in this key. It should be noted that it does not get instantly get written to the register. It only gets written to the database when the system reboots, until that it only lives within memory. AppCompatCache also stores the timestamp for when the file was last modified. When it comes to malware it can be used to track any executable that has hit the disk. Even if deleted, renamed, etc. the entry will still be there.

**With windows 10 it can no longer be used to identify file execution**


With Windows XP there were at most 96 entries and LastUpdateTime is updated when the file was executed.\
As of Win 7+, the entries were increased to 1,024. _LastUpdateTime_ is replaced with an execution flag, This means it can no longer be used to determine the last execute time. Only if the exceptionable was run or not. When it comes to system files such as _cmd_, _regedit_, etc they first get shimmed at the time of execution.

Stored the following information on executable:

* File path
* Last modification date
* File size
* Executed

It possible to analysis the appcombatcache using Eric Zimmerman tool _AppCombatCacheParser_, it only need three parameters the source of the system file and the output type and directory.

```
AppCombatCacheParser --csv .\ -f .\SYSTEM
```

Tools:

* AppCompatCacheParser
* ShimCacheParser.py

Evidence location:

```
HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\AppCompatCache  
```

The usage of app combat cache is not as useful as it once was, but there are still something information such as what application have been installed on the machine that can still be retrieved from this evidence.