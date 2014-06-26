
SOURCES = MAX31855.vhdl MAX31855_tb.vhdl
TEST_BENCH = MAX31855_tb.vhdl
ENTITY = MAX31855_tb
GHDL = "/cygdrive/c/Program Files (x86)/Ghdl/bin/ghdl.exe"
STOP_TIME = 100000ns

build:
	$(GHDL) -a --workdir=Work --std=93c $(SOURCES) $(TEST_BENCH)
	$(GHDL) -e --workdir=Work --std=93c $(ENTITY)

run: build
	$(GHDL) -r --workdir=Work $(ENTITY) --stop-time=$(STOP_TIME) --vcd=$(TEST_BENCH:.vhdl=.vcd)
	..\bin\gtkwave $(TEST_BENCH:.vhdl=.vcd) $(ENTITY).traces