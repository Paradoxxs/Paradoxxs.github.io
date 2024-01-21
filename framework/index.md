---
layout: page
title: Framework
permalink: /framework/
---

<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8"/>
    <link type="text/css" rel="stylesheet" href="css/arf.css"/>
    <script type="text/javascript" src="js/d3.v3.min.js"></script>
    <title>Forensics framework</title>
  </head>

  <body>
    <div id="body">
      <div id="header">
        Forensics framework
          <hr/>
      </div>
    </div>

    <script src="js/arf.js"></script>

    <div class="legend"><p></p></div>

    <button id="windows" onclick="updateview('window.json')">Windows</button>
    <button id="android" onclick="updateview('android.json')">Android</button>
    <button id="ios" onclick="updateview('ios.json')">IOS</button>
    <button id="mac" onclick="updateview('mac.json')">Mac</button>
    <button id="linux" onclick="updateview('linux.json')">Linux</button>
    <button id="network" onclick="updateview('network.json')">Network</button>
    <button id="osint" onclick="updateview('osint.json')">OSINT</button>
    <button id="darkweb" onclick="updateview('darkweb.json')">Darkweb</button>
    <button id="CTI" onclick="updateview('cti.json')">CTI</button>
    <button id="blockchain" onclick="updateview('blockchain.json')">Blockchain</button>
    <button id="cloud" onclick="updateview('cloud.json')">Cloud</button>
    <button id="malware" onclick="updateview('malware.json')">Malware</button>
    <button id="opsec" onclick="updateview('opsec.json')">Opsec</button>
    <h3>Notes</h3>
    Forensics framework focused on where to gather evidence.  The intention is to help people find locate critical evidence with easy.<br>
      
    <p>Inspired by the OSINT framework</p>

  </body>

</html>
