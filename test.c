//#ifdef EZCMD3_TEST

#include <stdio.h>
#include <string.h>
#include "ezcmd3.h"

char buff[512];

typedef int(*cmd_func_t)(char *args[], int argc);
struct cmd_entry_s
{
  char *name;
  cmd_func_t entry;
};

int a_command(char *args[], int argc)
{
  if (argc < 2)
    {
      printf("test expected 1 argument to be printed\n\r");
      return -1;
    }
  printf("HELLO %s\n\r", args[1]);
  return 0;
}

struct cmd_entry_s cmd_list[] =
{
  [0] = {"test", a_command}
};


int main()
{
  struct ezcmd_context_s ctx;
  int argc = 0;
  char *args[32];

  ezcmd_init(&ctx, buff, sizeof(buff));
  for (;;)
    {
      while (ezcmd_intake(&ctx, getchar()) == EZCMD_PARSING);

      enum ezcmd_status_e stat = ezcmd_get_args(&ctx, &argc, args, sizeof(args)/sizeof(args[0]));
      if (stat != EZCMD_OK)
        {
          printf("command error %d\n\r", stat);
          return stat;
        }

      for (size_t i = 0; i < argc; i++)
        printf("Arg %d: [%s]\n\r", i, args[i]);
    
      for (size_t i = 0; i < sizeof(cmd_list) / sizeof(cmd_list[0]); i++)
        {
          if (!strcmp(cmd_list[i].name, args[0]))
            return cmd_list[i].entry(args, argc);
        }
    }
}

//#endif