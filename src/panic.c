#include "vga.h"
#include "stdlib.h"


void setBackground(vga_terminal *pterm)
{
  uint32_t idx;
  uint16_t c;
  
  pterm->terminal_color = MAKE_COLOR(COLOR_WHITE, COLOR_BLUE);
  c = MAKE_VGAENTRY(' ', MAKE_COLOR(COLOR_BLUE, COLOR_BLUE));
  idx = ((VGA_HEIGHT + 1) * VGA_WIDTH);
  while (idx--)
    {
      pterm->terminal_buffer[idx] = c;
    }
}

void printTitle(vga_terminal *pterm)
{

  char title[] = "Kernel";
  int x = (VGA_WIDTH / 2) - (strlen(title + 1) / 2);
  int y = (VGA_HEIGHT / 4);
  vga_color color = MAKE_COLOR(COLOR_BLUE, COLOR_WHITE);

  pterm->terminal_column = x;
  pterm->terminal_row = y;
  
  printkc(color, 6);
  printk(color, title);
  printk(0, "\n");
}

void printMessage(vga_terminal *pterm, uint32_t uiNumber, char *pszError, uint32_t uiAddr)
{
  int x = (VGA_WIDTH / 7);

  pterm->terminal_column = x;
  printf("A fatal exception %i (%s) has occured at %p\n", uiNumber, pszError, uiAddr);
  pterm->terminal_column = x;
  printf("the current application will be terminated.\n\n");
  pterm->terminal_column = x;
  printf("* Press any key to terminate the current application.\n");
  pterm->terminal_column = x;
  printf("* Press CTRL+ALT+DEL to restart your computer.\n");
  pterm->terminal_column = x;
  printf("  You will lose all unsaved information in all applications.\n");
}

void printPressAnyKey(vga_terminal *pterm)
{
  int x = (VGA_WIDTH / 2) - (strlen("Press any key to continue") / 2);

  printf("\n");
  pterm->terminal_column = x;
  printf("Press any key to continue\n");
}

void     terminalBlueScreenOfDeath(uint32_t uiNumber, char *pszError, uint32_t uiAddr)
{
  vga_terminal	*pterm = get_terminal_instance();

  pterm->terminal_buffer = VGA_BUFFER_BASE_MODE;
  setBackground(pterm);
  printTitle(pterm);
  printMessage(pterm, uiNumber, pszError, uiAddr);
  printPressAnyKey(pterm);
}
