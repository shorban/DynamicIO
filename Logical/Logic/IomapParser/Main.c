
#include <bur/plctypes.h>
#define TRUE	1
#define	FALSE	0
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	Start		= FALSE;
	CfgReadStep	= WAIT;
}

void _CYCLIC ProgramCyclic(void)
{
	
	switch(CfgReadStep)
	{
		case WAIT:
			if(Start)
			{
				CfgReadStep	= COPY_CFG;
			}
			break;
		
		/*case READ_HW_CONFIG:
			if(GetInfo.ident == 0)	GetInfo.enable = TRUE;
		
			if(GetInfo.enable)
			{
				GetInfo.infoKind = CONFIGURED_MODULES;
				DiagCreateInfo(&GetInfo);
				Ident = GetInfo.ident;
				GetStrInfo.ident = Ident;
				GetStrInfo.enable = TRUE;
				GetStrInfo.infoCode = HW_MODULE_NAME;
			
				i = 0;
				if(GetInfo.status == 0)
				{
					GetInfo.enable = FALSE;
				}	
			}
			if(	i < ( GetInfo.nrEntries) )
			{
				GetStrInfo.index = i;
				GetStrInfo.bufferLen = sizeof(InfoDesc);
				GetStrInfo.pBuffer = &InfoDesc;
				DiagGetStrInfo(&GetStrInfo);
				strcpy(ConnectedModuleList[GetStrInfo.index],InfoDesc);
			
				if(i == ( GetInfo.nrEntries - 1))
				{
					GetStrInfo.enable = FALSE;
					start = FALSE;
				}
				if(GetStrInfo.status == 0) i++;
			}
			break;
		*/
		case COPY_CFG:
			IOMMCopy.enable			= TRUE;
			IOMMCopy.pModuleName	= (UDINT) "iomap";//&BR_ModuleName;
			IOMMCopy.pNewModule		= (UDINT) "temp";
			IOMMCopy.memType		= doTEMP;
			
			AsIOMMCopy(&IOMMCopy);
			
			if(IOMMCopy.status == ERR_OK)
			{
				CfgReadStep	= GET_DATOBJ_INFO;	
			}
			break;
		
		case GET_DATOBJ_INFO:
			DO_Info.enable	= TRUE;
			DO_Info.pName	= IOMMCopy.pNewModule;
			
			DatObjInfo(&DO_Info);
			
			if(DO_Info.status == ERR_OK)
			{
				CfgReadStep	= CREATE_MEM_READER;	
			}
			break;
		
		case CREATE_MEM_READER:
			CreateMemoryReader.enable		= TRUE;
			CreateMemoryReader.pXmlMemory	= DO_Info.pDatObjMem;
			CreateMemoryReader.memorySize	= DO_Info.len;
			
			xmlCreateMemoryReader(&CreateMemoryReader);
			
			if(CreateMemoryReader.status == ERR_OK)
			{
				CfgReadStep	= READ_NEXT_NODE;	

			}
			break;
		
		case READ_NEXT_NODE:
			ReadNextNode.ident		= CreateMemoryReader.ident;
			ReadNextNode.pName		= (UDINT) &XmlNode.NodeName;
			ReadNextNode.nameSize	= sizeof(XmlNode.NodeName);
			ReadNextNode.pValue		= (UDINT) &XmlNode.NodeValue;
			ReadNextNode.valueSize	= sizeof(XmlNode.NodeValue);
			
			xmlReadNextNode(&ReadNextNode);
			
			if(ReadNextNode.status == ERR_OK)
			{
				if( (strcmp(&XmlNode.NodeName,(UDINT) "LN") == 0 ) && ( ReadNextNode.attributeCount != 0 ) )
				{
					CfgReadStep	= READ_LN_ATTR;
				}
				else if( (strcmp(&XmlNode.NodeName,(UDINT) "Prod") == 0 ) && ( ReadNextNode.attributeCount != 0 ) )
				{
					CfgReadStep	= READ_PROD_ATTR;
				}
				else if( (strcmp(&XmlNode.NodeName,(UDINT) "Cons") == 0 ) && ( ReadNextNode.attributeCount != 0 ) )
				{
					CfgReadStep	= READ_CONS_ATTR;
				}
				else
				{
					CfgReadStep	= READ_NEXT_NODE;
				}
			}
			else if(ReadNextNode.status == xmlERR_NO_FURTHER_XML_NODE)
			{
				CfgReadStep	= DELETE_DAT_OBJ;
			}
			
			break;
		
		case READ_LN_ATTR:
			if(attrNr < ReadNextNode.attributeCount)
			{
				ReadAttributeNr.enable		= TRUE;
				ReadAttributeNr.ident		= ReadNextNode.ident;
				ReadAttributeNr.index		= attrNr;
				ReadAttributeNr.pName		= (UDINT) &XmlNode.NodeAttr.AttrName;
				ReadAttributeNr.nameSize	= sizeof(XmlNode.NodeAttr.AttrName);
				ReadAttributeNr.pValue		= (UDINT) &XmlNode.NodeAttr.AttrValue;
				ReadAttributeNr.valueSize	= sizeof(XmlNode.NodeAttr.AttrValue);
				
				xmlReadAttributeNr(&ReadAttributeNr);
				
				if(ReadAttributeNr.status	==	ERR_OK)
				{
					if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "ID") == 0 )
					{
						strcpy(LinkNode.ID,XmlNode.NodeAttr.AttrValue);
					}
					else if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "Type") == 0 )
					{
						strcpy(LinkNode.Type,XmlNode.NodeAttr.AttrValue);
					}
					
					attrNr++;
				}
				
			}
			else
			{
				attrNr		= 0;
				CfgReadStep	= READ_NEXT_NODE;
			}
			break;
		
		case READ_PROD_ATTR:
			if(attrNr < ReadNextNode.attributeCount)
			{
				ReadAttributeNr.enable		=	TRUE;
				ReadAttributeNr.ident		= ReadNextNode.ident;
				ReadAttributeNr.index		= attrNr;
				ReadAttributeNr.pName		= (UDINT) &XmlNode.NodeAttr.AttrName;
				ReadAttributeNr.nameSize	= sizeof(XmlNode.NodeAttr.AttrName);
				ReadAttributeNr.pValue		= (UDINT) &XmlNode.NodeAttr.AttrValue;
				ReadAttributeNr.valueSize	= sizeof(XmlNode.NodeAttr.AttrValue);
				
				xmlReadAttributeNr(&ReadAttributeNr);
				
				if(ReadAttributeNr.status	==	ERR_OK)
				{
					if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "Device") == 0 )
					{
						strcpy(LinkNode.Prod.Device,XmlNode.NodeAttr.AttrValue);
					}
					else if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "DPName") == 0 )
					{
						strcpy(LinkNode.Prod.DPName,XmlNode.NodeAttr.AttrValue);
					}
					else if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "Kind") == 0 )
					{
						strcpy(LinkNode.Prod.Kind,XmlNode.NodeAttr.AttrValue);
					}
					
					attrNr++;
				}
			}
			else
			{
				attrNr		= 0;
				CfgReadStep	= READ_NEXT_NODE;
			}
			break;
		
		case READ_CONS_ATTR:
			if( attrNr < ReadNextNode.attributeCount )
			{
				ReadAttributeNr.enable		= TRUE;
				ReadAttributeNr.ident		= ReadNextNode.ident;
				ReadAttributeNr.index		= attrNr;
				ReadAttributeNr.pName		= (UDINT) &XmlNode.NodeAttr.AttrName;
				ReadAttributeNr.nameSize	= sizeof(XmlNode.NodeAttr.AttrName);
				ReadAttributeNr.pValue		= (UDINT) &XmlNode.NodeAttr.AttrValue;
				ReadAttributeNr.valueSize	= sizeof(XmlNode.NodeAttr.AttrValue);
				
				xmlReadAttributeNr(&ReadAttributeNr);
			
				if(ReadAttributeNr.status	==	ERR_OK)
				{
					if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "Device") == 0 )
					{
						strcpy(LinkNode.Cons.Device,XmlNode.NodeAttr.AttrValue);
					}
					else if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "DPName") == 0 )
					{
						strcpy(LinkNode.Cons.DPName,XmlNode.NodeAttr.AttrValue);
					}
					else if( strcmp(&XmlNode.NodeAttr.AttrName,(UDINT) "Kind") == 0 )
					{
						strcpy(LinkNode.Cons.Kind,XmlNode.NodeAttr.AttrValue);
					}
					
					attrNr++;
				}
			}
			else
			{
				attrNr		= 0;
				CfgReadStep	= READ_NEXT_NODE;
			}
			break;
		
		
		
		
		case WRITE_XML:
			switch (FW_Step)
			{
			
				case CREATE:
					fCreate.enable	= TRUE;
					fCreate.pDevice	= (UDINT) "root";
					fCreate.pFile	= &FileName;
									
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
					fOpen.pFile		= &FileName;//fCreate.pFile;
					fOpen.mode		= FILE_RW;
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
						CfgReadStep	= DELETE_DAT_OBJ;
					}
					break;
			}
			break;
		
		case DELETE_DAT_OBJ:
			DO_Delete.enable	= TRUE;
			DO_Delete.ident		= DO_Info.ident;
						
			DatObjDelete(&DO_Delete);
						
			if(DO_Delete.status == ERR_OK)
			{
				CfgReadStep	= CLOSE_MEM_READER;
			}
			break;
		
		case CLOSE_MEM_READER:
			CloseMemoryReader.enable	= TRUE;
			CloseMemoryReader.ident		= CreateMemoryReader.ident;
						
			xmlCloseMemoryReader(&CloseMemoryReader);
						
			if(CloseMemoryReader.status == ERR_OK)
			{
				Start		= FALSE;
				CfgReadStep	= WAIT;
			}
			break;
		
		case ERROR:
			Start		= FALSE;
			CfgReadStep	= WAIT;
			break;
		
	}
	
}

void _EXIT ProgramExit(void)
{

}

