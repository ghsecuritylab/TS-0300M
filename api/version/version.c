/**
 *
 *	@name				version.c
 *	@author 			KT
 *	@date 				2019/08/01
 *	@brief				
 *  @include			version.h
 *
 *  @API					
 *
 *  @description   
 *
 **/
/*******************************************************************************
 * includes
 ******************************************************************************/
#include <stdio.h>  
#include <stdarg.h>  
#include <string.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PROJECT_VERSION			"v1.0"
#define FINAL_BUILD_TIME		__DATE__
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/
void GetCompileDateTime(char *cDate,char *cTime)
{        
        const int  MONTH_PER_YEAR=12;
        const char szEnglishMonth[MONTH_PER_YEAR][4]={ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        char szTmpDate[40]={0};
        char szTmpTime[20]={0};
        char szMonth[4]={0};
        int iYear,iMonth,iDay,iHour,iMin,iSec;//,,

        //获取编译日期、时间
        sprintf(szTmpDate,"%s",__DATE__); //"Sep 18 2010"
        sprintf(szTmpTime,"%s",__TIME__);    //"10:59:19"
        
        sscanf(szTmpDate,"%s %d %d",szMonth,&iDay,&iYear);
        sscanf(szTmpTime,"%d:%d:%d",&iHour,&iMin,&iSec);
                
        for(int i=0;MONTH_PER_YEAR;i++)
        {
			if(strncmp(szMonth,szEnglishMonth[i],3)==0)
			{
					iMonth=i+1;
					break;
			}
        }

//				printf("%d,%d,%d,%d,%d,%d ",iYear,iMonth,iDay,iHour,iMin,iSec);
        sprintf(cDate,"%04d%02d%02d",iYear,iMonth,iDay);
				sprintf(cTime,"%02d%02d%02d",iHour,iMin,iSec);
}