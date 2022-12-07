FROM ubuntu:latest
MAINTAINER User GB
RUN apt-get update
RUN apt-get install nginx -y
RUN apt-get install php-fpm -y
VOLUME "/var/www/html"
EXPOSE 80
CMD service nginx start; service php7.0-fpm start
