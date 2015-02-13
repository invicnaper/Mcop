#Make file for Mcop
OBJ=help

all: $(OBJ)

help:
	@echo  '**************************************'	
	@echo  '*  MCOP Building    *'
	@echo  '**************************************'
	@echo "make compil   		 #compil MCOP"

compil: compilmsg
compilmsg:
	@echo "using gcc .."
	gcc mcop/mcop.c mcop/compress.c mcop/tree.c mcop/util.c -o m-cop -lm -DMCOP_REC=true

