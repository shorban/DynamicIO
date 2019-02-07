
#include <bur/plctypes.h>
#define TRUE	1
#define FALSE 	0


#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{
//	Тест опроса текущей конфигурации
	if(start)
	{
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
	}
}

void _EXIT ProgramExit(void)
{

}

