sudo echo "Going sudo!!!"

git pull
make

sudo cp -f mpd-update-queue /usr/bin/
sudo cp -f mpd-update-queue.* /etc/systemd/system/

sudo systemctl enable mpd-update-queue.timer
sudo systemctl start mpd-update-queue.timer
