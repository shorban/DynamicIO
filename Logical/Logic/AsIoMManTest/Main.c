
#include <bur/plctypes.h>
#define	TRUE	1
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
			IOMMCopy.enable			= TRUE;
			IOMMCopy.pModuleName	= &BR_ModuleName;
			IOMMCopy.pNewModule		= &DataObjName;
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
				CfgReadStep	= WriteXML;	
			}
			break;
		
		case WriteXML:
			switch (FW_Step)
			{
			
				case CREATE:
					fCreate.enable	= TRUE;
					fCreate.pDevice = (UDINT) "root";
					fCreate.pFile 	= &FileName;
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
					fOpen.pDevice	= (UDINT) "root";//= fCreate.pDevice;
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
						Start		= FALSE;
						CfgReadStep	= Wait;
					}
					break;

			}
	}
}

void _EXIT ProgramExit(void)
{

}

