CC = gcc
CFLAGS = -Wall -I.

SRCDIR = .
PARSERDIR = parser
EVALUATORDIR = evaluator
OBJDIR = obj

PARSER_SRCS = $(wildcard $(PARSERDIR)/*.c)
PARSER_OBJS = $(patsubst $(PARSERDIR)/%.c,$(OBJDIR)/%.o,$(PARSER_SRCS))

EVALUATOR_SRCS = $(wildcard $(EVALUATORDIR)/*.c)
EVALUATOR_OBJS = $(patsubst $(EVALUATORDIR)/%.c,$(OBJDIR)/%.o,$(EVALUATOR_SRCS))

MAIN_SRC = $(SRCDIR)/main.c
MAIN_OBJ = $(OBJDIR)/main.o

TARGET = lisp_int

$(TARGET): $(PARSER_OBJS) $(EVALUATOR_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(PARSERDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(EVALUATORDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
