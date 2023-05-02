The outcome of the threat research can come in one of many favors, everything from a report to new detection rules. Reporting can comes in many flavours the best I have found when it comes to incident reporting is [the dfir report](https://thedfirreport.com/). You get everything you need to ensure that you are able to detect the attack in your environment.\
When it comes to creating detection rules the most common are _Snort, YARA and Sigma_

The outcome of the threat research can come in one of many favors, everything from a report of excel spreadsheet, powerpoint or pdf that are delivered to the stakeholder. The best I have found when it comes to incident reporting threat report is [the dfir report](https://thedfirreport.com/).\
It can also come in form of detection rules.\
The most common detect rule are _Snort, YARA and Sigma_

Snort is a detection rule set for network traffic. Yara for files and Sigma is for log files.\
This allow defender to have an common framework for sharing detection rules. That is vendor neutral.

### Reporting

It important to understand when written an report that the reader is not as technical as you. Which is why it required by you to properly explain everything that everyone can understand it no matter their level.

The structure I use for my reports are as followed.

* Hypothesis/goal
* Conclusion
* Analyses
* Appendix

I would like to add a quick tip. Create templates for the commonly used techniques that you can quickly insert into your reports to explain the method you went through.



[Sigma](https://github.com/SigmaHQ/sigma) is a tool for identifying pattern in log event. These rules consist of a set of detection rule used to identify malicious events. It uses a yml format for it rule definition.

Structure Sigma rule for detection of new schedule task created

```yml
title: Scheduled Task Creation # Name of the rule 
status: experimental 
description: Detects the creation of scheduled tasks in user session
author: Florian Roth
logsource:
    category: process_creation
    product: windows
detection:
    selection:
        Image: '*\schtasks.exe' 
        CommandLine: '* /create *'
    filter: 
        User: NT AUTHORITY\SYSTEM
    condition: selection and not filter
fields: # The field to search in
    - CommandLine
    - ParentCommandLine
tags:
    - attack.execution
    - attack.persistence
    - attack.privilege_escalation
    - attack.t1053
    - attack.s0111
falsepositives:
    - Administrative activity
    - Software installation
level: low # Alert level
```

[Snort](https://www.snort.org/) is a open source IPS, which uses a series of rules that define malicious network activity.\
The rule are used to filter on network packets to find once that matches the defined rules.

Yara is a pattern matching tool used to identify binary files. Using hexadecimal and strings contained within a file.

Installing yara

```
sudo apt install yara
```

### Structure

#### Module

Allow you to extend the functionality of yara. _import "pe"_ can be used to match data from PE files.

#### Meta

Describe information by the author of the yara what the purpose of the rule are. Such as author name, date, description of the rule, etc.

#### Strings

Defines keyword that we want to search for. You can both define strings, hexadecimal and regex. that the engine used to identify samples.

Defined as followed within a rule

```
strings:
    $s = "strings1" nocase wide
    $hex = {00 ?? 38 [2-4] B4}
    $domain_reg = [(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]]
```

You can use text strings modifier to extend the function

| modifier       | description                                |
| -------------- | ------------------------------------------ |
| nocase         | case insensitive                           |
| wide           | encoded strings with 2 bytes per character |
| fullword       | non alphanumerical                         |
| xor(0x01-0xff) | look for xor encryption strings            |
| base64         | base64 encoded strings                     |

Within in hex string you are also able to define wildcard using _?_ As you can see above I have defined that the second hex can be anything.

#### Condition

Tell yara what keyword should be present in the binary before it a match, by default it will use _any of them_ which tells the system to match is any of the keyword is found in the sample

Tell yara to only match is there if the string is present 5 or more. e.g.

```
condition:
    $s >= 5
```

You are also able to combine multiple keywords using condition such as **and , not, or** The functionality follow the same as you would see in any other programming language

### Automation gernation of yara

You can use yargen to automate the process of generate yara rules based on files

| parameter     | description                                           |
| ------------- | ----------------------------------------------------- |
| -m            | path to files you generate file for                   |
| --excludegood | exclude good strings (string found in legit software) |
| -o            | output location and name of the yara rule.            |

```
python3 yarGen.py -m suspicious-files --excludegood -o
```

There exist many more tool that will automate the process of generating yara rules, this is just one of them.