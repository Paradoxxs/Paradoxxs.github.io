---
layout: page
title: Radicalization Matrix
permalink: /radicalization/
---

<style>
/* Matrix Container */
.matrix-container {
    width: 100%;
    overflow-x: auto;
    margin: 20px 0;
    background: #fff;
    border: 1px solid #ddd;
}

/* Matrix Table */
.attack-matrix {
    width: 100%;
    border-collapse: collapse;
    font-size: 12px;
    min-width: 1200px;
}

/* Header Row - Tactics */
.attack-matrix thead th {
    background: #d62828;
    color: white;
    padding: 15px 10px;
    text-align: center;
    font-weight: bold;
    border: 1px solid #a71e1e;
    vertical-align: top;
    min-width: 150px;
    font-size: 13px;
}

/* Technique Cells */
.attack-matrix td {
    border: 1px solid #ddd;
    padding: 8px;
    vertical-align: top;
    background: #f8f9fa;
}

/* Technique Items */
.technique {
    background: white;
    border: 1px solid #0066cc;
    margin: 4px 0;
    padding: 8px;
    border-radius: 3px;
    cursor: pointer;
    transition: all 0.2s;
    font-size: 11px;
}

.technique:hover {
    background: #e6f2ff;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.technique-name {
    font-weight: bold;
    color: #0066cc;
    margin-bottom: 4px;
}

.technique-id {
    color: #666;
    font-size: 10px;
    margin-bottom: 4px;
}

.technique-description {
    color: #333;
    font-size: 10px;
    line-height: 1.4;
}

/* Modal for technique details */
.modal {
    display: none;
    position: fixed;
    z-index: 1000;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    overflow: auto;
    background-color: rgba(0,0,0,0.4);
}

.modal-content {
    background-color: #fefefe;
    margin: 5% auto;
    padding: 20px;
    border: 1px solid #888;
    width: 80%;
    max-width: 800px;
    border-radius: 5px;
}

.close {
    color: #aaa;
    float: right;
    font-size: 28px;
    font-weight: bold;
    cursor: pointer;
}

.close:hover,
.close:focus {
    color: #000;
}

/* Info Section */
.info-section {
    background: #f0f0f0;
    padding: 20px;
    margin: 20px 0;
    border-left: 4px solid #d62828;
}

.info-section h3 {
    margin-top: 0;
    color: #d62828;
}

.legend {
    background: #fff;
    padding: 15px;
    margin: 20px 0;
    border: 1px solid #ddd;
}

.legend-item {
    display: inline-block;
    margin-right: 20px;
    margin-bottom: 10px;
}

.legend-box {
    display: inline-block;
    width: 20px;
    height: 20px;
    margin-right: 5px;
    vertical-align: middle;
    border: 1px solid #333;
}
</style>

<div class="info-section">
    <h2>Radicalization Matrix - Psychology of Extremism</h2>
    <p>This matrix maps the psychological tactics and stages used in radicalization processes, including cult recruitment, online extremism, and ideological manipulation. Inspired by MITRE ATT&CK, this framework synthesizes research from:</p>
    <ul>
        <li><strong>McCauley & Moskalenko</strong> - Pyramid of Radicalization (Individual, Group, Mass levels)</li>
        <li><strong>Robert Jay Lifton</strong> - Eight Criteria for Thought Reform</li>
        <li><strong>Steven Hassan</strong> - BITE Model (Behavior, Information, Thought, Emotional control)</li>
        <li><strong>Online Extremism Research</strong> - Algorithmic radicalization and digital manipulation</li>
    </ul>
</div>

<div class="legend">
    <h4>How to Use This Matrix:</h4>
    <p>Each column represents a <strong>Tactic</strong> (stage or method of radicalization). Each cell contains <strong>Techniques</strong> (specific methods used). Click on any technique to see detailed information.</p>
</div>

