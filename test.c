//#ifdef EZCMD3_TEST

#include <stdio.h>
#include "ezcmd3.h"

char buff[512];

int main()
{
  struct ezcmd_context_s ctx;
  ezcmd_init(&ctx, buff, sizeof(buff));
  for (;;)
    {
      while (ezcmd_intake(&ctx, getchar()) == EZCMD_PARSING);
      printf("done\n\r");
      int argc = 0;
      char *args[32];
      enum ezcmd_status_e stat = ezcmd_get_args(&ctx, &argc, args, sizeof(*args));
      if (stat != EZCMD_OK)
        {
          printf("command error %d\n\r", stat);
          return stat;
        }
      for (size_t i = 0; i < argc; i++)
        {
          printf("Arg %d: [%s]\n\r", i, args[i]);
        }
    }

}

//#endif