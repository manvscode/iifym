#
#  Copyright (C) 2016 by Joseph A. Marrero. http://www.joemarrero.com/
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.
#

#CFLAGS = -O0 -g -Wall -fsanitize=undefined -D_POSIX_C_SOURCE -I /usr/local/include -I extern/include/
CFLAGS = -std=c99 -O2 -Wall -fsanitize=undefined -D_POSIX_C_SOURCE -I /usr/local/include -I extern/include/ -I extern/include/xtd-1.0.0/ -I extern/include/collections-1.0.0/
LDFLAGS = extern/lib/libxtd.a extern/lib/libcollections.a -L /usr/local/lib -L extern/lib/ -lm
CWD = $(shell pwd)

# TDEE calculation tool.
TDEECALC_BIN = tdee_calc
TDEECALC_SOURCES = src/tdee_calc.c

# IIFYM tool.
#IIFYM_BIN = iifym
#IIFYM_SOURCES = src/iifym.c

all: extern/libxtd \
	 extern/libcollections \
	 bin/$(TDEECALC_BIN)

bin/$(TDEECALC_BIN): $(TDEECALC_SOURCES:.c=.o)
	@mkdir -p bin
	@echo "Linking: $^"
	@$(CC) $(CFLAGS) -o bin/$(TDEECALC_BIN) $^ $(LDFLAGS)
	@echo "Created $@"

bin/$(IIFYM_BIN): $(IIFYM_SOURCES:.c=.o)
	#@mkdir -p bin
	#@echo "Linking: $^"
	#@$(CC) $(CFLAGS) -o bin/$(IIFYM_BIN) $^ $(LDFLAGS)
	#@echo "Created $@"

src/%.o: src/%.c
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) -c $< -o $@

#################################################
# Dependencies                                  #
#################################################
extern/libxtd:
	@mkdir -p extern/libxtd/
	@git clone https://bitbucket.org/manvscode/libxtd.git extern/libxtd/
	@cd extern/libxtd && autoreconf -i && ./configure --libdir=$(CWD)/extern/lib/ --includedir=$(CWD)/extern/include/ && make && make install

extern/libcollections:
	@mkdir -p extern/libcollections/
	@git clone https://bitbucket.org/manvscode/libcollections.git extern/libcollections/
	@cd extern/libcollections && autoreconf -i && ./configure --libdir=$(CWD)/extern/lib/ --includedir=$(CWD)/extern/include/ && make && make install

#################################################
# Cleaning                                      #
#################################################
clean_extern:
	@rm -rf extern

clean:
	@rm -rf src/*.o
	@rm -rf bin
