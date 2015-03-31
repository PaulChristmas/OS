# Created by PaulChristmas
# 15.03.15

DIRECTORIES=cat revwords filter bufcat

all: 
	@$(foreach ex, $(DIRECTORIES), $(MAKE) -C $(ex);)

clean:
	@$(foreach ex, $(DIRECTORIES), $(MAKE) -C $(ex) clean;)

