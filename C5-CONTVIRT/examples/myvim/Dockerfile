FROM debian:12
RUN apt update; apt install -y vim; apt clean
RUN apt update; apt install -y htop; apt clean
COPY ./toto /toto.txt
CMD ["vim", "/toto.txt"]
