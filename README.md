# Mcop
 a huffman compressor/decompressor written in C
 
 ![alt text]( http://nsa33.casimages.com/img/2015/02/13/150213091934728223.png "mcop logo")
 
# How To Use

 using Mcop under Linux , please use : 

	$ make compil    #will compile Mcop

then execute :

	$ ./m-cop


| Compress file |

	$ ./m-cop -c <file>


| Decompress file |

	$ ./m-cop -d <file>

| Compress files in directory |

	$ ./m-cop -r --type <type of file (.txt)>


You can set --verbose mode for every action , just add --verbose at the end

	$ ./m-cop -c <file> --verbose
	
| GCC |

the Option <b>MCOP_REC</b> is set by default in gcc , so using ./m-cop -r is allowed
	
| Windows |

Just add the source code to VC and then Compile