<div class="matrix-container">
    <table class="attack-matrix">
        <thead>
            <tr>
                <th>Vulnerability<br>Exploitation</th>
                <th>Initial<br>Contact</th>
                <th>Engagement &<br>Love Bombing</th>
                <th>Indoctrination</th>
                <th>Information<br>Control</th>
                <th>Thought<br>Control</th>
                <th>Behavioral<br>Control</th>
                <th>Isolation</th>
                <th>Deep<br>Radicalization</th>
                <th>Mobilization</th>
                <th>Exit &<br>Recovery</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <!-- Vulnerability Exploitation -->
                <td>
                    <div class="technique" onclick="showModal('T001')">
                        <div class="technique-id">T001</div>
                        <div class="technique-name">Social Isolation</div>
                        <div class="technique-description">Target individuals disconnected from mainstream society</div>
                    </div>
                    <div class="technique" onclick="showModal('T002')">
                        <div class="technique-id">T002</div>
                        <div class="technique-name">Economic Hardship</div>
                        <div class="technique-description">Exploit financial struggles and resentment</div>
                    </div>
                    <div class="technique" onclick="showModal('T003')">
                        <div class="technique-id">T003</div>
                        <div class="technique-name">Identity Crisis</div>
                        <div class="technique-description">Target those searching for purpose and belonging</div>
                    </div>
                    <div class="technique" onclick="showModal('T004')">
                        <div class="technique-id">T004</div>
                        <div class="technique-name">Victimhood Narrative</div>
                        <div class="technique-description">Reinforce perception of being wronged by society</div>
                    </div>
                    <div class="technique" onclick="showModal('T005')">
                        <div class="technique-id">T005</div>
                        <div class="technique-name">Loss & Trauma</div>
                        <div class="technique-description">Exploit recent personal loss or rejection</div>
                    </div>
                </td>
                
                <!-- Initial Contact -->
                <td>
                    <div class="technique" onclick="showModal('T006')">
                        <div class="technique-id">T006</div>
                        <div class="technique-name">Algorithmic Exposure</div>
                        <div class="technique-description">YouTube/TikTok algorithms suggesting extreme content</div>
                    </div>
                    <div class="technique" onclick="showModal('T007')">
                        <div class="technique-id">T007</div>
                        <div class="technique-name">Online Communities</div>
                        <div class="technique-description">Forums, Discord, Telegram groups as entry points</div>
                    </div>
                    <div class="technique" onclick="showModal('T008')">
                        <div class="technique-id">T008</div>
                        <div class="technique-name">Charismatic Leadership</div>
                        <div class="technique-description">Influential figures providing answers</div>
                    </div>
                    <div class="technique" onclick="showModal('T009')">
                        <div class="technique-id">T009</div>
                        <div class="technique-name">Gatekeeper Content</div>
                        <div class="technique-description">Moderate content leading to extreme ideology</div>
                    </div>
                    <div class="technique" onclick="showModal('T010')">
                        <div class="technique-id">T010</div>
                        <div class="technique-name">Peer Recruitment</div>
                        <div class="technique-description">Friends/family already radicalized introduce target</div>
                    </div>
                </td>
                
                <!-- Engagement & Love Bombing -->
                <td>
                    <div class="technique" onclick="showModal('T011')">
                        <div class="technique-id">T011</div>
                        <div class="technique-name">Love Bombing</div>
                        <div class="technique-description">Overwhelming affection creating dependency</div>
                    </div>
                    <div class="technique" onclick="showModal('T012')">
                        <div class="technique-id">T012</div>
                        <div class="technique-name">Instant Belonging</div>
                        <div class="technique-description">Immediate acceptance into group</div>
                    </div>
                    <div class="technique" onclick="showModal('T013')">
                        <div class="technique-id">T013</div>
                        <div class="technique-name">Shared Enemy</div>
                        <div class="technique-description">Unite against common perceived threats</div>
                    </div>
                    <div class="technique" onclick="showModal('T014')">
                        <div class="technique-id">T014</div>
                        <div class="technique-name">Special Knowledge</div>
                        <div class="technique-description">Access to 'hidden truths' outsiders don't know</div>
                    </div>
                    <div class="technique" onclick="showModal('T015')">
                        <div class="technique-id">T015</div>
                        <div class="technique-name">Hero Narrative</div>
                        <div class="technique-description">Position as part of important mission</div>
                    </div>
                </td>
                
                <!-- Indoctrination -->
                <td>
                    <div class="technique" onclick="showModal('T016')">
                        <div class="technique-id">T016</div>
                        <div class="technique-name">Us vs Them</div>
                        <div class="technique-description">Binary worldview of allies vs enemies</div>
                    </div>
                    <div class="technique" onclick="showModal('T017')">
                        <div class="technique-id">T017</div>
                        <div class="technique-name">Dehumanization</div>
                        <div class="technique-description">Portray out-groups as less than human</div>
                    </div>
                    <div class="technique" onclick="showModal('T018')">
                        <div class="technique-id">T018</div>
                        <div class="technique-name">Conspiracy Theories</div>
                        <div class="technique-description">Complex theories explaining contradictions</div>
                    </div>
                    <div class="technique" onclick="showModal('T019')">
                        <div class="technique-id">T019</div>
                        <div class="technique-name">Pseudo-Science</div>
                        <div class="technique-description">Misuse of biology/psychology to justify beliefs</div>
                    </div>
                    <div class="technique" onclick="showModal('T020')">
                        <div class="technique-id">T020</div>
                        <div class="technique-name">Purity Spirals</div>
                        <div class="technique-description">Competition for most extreme commitment</div>
                    </div>
                    <div class="technique" onclick="showModal('T021')">
                        <div class="technique-id">T021</div>
                        <div class="technique-name">Historical Revisionism</div>
                        <div class="technique-description">Rewrite history to support narrative</div>
                    </div>
                </td>
                
                <!-- Information Control -->
                <td>
                    <div class="technique" onclick="showModal('T022')">
                        <div class="technique-id">T022</div>
                        <div class="technique-name">Milieu Control</div>
                        <div class="technique-description">Filter all information entering environment</div>
                    </div>
                    <div class="technique" onclick="showModal('T023')">
                        <div class="technique-id">T023</div>
                        <div class="technique-name">Echo Chambers</div>
                        <div class="technique-description">Only interact with like-minded individuals</div>
                    </div>
                    <div class="technique" onclick="showModal('T024')">
                        <div class="technique-id">T024</div>
                        <div class="technique-name">Mainstream Demonization</div>
                        <div class="technique-description">Portray outside sources as corrupt/lying</div>
                    </div>
                    <div class="technique" onclick="showModal('T025')">
                        <div class="technique-id">T025</div>
                        <div class="technique-name">Filter Bubbles</div>
                        <div class="technique-description">Algorithmic isolation from opposing views</div>
                    </div>
                    <div class="technique" onclick="showModal('T026')">
                        <div class="technique-id">T026</div>
                        <div class="technique-name">Selective Evidence</div>
                        <div class="technique-description">Cherry-pick data, ignore contradictions</div>
                    </div>
                </td>
                
                <!-- Thought Control -->
                <td>
                    <div class="technique" onclick="showModal('T027')">
                        <div class="technique-id">T027</div>
                        <div class="technique-name">Thought-Stopping Clichés</div>
                        <div class="technique-description">Simple phrases shutting down critical thinking</div>
                    </div>
                    <div class="technique" onclick="showModal('T028')">
                        <div class="technique-id">T028</div>
                        <div class="technique-name">Loaded Language</div>
                        <div class="technique-description">Specialized terminology shaping perception</div>
                    </div>
                    <div class="technique" onclick="showModal('T029')">
                        <div class="technique-id">T029</div>
                        <div class="technique-name">Sacred Science</div>
                        <div class="technique-description">Group possesses absolute truth</div>
                    </div>
                    <div class="technique" onclick="showModal('T030')">
                        <div class="technique-id">T030</div>
                        <div class="technique-name">Reality Distortion</div>
                        <div class="technique-description">Gaslighting about events and facts</div>
                    </div>
                    <div class="technique" onclick="showModal('T031')">
                        <div class="technique-id">T031</div>
                        <div class="technique-name">Doctrine Over Person</div>
                        <div class="technique-description">Ideology more important than experience</div>
                    </div>
                </td>
                
                <!-- Behavioral Control -->
                <td>
                    <div class="technique" onclick="showModal('T032')">
                        <div class="technique-id">T032</div>
                        <div class="technique-name">Social Pressure</div>
                        <div class="technique-description">Peer pressure enforcing group norms</div>
                    </div>
                    <div class="technique" onclick="showModal('T033')">
                        <div class="technique-id">T033</div>
                        <div class="technique-name">Public Commitment</div>
                        <div class="technique-description">Require public statements increasing dedication</div>
                    </div>
                    <div class="technique" onclick="showModal('T034')">
                        <div class="technique-id">T034</div>
                        <div class="technique-name">Incremental Escalation</div>
                        <div class="technique-description">Gradually increase extreme behaviors</div>
                    </div>
                    <div class="technique" onclick="showModal('T035')">
                        <div class="technique-id">T035</div>
                        <div class="technique-name">Guilt & Shame</div>
                        <div class="technique-description">Emotional manipulation for compliance</div>
                    </div>
                    <div class="technique" onclick="showModal('T036')">
                        <div class="technique-id">T036</div>
                        <div class="technique-name">Status Hierarchies</div>
                        <div class="technique-description">Ranks and rewards for deeper commitment</div>
                    </div>
                    <div class="technique" onclick="showModal('T037')">
                        <div class="technique-id">T037</div>
                        <div class="technique-name">Fear of Ostracism</div>
                        <div class="technique-description">Threaten exclusion for questioning</div>
                    </div>
                </td>
                
                <!-- Isolation -->
                <td>
                    <div class="technique" onclick="showModal('T038')">
                        <div class="technique-id">T038</div>
                        <div class="technique-name">Family Alienation</div>
                        <div class="technique-description">Cut ties with non-believing family</div>
                    </div>
                    <div class="technique" onclick="showModal('T039')">
                        <div class="technique-id">T039</div>
                        <div class="technique-name">Friend Replacement</div>
                        <div class="technique-description">Replace old networks with group members</div>
                    </div>
                    <div class="technique" onclick="showModal('T040')">
                        <div class="technique-id">T040</div>
                        <div class="technique-name">Time Monopolization</div>
                        <div class="technique-description">Consume all free time with activities</div>
                    </div>
                    <div class="technique" onclick="showModal('T041')">
                        <div class="technique-id">T041</div>
                        <div class="technique-name">Financial Dependence</div>
                        <div class="technique-description">Create economic ties making leaving hard</div>
                    </div>
                    <div class="technique" onclick="showModal('T042')">
                        <div class="technique-id">T042</div>
                        <div class="technique-name">Bridge Burning</div>
                        <div class="technique-description">Actions making return to normal life impossible</div>
                    </div>
                </td>
                
                <!-- Deep Radicalization -->
                <td>
                    <div class="technique" onclick="showModal('T043')">
                        <div class="technique-id">T043</div>
                        <div class="technique-name">Identity Fusion</div>
                        <div class="technique-description">Complete merge of personal and group identity</div>
                    </div>
                    <div class="technique" onclick="showModal('T044')">
                        <div class="technique-id">T044</div>
                        <div class="technique-name">Moral Disengagement</div>
                        <div class="technique-description">Justify harmful actions through ideology</div>
                    </div>
                    <div class="technique" onclick="showModal('T045')">
                        <div class="technique-id">T045</div>
                        <div class="technique-name">Martyrdom Glorification</div>
                        <div class="technique-description">Romanticize sacrifice for the cause</div>
                    </div>
                    <div class="technique" onclick="showModal('T046')">
                        <div class="technique-id">T046</div>
                        <div class="technique-name">Deindividuation</div>
                        <div class="technique-description">Loss of individual identity and awareness</div>
                    </div>
                    <div class="technique" onclick="showModal('T047')">
                        <div class="technique-id">T047</div>
                        <div class="technique-name">Mission Obsession</div>
                        <div class="technique-description">Single-minded focus on group's goals</div>
                    </div>
                </td>
                
                <!-- Mobilization -->
                <td>
                    <div class="technique" onclick="showModal('T048')">
                        <div class="technique-id">T048</div>
                        <div class="technique-name">Stochastic Terrorism</div>
                        <div class="technique-description">Rhetoric inspiring violence without orders</div>
                    </div>
                    <div class="technique" onclick="showModal('T049')">
                        <div class="technique-id">T049</div>
                        <div class="technique-name">Lone Wolf Activation</div>
                        <div class="technique-description">Individual attacks inspired by ideology</div>
                    </div>
                    <div class="technique" onclick="showModal('T050')">
                        <div class="technique-id">T050</div>
                        <div class="technique-name">Recruitment Activities</div>
                        <div class="technique-description">Active recruiting of new members</div>
                    </div>
                    <div class="technique" onclick="showModal('T051')">
                        <div class="technique-id">T051</div>
                        <div class="technique-name">Propaganda Creation</div>
                        <div class="technique-description">Produce content to spread ideology</div>
                    </div>
                    <div class="technique" onclick="showModal('T052')">
                        <div class="technique-id">T052</div>
                        <div class="technique-name">Meme Warfare</div>
                        <div class="technique-description">Spread ideology through viral content</div>
                    </div>
                </td>
                
                <!-- Exit & Recovery -->
                <td>
                    <div class="technique" onclick="showModal('T053')">
                        <div class="technique-id">T053</div>
                        <div class="technique-name">Cognitive Dissonance</div>
                        <div class="technique-description">Recognize contradictions in beliefs</div>
                    </div>
                    <div class="technique" onclick="showModal('T054')">
                        <div class="technique-id">T054</div>
                        <div class="technique-name">Professional Deradicalization</div>
                        <div class="technique-description">Therapy specialized in cult recovery</div>
                    </div>
                    <div class="technique" onclick="showModal('T055')">
                        <div class="technique-id">T055</div>
                        <div class="technique-name">Former Member Support</div>
                        <div class="technique-description">Connect with others who left</div>
                    </div>
                    <div class="technique" onclick="showModal('T056')">
                        <div class="technique-id">T056</div>
                        <div class="technique-name">Identity Reconstruction</div>
                        <div class="technique-description">Rebuild sense of self outside group</div>
                    </div>
                    <div class="technique" onclick="showModal('T057')">
                        <div class="technique-id">T057</div>
                        <div class="technique-name">Critical Thinking Skills</div>
                        <div class="technique-description">Teach evaluation and logical reasoning</div>
                    </div>
                    <div class="technique" onclick="showModal('T058')">
                        <div class="technique-id">T058</div>
                        <div class="technique-name">New Purpose Development</div>
                        <div class="technique-description">Find healthy alternatives for meaning</div>
                    </div>
                </td>
            </tr>
        </tbody>
    </table>
