#include "ezcmd3.h"
#include <string.h>

void ezcmd_reset(struct ezcmd_context_s *ctx)
{
  ctx->curpos = 0;
  ctx->status = EZCMD_OK;
  memset(ctx->buff, 0, ctx->bufflen);
}

void ezcmd_init(struct ezcmd_context_s *ctx, char *buff, size_t len)
{
  memset(ctx, 0, sizeof(ctx));
  ctx->buff = buff;
  ctx->bufflen = len;
  ctx->status = EZCMD_OK;
}

enum ezcmd_status_e ezcmd_intake(struct ezcmd_context_s *ctx, char c)
{
  if (ctx->status != EZCMD_PARSING)
    {
      ezcmd_reset(ctx);
      ctx->status = EZCMD_PARSING;
    }

  if (ctx->curpos >= ctx->bufflen)
    {
      ctx->status = EZCMD_ERR_OVERFLOW;
      return EZCMD_ERR_OVERFLOW;
    }

  if (c == EZCMD3_TERMINATOR)
    {
      ctx->status = EZCMD_OK;
      return EZCMD_OK;
    }

  ctx->buff[ctx->curpos++] = c;
  ctx->status = EZCMD_PARSING;
  return EZCMD_PARSING;
}

enum ezcmd_status_e ezcmd_get_args(struct ezcmd_context_s *ctx, int *argc, char *args[], size_t arglen)
{
  if (ctx->status != EZCMD_OK) return ctx->status;

  if (arglen < 1)
    {
      ctx->status = EZCMD_ERR_ARG_OVERFLOW;
      return EZCMD_ERR_ARG_OVERFLOW;
    }

  /* Replace unquoted white spaces to null */

  char quote = 0;
  for (size_t i = 0; i < ctx->curpos; i++)
    {
      char c = ctx->buff[i];
      if (c == '\"')
        {
          quote = !quote;
          continue;
        }

      if (!quote && c == ' ')
        {
          ctx->buff[i] = '\0';
        }
    }

  /* Set arg pointers */

  (*argc) = 0;
  args[(*argc)++] = ctx->buff;

  for (size_t i = 0; i < ctx->curpos; i++)
    {
      char c = ctx->buff[i];
      if (c == '\0')
        {
          if ((*argc) >= arglen)
            {
              ctx->status = EZCMD_ERR_ARG_OVERFLOW;
              return EZCMD_ERR_ARG_OVERFLOW;
            }

          if (i+1 > ctx->curpos)
            {
              ctx->status = EZCMD_ERR_ARG_OVERFLOW;
              return EZCMD_ERR_ARG_OVERFLOW;
            }
          args[(*argc)++] = ctx->buff+i+1;
        }
    }

  ctx->status = EZCMD_OK;
  return EZCMD_OK;
}
