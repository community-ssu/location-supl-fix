location-supl-fix: location-supl-fix.c
	$(CC) -W -Wall -O2 $(CFLAGS) $(shell pkg-config --libs --cflags hildon-1 gconf-2.0) location-supl-fix.c -o location-supl-fix

clean:
	$(RM) location-supl-fix

install: location-supl-fix
	install -d $(DESTDIR)/etc/event.d/
	install -d $(DESTDIR)/usr/bin/
	install -m644 event.d $(DESTDIR)/etc/event.d/location-supl-fix
	install -m755 location-supl-fix $(DESTDIR)/usr/bin/
