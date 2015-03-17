# Created by PaulChristmas
# 15.03.15

DIRECTORIES=cat revwords

all: 
	@$(foreach ex, $(DIRECTORIES), $(MAKE) -C $(ex);)

clean:
	@$(foreach ex, $(DIRECTORIES), $(MAKE) -C $(ex) clean;)

