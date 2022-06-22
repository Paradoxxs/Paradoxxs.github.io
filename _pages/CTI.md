---
layout: page
title: CTI
permalink: /CTI/
---



# Cyber threat intelligence / Invegitation

## Overview

The goal of threat intelligence is to gather, evaluate and analysis data related to a threat actor,
to better understand their tactic technique and procedure to make better decisions on how to take action aginst the threat.
     Gathering, evaluating, and analyzing data related to the [Threat](Threat.md)
with the goal to prevent the threat entirely or limit the damage caused.
This is done by understanding the threat, what tool they use and how to mitigate them.

### Cyber 

### Threat 
Threat is an actor is with capability and intent to hurt the target 

### Intelligence 
Collection and processing of information against an specific target or question and transforming in something actionable for the consumer. 

#### Shermen kent 

The father of western intelligence analysis, during the world war II he joined the *Office of Strategic service* (OSS), which would take become the CIA. During his time, he heavily focused on how to prefessionalize the analysis process instead of allowing rash decisions and judgement to take action. which is why he wrote the *Strategic intelligence for american world policy*

##### Kent doctrine 
  
1. Focus on policymaker concerns
2. Avoidance of personal policy agenda
3. Intellectual rigor
4. Conscious effort to avoid analytic biases
5. Willingess to consider other judgements
6. Systematic use of outsideexperts
7. Colletive responsibility for judgement
8. Effective communication of policy-support information and judgements
9. Candid admission of mistakes 

## Intelligence level

- Tactical
  - Speific action that can be taken to defend the organisation
- Operational
  - Bridges tactical and strategic, by assessing the organization operating enviroment to identify potential risk
- Strategic
  - Define the objectives and guidance on what threat should be mitigated and the security posture of the organization.

## Intelligence process lifecycle

1. Direction
    - Understanding the needs of the audience, and define intelligence requirements to address the threat
    - What assets need to be protected?
2. Collection
    - Gathering of data from different source
3. Processing
    - Data is transformed into a understandable format.
4. Analysis
    - Assessment of the treat capability and vulnerability, based on the data collected.
5. Dissemination
    - Distrubution of the intelligence report
6. Feedback
    - Feedback loop for improving the process.

## Intelligence classification

- Unknownunknown
  - Unaware of the existence of a threat
- Knownunlnown
  - The threat is known but not understood
- Knownknown
  - We both know and understand the threat, and resource to put in place to mitigate them.

## Gathering and correlating information

