/*********************IMPORTANT DRAKVUF LICENSE TERMS***********************
 *                                                                         *
 * DRAKVUF Dynamic Malware Analysis System (C) 2014-2015 Tamas K Lengyel.  *
 * Tamas K Lengyel is hereinafter referred to as the author.               *
 * This program is free software; you may redistribute and/or modify it    *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE   *
 * CLARIFICATIONS AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your   *
 * right to use, modify, and redistribute this software under certain      *
 * conditions.  If you wish to embed DRAKVUF technology into proprietary   *
 * software, alternative licenses can be aquired from the author.          *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Reads or includes copyrighted data files.                             *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * DRAKVUF with other software in compressed or archival form does not     *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * DRAKVUF or grant special permissions to use it in other open source     *
 * software.  Please contact tamas.k.lengyel@gmail.com with any such       *
 * requests.  Similarly, we don't incorporate incompatible open source     *
 * software into Covered Software without special permission from the      *
 * copyright holders.                                                      *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * DRAKVUF in other works, are happy to help.  As mentioned above,         *
 * alternative license can be requested from the author to integrate       *
 * DRAKVUF into proprietary applications and appliances.  Please email     *
 * tamas.k.lengyel@gmail.com for further information.                      *
 *                                                                         *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes.          *
 *                                                                         *
 * Source code also allows you to port DRAKVUF to new platforms, fix bugs, *
 * and add new features.  You are highly encouraged to submit your changes *
 * on https://github.com/tklengyel/drakvuf, or by other methods.           *
 * By sending these changes, it is understood (unless you specify          *
 * otherwise) that you are offering unlimited, non-exclusive right to      *
 * reuse, modify, and relicense the code.  DRAKVUF will always be          *
 * available Open Source, but this is important because the inability to   *
 * relicense code has caused devastating problems for other Free Software  *
 * projects (such as KDE and NASM).                                        *
 * To specify special license conditions of your contributions, just say   *
 * so when you send them.                                                  *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the DRAKVUF   *
 * license file for more details (it's in a COPYING file included with     *
 * DRAKVUF, and also available from                                        *
 * https://github.com/tklengyel/drakvuf/COPYING)                           *
 *                                                                         *
 ***************************************************************************/

#ifndef STRUCTURES_H
#define STRUCTURES_H

/******************************************/

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <glib.h>
#include <libvmi/libvmi.h>
#include <libvmi/events.h>

#include "libdrakvuf.h"
#include "../xen_helper/xen_helper.h"

#ifdef DRAKVUF_DEBUG
#define PRINT_DEBUG(args...) \
    do { \
        fprintf (stderr, args); \
    } while (0)
#else
#define PRINT_DEBUG(args...) \
    do {} while(0)
#endif

static vmi_mem_access_t mem_conversion[] = {
    [MEMACCESS_R] = VMI_MEMACCESS_R,
    [MEMACCESS_W] = VMI_MEMACCESS_W,
    [MEMACCESS_X] = VMI_MEMACCESS_X,
    [MEMACCESS_RW] = VMI_MEMACCESS_RW,
    [MEMACCESS_RX] = VMI_MEMACCESS_RX,
    [MEMACCESS_RWX] = VMI_MEMACCESS_RWX
};

struct drakvuf {
    char *dom_name;
    domid_t domID;
    char *rekall_profile;

    xen_interface_t *xen;
    uint16_t altp2m_idx, altp2m_idr;

    xen_pfn_t zero_page_gfn;

    // VMI
    GMutex vmi_lock;
    vmi_instance_t vmi;

    vmi_event_t *step_event[16];

    // Processing trap removals in trap callbacks
    // is problematic so we save all such requests
    // in a list to be processed after all callbacks
    // are finished.
    bool in_callback;
    GHashTable *remove_traps;

    int interrupted;
    page_mode_t pm;
    unsigned int vcpus;
    unsigned int init_memsize;
    unsigned int memsize;

    GHashTable *remapped_gfns; // Key: gfn
                               // val: remapped gfn

    GHashTable *guards;  // Key: gfn
                         // val: vmi_event_t
    GHashTable *guards2; // Key: gfn
                         // val: vmi_event_t

    GHashTable *breakpoint_lookup_pa;   // key: PA of trap
                                        // val: struct breakpoint
    GHashTable *breakpoint_lookup_trap; // key: trap pointer
                                        // val: struct breakpoint

    GHashTable *memaccess_lookup_gfn;  // key: gfn of trap
                                       // val: struct memaccess
    GHashTable *memaccess_lookup_trap; // key: trap pointer
                                       // val: struct memaccess
};

struct breakpoint {
    addr_t pa;
    vmi_event_t *guard, *guard2;
} __attribute__ ((packed));

struct memaccess {
    addr_t gfn;
    addr_t pa;
    vmi_event_t *memtrap;
} __attribute__ ((packed));

struct wrapper {
    trap_type_t type;
    drakvuf_t drakvuf;
    GSList *traps; /* List of DRAKVUF traps registered for this event */
    union {
        struct memaccess memaccess;
        struct breakpoint breakpoint;
    };
} __attribute__ ((packed));

struct free_trap_wrapper {
    unsigned int counter;
    drakvuf_trap_t *trap;
    void (*free_routine)(drakvuf_trap_t *trap);
};

struct memcb_pass {
    drakvuf_t drakvuf;
    addr_t gfn;
};

struct remapped_gfn {
    xen_pfn_t o;
    xen_pfn_t r;
    bool active;
};

#endif
