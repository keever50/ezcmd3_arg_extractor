#ifndef _EZCMD3_H
#define _EZCMD3_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EZCMD3_TERMINATOR '\n'

enum ezcmd_status_e
{
  EZCMD_OK,
  EZCMD_PARSING,
  EZCMD_ERR_OVERFLOW,
  EZCMD_ERR_ARG_OVERFLOW
};

struct ezcmd_context_s
{
  char *buff;
  size_t bufflen;
  size_t curpos;
  enum ezcmd_status_e status;
};

void ezcmd_init(struct ezcmd_context_s *ctx, char *buff, size_t len);
enum ezcmd_status_e ezcmd_intake(struct ezcmd_context_s *ctx, char c);
enum ezcmd_status_e ezcmd_get_args(struct ezcmd_context_s *ctx, int *argc, char *args[], size_t arglen);

#endif