Data in a vacuum, without context, is difficult to interpret and understand, which is why we have multiple sources of data that can be correlated together to create intelligence, by enriching data and providing value by passing the information to the different stakeholders.
Sources
![](https://remnote-user-data.s3.amazonaws.com/SvsPH0IO5tuMWpPgrTVWhr3Z6ZQns2_tK1Yfv56svF0cW07iL2HLxk5dcFj7PYeTykEehQ5t1cOrv8YnwBRi-HtTuMfKyGE8h66uuhgEAzwjrPT6TgfQnzcCe8FUDILF.png)

## Threat modeling

Representation of a threat and how it related to the consumer

## Collection management framework

Datasheet that explain the source of informations, and what information can be answered from the different sources.
And what can be used to pivot on.

![](https://remnote-user-data.s3.amazonaws.com/OopTWh5cncwsJE4xXVMQjPLaLSjBTCMY9co-lEfgzAo8Cq9MEWDXFCMN4Bk2mYPgdPayPRXyerAdSeIhC5ipWlruyTy2t__r3wqjUAC4jje4HFP_1WTsHTB0P58wNQs-.png)

![](https://remnote-user-data.s3.amazonaws.com/N46wlL6t_4fFAuPl0dYoTnabr77RuKlooSjy0aMJvx40eEFCwWWZ5DvwTDtb-7xQnT9SSHfH2K0aBsk5d5B772CQqo4E1bPsk6kc_bykdItMh8CEO789MVI6lEw_M6ZW.png)

## Intel to threat hunting and incident response

 1. Threat model
    - Select a threat and its tactics techniques and procedures (TTP)
 2. Create a hypothesis
    - Create a testable statement related to how the threat TTP would impact your organisation
 3. Overlay the tradecraft and your CMF
    - Map the hypothesis to the CMF to identify what needed to be tested
 4. Hunting
    - Hunt aginst the hypothesis and CMF
 5. Learn
    - Identify gaps and opportunities of improvement
      Create playbooks for future investigation against the TTP in your environment

## Four type of threat detection

![](https://remnote-user-data.s3.amazonaws.com/x29FpsM1_slrWzG_eAM0Yhpc2KNLMO-AgpdMznCllBLTqY_MNQ4agXPNnaM917bqfioqOqMSm3LLRYN_KTvHed8kY2r72ZeKOh832P7yQkycUFwDBzEsQ6F2_TOvwhN1.png)

## Information pivot

IP ⇒ Domain ⇒ WhoIs or SSL cert ⇒ etc. <br>
Email ⇒ username ⇒ account ⇒ etc. <br>

- IP addresses
  - Source, intermediary
- Domains
  - Compromised, actor registered, DDNS
- Accounts
  - Email account, VPS account, Service account, Personal account
- Unique strings
  - Passwords, Mutex, handles, encryption keys

## Courses of Action

Matrix
![](https://remnote-user-data.s3.amazonaws.com/Lozxdt21TNKsSlNfbfbxV3yykrJNlY7yRhlKfk4sHUf6pnDbV5ygSkvTXKr8c_nE-2E764Nf9uk_Vw-xGclQPNtBIy7MiB6nQxb4G10YraWF7E9jV0Ru9_DRXE0YJ0Z2.png)

## Collection sources

- Tactical
  - The technical tactics, techniques and procedures used by the threat actor, that the technical personal that use to tune their detection engines.
eg.

The analyst to map an malware to the **capabilities** of the diamond model and it can be used to pivoting to identify commonalities in intrusions, such as domain and IP used.
it should be noted an quick downfall of tracking malware, is that it quickly becomes tracking the author instead of the operator.

- Operational
  - Reporting on threat groups

- Strategic
  - Geopolitical reports

## Data pivoting / Analytic leaps
 1. Start with single indicator
 2. Pivot through each data source and add relevant data points
 3. Validate, ensure links contain context and ensure the links are meaningful
 4. Identify the relevant indicators  

Kevin bacon effect, It takes 6 hops/pivoting to know anyone in the world.

## The Rule of 2

Simply way for campaign creation is applying the diamond model looking for overlaps between two vertices in intrusions or campaigns 

## Pyramid of pain

![](https://remnote-user-data.s3.amazonaws.com/g5p1PSh-1o05NUSgQmhouqlrwO9f18sqF-tml3DI0VwG9TkkqWk7Xzm6BGO3EDTf13uRFDTLFHUOpy8Smhhakct4i4OtYx_l9ZEd6GexLn0tGt75mY_L2hRbLe7R_SfI.png)

## Collection

### Threat feeds

Before acquiring an threat feed you need to understand why you need it, An good way to start with threat feed is using open source like DShield, if you do not know how to handle it, you are not ready for the next level.
One of the key question to ask about threat feed is the data source of the feed.
Processing
Rosetta stone
Translation naming schema what the different vendors calls malware, threat actors, etc..
Very helpful to understand different threat reports.
 Analysis
Bias
Everyone has bias, and it important as an analyst to be aware of your own bias.
Which is why the CTI team, need to be compromised of multiple different type of people to combat biases.
Cognitive bias
[24 Cognitive Biases stuffing up your thinking](https://yourbias.is)
Structured analytic techniques (SAT)
Decision matrix
Decision trees

## Dissemination

### Traffic light protocol (TLP)

Defined widely recognized threat intel protection level and who it can be shared with.
![](https://remnote-user-data.s3.amazonaws.com/a3ZQFulpDQV1Jd96ztQoQ8LY5GnnYfySNMbJ5Np-CB-ocw4DrZ_PlG7n8jeS0NdBQbFBi69JxcYWJs5V4dSQw-Iv9_sEOkg1XD6YA3UgfGlBJ2KSdWEj4zZygzbxe732.png)

### Estimative language

Because the meaning of words like likely, might, etc. is highly subjectively,  which is why it is important to have an agreedupon language of the estimate, like a scale
![](https://remnote-user-data.s3.amazonaws.com/clrfQYuefDhDtBOT7T4PnYaHtz_W_tUCNRXwJpj8d3hJ3_py6mYTgJoPfEoNkt618tUpSzARCFGq2W2yeJ1b4-MvhWX1Iw9jQVnYrVX9Ygtsy57wOh81UHBtTBkf5DmJ.png)
Another good idea is to add percentages to make the meaning clear.
e.g. might happen (70%)

## Frameworks

### Overview

Structure for thinking how attackers operate, the methods involved and where in the overall attack lifecycle event is occurring
Focus attention on proper area to ensure follow up, eradication and mitigation of future threat
Common language to communicate internally and externaly regarding the threat. 
Cyber kill chain  Based on military concept of the kill chain
Like a chain if one of the link break the whole attack fails. 
![](https://remnote-user-data.s3.amazonaws.com/clrfQYuefDhDtBOT7T4PnYaHtz_W_tUCNRXwJpj8d3hJ3_py6mYTgJoPfEoNkt618tUpSzARCFGq2W2yeJ1b4-MvhWX1Iw9jQVnYrVX9Ygtsy57wOh81UHBtTBkf5DmJ.png)

### Diamon model

![](https://remnote-user-data.s3.amazonaws.com/XDWmqBbConGqoXBxg5WYngqUMXyZNofQzsQtp2he2z989egpyVnfTDDQNHZbooYtXhe8mRFgRpnsjQDl1y7ZJWRUwPlNVaoF0iIXzbUT0QZGIiDohS31jitVMo2T6YNA.png)
Overview
    Describes an adversary deploys a capability via infrastructure against a victim
    Developed to be complementary to the cyberthreat kill chain 
    For every intrusion event there exists an adversary taking a step towards an intended goal by using a capability over infrastructure against a victim to produce a result
Adversary
    Threat / Operators
    One of the main problem that is seen a lot is the tracking of malware authors instead of Threat / operator
Infrastructure
Victim
It important to disquietly between victim and target
Capability/  Tactics, techniques and procedures  (TTP)
What tools, techniques, etc. do they use to perm their action

### Axioms

1. In every intrusion event an adversary takes a step towards an intended goal by using a capability over infrastructure against a victim to produce a result.
2. There exists a set of adversaries which seek to compromise computer systems or networks to further their intent and satisfy their needs.
3. Every system, and by extension every victim asset, has vulnerabilities and  exposures
4. Every malicious activity contains two or more phases which must be successfully executed in succession to achieve the desired result.
5. Every intrusion event requires one or more external resources to be satisfied prior to success.
6. A relationship always exists between the Adversary and their Victim(s) even if distant, fleeting, or indirect.
7. There exists a subset of the set of adversaries which have the motivation, resources, and capabilities to sustain malicious effects for a significant length of time against one or more victims while resisting mitigation efforts.

### Mitre attack

Track the different tactic that can be used in an attack and track the tactic the different threat group utilize.

## Building CTI program

Requirement creation
Identify and consult key stakeholders
map analyst workflows and data processes
Determine input and output needs
Prioritize requirements (MoSCoW)
    Musthave, Shouldhave, Couldhave, and Wish (buy) or Will not have at this time (build)  

Question to ask
What are your requirements ?
Who are the audiences?
How do the consumer wants to consume the information?
Competencies of CTI team
No single person can fill all the competencies, which is why it important to have a diverge team.
![](https://remnote-user-data.s3.amazonaws.com/CrG1W9AaVoxvf3VinRf1UqBJO7aMDzRkFvZ434mUv4zC0abKf-Y1QecdjvSLQJe3KE6qtUMFOqr-YND7yOGfqXhO75HcYJ6h0R08K01SeT_hjUybotFo8-Uj1R-IkK1f.png)

Mapping processes to each requirement level
Analysing the requirements in context of the organization
Understand your assets and their value
Identify threat actors motivated to access or harm your assets.
Determine the methods the threat actors would use
Map the attack surface and analyse it in context of the method used by threat actors.

### Tactical

What signature can we write to best identify malicious activity
Establishing and maintaining a malware zoo  

### Operational

What groups are likely to target our organization
Defining threat actor collections and profiling practices

### Strategic

What is the risk of acquiring a new company based in certain country
Standardizing research practices and report outputs  

## Tool collection

[GitHub  IVMachiavelli/awesomethreatintelligence: A curated list of Awesome Threat Intelligence resources](https://github.com/IVMachiavelli/awesomethreatintelligence)
