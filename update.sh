git pull
make
cp -f mpd-update-queue /usr/bin/
cp -f mpd-update-queue.* /etc/systemd/system/

sudo systemctl enable mpd-update-queue.timer