#----------------------------------------#
#-- Makefile for Module Driver         --#
#-- Created by Nhi Van Pham @ 2018     --#
#----------------------------------------#

MODULES =  $(subst /,,$(dir $(wildcard */src)))

LIBS	:= $(addprefix libs/lib,$(addsuffix .a,$(MODULES)))
DRVLIBPATH    = $(CURDIR)\libs

export DRVLIBPATH

all: credir $(LIBS)

credir:
	@if NOT EXIST libs (mkdir libs)

$(LIBS) :
	$(MAKE) -C $(subst lib,,$(subst .a,,$(notdir $@)))

.PHONY: all $(LIBS)
