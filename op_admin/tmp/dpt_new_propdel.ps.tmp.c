#line 1 "/usr/riverbed/18.6/models/std/links/dpt_new_propdel.ps.c"
/* dpt_new_propdel.ps.c */
/* Default propagation delay model for pt-to-pt link Transceiver Pipeline */

/**********************************/
/*       Copyright (c) 2013       */
/*   Riverbed Technology, Inc.    */
/*      All Rights Reserved.      */
/**********************************/


#include "opnet.h"
#include <math.h>
#include "link_delay.h"

#define DISTANCE_BASED 1E+15


#if defined (__cplusplus)
   extern "C"
#endif
void dpt_new_propdel_mt(OP_SIM_CONTEXT_ARG_OPT_COMMA Packet* pkptr)
{
   Objid link_objid;
   double prop_delay;

   /** Compute propagation delay associated with a    **/
   /** packet transmission on a point-to-point link.  **/
#ifndef BIN
#define BIN
#endif
#ifndef BOUT
#define BOUT
#endif
#line 28
   FIN_MT(dpt_new_propdel(pkptr));

   /* Obtain object id of link carrying transmission. */
   link_objid = op_td_get_int(pkptr, OPC_TDA_PT_LINK_OBJID);

   /* Obtain propagation delay associated with that link. */
   if(op_ima_obj_attr_get(link_objid, "delay", &prop_delay) == OPC_COMPCODE_FAILURE)
      op_sim_end("Error in point-to-point propagation delay pipeline stage (dpt_propdel):", "Unable to get propagation delay from link attribute.",
                 OPC_NIL, OPC_NIL);

   if(prop_delay == DISTANCE_BASED)
   {BIN{
      prop_delay = link_delay(OP_SIM_CONTEXT_PTR_OPT_COMMA link_objid);
   }BOUT}

   /* Place propagation delay in packet transmission data attribute. */
   op_td_set_dbl(pkptr, OPC_TDA_PT_PROP_DELAY, prop_delay);

   FOUT
}

