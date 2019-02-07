
TYPE
	Module_typ : 	STRUCT 
		ModuleName : STRING[80];
		ModulePath : STRING[80];
		ChanelVariable : ARRAY[0..15]OF STRING[80];
		ModuleType : UDINT;
		ModuleLinkList : STRING[800];
	END_STRUCT;
END_TYPE
