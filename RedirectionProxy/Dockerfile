#---------------------------------------------------------------------
# DEVELOPMENT IMAGE
#---------------------------------------------------------------------
FROM ubuntu:focal

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get upgrade --yes && DEBIAN_FRONTEND=noninteractive apt-get install --yes \
    build-essential \
    psmisc \
    git \
    curl \
    vim \
    net-tools \
    python3 \
    python3-pip \
    tcpdump \
    iptables \
    iputils-ping 

RUN pip install requests
RUN pip install netifaces
RUN pip install pyinstaller

WORKDIR /usr/src/
#RUN mkdir rpSCP
#WORKDIR /root/rpSCP

# Add Redirection Proxy to the container
COPY ./RedirectionProxy.py /usr/src/
RUN pyinstaller --onefile RedirectionProxy.py 
WORKDIR /usr/src/dist

RUN adduser proxyop -u 1005 --gecos "proxy op, , , " --disabled-password
USER proxyop


# expose ports
EXPOSE 10096

#CMD [ "sleep", "infinity" ]
#ENTRYPOINT ["/bin/bash", "-c"]
ENTRYPOINT ["su", "proxyop", "-c"]
CMD ["./RedirectionProxy"]
