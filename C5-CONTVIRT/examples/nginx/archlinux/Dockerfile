FROM archlinux

RUN pacman -Sy --noconfirm nginx

EXPOSE 80/tcp

CMD ["nginx", "-g", "daemon off;"]
