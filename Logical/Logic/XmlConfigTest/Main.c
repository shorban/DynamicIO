
#include <bur/plctypes.h>
#define TRUE	1
#define FALSE	0
UDINT StringCombiner(STRING* pDest,STRING* pIoType, STRING* pSrc1, STRING* pSrc2)
{
	strcpy(pDest,pIoType);
	strcat(pDest,".");
	strcat(pDest,pSrc1);
	strcat(pDest,".");
	strcat(pDest,pSrc2);
	return pDest;
}
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	
	DigOut[1]	=	DigOut[1];
	DigOut[2]	=	DigOut[2];
	DigOut[3]	=	DigOut[3];
	DigOut[4]	=	DigOut[4];
	DigOut[5]	=	DigOut[5];
	DigOut[6]	=	DigOut[6];
	DigOut[7]	=	DigOut[7];
	DigOut[8]	=	DigOut[8];
	DigOut[9]	=	DigOut[9];
	DigOut[10]	=	DigOut[10];
	DigOut[11]	=	DigOut[11];
	DigOut[12]	=	DigOut[12];
	DigOut[13]	=	DigOut[13];
	DigOut[14]	=	DigOut[14];
	DigOut[15]	=	DigOut[15];
	
	Step	= Wait;
}

void _CYCLIC ProgramCyclic(void)
{
	switch(Step)
	{
		case Wait:
			if(Start)
			{
				strcpy(DOF322.ChanelName[0],"DigitalOutput01");
				strcpy(DOF322.ChanelName[1],"DigitalOutput02");
				strcpy(DOF322.ChanelName[2],"DigitalOutput03");
				strcpy(DOF322.ChanelName[3],"DigitalOutput04");
				strcpy(DOF322.ChanelName[4],"DigitalOutput05");
				strcpy(DOF322.ChanelName[5],"DigitalOutput06");
				strcpy(DOF322.ChanelName[6],"DigitalOutput07");
				strcpy(DOF322.ChanelName[7],"DigitalOutput08");
				strcpy(DOF322.ChanelName[8],"DigitalOutput09");
				strcpy(DOF322.ChanelName[9],"DigitalOutput10");
				strcpy(DOF322.ChanelName[10],"DigitalOutput11");
				strcpy(DOF322.ChanelName[11],"DigitalOutput12");
				strcpy(DOF322.ChanelName[12],"DigitalOutput13");
				strcpy(DOF322.ChanelName[13],"DigitalOutput14");
				strcpy(DOF322.ChanelName[14],"DigitalOutput15");
				strcpy(DOF322.ChanelName[15],"DigitalOutput16");
				
				strcpy(DOF322.ChanelVarName[0],"::DigOut[15]");
				strcpy(DOF322.ChanelVarName[1],"::DigOut[14]");
				strcpy(DOF322.ChanelVarName[2],"::DigOut[13]");
				strcpy(DOF322.ChanelVarName[3],"::DigOut[12]");
				strcpy(DOF322.ChanelVarName[4],"::DigOut[11]");
				strcpy(DOF322.ChanelVarName[5],"::DigOut[10]");
				strcpy(DOF322.ChanelVarName[6],"::DigOut[9]");
				strcpy(DOF322.ChanelVarName[7],"::DigOut[8]");
				strcpy(DOF322.ChanelVarName[8],"::DigOut[7]");
				strcpy(DOF322.ChanelVarName[9],"::DigOut[6]");
				strcpy(DOF322.ChanelVarName[10],"::DigOut[5]");
				strcpy(DOF322.ChanelVarName[11],"::DigOut[4]");
				strcpy(DOF322.ChanelVarName[12],"::DigOut[3]");
				strcpy(DOF322.ChanelVarName[13],"::DigOut[2]");
				strcpy(DOF322.ChanelVarName[14],"::DigOut[1]");
				strcpy(DOF322.ChanelVarName[15],"::DigOut[0]");
				
				strcpy(DOF322.ChanelType,"BOOL");
				strcpy(DOF322.ModulePath,"SL1.IF2.ST3");
				strcpy(DOF322.ModuleName,"SL1.IF2.ST3");
				Step	= CreateMem;
			}
			break;
		
		
		
		case CreateMem:
			CreateMemory.enable		= TRUE;
			xmlCreateMemoryWriter(&CreateMemory);
			if( CreateMemory.status == ERR_OK )
			{
				Ident	= CreateMemory.ident;
				Step	= WriteHeader;
			}
			break;
		
		case WriteHeader:
			WriteStartDocument.ident		= Ident;
			WriteStartDocument.enable		= TRUE;
		//	WriteStartDocument.pEncoding	= &XmlEnc;
			WriteStartDocument.pVersion		= (UDINT) "1.0";
			xmlWriteStartDocument(&WriteStartDocument);
			if(WriteStartDocument.status == ERR_OK)
			{
				Step	= WriteArV;
			}
			
			break;		
		case WriteArV:
			WritePI.ident	= Ident;
			WritePI.pTarget	= (UDINT) "AutomationRuntimeIOSystem";
			WritePI.pValue	= (UDINT) "Version=\"1.0\"";
			WritePI.enable	= TRUE;
			xmlWritePI(&WritePI);
			if(WritePI.status == ERR_OK)
			{
				Step	= WriteIO_Tag;
			}
			
			break;
		
		case WriteIO_Tag:
			WriteStartElement.ident		= Ident;
			WriteStartElement.pName		= (UDINT) "IO";
			WriteStartElement.enable	= TRUE;
			xmlWriteStartElement(&WriteStartElement);
			if(WriteStartElement.status == ERR_OK)
			{
				Step = WriteIO_TagAttr;
			}
			
			break;
		
		
		
		case WriteIO_TagAttr:
			WriteAttribute.ident	= Ident;
			WriteAttribute.pName	= (UDINT) "xmlns";
			WriteAttribute.pValue	= (UDINT) "http://www.br-automation.com/AR/IO";
			WriteAttribute.enable	= TRUE;
			xmlWriteAttribute(&WriteAttribute);
			if(WriteAttribute.status == ERR_OK)
			{
				Step	= WriteLinksTag;
			}
			break;
		
		
		case WriteLinksTag:
			WriteStartElement.ident		= Ident;
			WriteStartElement.pName		= (UDINT) "Links";
			WriteStartElement.enable	= TRUE;
			xmlWriteStartElement(&WriteStartElement);
			if(WriteStartElement.status == ERR_OK)
			{
				WriteStartElement.enable	= 0;
				Step = WriteLinkNodes;
				LN_Step	= WriteLN_Tag;
				i = 0;
			}
			
			break;
		
		case WriteLinkNodes:
			
			switch(LN_Step)
			{
				case WriteLN_Tag:
					WriteStartElement.ident		= Ident;
					WriteStartElement.pName		= (UDINT) "LN";
					WriteStartElement.enable	= TRUE;
					xmlWriteStartElement(&WriteStartElement);
					if(WriteStartElement.status == ERR_OK)
					{
						LN_Step = WriteLN_ID;
					}
			
					break;
				
				case WriteLN_ID:
				//STRING Buff[80];
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "ID";
					WriteAttribute.pValue	= (UDINT) StringCombiner(&Buff,"%QX",DOF322.ModulePath,DOF322.ChanelName[i]);/*"SL1.IF2.ST1.SL1.Input01"*/
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteLN_Type;
					}
					break;
			
				
				case WriteLN_Type:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "Type";
					WriteAttribute.pValue	= &DOF322.ChanelType; //(UDINT) "BOOL";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteProdTag;
					}
					break;
				
				case WriteProdTag:
					WriteStartElement.ident		= Ident;
					WriteStartElement.pName		= (UDINT) "Prod";
					WriteStartElement.enable	= TRUE;
					xmlWriteStartElement(&WriteStartElement);
					if(WriteStartElement.status == ERR_OK)
					{
						LN_Step = WriteProdDevice;
					}
			
					break;
				
				case WriteProdDevice:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "Device";
					WriteAttribute.pValue	= &DOF322.ModulePath; //(UDINT) "SL1.IF2.ST1.SL2";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						WriteAttribute.enable	= FALSE;
						LN_Step	= WriteProdDPName;
					}
					break;
				
				case WriteProdDPName:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "DPName";
					WriteAttribute.pValue	= &DOF322.ChanelName[i]; //(UDINT) "Input01";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteProdKind;
						WriteAttribute.enable	= FALSE;
					}
					break;
				
				case WriteProdKind:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "Kind";
					WriteAttribute.pValue	= (UDINT) "io";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						WriteAttribute.enable	= FALSE;
						LN_Step	= WriteProd_TagEnd;
					}
					break;
				case WriteProd_TagEnd:
					WriteEndElement.ident	= Ident;
					WriteEndElement.enable	= TRUE;
					xmlWriteEndElement(&WriteEndElement);
					if(WriteEndElement.status	== ERR_OK)
					{
						LN_Step	= WriteConsTag;
						WriteEndElement.enable	= FALSE;
						WriteStartElement.enable	= FALSE;
					}
					break;
			
				case WriteConsTag:
					WriteStartElement.ident		= Ident;
					WriteStartElement.pName		= (UDINT) "Cons";
					WriteStartElement.enable	= TRUE;
					xmlWriteStartElement(&WriteStartElement);
					if(WriteStartElement.status == ERR_OK)
					{
						LN_Step = WriteConsDevice;
					}
			
					break;
				
				case WriteConsDevice:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "Device";
					WriteAttribute.pValue	= (UDINT) "TC#1-CPYDEV";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteConsDPName;
					}
					break;
				
				case WriteConsDPName:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "DPName";
					WriteAttribute.pValue	= &DOF322.ChanelVarName[i];
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteConsKind;
					}
					break;
				
				case WriteConsKind:
					WriteAttribute.ident	= Ident;
					WriteAttribute.pName	= (UDINT) "Kind";
					WriteAttribute.pValue	= (UDINT) "pv";
					WriteAttribute.enable	= TRUE;
					xmlWriteAttribute(&WriteAttribute);
					if(WriteAttribute.status == ERR_OK)
					{
						LN_Step	= WriteCons_TagEnd;
					}
					break;
					
				case WriteCons_TagEnd:
					WriteEndElement.ident	= Ident;
					WriteEndElement.enable	= TRUE;
					xmlWriteEndElement(&WriteEndElement);
					if(WriteEndElement.status	== ERR_OK)
					{
						LN_Step	= WriteLN_TagEnd;
					}
					break;
			
				case WriteLN_TagEnd:
					WriteEndElement.ident	= Ident;
					WriteEndElement.enable	= TRUE;
					xmlWriteEndElement(&WriteEndElement);
					if(WriteEndElement.status	== ERR_OK)
					{
						i++;
						if(i<DOF322.ChanelNumber)
							{
							
								LN_Step	= WriteLN_Tag;
							
							}
							else
							{
								Step	= WriteLinksTagEnd;
							}
					}
					break;
				
				
			}
			break;
		
		
		case WriteLinksTagEnd:
			WriteEndElement.ident	= Ident;
			WriteEndElement.enable	= TRUE;
			xmlWriteEndElement(&WriteEndElement);
			if(WriteEndElement.status	== ERR_OK)
			{

				Step	= WriteIO_TagEnd;
			}
			break;
		
		
		case WriteIO_TagEnd:
			WriteEndElement.ident	= Ident;
			WriteEndElement.enable	= TRUE;
			xmlWriteEndElement(&WriteEndElement);
			if(WriteEndElement.status	== ERR_OK)
			{
				Step	= WriteEndDoc;
			}
			break;
		
		case WriteEndDoc:
			WriteEndDocument.ident	= Ident;
			WriteEndDocument.enable	= TRUE;
			xmlWriteEndDocument(&WriteEndDocument);
			if(WriteEndDocument.status	== ERR_OK)
			{
				Step	= GetMemPointer;
			}
			break;
		
		case GetMemPointer:
			GetMemoryInfo.ident		= Ident;
			GetMemoryInfo.enable	= TRUE;
			xmlGetMemoryInfo(&GetMemoryInfo);
			if(GetMemoryInfo.status	== ERR_OK)
			{
				Step	= WriteDataObj;
				FW_Step	= OPEN;
			}
			break;
		
		case WriteDataObj:
			DO_Create.enable	= TRUE;
			DO_Create.pName		= (UDINT)	"NewIomap";
			DO_Create.MemType	= doTEMP;
			DO_Create.pCpyData	= GetMemoryInfo.pXmlData;
			DO_Create.len		= GetMemoryInfo.xmlDataSize;
			DatObjCreate(&DO_Create);
			if(DO_Create.status == ERR_OK)
			{
				Step = CopyXML;
			}
			break;
				
		case CopyXML:
			//memcpy(&XmlData,GetMemoryInfo.pXmlData,GetMemoryInfo.xmlDataSize);
			switch (FW_Step)
			{
			/*
			case CREATE:
					fCreate.enable = TRUE;
					fCreate.pDevice = (UDINT) "root";
					fCreate.pFile = (UDINT) "test.xml";
					FileCreate(&fCreate);
					if(fCreate.status == ERR_OK)
					{
						fIdent	= fCreate.ident;
						step	= WRITE;
					}
					break;
			*/
			case OPEN:
					fOpen.pDevice	=	(UDINT) "root";//= fCreate.pDevice;
					fOpen.pFile	= (UDINT) "test.xml";//fCreate.pFile;
					fOpen.mode	= FILE_RW;
				fOpen.enable	= TRUE;
				FileOpen(&fOpen);
				if(fOpen.status == ERR_OK)
				{
					fIdent	= fOpen.ident;
					FW_Step	= WRITE;
				}
				break;
			
			case WRITE:
				fWrite.ident	= fIdent;
				fWrite.offset	= 0;
				fWrite.pSrc		= GetMemoryInfo.pXmlData;//DO_Create.pDatObjMem;
				fWrite.len		= GetMemoryInfo.xmlDataSize;//DO_Create.len;
				fWrite.enable	= TRUE;
				FileWrite(&fWrite);
				if(fWrite.status == ERR_OK)
				{
					FW_Step	= CLOSE;
				}
				break;
			
			case CLOSE:
				fClose.ident	= fIdent;
				fClose.enable	= TRUE;
				
				FileClose(&fClose);
				if(fClose.status == ERR_OK)
				{
					//Start	= FALSE;
					Step	= RemoveOldIomap;
				}
				break;

			}
			
			break;
		
		case RemoveOldIomap:
			IOMMRemove.enable	= TRUE;
			IOMMRemove.pModuleName = (UDINT) "iomap";
			AsIOMMRemove(&IOMMRemove);
			if(IOMMRemove.status == ERR_OK)
			{
				Step	= CreateNewIomap;
			}
			else if(IOMMRemove.status == iommERR_NOSUCH_MODULE)
			{
				Step	= CreateNewIomap;
			}
			break;
		
		case CreateNewIomap:
			IOMMCreate.enable	= TRUE;
			IOMMCreate.pDataObject	=  DO_Create.pName;
			IOMMCreate.memType		= doUSRROM;
			IOMMCreate.moduleKind	= iommMAPPING;
			IOMMCreate.pNewModule	= (UDINT) "iomap";
			AsIOMMCreate(&IOMMCreate);
			if(IOMMCreate.status == ERR_OK)
			{
				Step	= DeleteDatObj;//DeleteDatObj;
			}
			break;
		
		case DeleteDatObj:
			DO_Delete.enable	= TRUE;
			DO_Delete.ident		= DO_Create.ident;
			DatObjDelete(&DO_Delete);
			if(DO_Delete.status == ERR_OK)
			{
				Step	= WarmRestart;
			}
			break;
		
		case WarmRestart:	
			Start	= FALSE;
			Step	= Wait;
			break;
		
	}
}

void _EXIT ProgramExit(void)
{

}