</div>

<!-- Modal for detailed technique information -->
<div id="techniqueModal" class="modal">
    <div class="modal-content">
        <span class="close" onclick="closeModal()">&times;</span>
        <h2 id="modalTitle"></h2>
        <div id="modalContent"></div>
    </div>
</div>

<div class="info-section">
    <h3>Academic References:</h3>
    <ul>
        <li>McCauley, C., & Moskalenko, S. (2011). <em>Friction: How Radicalization Happens to Them and Us</em></li>
        <li>Lifton, R. J. (1961). <em>Thought Reform and the Psychology of Totalism</em></li>
        <li>Hassan, S. (2018). <em>The Cult of Trump: A Leading Cult Expert Explains How the President Uses Mind Control</em></li>
        <li>Ribeiro, M. H., et al. (2020). "Auditing radicalization pathways on YouTube." <em>FAT* 2020</em></li>
    </ul>
</div>

<script>
// Technique details database
const techniqueDetails = {
    'T001': {
        name: 'Social Isolation',
        description: 'Targets individuals who feel disconnected from mainstream society, family, or friends. This vulnerability makes them more receptive to groups offering belonging.',
        examples: ['Recent move to new city', 'Social rejection', 'Online-only social life', 'Feeling misunderstood by peers'],
        mitigation: 'Build strong social networks, encourage diverse friendships, community engagement'
    },
    'T006': {
        name: 'Algorithmic Exposure',
        description: 'YouTube, TikTok, and other platform algorithms progressively recommend more extreme content, creating "rabbit holes" that lead users from moderate to radical content.',
        examples: ['YouTube autoplay to extreme videos', 'TikTok For You Page', 'Recommendation engines', 'Content rabbit holes'],
        mitigation: 'Media literacy education, diverse content consumption, algorithm awareness'
    },
    'T016': {
        name: 'Us vs Them',
        description: 'Creates a binary worldview where people are divided into allies and enemies, with no middle ground or nuance allowed.',
        examples: ['Red pill/blue pill framing', 'Awake vs sheep mentality', 'Based vs normie', 'Patriots vs traitors'],
        mitigation: 'Encourage nuanced thinking, expose to diverse perspectives'
    },
    'T027': {
        name: 'Thought-Stopping Clichés',
        description: 'Simple phrases that shut down critical thinking and questioning. When doubt arises, these clichés are used to stop reflection.',
        examples: ['"Trust the plan"', '"Do your own research"', '"You\'re overthinking it"', '"They want you to think that"'],
        mitigation: 'Recognize manipulation tactics, practice critical analysis'
    },
    'T043': {
        name: 'Identity Fusion',
        description: 'The complete merging of personal identity with group identity, where self-concept becomes inseparable from the group.',
        examples: ['Using "we" instead of "I"', 'Group symbols as personal identity', 'Cannot imagine life outside group'],
        mitigation: 'Maintain individual hobbies, diverse relationships, personal goals separate from group'
    }
    // Add more as needed
};

function showModal(techniqueId) {
    const modal = document.getElementById('techniqueModal');
    const details = techniqueDetails[techniqueId];
    
    if (details) {
        document.getElementById('modalTitle').innerHTML = techniqueId + ': ' + details.name;
        let content = '<p><strong>Description:</strong> ' + details.description + '</p>';
        if (details.examples) {
            content += '<p><strong>Examples:</strong></p><ul>';
            details.examples.forEach(ex => {
                content += '<li>' + ex + '</li>';
            });
            content += '</ul>';
        }
        if (details.mitigation) {
            content += '<p><strong>Prevention/Mitigation:</strong> ' + details.mitigation + '</p>';
        }
        document.getElementById('modalContent').innerHTML = content;
    } else {
        document.getElementById('modalTitle').innerHTML = techniqueId;
        document.getElementById('modalContent').innerHTML = '<p>Detailed information for this technique will be added soon.</p>';
    }
    
    modal.style.display = 'block';
}

function closeModal() {
    document.getElementById('techniqueModal').style.display = 'none';
}

// Close modal when clicking outside
window.onclick = function(event) {
    const modal = document.getElementById('techniqueModal');
    if (event.target == modal) {
        modal.style.display = 'none';
    }
}
</script>
