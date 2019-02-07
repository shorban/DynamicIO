
TYPE
	ProgramStep_enum : 
		(
		Wait,
		WriteEndDoc,
		CreateMem,
		WriteArV,
		WriteHeader,
		WriteIO_Tag,
		WriteIO_TagAttr,
		WriteLinksTag,
		WriteLinkNodes,
		WriteLinksTagEnd,
		WriteIO_TagEnd,
		GetMemPointer,
		WriteDataObj,
		CopyXML,
		RemoveOldIomap,
		CreateNewIomap,
		DeleteDatObj,
		WarmRestart
		);
	FileMgrStep_enum : 
		(
		CREATE,
		OPEN,
		WRITE,
		CLOSE
		);
	WriteLNStep_enum : 
		(
		WriteLN_Tag,
		WriteLN_ID,
		WriteLN_Type,
		WriteProdTag,
		WriteProdDevice,
		WriteProdDPName,
		WriteProdKind,
		WriteProd_TagEnd,
		WriteConsTag,
		WriteConsDevice,
		WriteConsDPName,
		WriteConsKind,
		WriteCons_TagEnd,
		WriteLN_TagEnd
		);
	ModuleType : 	STRUCT 
		ModuleName : STRING[80];
		ModulePath : STRING[80];
		ModuleType : STRING[80];
		ChanelNumber : USINT;
		ChanelType : STRING[80];
		ChanelVarName : ARRAY[0..15]OF STRING[80];
		ChanelName : ARRAY[0..15]OF STRING[80];
	END_STRUCT;
END_TYPE
