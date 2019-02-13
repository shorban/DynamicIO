
TYPE
	FileMgrStep_enum : 
		(
		CREATE,
		OPEN,
		WRITE,
		CLOSE
		);
	ReadCfg_enum : 
		(
		WAIT,
		READ_HW_CONFIG,
		COPY_CFG,
		GET_DATOBJ_INFO,
		CREATE_MEM_READER,
		READ_NEXT_NODE,
		READ_LN_ATTR,
		READ_PROD_ATTR,
		READ_CONS_ATTR,
		WRITE_XML,
		DELETE_DAT_OBJ,
		CLOSE_MEM_READER,
		ERROR
		);
	XmlNode_type : 	STRUCT 
		NodeName : STRING[80];
		NodeValue : STRING[80];
		NodeAttr : XmlNodeAttr_type;
	END_STRUCT;
	XmlNodeAttr_type : 	STRUCT 
		AttrName : STRING[80];
		AttrValue : STRING[80];
	END_STRUCT;
	LN_type : 	STRUCT 
		ID : STRING[80];
		Type : STRING[80];
		Prod : Prod_type;
		Cons : Cons_type;
	END_STRUCT;
	Cons_type : 	STRUCT 
		Device : STRING[80];
		DPName : STRING[80];
		Kind : STRING[10];
	END_STRUCT;
	Prod_type : 	STRUCT 
		Device : STRING[80];
		DPName : STRING[80];
		Kind : STRING[10];
	END_STRUCT;
END_TYPE
