Models and frameworks are conceptual structures that are used to organize and understand data, by providing a way to structure complex information, there by making it easier to understand and manage information.

### Cyber kill chain

Based on the military concept of the kill chain.\
The idea is like a chain if one of the link break the whole attack falls apart.\
It an representation of the stages that an adversary have to go through to successfully perform an attack.

Stages:

1. Reconnaissance
2. Weaponization
3. Delivery
4. Exploit
5. Installation
6. Command and control
7. Action

The cyber kill chain is a model that is used to describe the stages of a cyber attack, from the initial intrusion to the final outcome. The cyber kill chain was developed by Lockheed Martin, and it is based on the military concept of the kill chain, which describes the stages of a military attack.

The cyber kill chain consists of seven stages:

1. Reconnaissance: This is the first stage of the cyber kill chain, and it involves gathering information about the target, such as its vulnerabilities and potential points of entry.
2. Weaponization: In this stage, the attacker creates a tool or payload (such as a virus or malware) that can be used to exploit the target's vulnerabilities.
3. Delivery: The attacker then delivers the weaponized payload to the target, often through phishing emails or other tactics that are designed to evade detection.
4. Exploitation: Once the payload has been delivered, the attacker attempts to exploit the target's vulnerabilities in order to gain access to the system or network.
5. Installation: If the exploitation is successful, the attacker will then install additional tools or malware on the target system, which can be used to maintain access and control over the system.
6. Command and control: At this stage, the attacker establishes a foothold on the target system, and begins to issue commands and control the system remotely.
7. Actions on objectives: Finally, the attacker carries out the objectives of the attack, such as stealing data, disrupting operations, or damaging the system.

The cyber kill chain provides a useful framework for understanding the stages of a cyber attack, and for identifying potential points of intervention or defense. By understanding the different stages of the cyber kill chain, organizations can develop strategies for detecting and defending against attacks, and for responding to attacks when they occur.

### Diamond model

The Diamond Model of Intrusion Analysis is a framework for understanding and analyzing the motivations, capabilities, and actions of malicious cyber actors. It was developed by security experts at the US National Security Agency (NSA) and is based on the idea that a thorough understanding of an adversary's capabilities, intentions, and tactics is essential for effectively defending against cyber threats. The Diamond Model consists of four main elements, or "facets," which are: the adversary's motivations and objectives, the adversary's capabilities, the adversary's techniques and tactics, and the victim's profile and defenses. By examining these facets, analysts can gain a more complete picture of the threat and develop more effective countermeasures.

#### Elements of the Diamond Model

the four main elements, or "facets," of the Diamond Model of Intrusion Analysis are:

* Adversary motivations and objectives: This facet focuses on understanding why the adversary is carrying out the attack, what their goals are, and what they hope to achieve. This could include motivations such as financial gain, espionage, or political activism.
* Adversary capabilities: This facet examines the adversary's technical capabilities, such as their level of expertise, the tools and techniques they use, and their access to resources. This information can help analysts understand the adversary's capabilities and limitations, and identify potential vulnerabilities.
* Adversary techniques and tactics: This facet looks at the specific tactics and techniques the adversary uses to carry out their attack. This could include information on how they gain access to the victim's systems, how they move around within the network, and how they maintain their presence and cover their tracks.
* Victim profile and defenses: This facet examines the victim's systems and defenses, including information on their network architecture, security controls, and response capabilities. This information can help analysts understand the vulnerabilities and weaknesses of the victim's systems, and identify potential points of entry for the adversary.

Diamon model is an representation of the element required for intrusion.\
The model describes how an adversary deploys a capability via infrastructure against a victim.

It was developed as a complementary tool to the cyber kill chain for every link in the chain there exist an intrusion event taking the adversary a step towards an intended goal by using a capability over infrastructure against a victim to produce a result.

#### Adversary

Threat / Operator

One of the main problem that is seen a lot is the tracking of malware authors instead of Threat / operator

#### Infrastructure

What system, network, e.g are they using to deliver their capabilities

#### Victim

It important to disquiet's between victim and target.\
Just because you see an threat group in your network that does not mean your were their target. You could just be an victim they used to pivot to their true target.

### Capability/ Tactics, techniques and procedures (TTP)

The methodology the of the threat actor to achieve their objective.

#### Axioms

1. In every intrusion event an adversary takes a step towards an intended goal by using a capability over infrastructure against a victim to produce a result.
2. There exists a set of adversaries which seek to compromise computer systems or networks to further their intent and satisfy their needs.
3. Every system, and by extension every victim asset, has vulnerabilities and exposures
4. Every malicious activity contains two or more phases which must be successfully executed in succession to achieve the desired result.
5. Every intrusion event requires one or more external resources to be satisfied prior to success.
6. A relationship always exists between the Adversary and their Victim(s) even if distant, fleeting, or indirect.
7. There exists a subset of the set of adversaries which have the motivation, resources, and capabilities to sustain malicious effects for a significant length of time against one or more victims while resisting mitigation efforts.

#### The rule of 2

By taking specific identifier correlated on two or more verticals with the diamond model can be used to define an activity group.\
e.g. observation of a very specific capability, which communicate consistently with infrastructure, that could be defined as a activity group

### Mitre ATT\&CK

[Mitre ATT\&CK](https://attack.mitre.org/) is a framework that is used to describe the tactics, techniques, and procedures (TTPs) used by attackers. It is a comprehensive model that covers the entire attack lifecycle, from the initial intrusion to the final outcome of the attack.

MITRE ATT\&CK was developed by the nonprofit organization MITRE, and it is based on real-world observations of attacks. It is designed to provide a standardized language for describing TTPs, and to help organizations understand the tactics and techniques that are commonly used by attackers.

The MITRE ATT\&CK framework is organized into different matrices, each of which covers a different stage of the attack lifecycle. The matrices include:

Initial access: This matrix covers the tactics and techniques that attackers use to gain initial access to a target system or network. Execution: This matrix covers the tactics and techniques that attackers use to execute their payloads or other tools once they have gained access to the target. Persistence: This matrix covers the tactics and techniques that attackers use to maintain access to the target and to persist on the system over time. Privilege escalation: This matrix covers the tactics and techniques that attackers use to gain increased privileges on the target system. Defense evasion: This matrix covers the tactics and techniques that attackers use to evade detection and to avoid being detected by security defenses. Overall, MITRE ATT\&CK is a valuable tool for organizations that want to understand the tactics and techniques that are commonly used by attackers. It can help organizations to better understand the threats they face, and to develop more effective strategies for detecting and defending against attacks.

[Mitre attack](https://attack.mitre.org/) goal is to track the tactic used in intrusions. Categorize them into the different stages of an intrusion.\
Mitre attack also tracks what tactics the different threat groups are utilizing. Allow you to map the different TTP an specific threat group is using, to your defends matrix. With the goal to identify if you have are missing visibility and detection in your network.\
To help working with the attack framework Mitre have developed tools to help you.

[MITRE ATT\&CK Navigator](https://mitre-attack.github.io/attack-navigator/) is a web tool for help you explore the ATT\&CK matrices.\
It used to visualize your organization defensive coverage.

[Attack flow](https://github.com/center-for-threat-informed-defense/attack-flow) help visualize the sequence of actions that an threat actor uses to achieve their objective. It uses the JSON format to define the flow of actions.\\