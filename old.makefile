OBJDIR=build
AR=ar
CC=gcc
CPLUS=g++
OBJDIR=build
AR=ar
QUICKJS_PATH=/home/sxs/quickjs-master/quickjs-master
LIBUV_PATH=/home/sxs/libuv
TEST=test
TEMP=temp

build: clean mkdir $(OBJDIR)/libsjs.a

QJS_LIB_OBJS=$(OBJDIR)/jsapi.o $(OBJDIR)/util.o $(OBJDIR)/vm.o $(OBJDIR)/std.o $(OBJDIR)/network.o

$(OBJDIR)/libsjs.a: $(QUICKJS_PATH)/x86-build/libquickjs.a $(LIBUV_PATH)/x86-build/libuv_a.a $(OBJDIR)/libsrc.a
	ar crsT $@ $^

$(OBJDIR)/libsrc.a: $(QJS_LIB_OBJS)
	ar crs $@ $^

mkdir:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: ./src/%.c
	$(CC) -g -O0 -I $(QUICKJS_PATH) -I $(LIBUV_PATH)/include -I ./src -c -o $@ $<

clean:
	rm -rf $(OBJDIR)

test: $(TEST)/test

$(TEST)/test: $(TEST)/regist_jsapi.c $(TEST)/render/render.cpp $(TEST)/render/components/main.cpp $(TEST)/render/components/view.cpp $(OBJDIR)/libsjs.a
	$(CPLUS) -g -O0 -I $(QUICKJS_PATH) -I $(LIBUV_PATH)/include -I ./src -I $(TEST)/render -I $(TEST)/render/components -o $@ $^ -lm -ldl -lpthread