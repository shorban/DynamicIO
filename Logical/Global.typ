
TYPE
	Module_type : 	STRUCT 
		ModuleName : STRING[80];
		ModulePath : STRING[80];
		ChannelType : STRING[80] := 'BOOL';
		Channel : ARRAY[0..15]OF Channel_type;
		ModuleType : STRING[10] := '%QX';
	END_STRUCT;
	Channel_type : 	STRUCT 
		ChannelVar : STRING[80];
		ChannelName : STRING[80];
	END_STRUCT;
END_TYPE
