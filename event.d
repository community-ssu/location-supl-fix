author "Pali Rohár <pali.rohar@gmail.com>"
description "Fix A-GPS location supl server"
start on started hildon-desktop
exec su user -c "source /etc/osso-af-init/af-defines.sh; exec /usr/bin/location-supl-fix"
