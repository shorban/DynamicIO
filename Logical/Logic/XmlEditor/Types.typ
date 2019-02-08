
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
		Wait,
		CopyCfg,
		GetDatObjData,
		CreateMemReader,
		ReadXmlNode,
		ReadXmlNodeAttributes,
		DeleteDataObject,
		WriteXML,
		CloseMemReader
		);
	XmlNode_type : 	STRUCT 
		NodeName : STRING[80];
		NodeValue : STRING[80];
		NodeAttr : ARRAY[0..14]OF XmlNodeAttr_type;
	END_STRUCT;
	XmlNodeAttr_type : 	STRUCT 
		AttrName : STRING[80];
		AttrValue : STRING[80];
	END_STRUCT;
END_TYPE
