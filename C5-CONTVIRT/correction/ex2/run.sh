docker run -ti -p 8080:80  -v $PWD/site/:/usr/share/nginx/html --mount type=bind,source=$PWD/default.conf,target=/etc/nginx/conf.d/default.conf  nginx
