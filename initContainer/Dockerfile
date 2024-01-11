#---------------------------------------------------------------------
# DEVELOPMENT IMAGE
#---------------------------------------------------------------------
FROM ubuntu:focal

RUN apt-get update &&  \
    apt-get install -y \
    build-essential \
    psmisc \
    net-tools \
    iputils-ping \
    iptables 

# Copy the initialization script into the container.
COPY init.sh /usr/local/bin/

# Mark the initialization script as executable.
RUN chmod +x /usr/local/bin/init.sh

# Start the initialization script on container startup.
ENTRYPOINT ["init.sh"]
