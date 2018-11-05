# 15693-TI-tag-it STANDARD
Chameleon mini rev G Texas Tag-it STANDARD

Tag-it standard functionality added and tested.
Two new files, TITagitstandard.h and TITagitstandard.c, were added to the exsisting iso 15693 codec and application files. 
A few changes to the firmare files are necessary to include tag-it standard functionality as explained below:

add the the following line to file /Chameleon-Mini/Application/application.h: 

#include "TITagitstandard.h"

add the following lines to file /Chameleon-Mini/configuration.h:

#ifdef CONFIG_TITAGITSTANDARD_SUPPORT
	CONFIG_TITAGITSTANDARD,
#endif

add the following to /Chameleon-Mini/configuration.c

#ifdef CONFIG_TITAGITSTANDARD_SUPPORT
	{ .Id = CONFIG_TITAGITSTANDARD,	.Text = "TITAGITSTANDARD" },
#endif

#ifdef CONFIG_TITAGITSTANDARD_SUPPORT
    [CONFIG_TITAGITSTANDARD] = {
    	.CodecInitFunc = ISO15693CodecInit,
    	.CodecDeInitFunc = ISO15693CodecDeInit,
		.CodecTaskFunc = ISO15693CodecTask,
		.ApplicationInitFunc = TITagitstandardAppInit,
		.ApplicationResetFunc = TITagitstandardAppReset,
		.ApplicationTaskFunc = TITagitstandardAppTask,
		.ApplicationTickFunc = TITagitstandardAppTick,
		.ApplicationProcessFunc = TITagitstandardAppProcess,
		.ApplicationGetUidFunc = TITagitstandardGetUid,
		.ApplicationSetUidFunc = TITagitstandardSetUid,
		.UidSize = ISO15693_GENERIC_UID_SIZE,
		.MemorySize = ISO15693_GENERIC_MEM_SIZE,
		.ReadOnly = false
    },
#endif

add the following line to /Chameleon-Mini/Makefile:

SRC         +=  Application/TITagitstandard.c
