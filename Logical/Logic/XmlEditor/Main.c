
#include <bur/plctypes.h>
#define TRUE	1
#define	FALSE	0
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{
	
	switch(CfgReadStep)
	{
		case Wait:
			if(Start)
			{
				CfgReadStep	= CopyCfg;
			}
			break;
		
		case CopyCfg:
			IOMMCopy.enable	=	TRUE;
			IOMMCopy.pModuleName	=	&BR_ModuleName;
			IOMMCopy.pNewModule		= 	&DataObjName;
			IOMMCopy.memType		= doTEMP;
			AsIOMMCopy(&IOMMCopy);
			if(IOMMCopy.status == ERR_OK)
			{
				CfgReadStep	= GetDatObjData;	
			}
			break;
		
		case GetDatObjData:
			DO_Info.enable	= TRUE;
			DO_Info.pName	= IOMMCopy.pNewModule;
			DatObjInfo(&DO_Info);
			if(DO_Info.status == ERR_OK)
			{
				CfgReadStep	= CreateMemReader;	
			}
			break;
		
		case CreateMemReader:
			CreateMemoryReader.enable	= TRUE;
			CreateMemoryReader.pXmlMemory	= DO_Info.pDatObjMem;
			CreateMemoryReader.memorySize	= DO_Info.len;
			xmlCreateMemoryReader(&CreateMemoryReader);
			if(CreateMemoryReader.status == ERR_OK)
			{
				CfgReadStep	= ReadXmlNode;	
				NodeNr = 0;
				ReadNextNode.enable	= TRUE;
			}
			break;
		
		case ReadXmlNode:
			ReadNextNode.ident	= CreateMemoryReader.ident;
			ReadNextNode.pName	= (UDINT) &XmlNode[NodeNr].NodeName;
			ReadNextNode.nameSize	= sizeof(XmlNode[NodeNr].NodeName);
			ReadNextNode.pValue		= (UDINT) &XmlNode[NodeNr].NodeValue;
			ReadNextNode.valueSize	= sizeof(XmlNode[NodeNr].NodeValue);
			xmlReadNextNode(&ReadNextNode);
			if(ReadNextNode.status == ERR_OK)
			{
				attrNr	= 0;
				ReadNextNode.enable	= FALSE;
				CfgReadStep	= ReadXmlNodeAttributes;	
			}
			else if(ReadNextNode.status == xmlERR_NO_FURTHER_XML_NODE)
			{
				CfgReadStep	= WriteXML;
			}
			
			break;
		
		case ReadXmlNodeAttributes:
			if(attrNr < ReadNextNode.attributeCount)
			{
				ReadAttributeNr.ident	= ReadNextNode.ident;
				ReadAttributeNr.enable	=	TRUE;
				ReadAttributeNr.index	= attrNr;
				ReadAttributeNr.pName	= (UDINT) &XmlNode[NodeNr].NodeAttr[attrNr].AttrName;
				ReadAttributeNr.nameSize	= sizeof(XmlNode[NodeNr].NodeAttr[attrNr].AttrName);
				ReadAttributeNr.pValue	= (UDINT) &XmlNode[NodeNr].NodeAttr[attrNr].AttrValue;
				ReadAttributeNr.valueSize	= sizeof(XmlNode[NodeNr].NodeAttr[attrNr].AttrValue);
				xmlReadAttributeNr(&ReadAttributeNr);
				if(ReadAttributeNr.status	==	ERR_OK)
				{
					attrNr++;
				}
				
			}
			else
			{
				NodeNr++;
				ReadNextNode.enable	= TRUE;
				CfgReadStep	= ReadXmlNode;
			}
			break;
		
		
		
		
		case WriteXML:
			switch (FW_Step)
			{
			
				case CREATE:
					fCreate.enable = TRUE;
					fCreate.pDevice = (UDINT) "root";
					fCreate.pFile = &FileName;
					FileCreate(&fCreate);
					if(fCreate.status == ERR_OK)
					{
						fIdent	= fCreate.ident;
						FW_Step	= WRITE;
					}
					else if(fCreate.status == fiERR_EXIST)
					{
						FW_Step	= OPEN;
					}
					break;
			
				case OPEN:
					fOpen.pDevice	=	(UDINT) "root";//= fCreate.pDevice;
					fOpen.pFile	= &FileName;//fCreate.pFile;
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
					fWrite.pSrc		= DO_Info.pDatObjMem;
					fWrite.len		= DO_Info.len;
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
						CfgReadStep	= DeleteDataObject;
					}
					break;

			}
		
		case DeleteDataObject:
			DO_Delete.enable	= TRUE;
			DO_Delete.ident		= DO_Info.ident;
			DatObjDelete(&DO_Delete);
			if(DO_Delete.status == ERR_OK)
			{
				CfgReadStep	= CloseMemReader;
			}
			break;
		
		case CloseMemReader:
			CloseMemoryReader.enable	= TRUE;
			CloseMemoryReader.ident		= CreateMemoryReader.ident;
			xmlCloseMemoryReader(&CloseMemoryReader);
			if(CloseMemoryReader.status == ERR_OK)
			{
				CfgReadStep	= Wait;
				Start	= FALSE;
			}
			break;
		
	}
	
}

void _EXIT ProgramExit(void)
{

}

