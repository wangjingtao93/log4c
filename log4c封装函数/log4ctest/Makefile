cc = gcc
prom = log4ctest
deps = $(shell find ./ -name "*.h" )
src = $(shell find ./ -name "*.c")
obj = $(src:%.c=%.o)
LIBPATH = /usr/local/lib/ 
LNAME = log4c

$(prom): $(obj)
	$(cc) -o $(prom) $(obj) -L$(LIBPATH) -l$(LNAME)

%.o: %.c $(deps)
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
