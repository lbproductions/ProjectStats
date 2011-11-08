/*
	udpserver.c

	SOAP-over-UDP demo server with zlib compression and WS-Addressing

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapH.h"
#include "udp.nsmap"

#define MAX_HISTORY (1000)

char *received_id[MAX_HISTORY];
int last_received;
void init_received();
int check_received(const char *id);

int id_count = 1;

int main()
{ struct soap soap;
  init_received();
  soap_init1(&soap, SOAP_IO_UDP);
  if (!soap_valid_socket(soap_bind(&soap, NULL, 10000, 100)))
  { soap_print_fault(&soap, stderr);
    exit(1);
  }
  for (;;)
  { printf("Accepting requests...\n");
    if (soap_serve(&soap))
      soap_print_fault(&soap, stderr);
    soap_destroy(&soap);
    soap_end(&soap);
  }
  soap_done(&soap);
  return 0;
}

void init_received()
{ int i;
  for (i = 0; i < MAX_HISTORY; i++)
    received_id[i] = NULL;
  last_received = 0;
}

int check_received(const char *id)
{ int i;
  if (!id)
    return 1;
  /* Check if Message ID already received */
  for (i = 0; i < MAX_HISTORY; i++)
  { if (received_id[i] && !strcmp(id, received_id[i]))
      return 1;
  }
  if (received_id[last_received])
    free(received_id[last_received]);
  received_id[last_received++] = strdup(id);
  /* Wrap to overwrite old IDs */
  if (last_received >= MAX_HISTORY)
    last_received = 0;
  return 0;
}

int check_header(struct soap *soap)
{ /* MUST have received a SOAP Header */
  if (!soap->header)
    return soap_sender_fault(soap, "No SOAP header", NULL);
  /* ... with a Message ID */
  if (!soap->header->wsa__MessageID)
    return soap_sender_fault(soap, "No WS-Addressing MessageID", NULL);
  soap->header->wsa__RelatesTo = (struct wsa__Relationship*)soap_malloc(soap, sizeof(struct wsa__Relationship));
  soap_default_wsa__Relationship(soap, soap->header->wsa__RelatesTo);
  soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;
  return SOAP_OK;
}

int ns__echoString(struct soap *soap, char *str, char **res)
{ /* Get Header info and setup response Header */
  if (check_header(soap))
  { printf("Malformed header\n");
    return SOAP_FAULT; /* there was a problem */
  }

  /* If message with MessageID already received, ignore it */
  if (check_received(soap->header->wsa__MessageID))
  { printf("Request message %s already received\n", soap->header->wsa__MessageID);
    return SOAP_STOP;
  }

  printf("Request message %s accepted\n", soap->header->wsa__MessageID);

  /* Check ReplyTo has Address */
  if (!soap->header->wsa__ReplyTo || !soap->header->wsa__ReplyTo->Address)
    return soap_sender_fault(soap, "No WS-Addressing ReplyTo address", NULL);
  /* Copy Header info into response Header */
  soap->header->wsa__To = soap->header->wsa__ReplyTo->Address;

  /* Add info to response Header */
  soap->header->wsa__MessageID = soap_strdup(soap, soap_int2s(soap, id_count++));
  soap->header->wsa__Action = "http://genivia.com/udp/echoStringResponse";

  /* Copy request string into response string */
  printf("Response message %s returned\n", soap->header->wsa__MessageID);
  *res = str;

  return SOAP_OK;
}

int ns__sendString(struct soap *soap, char *str)
{ if (check_header(soap))
    printf("Malformed header\n");
  else if (check_received(soap->header->wsa__MessageID))
    printf("One-way message %s already received\n", soap->header->wsa__MessageID);
  else
    printf("One-way message %s accepted and serviced\n", soap->header->wsa__MessageID);
  return SOAP_OK;
}
