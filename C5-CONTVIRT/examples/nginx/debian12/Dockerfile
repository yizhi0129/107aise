FROM debian:12

RUN apt-get update && apt-get install nginx -y && apt-get clean

EXPOSE 80/tcp

CMD ["nginx", "-g", "daemon off;"]
