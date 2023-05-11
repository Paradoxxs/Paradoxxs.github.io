Firewalla Gold is already running Bro/Zeek on the device. To enhance your network security analysis capabilities, you can integrate RITA (Real Intelligence Threat Analytics) into your Firewalla Gold setup. RITA is an open-source framework designed to detect and analyze network intrusions by processing Bro/Zeek logs. In this blog post, we'll walk you through the steps to install MongoDB and RITA, and configure the system to import Bro/Zeek logs using a cron job.

## Get RITA

First, let's download the RITA source code and install it. To do this, run the following commands:

```Bash
git clone https://github.com/activecm/rita 
cd rita
sudo ./install.sh --disable-zeek --disable-mongo # This will only install RITA; Zeek is already on the device, and MongoDB will be installed using Docker
```

## Get and Install MongoDB as a Docker Container

Next, we need to set up MongoDB using a Docker container. To pull the MongoDB image and run it as a container, execute the following commands:

```Bash
sudo docker pull mongo:3.6 # Get Docker image
sudo docker run --name mongo -p 27017:27017 -v /data/mongodata:/data/db -d mongo:3.6 
```

With MongoDB up and running, RITA should now be connected to it.

## Import Bro/Zeek Logs Using Cron

The final step is to create a cron job that will import the log files into RITA every hour. This setup will ensure that your security analysis is updated regularly and that the logs are processed incrementally.

```Bash
crontab -e
# Add the following code to the cron file to import every hour
0 * * * * /usr/local/bin/rita import --rolling /log/blog/$(date --date='-1 hour' +\%Y-\%m-\%d)/ Firewalla_logs
```

Congratulations! You now have RITA running on your Firewalla Gold, significantly enhancing your network security analysis capabilities. With RITA's advanced threat detection and analysis features, you can gain better insights into potential security risks and respond to them more effectively.