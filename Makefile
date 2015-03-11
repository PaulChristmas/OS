# Created by PaulChristmas
# 11.03.15

# Homework directories
DIRECTORIES=lib cat

all:
	for current in $(DIRECTORIES); do \
		$(MAKE) -C $$current; \
	done

clean:
	for current in $(DIRECTORIES); do \
		$(MAKE) -C $$current clean; \
	done	
