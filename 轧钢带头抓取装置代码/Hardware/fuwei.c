#include "stm32f10x.h"                  // Device header
int boot_jump(u32 Map, u32 Reset)
{                
    __set_MSP(Map);
    ((void(*)())(Reset))();
	return 0;
}
 
void soft_reset_do(void)
{
    u32 addr = 0x08000000;//APP_ADDR0;
 
    u32 base = addr > NVIC_VectTab_FLASH ? NVIC_VectTab_FLASH:NVIC_VectTab_RAM;
    u32 offset = addr - base;
 
    NVIC_SetVectorTable(base, offset);
    
    u32 map = *((u32* )addr);
    u32 reset = *((u32*)(addr + 4));
    boot_jump(map,reset);

}
